#ifndef __FLYFAO__H
#define __FLYFAO__H

#define FLYFAO_CLASS_ID	Class_ID(0x375dc9ae, 0x4baacec0)

#include "Simpobj.h"

class Flyfao : public SimpleObject, public IParamArray {

	public:
		HWND hParams;

		int nkeys,nverts,nfaces;
		float *verts;
		float *uvs;
		unsigned short *faces;
		
		virtual void add_key(Mesh *mesh,Matrix3 tm,Point3 pos, Matrix3 piv);
		virtual void delete_key(int key);
		virtual void open_file_dialog();
		virtual void open_save_file_dialog();
		virtual int load_fao(char *file);
		virtual int save_fao(char *file,char *skin,Point3 pivot);

		//Class vars
		static IObjParam *ip;			//Access to the interface
		static IParamMap *pmapParam;	//handle to the parammap		
		
		// Constructor/Destructor
		Flyfao();
		~Flyfao();

		// From BaseObject
		CreateMouseCallBack* GetCreateMouseCallBack();
		
		// From Object
		BOOL HasUVW();
		void SetGenUVW(BOOL sw);
		int CanConvertToType(Class_ID obtype);
		Object* ConvertToType(TimeValue t, Class_ID obtype);
		void GetCollapseTypes(Tab<Class_ID> &clist,Tab<TSTR*> &nlist);
		int IntersectRay(TimeValue t, Ray& ray, float& at, Point3& norm);
		TCHAR *GetObjectName();
		//TODO: Evaluate the object and return the ObjectState
		ObjectState Eval(TimeValue t) { return ObjectState(this); };		
		//TODO: Return the validity interval of the object as a whole
		Interval ObjectValidity(TimeValue t) { return FOREVER; }

		// From Animatable
		void BeginEditParams( IObjParam  *ip, ULONG flags,Animatable *prev);
		void EndEditParams( IObjParam *ip, ULONG flags,Animatable *next);
		void DeleteThis() {delete this;}
		Class_ID ClassID() { return FLYFAO_CLASS_ID; } 

		// From ReferenceTarget
		RefTargetHandle Clone(RemapDir& remap = NoRemap());
		IOResult Load(ILoad *iload);
		IOResult Save(ISave *isave);
		// From IParamArray
		BOOL SetValue(int i, TimeValue t, int v);
		BOOL SetValue(int i, TimeValue t, float v);
		BOOL SetValue(int i, TimeValue t, Point3 &v);
		BOOL GetValue(int i, TimeValue t, int &v, Interval &ivalid);
		BOOL GetValue(int i, TimeValue t, float &v, Interval &ivalid);
		BOOL GetValue(int i, TimeValue t, Point3 &v, Interval &ivalid);
		// From SimpleObject
		void BuildMesh(TimeValue t);
		BOOL OKtoDisplay(TimeValue t);
		void InvalidateUI();
		ParamDimension *GetParameterDim(int pbIndex);
		TSTR GetParameterName(int pbIndex);
};

#endif // __FLYFAO__H
