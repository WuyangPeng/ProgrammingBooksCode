#include "Max.h"
#include "Stdmat.h"

#include "../../../lib/Fly3D.h"

#include "resource.h"

#define IMPFLYBSP_CLASS_ID	Class_ID(0x3a9289d2, 0x82f062be)

ClassDesc* GetimpflybspDesc();

int controlsInit = FALSE;
HINSTANCE hInstance;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved)
{
	hInstance = hinstDLL;				// Hang on to this DLL's instance handle.

	if (!controlsInit) {
		controlsInit = TRUE;
		InitCustomControls(hInstance);	// Initialize MAX's custom controls
		InitCommonControls();			// Initialize Win95 controls
	}
			
	return (TRUE);
}

TCHAR *GetString(int id)
{
	static TCHAR buf[256];

	if (hInstance)
		return LoadString(hInstance, id, buf, sizeof(buf)) ? buf : NULL;
	return NULL;
}

__declspec( dllexport ) const TCHAR* LibDescription()
{
	return GetString(IDS_LIBDESCRIPTION);
}

__declspec( dllexport ) int LibNumberClasses()
{
	return 1;
}

__declspec( dllexport ) ClassDesc* LibClassDesc(int i)
{
	switch(i) {
		case 0: return GetimpflybspDesc();
		default: return 0;
	}
}

__declspec( dllexport ) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

class impflybsp : public SceneImport, public flyEngine {
	public:

	int *vertflag;

	//Constructor/Destructor
	impflybsp();
	~impflybsp();

	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
	int				DoImport(const TCHAR *name,ImpInterface *i,Interface *gi, BOOL suppressPrompts=FALSE);	// Import file
	void			build_mesh(TriObject *obj,int flag);
	void			select_bsp_faces(bsp_node *n);
};

class impflybspClassDesc:public ClassDesc {
	public:
	int 			IsPublic() {return 1;}
	void *			Create(BOOL loading = FALSE) {return new impflybsp();}
	const TCHAR *	ClassName() {return GetString(IDS_CLASS_NAME);}
	SClass_ID		SuperClassID() {return SCENE_IMPORT_CLASS_ID;}
	Class_ID		ClassID() {return IMPFLYBSP_CLASS_ID;}
	const TCHAR* 	Category() {return GetString(IDS_CATEGORY);}
	void			ResetClassParams (BOOL fileReset);
};

static impflybspClassDesc impflybspDesc;
ClassDesc* GetimpflybspDesc() {return &impflybspDesc;}

void impflybspClassDesc::ResetClassParams (BOOL fileReset) 
{
}

impflybsp::impflybsp()
{

}

impflybsp::~impflybsp() 
{

}

int impflybsp::ExtCount()
{
	return 1;
}

const TCHAR *impflybsp::Ext(int n)
{
	return _T("BSP");
}

const TCHAR *impflybsp::LongDesc()
{
	return _T("Fly3D BSP File");
}
	
const TCHAR *impflybsp::ShortDesc() 
{
	return _T("Fly3D BSP");
}

const TCHAR *impflybsp::AuthorName()
{
	return _T("Paralelo Computação Ltda.");
}

const TCHAR *impflybsp::CopyrightMessage() 
{
	return _T("");
}

const TCHAR *impflybsp::OtherMessage1() 
{
	return _T("");
}

const TCHAR *impflybsp::OtherMessage2() 
{
	return _T("");
}

unsigned int impflybsp::Version()
{
	return 100;
}

void impflybsp::ShowAbout(HWND hWnd)
{
}

void impflybsp::select_bsp_faces(bsp_node *n)
{
	if(n->child[0])
		select_bsp_faces(n->child[0]);

	if(n->child[1])
		select_bsp_faces(n->child[1]);

	if(n->elem)
	{
		static_mesh *o=(static_mesh *)n->elem;

		for(int i=0;i<o->objmesh->nf;i++)
		{
			o->objmesh->faces[i]->indx=1;
			vertflag[o->objmesh->faces[i]->vert[0]-vert]=1;
			vertflag[o->objmesh->faces[i]->vert[1]-vert]=1;
			vertflag[o->objmesh->faces[i]->vert[2]-vert]=1;
		}
	}
}


