#include "d3dstuff.h"
#include "MyMath.h"
#include "physics.h"

d3dInfo	D3D;
LPDIRECT3DRMWINDEVICE WinDev;
texInfo	Texture;

//------------------------------------------------------------------------//
//------------------------------------------------------------------------//

LPDIRECT3DRMMESH        ClothMesh = 0;
D3DRMGROUPINDEX			ClothGroup;
LPDIRECT3DRMTEXTURE		ClothTex = 0;
LPDIRECT3DRMMATERIAL	ClothMat = NULL;
D3DVALUE				BoxW, BoxH;








//------------------------------------------------------------------------//
//------------------------------------------------------------------------//
//------------------------------------------------------------------------//
//------------------------------------------------------------------------//



BOOL	CreateD3DRMObject(void)
{
	HRESULT	retval;

    retval = Direct3DRMCreate(&(D3D.D3DRM));
    
    if (retval != D3DRM_OK) {        
        return FALSE;
    }

	return TRUE;

}

BOOL	CreateD3DRMClipperObject(HWND hwnd)
{
    if (FAILED(DirectDrawCreateClipper(0, &(D3D.DDClipper), NULL))) {
        return FALSE;
    }

    if (FAILED(D3D.DDClipper->SetHWnd(0, hwnd))) {
        RELEASE(D3D.DDClipper);
        return FALSE;
    }

	return TRUE;
}

BOOL	CreateViewPort(HWND hwnd)
{
    D3D.Model = D3DCOLOR_RGB;
    
    if (!CreateDevice(hwnd)) {
        return FALSE;
    }

	return TRUE;
}

BOOL	CreateDevice(HWND hwnd)
{
    RECT rect;
    int devCaps;
    HDC hdc;
    
    GetClientRect(hwnd, &rect);  
    if (FAILED(D3D.D3DRM->CreateDeviceFromClipper(	D3D.DDClipper, 
													NULL,
													rect.right, 
													rect.bottom, 
													&(D3D.Device) )))
									return FALSE;

    hdc = GetDC(hwnd);    
    devCaps = GetDeviceCaps(hdc, BITSPIXEL);
    ReleaseDC(hwnd, hdc);
    
    switch (devCaps)
    {
    case 1:
        if (FAILED(D3D.Device->SetShades(4)))
            return FALSE;

        if (FAILED(D3D.D3DRM->SetDefaultTextureShades(4)))
            return FALSE;

        break;

    case 16:
        if (FAILED(D3D.Device->SetShades(32)))
            return FALSE;

        if (FAILED(D3D.D3DRM->SetDefaultTextureColors(64)))
            return FALSE;

        if (FAILED(D3D.D3DRM->SetDefaultTextureShades(32)))
            return FALSE;

        if (FAILED(D3D.Device->SetDither(FALSE)))
            return FALSE;
        break;

    case 24:
    case 32:
        if (FAILED(D3D.Device->SetShades(256)))
            return FALSE;

        if (FAILED(D3D.D3DRM->SetDefaultTextureColors(64)))
            return FALSE;

        if (FAILED(D3D.D3DRM->SetDefaultTextureShades(256)))
            return FALSE;

        if (FAILED(D3D.Device->SetDither(FALSE)))
            return FALSE;
        break;

    default:
        if (FAILED(D3D.Device->SetDither(FALSE)))
            return FALSE;
    }	

	D3D.Device->SetQuality(D3DRMRENDER_GOURAUD);
	//D3D.Device->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
 
    if (!CreateScene())
        return FALSE;

    if (FAILED(D3D.D3DRM->CreateViewport(	D3D.Device,
											D3D.Camera,						
											0, 0,
											D3D.Device->GetWidth(),
											D3D.Device->GetHeight(),
											&(D3D.View) )))        
        return FALSE;

    
    if (FAILED(D3D.View->SetBack(D3DVAL(15000.0))))
        return FALSE;
    
    return TRUE;
}

