#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "iparamm.h"
#include "flyfao.h"

HINSTANCE hInstance;
int controlsInit = FALSE;

TCHAR *GetString(int id);

extern HINSTANCE hInstance;

IObjParam *Flyfao::ip			= NULL;
IParamMap *Flyfao::pmapParam	= NULL;

class FlyfaoClassDesc:public ClassDesc {
	public:
	int 			IsPublic() {return 1;}
	void *			Create(BOOL loading = FALSE) {return new Flyfao();}
	const TCHAR *	ClassName() {return GetString(IDS_CLASS_NAME);}
	SClass_ID		SuperClassID() {return GEOMOBJECT_CLASS_ID;}
	Class_ID		ClassID() {return FLYFAO_CLASS_ID;}
	const TCHAR* 	Category() {return GetString(IDS_CATEGORY);}
	void			ResetClassParams (BOOL fileReset);
};

class flyfaoDlg : public ParamMapUserDlgProc {
	public:
		Flyfao *ff;
		BOOL DlgProc(TimeValue t,IParamMap *map,HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
		void DeleteThis() {}
	};

class PickControlNode : 
		public PickModeCallback,
		public PickNodeCallback {
	public:				
		Flyfao *ff;
		INode *node;

		PickControlNode() { ff=NULL; node=NULL; }
		BOOL HitTest(IObjParam *ip,HWND hWnd,ViewExp *vpt,IPoint2 m,int flags);		
		BOOL Pick(IObjParam *ip,ViewExp *vpt);		
		void EnterMode(IObjParam *ip);
		void ExitMode(IObjParam *ip);		
		BOOL Filter(INode *node);
		PickNodeCallback *GetFilter() { return this; }
		BOOL RightClick(IObjParam *ip,ViewExp *vpt) { return TRUE; }
	};

class FlyfaoCreateCallBack : public CreateMouseCallBack {
	IPoint2 sp0;
	Flyfao *ob;
	Point3 p0;
public:	
	int proc( ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat);
	void SetObj(Flyfao *obj) {ob = obj;}
};

static flyfaoDlg flyfaodlg;
static FlyfaoClassDesc FlyfaoDesc;
static PickControlNode thePickMode;
static FlyfaoCreateCallBack FlyfaoCreateCB;

ClassDesc* GetFlyfaoDesc() { return &FlyfaoDesc; }

#define PB_KEY	0

static ParamUIDesc descParam[] = {
	ParamUIDesc(
		PB_KEY,
		EDITTYPE_INT,
		IDC_KEY,IDC_KEY_SPIN,
		0,256,
		1),	
	}; 	

#define PARAMDESC_LENGTH 1

static ParamBlockDescID descVer1[] = {
	{ TYPE_INT, NULL, TRUE, 0 },
	};

#define CURRENT_DESCRIPTOR descVer1

#define PBLOCK_LENGTH	1

#define CURRENT_VERSION	1

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved)
{
	hInstance = hinstDLL;

	if (!controlsInit) {
		controlsInit = TRUE;
		InitCustomControls(hInstance);
		InitCommonControls();
	}
			
	return (TRUE);
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
		case 0: return GetFlyfaoDesc();
		default: return 0;
	}
}

__declspec( dllexport ) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

TCHAR *GetString(int id)
{
	static TCHAR buf[256];
	if (hInstance)
		return LoadString(hInstance, id, buf, sizeof(buf)) ? buf : NULL;
	return NULL;
}

void FlyfaoClassDesc::ResetClassParams (BOOL fileReset) 
{
}

BOOL PickControlNode::Filter(INode *node)
	{
	node->BeginDependencyTest();
	ff->NotifyDependents(FOREVER,0,REFMSG_TEST_DEPENDENCY);
	if (node->EndDependencyTest()) 
		return FALSE;
	else return TRUE;
	}

BOOL PickControlNode::HitTest(
		IObjParam *ip,HWND hWnd,ViewExp *vpt,IPoint2 m,int flags)
	{	
	if (ip->PickNode(hWnd,m,this)) 
		return TRUE;
	else return FALSE;
	}

