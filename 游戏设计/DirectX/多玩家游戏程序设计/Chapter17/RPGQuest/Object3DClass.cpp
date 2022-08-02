#include "Object3DClass.h"

// Constructor
Object3DClass::Object3DClass(void)
{
	pMesh = NULL;	
	pMeshMaterials = NULL;
	pMeshTextures = NULL;
	pD3DXMtrlBuffer = NULL;
	pd3dDevice = NULL;
}

// Destructor
Object3DClass::~Object3DClass(void)
{
	vCleanup();
}

//-----------------------------------------------------------------------------
// Name: Object3DClass::hLoad()
// Desc: Loads 3D data for the materials, geometry, and textures 
//-----------------------------------------------------------------------------
HRESULT Object3DClass::hLoad(char *szName,LPDIRECT3DDEVICE8 p3d)
{
	HRESULT			hResult = S_OK;
	int				i;
	char			szFullPath[256];
	D3DXMATERIAL*	d3dxMaterials;

	// Set the IDirect3DDevice8 pointer to the internal one
	pd3dDevice = p3d;
	// Initialize number of materials to zero
	dwNumMaterials = 0;
	// Load Login Geometry
	if( FAILED( D3DXLoadMeshFromX( 
		szName, 
		D3DXMESH_SYSTEMMEM, 
		pd3dDevice, 
		NULL, 
		&pD3DXMtrlBuffer, 
		&dwNumMaterials, 
		&pMesh ) ) ) {
		return(-1);
	}
	// Set temp pointer for easier to read code
	d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	// Create the materials and textures
	pMeshMaterials = new D3DMATERIAL8[dwNumMaterials];
	pMeshTextures = new LPDIRECT3DTEXTURE8[dwNumMaterials];
	// Load in material information and textures
	for( i = 0; i < (signed)dwNumMaterials ; i++ ) {
		// Copy the material
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		// Set the ambient color for the material (D3DX does not do this)
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
		sprintf(szFullPath,"Data//3DObjects//%s",d3dxMaterials[i].pTextureFilename);
		// If the texture did not load, set it to NULL
		if( FAILED( D3DXCreateTextureFromFile( 
			pd3dDevice,
			szFullPath,
			&pMeshTextures[i] ) ) ) {
			// Delete the texture from memory
			delete pMeshTextures[i];
			pMeshTextures[i] = NULL;
		}
	}
	SAFE_RELEASE(pD3DXMtrlBuffer);

	return( hResult );
}

//-----------------------------------------------------------------------------
// Name: Object3DClass::vDisplayXYZ()
// Desc: Displays the 3D object at given cordinates and rotation 
//-----------------------------------------------------------------------------
void Object3DClass::vDisplayXYZ(float x, float y, float z, float rx, float ry, float rz)
{
	D3DXMATRIX	matWorld,matRotation,matTranslation,matScale;
	int			mat;
	
	// Set default translation
	D3DXMatrixIdentity( &matTranslation );
	// Rotate on X
	D3DXMatrixRotationX( &matRotation, rx/RADIAN_TO_DEGREES );
	D3DXMatrixMultiply(&matTranslation,&matRotation,&matTranslation);
	// Rotate on Y
	D3DXMatrixRotationY( &matRotation, ry/RADIAN_TO_DEGREES );
	D3DXMatrixMultiply(&matTranslation,&matRotation,&matTranslation);
	// Rotate on Z
	D3DXMatrixRotationZ( &matRotation, rz/RADIAN_TO_DEGREES );
	D3DXMatrixMultiply(&matTranslation,&matRotation,&matTranslation);
	// Move to X,Y,Z coordinates
	matTranslation._41 = x;
	matTranslation._42 = y;
	matTranslation._43 = z;
	// Set the matrix
	pd3dDevice->SetTransform( D3DTS_WORLD, &matTranslation );

	// Display each material
	for( mat = 0 ; mat < (signed)dwNumMaterials ; mat++ ) {
		pd3dDevice->SetMaterial( &pMeshMaterials[mat] );
		// Activate the appropriate texture
		pd3dDevice->SetTexture( 0, pMeshTextures[mat] );
		// Draw the mesh subset
		pMesh->DrawSubset( mat );
		// Turn off the texture
		pd3dDevice->SetTexture( 0, NULL );
	}
}

//-----------------------------------------------------------------------------
// Name: Object3DClass::vCleanup()
// Desc: Releases all memory associated with the object
//-----------------------------------------------------------------------------
void Object3DClass::vCleanup(void)
{
	SAFE_RELEASE(pMesh);
	SAFE_DELETE_ARRAY(pMeshMaterials)
	SAFE_DELETE_ARRAY(pMeshTextures);
	SAFE_RELEASE(pD3DXMtrlBuffer);
}