BOOL	CreateScene(void)
{
    if (FAILED(D3D.D3DRM->CreateFrame(NULL, &(D3D.Scene) )))
		return FALSE;
	
    if (FAILED(D3D.D3DRM->CreateFrame(D3D.Scene, &(D3D.Camera) )))
        return FALSE;

    if (FAILED(D3D.D3DRM->CreateFrame(D3D.Scene, &(D3D.Camera2) )))
        return FALSE;

	if (FAILED(D3D.D3DRM->CreateFrame(D3D.Scene, &(D3D.Camera3) )))
        return FALSE;

	if (!SetupSceneLights())
		return FALSE;

	if (!LoadBackground())
		return FALSE;

	Texture.power = 2; 
	Texture.su = 12.0F;
	Texture.sv = 12.0F;
	Texture.type = D3DRMWRAP_FLAT;

	if (!LoadObject(D3D.Scene, "HGrad_BW.bmp", "pole.x", 100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, FALSE))
		return FALSE;

	Texture.power = 24; // mat
	Texture.su = 8.0F;
	Texture.sv = 8.0F;
	Texture.type = D3DRMWRAP_FLAT;
	if (!LoadObject(D3D.Scene, "GROUNDGRASS.PPM", "land.x", 4000.0f, 4000.0f, 4000.0f, 0.0f, 0.0f, 0.0f, FALSE))
		return FALSE;

	if (FAILED(D3D.Camera->SetPosition(D3D.Scene, 0.0, 150.0, -500)))
		return FALSE;
	D3D.Camera->SetRotation(D3D.Scene, 0, 0, 0, 0);
	D3D.Camera->SetOrientation(D3D.Scene, 0,0,1, 0, 1, 0);

	if (FAILED(D3D.Camera2->SetPosition(D3D.Scene, 500.0, 100.0, 0.0)))
		return FALSE;
	D3D.Camera2->SetRotation(D3D.Scene, 0, 0, 0, 0);
	D3D.Camera2->SetOrientation(D3D.Scene, -1,0,0, 0, 1, 0);

	if (FAILED(D3D.Camera3->SetPosition(D3D.Scene, 0.0, 200.0, 0.0)))
		return FALSE;
	D3D.Camera3->SetRotation(D3D.Scene, 0, 0, 0, 0);
	D3D.Camera3->SetOrientation(D3D.Scene, 0,0,-1, 0, 1, 0);


    return TRUE;
}

BOOL	Render(void)
{

	D3D.Camera2->LookAt(D3D.Camera, D3D.Scene, D3DRMCONSTRAIN_Z);
	D3D.Camera3->LookAt(D3D.Camera, D3D.Scene, D3DRMCONSTRAIN_Z);


    if (FAILED(D3D.Scene->Move(D3DVAL(0.0))))
        return FALSE;

    if (FAILED(D3D.View->Clear()))
        return FALSE;

    if (FAILED(D3D.View->Render(D3D.Scene)))
        return FALSE;

    if (FAILED(D3D.Device->Update()))
        return FALSE;

    return TRUE;
}

void	CleanUp(void)
{
	RELEASE(D3D.Scene);
	RELEASE(D3D.Camera);
	RELEASE(D3D.Camera2);
	RELEASE(D3D.Camera3);
	RELEASE(D3D.View);
	RELEASE(D3D.Device);	
	RELEASE(D3D.D3DRM);
	RELEASE(D3D.DDClipper);
	RELEASE(ClothMesh);	
	RELEASE(ClothTex);
	RELEASE(ClothMat);
}