BOOL PickControlNode::Pick(IObjParam *ip,ViewExp *vpt)
	{
	node = vpt->GetClosestHit();
	if (node) 
		{

		}
	return TRUE;
	}

void PickControlNode::EnterMode(IObjParam *ip)
	{
	node=0;
	}

void PickControlNode::ExitMode(IObjParam *ip)
	{
	if (node)
		{
		Object *obj = node->EvalWorldState(ip->GetTime()).obj;
		if(obj->CanConvertToType(triObjectClassID))
			{
			char *name=node->GetName();
			Mesh *mesh=&((TriObject *)obj->ConvertToType(ip->GetTime(),triObjectClassID))->mesh;
			Matrix3 piv(1);
			piv.PreTranslate(node->GetObjOffsetPos());
			PreRotateMatrix(piv, node->GetObjOffsetRot());
			ApplyScaling(piv, node->GetObjOffsetScale());
			Matrix3 tm=node->GetObjectTM(ip->GetTime());
			Point3 pos=tm.GetTrans();
			ff->add_key(mesh,tm,pos,piv);
			}
		}
	}

void Flyfao::add_key(Mesh *mesh,Matrix3 tm,Point3 pos, Matrix3 piv)
{
	if (nkeys==0)
		{
		nfaces=mesh->numFaces;
		nverts=mesh->numVerts;
		verts=new float[nverts*3];
		faces=new unsigned short[nfaces*3];
		uvs=new float[nfaces*3*2];
		int i;
		Point3 p;
		for( i=0;i<nverts;i++ )
		{
			p=mesh->verts[i]*piv;
			p=p*tm;
			p=p-pos;
 			verts[i*3]=p.x;
			verts[i*3+1]=p.y;
			verts[i*3+2]=p.z;
		}
		for( i=0;i<nfaces;i++ )
			{
			faces[i*3]=(unsigned short)mesh->faces[i].v[0];
			faces[i*3+1]=(unsigned short)mesh->faces[i].v[1];
			faces[i*3+2]=(unsigned short)mesh->faces[i].v[2];
			if (mesh->tVerts)
				{
				uvs[i*6]=mesh->tVerts[mesh->tvFace[i].t[0]].x;
				uvs[i*6+1]=mesh->tVerts[mesh->tvFace[i].t[0]].y;
				uvs[i*6+2]=mesh->tVerts[mesh->tvFace[i].t[1]].x;
				uvs[i*6+3]=mesh->tVerts[mesh->tvFace[i].t[1]].y;
				uvs[i*6+4]=mesh->tVerts[mesh->tvFace[i].t[2]].x;
				uvs[i*6+5]=mesh->tVerts[mesh->tvFace[i].t[2]].y;
				}
			else
				uvs[i*6]=uvs[i*6+1]=uvs[i*6+2]=
				uvs[i*6+3]=uvs[i*6+4]=uvs[i*6+5]=0;
			}
		nkeys++;
		}
	else if (mesh->numVerts==nverts && mesh->numFaces==nfaces)
	{
		int i,j=nverts*nkeys;
		float *tmp=new float[(j+nverts)*3];
		memcpy(tmp,verts,sizeof(float)*j*3);
		delete verts;
		verts=tmp;
		Point3 p;
		for( i=0;i<nverts;i++ )
		{
			p=mesh->verts[i]*piv;
			p=p*tm;
			p=p-pos;
 			verts[(j+i)*3]=p.x;
			verts[(j+i)*3+1]=p.y;
			verts[(j+i)*3+2]=p.z;
		}
		nkeys++;
	}
	char str[256];
	sprintf(str,"Num faces: %i",nfaces);
	SetDlgItemText(hParams,IDC_NUMFACES,str);
	sprintf(str,"Num verts: %i",nverts);
	SetDlgItemText(hParams,IDC_NUMVERTS,str);
	sprintf(str,"Total keys: %i",nkeys);
	SetDlgItemText(hParams,IDC_NUMKEYS,str);
	pblock->SetValue(PB_KEY,0,0);
}

