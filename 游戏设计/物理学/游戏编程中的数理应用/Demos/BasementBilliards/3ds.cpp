
#include "3ds.h"


//	This constructor initializes the tChunk data
CLoad3DS::CLoad3DS()
{
	m_CurrentChunk = new tChunk;				// Initialize and allocate our current chunk
	m_TempChunk = new tChunk;					// Initialize and allocate a temporary chunk
}

//	This is called by the client to open the .3ds file, read it, then clean up
bool CLoad3DS::Import3DS(t3DModel *pModel, char *strFileName)
{
	char strMessage[255] = {0};

	// Open the 3DS file
	m_FilePointer = fopen(strFileName, "rb");

	// Make sure we have a valid file pointer (we found the file)
	if(!m_FilePointer) 
	{
		sprintf(strMessage, "Unable to find the file: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}


	// Read the first chuck of the file to see if it's a 3DS file
	ReadChunk(m_CurrentChunk);

	// Make sure this is a 3DS file
	if (m_CurrentChunk->ID != PRIMARY)
	{
		sprintf(strMessage, "Unable to load PRIMARY chuck from file: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	// Now we actually start reading in the data.  ProcessNextChunk() is recursive

	// Begin loading objects, by calling this recursive function
	ProcessNextChunk(pModel, m_CurrentChunk);

	// After we have read the whole 3DS file, we want to calculate our own vertex normals.
	ComputeNormals(pModel);

	// Clean up after everything
	CleanUp();

	return true;
}

//	This function cleans up our allocated memory and closes the file
void CLoad3DS::CleanUp()
{
	fclose(m_FilePointer);						// Close the current file pointer
	delete m_CurrentChunk;						// Free the current chunk
	delete m_TempChunk;							// Free our temporary chunk
}


//	This function reads the main sections of the .3DS file, then dives deeper with recursion
void CLoad3DS::ProcessNextChunk(t3DModel *pModel, tChunk *pPreviousChunk)
{
	t3DObject newObject = {0};					// This is used to add to our object list
	tMaterialInfo newTexture = {0};				// This is used to add to our material list
	unsigned int version = 0;					// This will hold the file version
	int buffer[50000] = {0};					// This is used to read past unwanted data

	m_CurrentChunk = new tChunk;				// Allocate a new chunk				


	// Continue to read the sub chunks until we have reached the length.
	// After we read ANYTHING we add the bytes read to the chunk and then check
	// check against the length.
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// Read next Chunk
		ReadChunk(m_CurrentChunk);

		// Check the chunk ID
		switch (m_CurrentChunk->ID)
		{
		case VERSION:							// This holds the version of the file
			
			// This chunk has an unsigned short that holds the file version.
			// Since there might be new additions to the 3DS file format in 4.0,
			// we give a warning to that problem.

			// Read the file version and add the bytes read to our bytesRead variable
			m_CurrentChunk->bytesRead += fread(&version, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);

			// If the file version is over 3, give a warning that there could be a problem
			if (version > 0x03)
				MessageBox(NULL, "This 3DS file is over version 3 so it may load incorrectly", "Warning", MB_OK);
			break;

		case OBJECTINFO:						// This holds the version of the mesh
			
			// This chunk holds the version of the mesh.  It is also the head of the MATERIAL
			// and OBJECT chunks.  From here on we start reading in the material and object info.

			// Read the next chunk
			ReadChunk(m_TempChunk);

			// Get the version of the mesh
			m_TempChunk->bytesRead += fread(&version, 1, m_TempChunk->length - m_TempChunk->bytesRead, m_FilePointer);

			// Increase the bytesRead by the bytes read from the last chunk
			m_CurrentChunk->bytesRead += m_TempChunk->bytesRead;

			// Go to the next chunk, which is the object has a texture, it should be MATERIAL, then OBJECT.
			ProcessNextChunk(pModel, m_CurrentChunk);
			break;

		case MATERIAL:							// This holds the material information

			// This chunk is the header for the material info chunks

			// Increase the number of materials
			pModel->numOfMaterials++;

			// Add a empty texture structure to our texture list.
			// If you are unfamiliar with STL's "vector" class, all push_back()
			// does is add a new node onto the list.  I used the vector class
			// so I didn't need to write my own link list functions.  
			pModel->pMaterials.push_back(newTexture);

			// Proceed to the material loading function
			ProcessNextMaterialChunk(pModel, m_CurrentChunk);
			break;

		case OBJECT:							// This holds the name of the object being read
				
			// This chunk is the header for the object info chunks.  It also
			// holds the name of the object.

			// Increase the object count
			pModel->numOfObjects++;
		
			// Add a new tObject node to our list of objects (like a link list)
			pModel->pObject.push_back(newObject);
			
			// Initialize the object and all it's data members
			memset(&(pModel->pObject[pModel->numOfObjects - 1]), 0, sizeof(t3DObject));

			// Get the name of the object and store it, then add the read bytes to our byte counter.
			m_CurrentChunk->bytesRead += GetString(pModel->pObject[pModel->numOfObjects - 1].strName);
			
			// Now proceed to read in the rest of the object information
			ProcessNextObjectChunk(pModel, &(pModel->pObject[pModel->numOfObjects - 1]), m_CurrentChunk);
			break;

		case EDITKEYFRAME:
			// Read past this chunk and add the bytes read to the byte counter
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;

		default: 
			
			// If we didn't care about a chunk, then we get here.  We still need
			// to read past the unknown or ignored chunk and add the bytes read to the byte counter.
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}

		// Add the bytes read from the last chunk to the previous chunk passed in.
		pPreviousChunk->bytesRead += m_CurrentChunk->bytesRead;
	}

	// Free the current chunk and set it back to the previous chunk (since it started that way)
	delete m_CurrentChunk;
	m_CurrentChunk = pPreviousChunk;
}


//	This function handles all the information about the objects in the file
void CLoad3DS::ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk)
{
	int buffer[50000] = {0};					// This is used to read past unwanted data

	// Allocate a new chunk to work with
	m_CurrentChunk = new tChunk;

	// Continue to read these chunks until we read the end of this sub chunk
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// Read the next chunk
		ReadChunk(m_CurrentChunk);

		// Check which chunk we just read
		switch (m_CurrentChunk->ID)
		{
		case OBJECT_MESH:					// This lets us know that we are reading a new object
		
			// We found a new object, so let's read in it's info using recursion
			ProcessNextObjectChunk(pModel, pObject, m_CurrentChunk);
			break;

		case OBJECT_VERTICES:				// This is the objects vertices
			ReadVertices(pObject, m_CurrentChunk);
			break;

		case OBJECT_FACES:					// This is the objects face information
			ReadVertexIndices(pObject, m_CurrentChunk);
			break;

		case OBJECT_MATERIAL:				// This holds the material name that the object has
			
			// We now will read the name of the material assigned to this object
			ReadObjectMaterial(pModel, pObject, m_CurrentChunk);			
			break;

		case OBJECT_UV:						// This holds the UV texture coordinates for the object

			// This chunk holds all of the UV coordinates for our object.  Let's read them in.
			ReadUVCoordinates(pObject, m_CurrentChunk);
			break;

		default:  

			// Read past the ignored or unknown chunks
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}

		// Add the bytes read from the last chunk to the previous chunk passed in.
		pPreviousChunk->bytesRead += m_CurrentChunk->bytesRead;
	}

	// Free the current chunk and set it back to the previous chunk (since it started that way)
	delete m_CurrentChunk;
	m_CurrentChunk = pPreviousChunk;
}


//	This function handles all the information about the material (Texture)
void CLoad3DS::ProcessNextMaterialChunk(t3DModel *pModel, tChunk *pPreviousChunk)
{
	int buffer[50000] = {0};					// This is used to read past unwanted data

	// Allocate a new chunk to work with
	m_CurrentChunk = new tChunk;

	// Continue to read these chunks until we read the end of this sub chunk
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// Read the next chunk
		ReadChunk(m_CurrentChunk);

		// Check which chunk we just read in
		switch (m_CurrentChunk->ID)
		{
		case MATNAME:							// This chunk holds the name of the material
			
			// Here we read in the material name
			m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strName, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;

		case MATDIFFUSE:						// This holds the R G B color of our object
			ReadColorChunk(&(pModel->pMaterials[pModel->numOfMaterials - 1]), m_CurrentChunk);
			break;
		
		case MATMAP:							// This is the header for the texture info
			
			// Proceed to read in the material information
			ProcessNextMaterialChunk(pModel, m_CurrentChunk);
			break;

		case MATMAPFILE:						// This stores the file name of the material

			// Here we read in the material's file name
			m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strFile, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		
		default:  

			// Read past the ignored or unknown chunks
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}

		// Add the bytes read from the last chunk to the previous chunk passed in.
		pPreviousChunk->bytesRead += m_CurrentChunk->bytesRead;
	}

	// Free the current chunk and set it back to the previous chunk (since it started that way)
	delete m_CurrentChunk;
	m_CurrentChunk = pPreviousChunk;
}