void impflybsp::build_mesh(TriObject *obj, int flag)
{
	int i, i0, j, nf, nv;

	for(i=0; i<nfaces;i++ )
		faces[i].indx=0;

	for(i=0; i<nvert;i++ )
		vertflag[i]=0;

	select_bsp_faces(bsp);

	nf=0;
	for(i=0; i<nfaces;i++ )
		if(faces[i].indx==flag) nf++;

	nv=0;
	for(i=0; i<nvert;i++ )
		if(vertflag[i]==flag) nv++;

	obj->mesh.setNumFaces(nf);
	obj->mesh.setNumVerts(nv);
	obj->mesh.setNumTVFaces(nf);
	obj->mesh.setNumTVerts(nf*3);

	i0=0;
	for( i=0;i<nvert;i++ )
	if(vertflag[i]==flag)
	{
		obj->mesh.setVert(i0,vert[i].x,vert[i].y,vert[i].z);
		vertflag[i]=i0;
		i0++;
	}

	i0=0;
	for( i=0;i<nfaces;i++ )
	if(faces[i].indx==flag)
	{
	for( j=0;j<3;j++ )
		{
		obj->mesh.tVerts[i0*3+j].x=faces[i].uv[j][0];
		obj->mesh.tVerts[i0*3+j].y=-faces[i].uv[j][1];
		obj->mesh.tVerts[i0*3+j].z=0;
		obj->mesh.faces[i0].v[j]=vertflag[faces[i].vert[j]-vert];
		obj->mesh.tvFace[i0].t[j]=i0*3+j;
		}
	obj->mesh.faces[i0].flags=EDGE_ALL;
	obj->mesh.faces[i0].smGroup=0;
	obj->mesh.faces[i0].setMatID(faces[i].texpic+1);
	i0++;
	}
}

int impflybsp::DoImport(const TCHAR *filename,ImpInterface *i,
						Interface *gi, BOOL suppressPrompts)
{
	char file[256],str[256],flypathname[256];
	strcpy(flypathname,filename);
	*(strrchr(flypathname,'\\')+1)=0;
	strcpy(file,strrchr(filename,'\\')+1);
	*strchr(file,'.')=0;

	strcpy(str,flypathname);
	strcat(str,file);
	strcat(str,".bsp");

	load_bsp(str);

	strcpy(str,flypathname);
	strcat(str,file);
	strcat(str,".tex");

	load_pictures(str);

	vertflag=new int[nvert];

	ImpNode *node=i->CreateNode();
	node->SetName(_T("flybsp"));

	TriObject *obj=(TriObject *)i->Create(GEOMOBJECT_CLASS_ID,Class_ID(TRIOBJ_CLASS_ID,0));
	node->Reference(obj);

	build_mesh(obj,1);

	MultiMtl *mm=(MultiMtl *)i->Create(MATERIAL_CLASS_ID,Class_ID(MULTI_CLASS_ID,0));
	mm->SetName(TSTR(_T("flybsp1")));
	mm->SetNumSubMtls(npiclib+1);
	int a,b=1;
	for( a=1;a<=npiclib;a++ )
	{
		StdMat *mat=(StdMat *)i->Create(MATERIAL_CLASS_ID,Class_ID(DMTL_CLASS_ID, 0));
		mat->SetAmbient(Color(0.2f,0.2f,0.2f),0);
		mat->SetDiffuse(Color(1.0f,1.0f,1.0f),0);
		mat->SetSpecular(Color(1.0f,1.0f,1.0f),0);
		mat->SetShininess(0,0);
		mat->SetShinStr(0,0);
		mat->SetTwoSided(FALSE);
		mat->SetTexmapAmt(ID_DI,1,0);
		mat->EnableMap(ID_DI,TRUE);
		sprintf(str,"flybspmat%02i",b++);
		mat->SetName(TSTR(_T(str)));
		if (piclib[a-1] && piclib[a-1]->name[0])
			{
			BitmapTex *tex1=(BitmapTex *)i->Create(TEXMAP_CLASS_ID,Class_ID(BMTEX_CLASS_ID,0));
			tex1->SetMapName(piclib[a-1]->name);
			mat->SetSubTexmap(ID_DI, tex1);
			}
		mm->SetSubMtl(a,mat);
	}
	node->GetINode()->SetMtl(mm);
	i->AddNodeToScene(node);

	for( a=0;a<nfaces;a++ )
		if (faces[a].indx==0)
			break;
	if (a<nfaces)
		{
		node=i->CreateNode();
		node->SetName(_T("flybsp2"));
		
		obj=(TriObject *)i->Create(GEOMOBJECT_CLASS_ID,Class_ID(TRIOBJ_CLASS_ID,0));
		node->Reference(obj);

		build_mesh(obj,0);
		
		node->GetINode()->SetMtl(mm);
		i->AddNodeToScene(node);
		}

	delete vertflag;

	i->RedrawViews();

	return TRUE;
}
	
