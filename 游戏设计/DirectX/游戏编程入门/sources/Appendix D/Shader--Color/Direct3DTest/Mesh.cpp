// Standalone Mesh class (no dependencies)

#include "Mesh.h"
using namespace std;

bool DoesFileExist(const std::string &filename)
{
	return (_access(filename.c_str(), 0) != -1);
}

void SplitPath(const std::string& inputPath, std::string* pathOnly, std::string* filenameOnly)
{
	std::string fullPath(inputPath);
	std::replace(fullPath.begin(),fullPath.end(),'\\','/');

	std::string::size_type lastSlashPos=fullPath.find_last_of('/');

	// check for there being no path element in the input
	if (lastSlashPos==std::string::npos)
	{
		*pathOnly="";
		*filenameOnly=fullPath;
	}
	else // do the split
	{
		if (pathOnly)
			*pathOnly=fullPath.substr(0,lastSlashPos);

		if (filenameOnly)
			*filenameOnly=fullPath.substr(lastSlashPos+1,fullPath.size()-lastSlashPos-1);
	}
}


bool FindFile(std::string *filename)
{
	if (!filename)
		return false;

	// Look for it first using the original filename and path
	if (DoesFileExist(*filename))
		return true;

	// Next try with stripping the path from it
	std::string pathOnly;
	std::string filenameOnly;
	SplitPath(*filename,&pathOnly,&filenameOnly);

	if (DoesFileExist(filenameOnly))
	{
		*filename=filenameOnly;
		return true;
	}

	// Could now try by looking in a specific data folder....
	return false;
}


Mesh::Mesh(LPDIRECT3DDEVICE9 dev)
{
	device = dev;
	mesh = 0;
	materials = 0;
    d3dxMaterials = 0;
    matbuffer = 0;
    material_count = 0;
	textures = 0;
	position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	velocity = D3DXVECTOR3(0.0f,0.0f,0.0f);
	rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	scale =	   D3DXVECTOR3(1.0f,1.0f,1.0f);
}

Mesh::~Mesh(void)
{
    if (materials != NULL) delete[] materials;

    //remove textures from memory
    if (textures != NULL) {
        for( DWORD i = 0; i < material_count; i++)
        {
            if (textures[i] != NULL)
                textures[i]->Release();
        }
        delete[] textures;
    }
    
    if (mesh != NULL) mesh->Release();

}

int Mesh::GetFaceCount()
{
	return this->mesh->GetNumFaces();
}

int Mesh::GetVertexCount()
{
	return this->mesh->GetNumVertices();
}


bool Mesh::Load(char* filename)
{
    HRESULT result;

    //load mesh from the specified file
    result = D3DXLoadMeshFromX( filename, D3DXMESH_SYSTEMMEM, device, NULL, &matbuffer, NULL, &material_count, &mesh);          		
    if (result != D3D_OK)  {
        return false;
    }

    //extract material properties and texture names from material buffer
    d3dxMaterials = (LPD3DXMATERIAL)matbuffer->GetBufferPointer();
    materials = new D3DMATERIAL9[material_count];
    textures  = new LPDIRECT3DTEXTURE9[material_count];

    //create the materials and textures
    for(DWORD i=0; i < material_count; i++)
    {
        //grab the material
        materials[i] = d3dxMaterials[i].MatD3D;

        //set ambient color for material 
        materials[i].Ambient = materials[i].Diffuse;
        //materials[i].Emissive = materials[i].Diffuse;
        materials[i].Power = 0.5f;
        //materials[i].Specular = materials[i].Diffuse;

        //load texture file if specified
        textures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL) 
		{
			string filename = d3dxMaterials[i].pTextureFilename;
			if( FindFile(&filename) )
			{
				result = D3DXCreateTextureFromFile(device, filename.c_str(), &textures[i]);
				if (result != D3D_OK) return false;
			}
		}
    }

    //done using material buffer
    matbuffer->Release();

	return true;
}


void Mesh::CreateSphere(double radius, int slices, int stacks)
{
	D3DXCreateSphere(device, (float)radius, slices, stacks, &mesh, NULL);
}

void Mesh::CreateCube(double width, double height, double depth)
{
	D3DXCreateBox(device, (float)width, (float)height, (float)depth, &mesh, NULL);
}

void Mesh::Draw()
{
	Transform();

	if (material_count == 0) {
		mesh->DrawSubset(0);
	}
	else {
		//draw each mesh subset
		for( DWORD i=0; i < material_count; i++ )
		{
			// Set the material and texture for this subset
			device->SetMaterial( &materials[i] );

			if (textures[i]) 
			{
				if (textures[i]->GetType() == D3DRTYPE_TEXTURE) 
				{
					D3DSURFACE_DESC desc;
					textures[i]->GetLevelDesc(0, &desc);
					if (desc.Width > 0) {
						device->SetTexture( 0, textures[i] );
					}
				}
			}
			
			// Draw the mesh subset
			mesh->DrawSubset( i );
		}
	}
}

void Mesh::Transform()
{
	double x = D3DXToRadian(rotation.x);
	double y = D3DXToRadian(rotation.y);
	double z = D3DXToRadian(rotation.z);


	//transform the mesh
	D3DXMatrixRotationYawPitchRoll(&matRotate, (float)x, (float)y, (float)z);
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
    D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);

	//apply transforms
	matWorld = matRotate * matScale * matTranslate;
    device->SetTransform(D3DTS_WORLD, &matWorld);
}

void Mesh::Rotate(D3DXVECTOR3 rot)
{
	Rotate(rot.x,rot.y,rot.z);
}

void Mesh::Rotate(double x,double y,double z)
{
	rotation.x += (float)x;
	rotation.y += (float)y;
	rotation.z += (float)z;
}