Flyfao::Flyfao()
{
	nkeys=0;
	nverts=0;
	nfaces=0;
	verts=0;
	uvs=0;
	faces=0;

	pblock = CreateParameterBlock(
				CURRENT_DESCRIPTOR, 
				PBLOCK_LENGTH, 
				CURRENT_VERSION);
	assert(pblock);
	MakeRefByID(FOREVER, 0, pblock);
}

Flyfao::~Flyfao()
{
	if (faces) delete faces;
	if (verts) delete verts;
	if (uvs) delete uvs;
}

#define FAO_DATA_CHUNK 9100

TCHAR *Flyfao::GetObjectName()
{
	return GetString(IDS_CLASS_NAME); 
}
 
IOResult Flyfao::Load(ILoad *iload)
{
	ULONG nb;
	IOResult res;
	while (IO_OK==(res=iload->OpenChunk())) 
	{
		switch(iload->CurChunkID())  
		{
			case FAO_DATA_CHUNK:
				res=iload->Read(&nkeys,sizeof(int),&nb);
				res=iload->Read(&nfaces,sizeof(int),&nb);
				res=iload->Read(&nverts,sizeof(int),&nb);
				if (nfaces)
				{
				verts=new float[nkeys*nverts*3];
				faces=new unsigned short[nfaces*3];
				uvs=new float[nfaces*3*2];
				res=iload->Read(faces,nfaces*3*sizeof(unsigned short),&nb);
				res=iload->Read(uvs,nfaces*3*2*sizeof(float),&nb);
				res=iload->Read(verts,nkeys*nverts*3*sizeof(float),&nb);
				}
				break;
		}
		iload->CloseChunk();
		if (res!=IO_OK)
			return res;
	}
	return IO_OK;
}

IOResult Flyfao::Save(ISave *isave)
{
	ULONG nb;
	isave->BeginChunk(FAO_DATA_CHUNK);
	isave->Write(&nkeys,sizeof(int),&nb);
	isave->Write(&nfaces,sizeof(int),&nb);
	isave->Write(&nverts,sizeof(int),&nb);
	isave->Write(faces,nfaces*3*sizeof(unsigned short),&nb);
	isave->Write(uvs,nfaces*3*2*sizeof(float),&nb);
	isave->Write(verts,nkeys*nverts*3*sizeof(float),&nb);
	isave->EndChunk();
	return IO_OK;
}

int Flyfao::load_fao(char *file)
{
	if (faces) delete faces;
	if (verts) delete verts;
	if (uvs) delete uvs;
	nkeys=0;
	nverts=0;
	nfaces=0;
	verts=0;
	uvs=0;
	faces=0;

	FILE *fp=fopen(file,"rb");
	if (fp)
		{
		int i,j;
		char skin[64];
		float pivotpos[3];

		fread(&i,1,sizeof(int),fp);
		if (i!=9171)
			{
			fclose(fp);
			return 0;
			}
		fread(&nfaces,1,sizeof(int),fp);
		fread(&nverts,1,sizeof(int),fp);
		fread(&nkeys,1,sizeof(int),fp);
		fread(&pivotpos,3,sizeof(float),fp);
		fread(skin,1,64,fp);

		verts=new float[nverts*nkeys*3];
		uvs=new float[6*nfaces];
		faces=new unsigned short[3*nfaces];

		fread(faces,nfaces,sizeof(unsigned short)*3,fp);
		fread(uvs,nfaces,sizeof(float)*6,fp);
		fread(verts,nverts*nkeys,sizeof(float)*3,fp);
		
		fclose(fp);
		
		float fac=(float)GetMasterScale(UNITS_CENTIMETERS)/10;
		j=nverts*nkeys*3;
		for( i=0;i<j;i++ )
		{
			verts[i]/=fac;
		}

		return 1;
		}
	return 0;
}

