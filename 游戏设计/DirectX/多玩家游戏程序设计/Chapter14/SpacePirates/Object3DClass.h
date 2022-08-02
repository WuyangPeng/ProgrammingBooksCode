#include <d3dx8.h>
#include <stdio.h>
#include "dxutil.h"
#define RADIAN_TO_DEGREES 57.29577951308232286465f

class Object3DClass
{
	private:
		
	public:
		LPD3DXMESH			pMesh;
		D3DMATERIAL8		*pMeshMaterials;
		LPDIRECT3DTEXTURE8	*pMeshTextures;
		DWORD				dwNumMaterials;
		LPD3DXBUFFER		pD3DXMtrlBuffer;
		LPDIRECT3DDEVICE8	pd3dDevice;

		Object3DClass(void);
		~Object3DClass(void);

		HRESULT hLoad(char *szName,LPDIRECT3DDEVICE8 p3d);
		void vCleanup(void);
		void vDisplayXYZ(float x, float y, float z, float rx=0.0f, float ry=0.0f, float rz=0.0f);
};