BOOL	SetupSceneLights(void)
{
	LPDIRECT3DRMMESHBUILDER	builder	= NULL;
	LPDIRECT3DRMLIGHT		light	= NULL;
	LPDIRECT3DRMFRAME		frame	= NULL;
	BOOL					retval	= TRUE;

	// create ambient light first
	if (FAILED(D3D.D3DRM->CreateMeshBuilder(&builder)))
		retval = FALSE;

	if (retval)
		if (FAILED(builder->SetQuality(D3DRMRENDER_GOURAUD)))
			retval = FALSE;
	
	if (retval)		
		if (FAILED(D3D.D3DRM->CreateLightRGB(	D3DRMLIGHT_AMBIENT, 
												D3DVAL(0.25), 
												D3DVAL(0.25), 
												D3DVAL(0.25), 
												&light) ))
			retval = FALSE;
	
	if (retval)		
		if (FAILED(D3D.D3DRM->CreateFrame(D3D.Scene, &frame)))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->SetPosition(D3D.Scene, D3DVAL(0.0), D3DVAL(1000.0), D3DVAL(0.0) )))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->AddVisual(builder) ))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->AddLight(light)))
			retval = FALSE;
	
	RELEASE(builder);
	RELEASE(frame);
	RELEASE(light);

	// now create directional light
	if (FAILED(D3D.D3DRM->CreateMeshBuilder(&builder)))
		retval = FALSE;

	if (retval)
		if (FAILED(builder->SetQuality(D3DRMRENDER_GOURAUD)))
			retval = FALSE;
	
	if (retval)		
		if (FAILED(D3D.D3DRM->CreateLightRGB(	D3DRMLIGHT_DIRECTIONAL, 
												D3DVAL(0.5), 
												D3DVAL(0.5), 
												D3DVAL(0.5), 
												&light) ))
			retval = FALSE;
	
	if (retval)		
		if (FAILED(D3D.D3DRM->CreateFrame(D3D.Scene, &frame)))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->SetOrientation(D3D.Scene, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0)))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->AddVisual(builder) ))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->AddLight(light)))
			retval = FALSE;
	
	RELEASE(builder);
	RELEASE(frame);
	RELEASE(light);


	// now create spot light
	if (FAILED(D3D.D3DRM->CreateMeshBuilder(&builder)))
		retval = FALSE;

	if (retval)
		if (FAILED(builder->SetQuality(D3DRMRENDER_GOURAUD)))
			retval = FALSE;
	
	if (retval)		
		if (FAILED(D3D.D3DRM->CreateLightRGB(	D3DRMLIGHT_POINT, 
												D3DVAL(0.5), 
												D3DVAL(1.0), 
												D3DVAL(0.5), 
												&light) ))
			retval = FALSE;
	
	if (retval)		
		if (FAILED(D3D.D3DRM->CreateFrame(D3D.Scene, &frame)))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->SetPosition(D3D.Scene, 200, 200, -200 )))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->AddVisual(builder) ))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->AddLight(light)))
			retval = FALSE;
	
	RELEASE(builder);
	RELEASE(frame);
	RELEASE(light);


	return retval;
}

BOOL	LoadBackground(void)
{
	LPDIRECT3DRMTEXTURE		tex;
	BOOL					retval = true;
	
	D3D.D3DRM->LoadTexture("clouds.ppm", &tex);

	if (FAILED(D3D.Scene->SetSceneBackgroundImage(tex) ))
		retval =  FALSE;

	RELEASE(tex);

	return retval;
}