int Flyfao::save_fao(char *file,char *skin,Point3 pivot)
{
	FILE *fp=fopen(file,"wb");
	if (fp)
		{
		int i=9171,j;
		char skinfile[64];
		float fac=(float)GetMasterScale(UNITS_CENTIMETERS)/10,f;
		pivot*=fac;
		strncpy(skinfile,skin,63); skin[63]=0;

		fwrite(&i,1,sizeof(int),fp);
		fwrite(&nfaces,1,sizeof(int),fp);
		fwrite(&nverts,1,sizeof(int),fp);
		fwrite(&nkeys,1,sizeof(int),fp);
		fwrite(&pivot.x,3,sizeof(float),fp);
		fwrite(skinfile,1,64,fp);

		fwrite(faces,nfaces,sizeof(unsigned short)*3,fp);
		fwrite(uvs,nfaces,sizeof(float)*6,fp);

		j=nverts*nkeys*3;
		for( i=0;i<j;i++ )
		{
			f=verts[i]*fac;
			fwrite(&f,1,sizeof(float),fp);
		}
		
		j=0;
		fwrite(&j,1,sizeof(int),fp);

		fclose(fp);

		return 1;
		}
	return 0;
}

void Flyfao::delete_key(int key)
{
	if (nkeys>0 && key<nkeys && key>=0)
	if (IDYES==MessageBox(hParams,"Are you sure do delete the curent selected key ?","Fly3D fao object",MB_ICONQUESTION|MB_YESNO))
	{
		if (nkeys==1)
		{
			if (faces) delete faces;
			if (verts) delete verts;
			if (uvs) delete uvs;
			nkeys=0;
			nverts=0;
			nfaces=0;
			verts=0;
			uvs=0;
			faces=0;
			key=0;
		}
		else
		{
			float *tmp=new float[(nkeys-1)*nverts*3];
			memcpy(tmp,verts,sizeof(float)*3*key*nverts);
			memcpy(&tmp[3*key*nverts],&verts[3*nverts*(key+1)],sizeof(float)*3*nverts*(nkeys-key-1));

			delete verts;
			verts=tmp;

			nkeys--;
			if (key>=nkeys)
				key=nkeys-1;
			if (key<0) 
				key=0;
		}

		pblock->SetValue(PB_KEY,0,key);
		char str[256];
		sprintf(str,"Num faces: %i",nfaces);
		SetDlgItemText(hParams,IDC_NUMFACES,str);
		sprintf(str,"Num verts: %i",nverts);
		SetDlgItemText(hParams,IDC_NUMVERTS,str);
		sprintf(str,"Total keys: %i",nkeys);
		SetDlgItemText(hParams,IDC_NUMKEYS,str);
	}
}

void Flyfao::open_file_dialog()
{
	OPENFILENAME ofn;
	char filename[256]="";
	memset(&ofn,0,sizeof(OPENFILENAME));
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=hParams;
	ofn.hInstance=hInstance;
	ofn.lpstrFilter="Fly animated object (*.fao)\0*.fao\0";
	ofn.lpstrDefExt="fao";
	ofn.lpstrFile=filename;
	ofn.nMaxFile=255;
	ofn.lpstrTitle="Open object";
	ofn.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		load_fao(filename);

		pblock->SetValue(PB_KEY,0,0);
		char str[256];
		sprintf(str,"Num faces: %i",nfaces);
		SetDlgItemText(hParams,IDC_NUMFACES,str);
		sprintf(str,"Num verts: %i",nverts);
		SetDlgItemText(hParams,IDC_NUMVERTS,str);
		sprintf(str,"Total keys: %i",nkeys);
		SetDlgItemText(hParams,IDC_NUMKEYS,str);
	}
}

void Flyfao::open_save_file_dialog()
{
	OPENFILENAME ofn;
	char filename[256]="";
	memset(&ofn,0,sizeof(OPENFILENAME));
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=hParams;
	ofn.hInstance=hInstance;
	ofn.lpstrFilter="Fly animated object (*.fao)\0*.fao\0";
	ofn.lpstrDefExt="fao";
	ofn.lpstrFile=filename;
	ofn.nMaxFile=255;
	ofn.lpstrTitle="Open object";
	ofn.Flags=OFN_PATHMUSTEXIST;
	if (GetOpenFileName(&ofn))
		save_fao(filename,"",Point3(0,0,0));
}