//	This function reads in a chunk ID and it's length in bytes
void CLoad3DS::ReadChunk(tChunk *pChunk)
{
	// This reads the chunk ID which is 2 bytes.
	// The chunk ID is like OBJECT or MATERIAL.  It tells what data is
	// able to be read in within the chunks section.  
	pChunk->bytesRead = fread(&pChunk->ID, 1, 2, m_FilePointer);

	// Then, we read the length of the chunk which is 4 bytes.
	// This is how we know how much to read in, or read past.
	pChunk->bytesRead += fread(&pChunk->length, 1, 4, m_FilePointer);
}

//	This function reads in a string of characters
int CLoad3DS::GetString(char *pBuffer)
{
	int index = 0;

	// Read 1 byte of data which is the first letter of the string
	fread(pBuffer, 1, 1, m_FilePointer);

	// Loop until we get NULL
	while (*(pBuffer + index++) != 0) {

		// Read in a character at a time until we hit NULL.
		fread(pBuffer + index, 1, 1, m_FilePointer);
	}

	// Return the string length, which is how many bytes we read in (including the NULL)
	return strlen(pBuffer) + 1;
}


//	This function reads in the RGB color data
void CLoad3DS::ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk)
{
	// Read the color chunk info
	ReadChunk(m_TempChunk);

	// Read in the R G B color (3 bytes - 0 through 255)
	m_TempChunk->bytesRead += fread(pMaterial->color, 1, m_TempChunk->length - m_TempChunk->bytesRead, m_FilePointer);

	// Add the bytes read to our chunk
	pChunk->bytesRead += m_TempChunk->bytesRead;
}