BOOL	LoadObject(LPDIRECT3DRMFRAME		fr, char *ftex, char *fname, float sx, float sy, float sz, float x, float y, float z, BOOL makechild)
{
	LPDIRECT3DRMMESHBUILDER	builder;
	LPDIRECT3DRMFRAME		frame;
	BOOL					retval = true;
	LPDIRECT3DRMTEXTURE		tex = 0;
	LPDIRECT3DRMMATERIAL	mat = NULL;
	LPDIRECT3DRMWRAP		wrap = NULL;
	LPDIRECT3DRMMESH        mesh = 0;
	

	
	if (D3D.D3DRM->LoadTexture (ftex, &tex) == D3DRM_OK)
	{
		D3D.D3DRM->CreateMaterial(Texture.power, &mat);
	}
	
	if (FAILED(D3D.D3DRM->CreateMeshBuilder(&builder)))
		retval = FALSE;

	if (retval)
		if (FAILED(builder->SetQuality(D3DRMRENDER_GOURAUD)))
			retval = FALSE;

	if (retval)
		if (builder->Load(fname, NULL, D3DRMLOAD_FROMFILE, (D3DRMLOADTEXTURECALLBACK) LoadTexture, NULL) != D3DRM_OK)
			retval = FALSE;

	if (retval)
		if(FAILED(D3D.D3DRM->CreateFrame(fr, &frame)))
			retval = FALSE;

	if (FAILED(builder->CreateMesh(&mesh)))
		return FALSE;

	if (FAILED(mesh->SetGroupTexture (D3DRMGROUP_ALLGROUPS, tex)))
		retval = FALSE;

	if (FAILED(mesh->SetGroupMaterial (D3DRMGROUP_ALLGROUPS, mat)))
		retval = FALSE;

	if (FAILED(builder->SetColorRGB (D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0))))
		retval = FALSE;

	if (FAILED(D3D.D3DRM->CreateWrap (Texture.type, NULL,
			                          D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
					                  D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
							          D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
									  D3DVAL(0.0), D3DVAL (0.0),
		                              D3DVAL(Texture.su), D3DVAL (Texture.sv),
				                      &wrap)))
		retval = FALSE;

	if (FAILED(wrap->Apply ((LPDIRECT3DRMOBJECT)mesh)))
		retval = FALSE;

	if (retval)
		if(FAILED(frame->AddVisual(mesh)))
			retval = FALSE;

	if (retval)
		mesh->Scale(sx, sy, sz);

	if (retval)
		if(FAILED(frame->SetPosition(fr, x, y, z)))
			retval = FALSE;

	if (retval && makechild)
	{
		if(FAILED(fr->AddChild(frame)))
			retval = FALSE;
		else
		{
			D3DVECTOR dir, up;

			GetCameraDirectionAndUp(&dir, &up);
			frame->SetOrientation(D3D.Scene, -dir.x, -dir.y, -dir.z, up.x, up.y, up.z);
		}
	}		

	RELEASE(frame);
	RELEASE(builder);
	RELEASE(wrap);
	RELEASE(mesh);

	return retval;
}

HRESULT		LoadTexture(char *name, void *arg, LPDIRECT3DRMTEXTURE *tex)
{
	return D3D.D3DRM->LoadTexture(name, tex);
}