BOOL flyfaoDlg::DlgProc(
		TimeValue t,IParamMap *map,
		HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		{
		char str[256];
		ff->hParams=hWnd;
		sprintf(str,"Num faces: %i",ff->nfaces);
		SetDlgItemText(hWnd,IDC_NUMFACES,str);
		sprintf(str,"Num verts: %i",ff->nverts);
		SetDlgItemText(hWnd,IDC_NUMVERTS,str);
		sprintf(str,"Total keys: %i",ff->nkeys);
		SetDlgItemText(hWnd,IDC_NUMKEYS,str);
		}
		break;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDC_ADDKEY:
			thePickMode.ff  = ff;
			ff->ip->SetPickMode(&thePickMode);
			break;
		case IDC_DELETEKEY:
			{
			int key;
			ff->pblock->GetValue(PB_KEY,ff->ip->GetTime(),key,FOREVER);
			ff->delete_key(key);
			}
			break;
		case IDC_LOAD:
			ff->open_file_dialog();
			break;
		case IDC_SAVE:
			ff->open_save_file_dialog();
			break;
		}
		break;
	}
	return FALSE;
}

void Flyfao::BeginEditParams(IObjParam *ip,ULONG flags,Animatable *prev)
{
	this->ip = ip;
	flyfaodlg.ff=this;
	SimpleObject::BeginEditParams(ip,flags,prev);

	if(pmapParam) {
		pmapParam->SetParamBlock(pblock);
	} else {
		pmapParam = CreateCPParamMap(
			descParam, PARAMDESC_LENGTH,
			pblock, 
			ip, 
			hInstance, 
			MAKEINTRESOURCE(IDD_PANEL),
			GetString(IDS_PARAMS), 
			0);
	}
	pmapParam->SetUserDlgProc(&flyfaodlg);
}

void Flyfao::EndEditParams( IObjParam *ip, ULONG flags,Animatable *next )
{
	SimpleObject::EndEditParams(ip,flags,next);
	if (flags&END_EDIT_REMOVEUI ) {
		DestroyCPParamMap(pmapParam);
		pmapParam  = NULL;
	}
	this->ip = NULL;
}

BOOL Flyfao::HasUVW() 
{ 
	return TRUE; 
}

void Flyfao::SetGenUVW(BOOL sw) 
{  
	if (sw==HasUVW()) return;
}

int FlyfaoCreateCallBack::proc(ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat )
{
	switch(msg)
	{
	case MOUSE_POINT:
	case MOUSE_MOVE:
		switch(point) 
		{
		case 0: 
			ob->suspendSnap = TRUE;
			sp0 = m;
			p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
			mat.SetTrans(p0);
			break;
		case 1:
			return CREATE_STOP;
		}
		break;
	case MOUSE_ABORT:
		return CREATE_ABORT;
	}

	return TRUE;
}

CreateMouseCallBack* Flyfao::GetCreateMouseCallBack() 
{
	FlyfaoCreateCB.SetObj(this);
	return(&FlyfaoCreateCB);
}