//	This function reads in the indices for the vertex array
void CLoad3DS::ReadVertexIndices(t3DObject *pObject, tChunk *pPreviousChunk)
{
	unsigned short index = 0;					// This is used to read in the current face index

	// Read in the number of faces that are in this object (int)
	pPreviousChunk->bytesRead += fread(&pObject->numOfFaces, 1, 2, m_FilePointer);

	// Alloc enough memory for the faces and initialize the structure
	pObject->pFaces = new tFace [pObject->numOfFaces];
	memset(pObject->pFaces, 0, sizeof(tFace) * pObject->numOfFaces);

	// Go through all of the faces in this object
	for(int i = 0; i < pObject->numOfFaces; i++)
	{
		// Next, we read in the A then B then C index for the face, but ignore the 4th value.
		// The fourth value is a visibility flag for 3D Studio Max, we don't care about this.
		for(int j = 0; j < 4; j++)
		{
			// Read the first vertice index for the current face 
			pPreviousChunk->bytesRead += fread(&index, 1, sizeof(index), m_FilePointer);

			if(j < 3)
			{
				// Store the index in our face structure.
				pObject->pFaces[i].vertIndex[j] = index;
			}
		}
	}
}


//	This function reads in the UV coordinates for the object
void CLoad3DS::ReadUVCoordinates(t3DObject *pObject, tChunk *pPreviousChunk)
{
	// Read in the number of UV coordinates there are (int)
	pPreviousChunk->bytesRead += fread(&pObject->numTexVertex, 1, 2, m_FilePointer);

	// Allocate memory to hold the UV coordinates
	pObject->pTexVerts = new CVector2 [pObject->numTexVertex];

	// Read in the texture coodinates (an array 2 float)
	pPreviousChunk->bytesRead += fread(pObject->pTexVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
}


//	This function reads in the vertices for the object
void CLoad3DS::ReadVertices(t3DObject *pObject, tChunk *pPreviousChunk)
{
	// Read in the number of vertices (int)
	pPreviousChunk->bytesRead += fread(&(pObject->numOfVerts), 1, 2, m_FilePointer);

	// Allocate the memory for the verts and initialize the structure
	pObject->pVerts = new CVector3 [pObject->numOfVerts];
	memset(pObject->pVerts, 0, sizeof(CVector3) * pObject->numOfVerts);

	// Read in the array of vertices (an array of 3 floats)
	pPreviousChunk->bytesRead += fread(pObject->pVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);

	// Go through all of the vertices that we just read and swap the Y and Z values
	for(int i = 0; i < pObject->numOfVerts; i++)
	{
		// Store off the Y value
		float fTempY = pObject->pVerts[i].y;

		// Set the Y value to the Z value
		pObject->pVerts[i].y = pObject->pVerts[i].z;

		// Set the Z value to the Y value, 
		// but negative Z because 3D Studio max does the opposite.
		pObject->pVerts[i].z = -fTempY;
	}
}


//	This function reads in the material name assigned to the object and sets the materialID
void CLoad3DS::ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk)
{
	char strMaterial[255] = {0};			// This is used to hold the objects material name
	int buffer[50000] = {0};				// This is used to read past unwanted data

	// strMaterial should now have a string of the material name, like "Material #2" etc..
	pPreviousChunk->bytesRead += GetString(strMaterial);

	// Go through all of the textures
	for(int i = 0; i < pModel->numOfMaterials; i++)
	{
		// If the material we just read in matches the current texture name
		if(strcmp(strMaterial, pModel->pMaterials[i].strName) == 0)
		{
			// Set the material ID to the current index 'i' and stop checking
			pObject->materialID = i;

			// Now that we found the material, check if it's a texture map.
			// If the strFile has a string length of 1 and over it's a texture
			if(strlen(pModel->pMaterials[i].strFile) > 0) {

				// Set the object's flag to say it has a texture map to bind.
				pObject->bHasTexture = true;
			}	
			break;
		}
		else
		{
			// Set the ID to -1 to show there is no material for this object
			pObject->materialID = -1;
		}
	}

	// Read past the rest of the chunk since we don't care about shared vertices
	// You will notice we subtract the bytes already read in this chunk from the total length.
	pPreviousChunk->bytesRead += fread(buffer, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
}			


//////////////////////////////	Math Functions  ////////////////////////////////*

// This computes the magnitude of a normal.   (magnitude = sqrt(x^2 + y^2 + z^2)
#define Mag(Normal) (sqrt(Normal.x*Normal.x + Normal.y*Normal.y + Normal.z*Normal.z))

// This calculates a vector between 2 points and returns the result
CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2)
{
	CVector3 vVector;							// The variable to hold the resultant vector

	vVector.x = vPoint1.x - vPoint2.x;			// Subtract point1 and point2 x's
	vVector.y = vPoint1.y - vPoint2.y;			// Subtract point1 and point2 y's
	vVector.z = vPoint1.z - vPoint2.z;			// Subtract point1 and point2 z's

	return vVector;								// Return the resultant vector
}

