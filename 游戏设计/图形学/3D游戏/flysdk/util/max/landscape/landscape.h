/**********************************************************************
 *<
	FILE: landscape.h

	DESCRIPTION:	Template Utility

	CREATED BY:

	HISTORY:

 *>	Copyright (c) 1997, All Rights Reserved.
 **********************************************************************/

#ifndef __LANDSCAPE__H
#define __LANDSCAPE__H

#include "Max.h"
#include "resource.h"
#include "istdplug.h"

#include "iparamm.h"
#include "Simpobj.h"
#include "Bmmlib.h"
#include "Bitmap.h"


TCHAR *GetString(int id);

extern ClassDesc* GetlandscapeDesc();

extern HINSTANCE hInstance;

#define LANDSCAPE_CLASS_ID	Class_ID(0xaf14425b, 0x6a596345)

class landscape : public SimpleObject, public IParamArray {

	public:

		Bitmap *displacebmp;
		Bitmap *colorbmp;
		char displacename[256],colorname[256];

		//Class vars
		static IObjParam *ip;			//Access to the interface
		static IParamMap *pmapParam;	//handle to the parammap		
		
		// Constructor/Destructor
		landscape();
		~landscape();
		
		// From BaseObject
		CreateMouseCallBack* GetCreateMouseCallBack();
		
		// From Object
		TCHAR *GetObjectName() { return GetString(IDS_CLASS_NAME); }
		BOOL HasUVW();
		void SetGenUVW(BOOL sw);
		int CanConvertToType(Class_ID obtype);
		Object* ConvertToType(TimeValue t, Class_ID obtype);
		void GetCollapseTypes(Tab<Class_ID> &clist,Tab<TSTR*> &nlist);
		int IntersectRay(TimeValue t, Ray& ray, float& at, Point3& norm);
		ObjectState Eval(TimeValue t) { return ObjectState(this); };		
		Interval ObjectValidity(TimeValue t) { return FOREVER; }

		// From Animatable
		void BeginEditParams( IObjParam  *ip, ULONG flags,Animatable *prev);
		void EndEditParams( IObjParam *ip, ULONG flags,Animatable *next);
		void DeleteThis() {delete this;}
		Class_ID ClassID() { return LANDSCAPE_CLASS_ID; } 

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

#endif // __LANDSCAPE__H