void Flyfao::BuildMesh(TimeValue t)
{
	int key;
	ivalid = FOREVER;
	pblock->GetValue(PB_KEY,t,key,FOREVER);
	if (key<0)
	{
		pblock->SetValue(PB_KEY,0,0);
		return;
	}
	if (key>=nkeys)
	{
		pblock->SetValue(PB_KEY,0,nkeys-1);
		return;
	}
	if (nkeys==0)
	{
		mesh.setNumVerts(0);
		mesh.setNumFaces(0);
		mesh.setNumTVerts(0);
		mesh.setNumTVFaces(0);
		return;
	}
	mesh.setNumVerts(nverts);
	mesh.setNumFaces(nfaces);
	mesh.setNumTVerts(nfaces*3);
	mesh.setNumTVFaces(nfaces);
	int i,j=nverts*key;
	for( i=0;i<nverts;i++ )
		mesh.setVert(i,verts[(j+i)*3],verts[(j+i)*3+1],verts[(j+i)*3+2]);
	for( i=0;i<nfaces;i++ )
	{
		mesh.faces[i].v[0]=faces[i*3];
		mesh.faces[i].v[1]=faces[i*3+1];
		mesh.faces[i].v[2]=faces[i*3+2];
		mesh.faces[i].flags=EDGE_ALL;
		mesh.faces[i].smGroup=1;
	}
	for( i=0;i<nfaces;i++ )
	{
		mesh.tvFace[i].t[0]=i*3;
		mesh.tvFace[i].t[1]=i*3+1;
		mesh.tvFace[i].t[2]=i*3+2;
		mesh.tVerts[i*3].x=uvs[i*6];
		mesh.tVerts[i*3].y=1.0f-uvs[i*6+1];
		mesh.tVerts[i*3].z=0;
		mesh.tVerts[i*3+1].x=uvs[i*6+2];
		mesh.tVerts[i*3+1].y=1.0f-uvs[i*6+3];
		mesh.tVerts[i*3+1].z=0;
		mesh.tVerts[i*3+2].x=uvs[i*6+4];
		mesh.tVerts[i*3+2].y=1.0f-uvs[i*6+5];
		mesh.tVerts[i*3+2].z=0;
	}
	mesh.InvalidateGeomCache();
	mesh.InvalidateTopologyCache();
	mesh.BuildStripsAndEdges();
}

BOOL Flyfao::OKtoDisplay(TimeValue t) 
{
	return TRUE;
}

void Flyfao::InvalidateUI() 
{
	if (pmapParam) pmapParam->Invalidate();
}

ParamDimension *Flyfao::GetParameterDim(int pbIndex) 
{
	return defaultDim;
}

TSTR Flyfao::GetParameterName(int pbIndex) 
{
	return GetString(IDS_PARAMS);
}

BOOL Flyfao::SetValue(int i, TimeValue t, int v) 
{
	return TRUE;
}

BOOL Flyfao::SetValue(int i, TimeValue t, float v)
{
	return TRUE;
}

BOOL Flyfao::SetValue(int i, TimeValue t, Point3 &v) 
{
	return TRUE;
}

BOOL Flyfao::GetValue(int i, TimeValue t, int &v, Interval &ivalid) 
{
	return TRUE;
}

BOOL Flyfao::GetValue(int i, TimeValue t, float &v, Interval &ivalid) 
{
	return TRUE;
}

BOOL Flyfao::GetValue(int i, TimeValue t, Point3 &v, Interval &ivalid) 
{	
	return TRUE;
}

Object* Flyfao::ConvertToType(TimeValue t, Class_ID obtype)
{
	return SimpleObject::ConvertToType(t,obtype);
}

int Flyfao::CanConvertToType(Class_ID obtype)
{
	if (obtype==defObjectClassID ||
		obtype==triObjectClassID ||
		obtype==FLYFAO_CLASS_ID) {
		return 1;
	} else {		
	return SimpleObject::CanConvertToType(obtype);
		}
}

int Flyfao::IntersectRay(
		TimeValue t, Ray& ray, float& at, Point3& norm)
{
	return FALSE;
}

void Flyfao::GetCollapseTypes(Tab<Class_ID> &clist,Tab<TSTR*> &nlist)
{
    Object::GetCollapseTypes(clist, nlist);
}

RefTargetHandle Flyfao::Clone(RemapDir& remap) 
{
	Flyfao* newob = new Flyfao();	
	if (nkeys)
	{
		newob->nkeys=nkeys;
		newob->nverts=nverts;
		newob->nfaces=nfaces;

		newob->faces=new unsigned short[nfaces*3];
		newob->uvs=new float[nfaces*6];
		newob->verts=new float[nkeys*nverts*3];

		memcpy(newob->faces,faces,sizeof(unsigned short)*3*nfaces);
		memcpy(newob->uvs,uvs,sizeof(float)*6*nfaces);
		memcpy(newob->verts,verts,sizeof(float)*3*nverts*nkeys);
	}
	newob->ReplaceReference(0,pblock->Clone(remap));
	newob->ivalid.SetEmpty();
	return(newob);
}
