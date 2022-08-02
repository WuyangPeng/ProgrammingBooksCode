#include "landscape.h"

ClassDesc* GetlandscapeDesc();

HINSTANCE hInstance;
int controlsInit = FALSE;

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

__declspec( dllexport ) const TCHAR* LibDescription()
{
	return GetString(IDS_LIBDESCRIPTION);
}

//TODO: Must change this number when adding a new class
__declspec( dllexport ) int LibNumberClasses()
{
	return 1;
}

__declspec( dllexport ) ClassDesc* LibClassDesc(int i)
{
	switch(i) {
		case 0: return GetlandscapeDesc();
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

class landscapeClassDesc:public ClassDesc {
	public:
	int 			IsPublic() {return 1;}
	void *			Create(BOOL loading = FALSE) {return new landscape();}
	const TCHAR *	ClassName() {return GetString(IDS_CLASS_NAME);}
	SClass_ID		SuperClassID() {return GEOMOBJECT_CLASS_ID;}
	Class_ID		ClassID() {return LANDSCAPE_CLASS_ID;}
	const TCHAR* 	Category() {return GetString(IDS_CATEGORY);}
	void			ResetClassParams (BOOL fileReset);
};

static landscapeClassDesc landscapeDesc;
ClassDesc* GetlandscapeDesc() {return &landscapeDesc;}

void landscapeClassDesc::ResetClassParams (BOOL fileReset) 
{
}

//TODO: Add Parameter block indices for various parameters
#define PB_SIZE				0
#define PB_SEGX				1
#define PB_SEGY				2
#define PB_DISPLACEVALUE	3
#define PB_MAPCOORD			4
#define PB_MAPCOORDTILE		5
#define PB_COLORZGRAD		6

//TODO: Add ParamUIDesc's for the various parameters
static ParamUIDesc descParam[] = {
	ParamUIDesc(
		PB_SIZE,
		EDITTYPE_FLOAT,
		IDC_SIZE0,IDC_SIZE0SPIN,
		1.0f,100000.0f,
		1.0f),	
	ParamUIDesc(
		PB_SEGX,
		EDITTYPE_INT,
		IDC_SEGX,IDC_SEGXSPIN,
		1,100000,
		1),	
	ParamUIDesc(
		PB_SEGY,
		EDITTYPE_INT,
		IDC_SEGY,IDC_SEGYSPIN,
		1,100000,
		1),	
	ParamUIDesc(
		PB_DISPLACEVALUE,
		EDITTYPE_FLOAT,
		IDC_DISPLACEVALUE,IDC_DISPLACEVALUESPIN,
		1.0f,10000.0f,
		1.0f),	
	ParamUIDesc(
		PB_MAPCOORD,
		TYPE_SINGLECHEKBOX,
		IDC_MAPCOORD),	
	ParamUIDesc(
		PB_MAPCOORDTILE,
		EDITTYPE_FLOAT,
		IDC_MAPPINGTILE,IDC_MAPPINGTILESPIN,
		1.0f,100.0f,
		1.0f),	
	ParamUIDesc(
		PB_COLORZGRAD,
		TYPE_SINGLECHEKBOX,
		IDC_COLORZGRAD),	
	}; 	

//TODO: Parameter descriptor length
#define PARAMDESC_LENGTH 7

//TODO: Add ParamBlockDescID's for the various parameters
static ParamBlockDescID descVer1[] = {
	{ TYPE_FLOAT, NULL, TRUE, 0 },
	{ TYPE_INT, NULL, TRUE, 0 },
	{ TYPE_INT, NULL, TRUE, 0 },
	{ TYPE_FLOAT, NULL, TRUE, 0 },
	{ TYPE_BOOL, NULL, TRUE, 0 },
	{ TYPE_FLOAT, NULL, TRUE, 0 },
	{ TYPE_BOOL, NULL, TRUE, 0 },
	};

#define CURRENT_DESCRIPTOR descVer1

#define PBLOCK_LENGTH	7

#define CURRENT_VERSION	1

IObjParam *landscape::ip			= NULL;
IParamMap *landscape::pmapParam	= NULL;

//--- landscape -------------------------------------------------------

landscape::landscape()
{
	strcpy(displacename,"None");
	strcpy(colorname,"None");

	displacebmp=0;
	colorbmp=0;

	pblock = CreateParameterBlock(
				CURRENT_DESCRIPTOR, 
				PBLOCK_LENGTH, 
				CURRENT_VERSION);
	assert(pblock);
	MakeRefByID(FOREVER, 0, pblock);
	
	pblock->SetValue(PB_SIZE,0, 0.0f);
	pblock->SetValue(PB_SEGX,0, 16);
	pblock->SetValue(PB_SEGY,0, 16);
	pblock->SetValue(PB_DISPLACEVALUE,0, 10.0f);
	pblock->SetValue(PB_MAPCOORD,0, 0);
	pblock->SetValue(PB_MAPCOORDTILE,0, 4.0f);
	pblock->SetValue(PB_COLORZGRAD,0, 0);
}

landscape::~landscape()
{
	if (displacebmp)
		displacebmp->DeleteThis();
	if (colorbmp)
		colorbmp->DeleteThis();
	displacebmp=0;
	colorbmp=0;
	displacename[0]=0;
	colorname[0]=0;
}

#define DISPLACE_IMAGE_CHUNK 9110
#define COLOR_IMAGE_CHUNK  9120

IOResult landscape::Load(ILoad *iload)
{
	ULONG nb;
	IOResult res;
	while (IO_OK==(res=iload->OpenChunk())) 
	{
		switch(iload->CurChunkID())  
		{
			case DISPLACE_IMAGE_CHUNK:
				res=iload->Read(displacename, iload->CurChunkLength(), &nb);
				break;
			case COLOR_IMAGE_CHUNK:
				res=iload->Read(colorname, iload->CurChunkLength(), &nb);
				break;
		}
		iload->CloseChunk();
		if (res!=IO_OK)
			return res;
	}
	if (displacename[0])
	{
		BitmapInfo bi(displacename);
		BMMRES status;
		displacebmp=TheManager->Load(&bi,&status);
		if (status!=BMMRES_SUCCESS)
			displacename[0]=0;
	}
	if (colorname[0])
	{
		BitmapInfo bi(colorname);
		BMMRES status;
		colorbmp=TheManager->Load(&bi,&status);
		if (status!=BMMRES_SUCCESS)
			colorname[0]=0;
	}
	return IO_OK;
}

IOResult landscape::Save(ISave *isave)
{
	ULONG nb;
	
	isave->BeginChunk(DISPLACE_IMAGE_CHUNK);
	isave->Write(displacename, strlen(displacename)+1, &nb);
	isave->EndChunk();

	isave->BeginChunk(COLOR_IMAGE_CHUNK);
	isave->Write(colorname, strlen(colorname)+1, &nb);
	isave->EndChunk();

	return IO_OK;
}

class landscapeDlgProc : public ParamMapUserDlgProc {
	public:
		landscape *ls;
		BOOL DlgProc(TimeValue t,IParamMap *map,HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
		void DeleteThis() {}
	};

static landscapeDlgProc landscapeProc;

BOOL landscapeDlgProc::DlgProc(
		TimeValue t,IParamMap *map,
		HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		if (wParam==IDC_DISPLACEIMAGEBUT)
		{
			BitmapInfo bi;
			if (ls->displacebmp)
				ls->displacebmp->DeleteThis();
			ls->displacebmp=0;
			strcpy(ls->displacename,"None");
			if (TheManager->SelectFileInput(&bi,hWnd,"Select displace image"))
				{
				BMMRES status;
				ls->displacebmp=TheManager->Load(&bi,&status);
				if (status==BMMRES_SUCCESS)
					strcpy(ls->displacename,bi.Filename());
				}
			SetDlgItemText(hWnd,IDC_DISPLACEIMAGEBUT,ls->displacename);
			float size;
			ls->pblock->GetValue(PB_SIZE,ls->ip->GetTime(),size,FOREVER);
			ls->pblock->SetValue(PB_SIZE,0, size);
		}
		else if (wParam==IDC_TEXTUREIMAGEBUT)
		{
			BitmapInfo bi;
			if (ls->colorbmp)
				ls->colorbmp->DeleteThis();
			ls->colorbmp=0;
			strcpy(ls->colorname,"None");
			if (TheManager->SelectFileInput(&bi,hWnd,"Select texture image"))
				{
				BMMRES status;
				ls->colorbmp=TheManager->Load(&bi,&status);
				if (status==BMMRES_SUCCESS)
					strcpy(ls->colorname,bi.Filename());
				}
			SetDlgItemText(hWnd,IDC_TEXTUREIMAGEBUT,ls->colorname);
			float size;
			ls->pblock->GetValue(PB_SIZE,ls->ip->GetTime(),size,FOREVER);
			ls->pblock->SetValue(PB_SIZE,0, size);
		}
		break;
	}
	return FALSE;
}

void landscape::BeginEditParams(IObjParam *ip,ULONG flags,Animatable *prev)
{
	this->ip = ip;
	landscapeProc.ls=this;
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
	pmapParam->SetUserDlgProc(&landscapeProc);
	
	HWND hWnd=pmapParam->GetHWnd();
	SetDlgItemText(hWnd,IDC_DISPLACEIMAGEBUT,displacename);
	SetDlgItemText(hWnd,IDC_TEXTUREIMAGEBUT,colorname);
}

void landscape::EndEditParams( IObjParam *ip, ULONG flags,Animatable *next )
{
	SimpleObject::EndEditParams(ip,flags,next);
	if (flags&END_EDIT_REMOVEUI ) {
		DestroyCPParamMap(pmapParam);
		pmapParam  = NULL;
	}
	this->ip = NULL;
}

BOOL landscape::HasUVW() 
{ 
	BOOL mapcoord;
	pblock->GetValue(PB_MAPCOORD,0,mapcoord,FOREVER);
	return mapcoord; 
}

void landscape::SetGenUVW(BOOL sw) 
{  
	if (sw==HasUVW()) return;
	pblock->SetValue(PB_MAPCOORD,0, sw);
}

class landscapeCreateCallBack : public CreateMouseCallBack {
	IPoint2 sp0;		//First point in screen coordinates
	landscape *ob;		//Pointer to the object 
	Point3 p0;			//First point in world coordinates
public:	
	int proc( ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat);
	void SetObj(landscape *obj) {ob = obj;}
};

int landscapeCreateCallBack::proc(ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat )
{
	if (msg == MOUSE_FREEMOVE)
		vpt->SnapPreview(m,m,NULL, SNAP_IN_3D);
	else
	if (msg==MOUSE_POINT)
		{
		if (point==0)
			{
			ob->suspendSnap = TRUE;
			sp0 = m;
			p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
			mat.SetTrans(p0);
			}
		else 
			{
			ob->suspendSnap = FALSE;
			return Length(sp0 - m)<3?CREATE_ABORT:CREATE_STOP;
			}
		}
	else if (msg==MOUSE_MOVE) 
		{
		float size=Length(p0 - vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE));
		ob->pblock->SetValue(PB_SIZE,0, size);
		ob->pmapParam->Invalidate();
		} 
	else 
		if (msg == MOUSE_ABORT) 
			return CREATE_ABORT;

	return CREATE_CONTINUE;
}

static landscapeCreateCallBack landscapeCreateCB;

CreateMouseCallBack* landscape::GetCreateMouseCallBack() 
{
	landscapeCreateCB.SetObj(this);
	return(&landscapeCreateCB);
}

void landscape::BuildMesh(TimeValue t)
{
	int nv,nf,ncvx,ncvy,x,y,i,segx,segy;
	Point3 p;
	float dx,dy,size,displacevalue,tile,maxdz=0;
	BOOL mapcoord;
	BOOL colorzgrad;
	
	ivalid = FOREVER;
	pblock->GetValue(PB_SIZE,t,size,FOREVER);
	pblock->GetValue(PB_SEGX,t,segx,FOREVER);
	pblock->GetValue(PB_SEGY,t,segy,FOREVER);
	pblock->GetValue(PB_DISPLACEVALUE,t,displacevalue,FOREVER);
	pblock->GetValue(PB_MAPCOORD,t,mapcoord,FOREVER);
	pblock->GetValue(PB_MAPCOORDTILE,t,tile,FOREVER);
	pblock->GetValue(PB_COLORZGRAD,t,colorzgrad,FOREVER);
	
	ncvx=segx+1;
	ncvy=segy+1;
	nv=ncvx*ncvy;
	nf=segx*2*segy;

	dx=size/(segx/2.0f);
	dy=size/(segy/2.0f);

	mesh.setNumVerts(nv);
	mesh.setNumFaces(nf);

	for( i=0,y=0;y<ncvy;y++ )
		for( x=0;x<ncvx;x++,i++ )
		{
		p.x=-size+dx*x;
		p.y=-size+dy*y;
		p.z=0;
		mesh.setVert(i,p);
		}
	for( i=0,y=0;y<segy;y++ )
		for( x=0;x<segx;x++ )
		{
			mesh.faces[i].v[0]=y*ncvx+x;
			mesh.faces[i].v[1]=y*ncvx+x+1;
			mesh.faces[i].v[2]=(y+1)*ncvx+x;
			mesh.faces[i].flags=EDGE_A|EDGE_C;
			mesh.faces[i].smGroup=1;
			i++;

			mesh.faces[i].v[0]=y*ncvx+x+1;
			mesh.faces[i].v[1]=(y+1)*ncvx+x+1;
			mesh.faces[i].v[2]=(y+1)*ncvx+x;
			mesh.faces[i].flags=EDGE_A|EDGE_B;
			mesh.faces[i].smGroup=1;
			i++;
		}
	
	if (displacebmp)
	{
	int wd,hd,c;
	float dz;
	wd=displacebmp->Width();
	hd=displacebmp->Height();
	BMM_Color_64 *ptr=new BMM_Color_64[wd]; 

	for( i=0,y=0;y<ncvy;y++ )
		{
		displacebmp->GetLinearPixels(0,y*(hd-1)/(ncvy-1),wd,ptr);
		for( x=0;x<ncvx;x++,i++ )
			{
			c=  (int)ptr[x*(wd-1)/(ncvx-1)].r+
				(int)ptr[x*(wd-1)/(ncvx-1)].g+
				(int)ptr[x*(wd-1)/(ncvx-1)].b;
			dz= displacevalue*(c/(float)0xffff);
			mesh.verts[i].z+=dz;
			if (dz>maxdz)
				maxdz=dz;
			}
		}

	delete ptr;
	}

	if (colorbmp)
	{
	int wt,ht,c;
	BMM_Color_64 *ptr=0;
	wt=colorbmp->Width();
	ht=colorbmp->Height();
	ptr=new BMM_Color_64[wt];
	
	mesh.setNumVertCol(nv);
	mesh.setNumVCFaces(nf);

	for( i=0;i<nf;i++ )
		for( c=0;c<3;c++ )
			mesh.vcFace[i].t[c]=mesh.faces[i].v[c];

	if (colorzgrad)
		{
			if (maxdz>0)
			{
			colorbmp->GetLinearPixels(0,0,wt,ptr);
			for( i=0,y=0;y<ncvy;y++ )
				{
				for( x=0;x<ncvx;x++,i++ )
					{
					c=(int)(mesh.verts[i].z/maxdz*(ht-1));
					mesh.vertCol[i].x=(ptr[c].r/(float)0xffff);
					mesh.vertCol[i].y=(ptr[c].g/(float)0xffff);
					mesh.vertCol[i].z=(ptr[c].b/(float)0xffff);
					}
				}
			}
		}
	else 
		for( i=0,y=0;y<ncvy;y++ )
			{
			colorbmp->GetLinearPixels(0,y*(ht-1)/(ncvy-1),wt,ptr);
			for( x=0;x<ncvx;x++,i++ )
				{
				mesh.vertCol[i].x=(ptr[x*(wt-1)/(ncvx-1)].r/(float)0xffff);
				mesh.vertCol[i].y=(ptr[x*(wt-1)/(ncvx-1)].g/(float)0xffff);
				mesh.vertCol[i].z=(ptr[x*(wt-1)/(ncvx-1)].b/(float)0xffff);
				}
			}

	delete ptr;
	}
	else 
	{
	mesh.setNumVertCol(nv);
	mesh.setNumVCFaces(nf);
	int c;
	for( i=0;i<nf;i++ )
		for( c=0;c<3;c++ )
			mesh.vcFace[i].t[c]=mesh.faces[i].v[c];
	for( i=0;i<nv;i++ )
		{
		mesh.vertCol[i].x=1.0f;
		mesh.vertCol[i].y=1.0f;
		mesh.vertCol[i].z=1.0f;
		}
	}

	if (mapcoord)
	{
	mesh.setNumTVerts(nv);
	mesh.setNumTVFaces(nf);
	for( i=0,y=0;y<ncvy;y++ )
		for( x=0;x<ncvx;x++,i++ )
			mesh.setTVert(i,(float)x/ncvx*tile,(float)y/ncvy*tile,0);
	for( i=0;i<nf;i++ )
		for( x=0;x<3;x++ )
			mesh.tvFace[i].t[x]=mesh.faces[i].v[x];
	}

	mesh.InvalidateGeomCache();
	mesh.InvalidateTopologyCache();
	mesh.BuildStripsAndEdges();
}

BOOL landscape::OKtoDisplay(TimeValue t) 
{
	float size;
	pblock->GetValue(PB_SIZE,t,size,FOREVER);
	if (size==0.0f) return FALSE;
	else return TRUE;
}

void landscape::InvalidateUI() 
{
	if (pmapParam) pmapParam->Invalidate();
}

ParamDimension *landscape::GetParameterDim(int pbIndex) 
{
	return defaultDim;
}

TSTR landscape::GetParameterName(int pbIndex) 
{
	return GetString(IDS_PARAMS);
}

BOOL landscape::SetValue(int i, TimeValue t, int v) 
{
	return TRUE;
}

BOOL landscape::SetValue(int i, TimeValue t, float v)
{
	return TRUE;
}

BOOL landscape::SetValue(int i, TimeValue t, Point3 &v) 
{
	return TRUE;
}

BOOL landscape::GetValue(int i, TimeValue t, int &v, Interval &ivalid) 
{
	return TRUE;
}

BOOL landscape::GetValue(int i, TimeValue t, float &v, Interval &ivalid) 
{
	return TRUE;
}

BOOL landscape::GetValue(int i, TimeValue t, Point3 &v, Interval &ivalid) 
{	
	return TRUE;
}

Object* landscape::ConvertToType(TimeValue t, Class_ID obtype)
{
	return SimpleObject::ConvertToType(t,obtype);
}

int landscape::CanConvertToType(Class_ID obtype)
{
	if (obtype==defObjectClassID ||
		obtype==triObjectClassID) {
		return 1;
	} else {		
	return SimpleObject::CanConvertToType(obtype);
		}
}

int landscape::IntersectRay(
		TimeValue t, Ray& ray, float& at, Point3& norm)
{
	return SimpleObject::IntersectRay(t,ray,at,norm);
}

void landscape::GetCollapseTypes(Tab<Class_ID> &clist,Tab<TSTR*> &nlist)
{
    Object::GetCollapseTypes(clist, nlist);
}

RefTargetHandle landscape::Clone(RemapDir& remap) 
{
	landscape* newob = new landscape();	
	newob->ReplaceReference(0,pblock->Clone(remap));
	newob->ivalid.SetEmpty();
	return(newob);
}