BOOL	CreateCloth(char *ftex, unsigned int *faces, int faceCount, float *vertices, int vertexCount, BOOL makechild)
{
	LPDIRECT3DRMMESHBUILDER	builder;
	LPDIRECT3DRMFRAME		frame;
	BOOL					retval = true;
	//LPDIRECT3DRMTEXTURE		tex = 0;
	//LPDIRECT3DRMMATERIAL	mat = NULL;
	LPDIRECT3DRMWRAP		wrap = NULL;	

	D3DRMVERTEX				d3dVertices[NUMVERTICES*2]; // TODO: dynamically allocate this....
	int						i;
	LPDIRECT3DRMFRAME		fr = D3D.Scene;
	float					*v;
	Vector					e1, e2, n;
	int						v1, v2, v3;
	unsigned int			*f;
	Vector					normals[NUMVERTICES*2];

	D3DRMBOX				box;
	D3DVALUE				w,h;


	Texture.power = 50; 
	Texture.su = 1.0F;
	Texture.sv = 1.0F;
	Texture.type = D3DRMWRAP_FLAT;
	
	if (D3D.D3DRM->LoadTexture (ftex, &ClothTex) == D3DRM_OK)
	{
		D3D.D3DRM->CreateMaterial(Texture.power, &ClothMat);
	} else
		retval = false;
	
//	if (FAILED(D3D.D3DRM->CreateMeshBuilder(&builder)))
//		retval = FALSE;

//	if (retval)
//		if (FAILED(builder->SetQuality(D3DRMRENDER_GOURAUD)))
//			retval = FALSE;

	if (retval)
		if(FAILED(D3D.D3DRM->CreateFrame(fr, &frame)))
			retval = FALSE;

	if (FAILED(D3D.D3DRM/*builder*/->CreateMesh(&ClothMesh))) // global variable for storing the cloth's mesh...
		return FALSE;

	if(retval)
		if(FAILED(ClothMesh->AddGroup(vertexCount, faceCount, 3, faces, &ClothGroup)))
			retval = FALSE;

	v = vertices;
	for(i=0; i<NUMVERTICES*2; i++)
	{		
		d3dVertices[i].position.x = *v; v++;
		d3dVertices[i].position.y = *v; v++;
		d3dVertices[i].position.z = *v; v++;

		d3dVertices[i].normal.x = 0;
		d3dVertices[i].normal.y = 0;
		d3dVertices[i].normal.z = 0;

		d3dVertices[i].tu = d3dVertices[i].position.x;
		d3dVertices[i].tv = d3dVertices[i].position.y;
	}

	
	f = faces;
	for(i=0; i<faceCount; i++)
	{
		v1 = *f; f++;
		v2 = *f; f++;
		v3 = *f; f++;

		e1.x = d3dVertices[v2].position.x - d3dVertices[v1].position.x;
		e1.y = d3dVertices[v2].position.y - d3dVertices[v1].position.y;
		e1.z = d3dVertices[v2].position.z - d3dVertices[v1].position.z;

		e2.x = d3dVertices[v3].position.x - d3dVertices[v1].position.x;
		e2.y = d3dVertices[v3].position.y - d3dVertices[v1].position.y;
		e2.z = d3dVertices[v3].position.z - d3dVertices[v1].position.z;
		
		n = e1^e2;
		
		normals[v1] += n;
		normals[v2] += n;
		normals[v3] += n;
	}

	for(i=0; i<vertexCount; i++)
	{
		normals[i].Normalize();

		d3dVertices[i].normal.x = normals[i].x;
		d3dVertices[i].normal.y = normals[i].y;
		d3dVertices[i].normal.z = normals[i].z;
	}
		
	if(retval)
		if(FAILED(ClothMesh->SetVertices(ClothGroup, 0, vertexCount, d3dVertices)))
			retval = FALSE;

	if(retval)
		if(FAILED(ClothMesh->SetGroupQuality(ClothGroup, D3DRMRENDER_GOURAUD)))
			retval = FALSE;

	if(retval)
		if(FAILED(ClothMesh->SetGroupColorRGB(ClothGroup, 1.0f, 0.0f, 0.0f))) //0.19f, 0.39f, 0.61f)))
			retval = FALSE;		

	if (FAILED(ClothMesh->SetGroupMapping (ClothGroup, Texture.type)))
		retval = FALSE;

	if (FAILED(ClothMesh->SetGroupMaterial (ClothGroup, ClothMat)))
		retval = FALSE;

	

/*	if (FAILED(ClothMesh->SetGroupTexture (ClothGroup, ClothTex)))
		retval = FALSE;

	ClothMesh->GetBox( &box );
	BoxW = w = box.max.x-box.min.x;
	BoxH = h = box.max.y-box.min.y;
	if (FAILED(D3D.D3DRM->CreateWrap (Texture.type, NULL,
			                          D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
					                  D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
							          D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
									  D3DVAL(1.0), D3DVAL (1.0),
		                              //D3DVAL(Texture.su), D3DVAL (Texture.sv),
									  D3DDivide(1,w), D3DDivide(1,h),
				                      &wrap)))
		retval = FALSE;


	if (FAILED(wrap->Apply ((LPDIRECT3DRMOBJECT)ClothMesh)))
		retval = FALSE;
*/
	if (retval)
		if(FAILED(frame->AddVisual(ClothMesh)))
			retval = FALSE;

	//if (retval)
	//	mesh->Scale(sx, sy, sz);

	if (retval)
		if(FAILED(frame->SetPosition(fr, 0, 0, 0)))
			retval = FALSE;

	if (retval && makechild)
	{
		if(FAILED(fr->AddChild(frame)))
			retval = FALSE;
		else
		{
			D3DVECTOR dir, up;

			GetCameraDirectionAndUp(&dir, &up);
			frame->SetOrientation(D3D.Scene, -dir.x, -dir.y, -dir.z, up.x, up.y, up.z);
		}
	}		

	RELEASE(frame);
	//RELEASE(builder);
//	RELEASE(wrap);
	

	return retval;
}