// This adds 2 vectors together and returns the result
CVector3 AddVector(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vResult;							// The variable to hold the resultant vector
	
	vResult.x = vVector2.x + vVector1.x;		// Add Vector1 and Vector2 x's
	vResult.y = vVector2.y + vVector1.y;		// Add Vector1 and Vector2 y's
	vResult.z = vVector2.z + vVector1.z;		// Add Vector1 and Vector2 z's

	return vResult;								// Return the resultant vector
}

// This divides a vector by a single number (scalar) and returns the result
CVector3 DivideVectorByScaler(CVector3 vVector1, float Scaler)
{
	CVector3 vResult;							// The variable to hold the resultant vector
	
	vResult.x = vVector1.x / Scaler;			// Divide Vector1's x value by the scaler
	vResult.y = vVector1.y / Scaler;			// Divide Vector1's y value by the scaler
	vResult.z = vVector1.z / Scaler;			// Divide Vector1's z value by the scaler

	return vResult;								// Return the resultant vector
}

// This returns the cross product between 2 vectors
CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vCross;								// The vector to hold the cross product
												// Get the X value
	vCross.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
												// Get the Y value
	vCross.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
												// Get the Z value
	vCross.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vCross;								// Return the cross product
}

float Dot(CVector3 v1, CVector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
}

// This returns the normal of a vector
CVector3 Normalize(CVector3 vNormal)
{
	double Magnitude;							// This holds the magitude			

	Magnitude = Mag(vNormal);					// Get the magnitude

	vNormal.x /= (float)Magnitude;				// Divide the vector's X by the magnitude
	vNormal.y /= (float)Magnitude;				// Divide the vector's Y by the magnitude
	vNormal.z /= (float)Magnitude;				// Divide the vector's Z by the magnitude

	return vNormal;								// Return the normal
}

