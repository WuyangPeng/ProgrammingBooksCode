#include "d3dstuff.h"

d3dInfo	D3D;
LPDIRECT3DRMWINDEVICE WinDev;
texInfo	Texture;


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

	Texture.power = 16.0F; 
	Texture.su = 1.0F;
	Texture.sv = 1.0F;
	Texture.type = D3DRMWRAP_SPHERE;

	if (!LoadObject(D3D.Scene, "test.bmp", "sphere2.x", 100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, FALSE))
		return FALSE;

	if (!LoadObject(D3D.Scene, "test.bmp","sphere2.x", 100.0f, 100.0f, 100.0f, 0.0f, 100.0f, 500.0f, FALSE))
		return FALSE;

	if (!LoadObject(D3D.Scene, "test.bmp","sphere2.x", 100.0f, 100.0f, 100.0f, 500.0f, 100.0f, 0.0f, FALSE))
		return FALSE;

	if (!LoadObject(D3D.Scene, "test.bmp","sphere2.x", 100.0f, 100.0f, 100.0f, -500.0f, 100.0f, -500.0f, FALSE))
		return FALSE;

	if (!LoadObject(D3D.Scene, "test.bmp", "sphere2.x", 100.0f, 100.0f, 100.0f, 0.0f, 1000.0f, 500.0f, FALSE))
		return FALSE;

	if (!LoadObject(D3D.Scene, "test.bmp", "sphere2.x", 100.0f, 100.0f, 100.0f, 5000.0f, 300.0f, 5000.0f, FALSE))
		return FALSE;

	if (!LoadObject(D3D.Scene, "test.bmp", "sphere2.x", 100.0f, 100.0f, 100.0f, -5000.0f, 300.0f, 5000.0f, FALSE))
		return FALSE;

	if (!LoadObject(D3D.Scene, "test.bmp", "sphere2.x", 100.0f, 100.0f, 100.0f, 5000.0f, 300.0f, -5000.0f, FALSE))
		return FALSE;

	if (!LoadObject(D3D.Scene, "test.bmp", "sphere2.x", 100.0f, 100.0f, 100.0f, -5000.0f, 300.0f, -5000.0f, FALSE))
		return FALSE;
	
	Texture.power = 24; // mat
	Texture.su = 8.0F;
	Texture.sv = 8.0F;
	Texture.type = D3DRMWRAP_FLAT;
	if (!LoadObject(D3D.Scene, "GROUNDGRASS.PPM", "land4.x", 20000.0f, 5000.0f, 20000.0f, 0.0f, -100.0f, 0.0f, FALSE))
		return FALSE;

	Texture.power = 2; // metallic
	Texture.su = 1.0F;
	Texture.sv = 1.0F;
	if (!LoadObject(D3D.Camera, NULL, "plane2.x", 20.0f, 20.0f, 20.0f, 0.0f, -10.0f, 0.0f, TRUE))//-10,100
		return FALSE;//"STEELPNL.PPM"

	if (FAILED(D3D.Camera->SetPosition(D3D.Scene, 0.0, 0.0, -200)))
		return FALSE;
	D3D.Camera->SetRotation(D3D.Scene, 0, 0, 0, 0);

	if (FAILED(D3D.Camera2->SetPosition(D3D.Scene, 0.0, 500.0, 0.0)))
		return FALSE;
	D3D.Camera2->SetRotation(D3D.Scene, 0, 0, 0, 0);
	D3D.Camera2->SetOrientation(D3D.Scene, 0,0,-1, 0, 1, 0);

	if (FAILED(D3D.Camera3->SetPosition(D3D.Scene, 0.0, 2000.0, 0.0)))
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
												D3DVAL(0.5), 
												D3DVAL(0.5), 
												D3DVAL(0.5), 
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
												D3DVAL(1.0), 
												D3DVAL(0.75), 
												D3DVAL(0.75), 
												&light) ))
			retval = FALSE;
	
	if (retval)		
		if (FAILED(D3D.D3DRM->CreateFrame(D3D.Scene, &frame)))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->SetPosition(D3D.Scene, D3DVAL(100.0), D3DVAL(200.0), D3DVAL(0.0) )))
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
		if (FAILED(D3D.D3DRM->CreateLightRGB(	D3DRMLIGHT_POINT, 
												D3DVAL(1.0), 
												D3DVAL(0.75), 
												D3DVAL(0.75), 
												&light) ))
			retval = FALSE;
	
	if (retval)		
		if (FAILED(D3D.D3DRM->CreateFrame(D3D.Scene, &frame)))
			retval = FALSE;

	if (retval)		
		if (FAILED(frame->SetPosition(D3D.Scene, D3DVAL(100.0), D3DVAL(700.0), D3DVAL(1000.0) )))
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

BOOL	LoadObject(LPDIRECT3DRMFRAME fr, char *ftex, char *fname, float sx, float sy, float sz, float x, float y, float z, BOOL makechild)
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
	D3D.Camera2->SetPosition(D3D.Scene, x, y+100, z-300);

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