void	UpdateCloth(unsigned int *faces, int faceCount, float *vertices, int vertexCount)
{

	LPDIRECT3DRMWRAP		wrap = NULL;	

	D3DRMVERTEX				d3dVertices[NUMVERTICES*2]; // TODO: dynamically allocate this....
	int						i;	
	float					*v;
	Vector					e1, e2, n;
	int						v1, v2, v3;
	unsigned int			*f;
	Vector					normals[NUMVERTICES*2];

	BOOL					retval = true;

	float					tu,tv,m;
	D3DRMBOX				box;
	D3DVALUE				w,h;

	Texture.power = 50; 
	Texture.su = 1.0F;
	Texture.sv = 1.0F;
	Texture.type = D3DRMWRAP_FLAT;

	v = vertices;
	for(i=0; i<NUMVERTICES*2; i++)
	{		
		d3dVertices[i].position.x = *v; v++;
		d3dVertices[i].position.y = *v; v++;
		d3dVertices[i].position.z = *v; v++;

		d3dVertices[i].normal.x = 0;
		d3dVertices[i].normal.y = 0;
		d3dVertices[i].normal.z = 0;
	}

	
	f = faces;
	for(i=0; i<faceCount; i++)
	{
		v1 = *f; f++;
		v2 = *f; f++;
		v3 = *f; f++;

		e1.x = d3dVertices[v2].position.x - d3dVertices[v1].position.x;
		e1.y = d3dVertices[v2].position.y - d3dVertices[v1].position.y;
		e1.z = d3dVertices[v2].position.z - d3dVertices[v1].position.z;

		e2.x = d3dVertices[v3].position.x - d3dVertices[v1].position.x;
		e2.y = d3dVertices[v3].position.y - d3dVertices[v1].position.y;
		e2.z = d3dVertices[v3].position.z - d3dVertices[v1].position.z;
		
		n = e1^e2;
		
		normals[v1] += n;
		normals[v2] += n;
		normals[v3] += n;
	}

	for(i=0; i<vertexCount; i++)
	{
		normals[i].Normalize();

		d3dVertices[i].normal.x = normals[i].x;
		d3dVertices[i].normal.y = normals[i].y;
		d3dVertices[i].normal.z = normals[i].z;
	}
		
	ClothMesh->SetVertices(ClothGroup, 0, vertexCount, d3dVertices);

	if (FAILED(ClothMesh->SetGroupMapping (ClothGroup, Texture.type)))
		retval = FALSE;

	if (FAILED(ClothMesh->SetGroupMaterial (ClothGroup, ClothMat)))
		retval = FALSE;
	
/*	if (FAILED(ClothMesh->SetGroupTexture (ClothGroup, ClothTex)))
		retval = FALSE;

	ClothMesh->GetBox( &box );
	w = box.max.x-box.min.x;
	h = box.max.y-box.min.y;
	if (FAILED(D3D.D3DRM->CreateWrap (Texture.type, NULL,
			                          D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
					                  D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
							          D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
									  D3DVAL(1.0), D3DVAL (1.0),
		                              //D3DVAL(Texture.su), D3DVAL (Texture.sv),
									  D3DDivide(1,w), D3DDivide(1,h),
				                      &wrap)))
		retval = FALSE;

	if (FAILED(wrap->Apply ((LPDIRECT3DRMOBJECT)ClothMesh)))
		retval = FALSE;

	RELEASE(wrap);
*/
}