//	This function computes the normals and vertex normals of the objects
void CLoad3DS::ComputeNormals(t3DModel *pModel)
{
	CVector3 vVector1, vVector2, vNormal, vPoly[3];

	// If there are no objects, we can skip this part
	if(pModel->numOfObjects <= 0)
		return;

	// Go through each of the objects to calculate their normals
	for(int index = 0; index < pModel->numOfObjects; index++)
	{
		// Get the current object
		t3DObject *pObject = &(pModel->pObject[index]);

		// Here we allocate all the memory we need to calculate the normals
		CVector3 *pNormals		= new CVector3 [pObject->numOfFaces];
		CVector3 *pTempNormals	= new CVector3 [pObject->numOfFaces];
		pObject->pNormals		= new CVector3 [pObject->numOfVerts];

		// Go though all of the faces of this object
		for(int i=0; i < pObject->numOfFaces; i++)
		{												
			// To cut down LARGE code, we extract the 3 points of this face
			vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
			vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
			vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];

			// Now let's calculate the face normals (Get 2 vectors and find the cross product of those 2)

			vVector1 = Vector(vPoly[0], vPoly[2]);		// Get the vector of the polygon (we just need 2 sides for the normal)
			vVector2 = Vector(vPoly[2], vPoly[1]);		// Get a second vector of the polygon

			vNormal  = Cross(vVector1, vVector2);		// Return the cross product of the 2 vectors (normalize vector, but not a unit vector)
			pTempNormals[i] = vNormal;					// Save the un-normalized normal for the vertex normals
			vNormal  = Normalize(vNormal);				// Normalize the cross product to give us the polygons normal

			pNormals[i] = vNormal;						// Assign the normal to the list of normals
		}

		//////////////// Now Get The Vertex Normals /////////////////

		CVector3 vSum = {0.0, 0.0, 0.0};
		CVector3 vZero = vSum;
		int shared=0;

		for (i = 0; i < pObject->numOfVerts; i++)			// Go through all of the vertices
		{
			for (int j = 0; j < pObject->numOfFaces; j++)	// Go through all of the triangles
			{												// Check if the vertex is shared by another face
				if (pObject->pFaces[j].vertIndex[0] == i || 
					pObject->pFaces[j].vertIndex[1] == i || 
					pObject->pFaces[j].vertIndex[2] == i)
				{
					vSum = AddVector(vSum, pTempNormals[j]);// Add the un-normalized normal of the shared face
					shared++;								// Increase the number of shared triangles
				}
			}      
			
			// Get the normal by dividing the sum by the shared.  We negate the shared so it has the normals pointing out.
			pObject->pNormals[i] = DivideVectorByScaler(vSum, float(-shared));

			// Normalize the normal for the final vertex normal
			pObject->pNormals[i] = Normalize(pObject->pNormals[i]);	

			vSum = vZero;									// Reset the sum
			shared = 0;										// Reset the shared
		}	
	

		for (i = 0; i < pObject->numOfVerts; ++i)			// Go through all of the vertices
		{
			// A temp vector to hold the sum of all the normals
			CVector3 temp = pObject->pNormals[i];
			// This array holds whether or not the vertex has been recognized as a problem
			bool *problem_vert = new bool[pObject->numOfVerts];
			bool problem_found = false;
			for (int j = 0; j < pObject->numOfVerts; ++j)			// Go through all of the vertices
			{
				// Initialing the array
				problem_vert[j] = false;
				// If we're not looking at ourselves.....
				if(i != j)
				{
					// Let's see if we have the same coordinate but different normals
					if(pObject->pVerts[i] == pObject->pVerts[j] &&
						pObject->pNormals[i] != pObject->pNormals[j])
					{
						// This could be a problem
						problem_vert[i] = true;
						problem_vert[j] = true;
						problem_found = true;
						// Add up our normals
						temp = temp + pObject->pNormals[j];
					}
				}
			}
			if(problem_found)
			{
				// Normalize the new normal
				temp = Normalize(temp);
				// Go through all verts.....
				for(j = 0; j < pObject->numOfVerts; ++j)
				{
					// ...look for the problem verts.... 
					if(problem_vert[j])
						// ....and set their normals to the unified normal
						pObject->pNormals[j] = temp;
				}
				// Free our memory
				delete [] problem_vert;
			}

		}	  	   
		// Free our memory and start over on the next object
		delete [] pTempNormals;
		delete [] pNormals;
	}
}