void	MoveCamera(float d)
{	
	D3DVECTOR	vpos;
	D3DVECTOR	vdir;
	D3DVECTOR	vup;	

	GetCameraPosition(&vpos);

	GetCameraDirectionAndUp(&vdir, &vup);

	// normalize direction
	NormalizeVector(&vdir);

	// calculate new movement vector;
	vdir.x *= d;
	vdir.y *= d;
	vdir.z *= d;	

	vpos.x += vdir.x;
	vpos.y += vdir.y;
	vpos.z += vdir.z;
	
	// set new position
	D3D.Camera->SetPosition(D3D.Scene, vpos.x, vpos.y, vpos.z);

	return;
}

void	StraifCamera(float d)
{
	D3DVECTOR	ux, uy, uz, vpos;
	
	GetCameraUnitVectors(&ux, &uy, &uz);
	GetCameraPosition(&vpos);
	ux.x *= d;
	ux.y *= d;
	ux.z *= d;

	vpos.x += ux.x;
	vpos.y += ux.y;
	vpos.z += ux.z;

	D3D.Camera->SetPosition(D3D.Scene, vpos.x, vpos.y, vpos.z);
}

void	GetCameraDirectionAndUp(D3DVECTOR* dir, D3DVECTOR* up)
{
	D3D.Camera->GetOrientation(D3D.Scene, dir, up);
	return;
}

void	GetCameraPosition(D3DVECTOR* pos)
{
	D3D.Camera->GetPosition(D3D.Scene, pos);
	return;
}

void	GetCameraUnitVectors(D3DVECTOR* vx, D3DVECTOR* vy, D3DVECTOR* vz)
{
	GetCameraDirectionAndUp(vz, vy);

	D3DRMVectorCrossProduct(vx, vy, vz);

	NormalizeVector(vx);
	NormalizeVector(vy);
	NormalizeVector(vz);
}

void	NormalizeVector(D3DVECTOR* v)
{
	float		mag;

	mag = (float) sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
	if (mag == 0) mag = 1;
	v->x /= mag;
	v->y /= mag;
	v->z /= mag;

	return;
}

void	YawCameraBy(float ar)
{
	// temporary
	D3DVECTOR	ux, uy, uz;

	GetCameraUnitVectors(&ux, &uy, &uz);
	D3D.Camera->SetRotation(D3D.Scene, uy.x, uy.y, uy.z, ar);
	D3D.D3DRM->Tick(0.1);
	
	return;

}

void	PitchCameraBy(float ar)
{
	// temporary
	D3DVECTOR	ux, uy, uz;

	GetCameraUnitVectors(&ux, &uy, &uz);
	D3D.Camera->SetRotation(D3D.Scene, ux.x, ux.y, ux.z, ar);
	return;

}

void	RollCameraBy(float ar)
{
	// temporary
	D3DVECTOR	ux, uy, uz;

	GetCameraUnitVectors(&ux, &uy, &uz);
	D3D.Camera->SetRotation(D3D.Scene, uz.x, uz.y, uz.z, ar);
	return;

}

void	SetCameraOrientation(float dx, float dy, float dz, float ux, float uy, float uz)
{
	D3D.Camera->SetOrientation(D3D.Scene, dx, dy, dz, ux, uy, uz);
	return;
}


void	SetCameraPosition(float x, float y, float z)
{		
	D3D.Camera->SetPosition(D3D.Scene, x, y, z);
	//D3D.Camera2->SetPosition(D3D.Scene, x, y+100, z-300);

	return;
}

void	SetCamera1(void)
{
	D3D.View->SetCamera(D3D.Camera);
}

void	SetCamera2(void)
{
	D3D.View->SetCamera(D3D.Camera2);
}

void	SetCamera3(void)
{
	D3D.View->SetCamera(D3D.Camera3);
}

