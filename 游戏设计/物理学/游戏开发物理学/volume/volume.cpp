// volume.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "mymath.h"

//------------------------------------------------------------------------//
// defines and typdefs
//------------------------------------------------------------------------//
#define	MAX_NUM_VERTICES	100
#define MAX_NUM_FACES		100

typedef struct VertexTag {
	float	x;
	float	y;
	float	z;
} TVertex;

typedef struct FaceTag {
	int	a;
	int b;
	int c;
} TFace;

//------------------------------------------------------------------------//
// Body3D class that represents a simple, triangulated polyhedron
//------------------------------------------------------------------------//
class Body3D {
public:
	int		nFaces;
	int		nVertices;
	TVertex	Vertex[MAX_NUM_VERTICES];
	TFace	Face[MAX_NUM_VERTICES];
	float	Volume;
	Vector	Centroid;

	Body3D(void); 
	
	void	ReadData(char *filename);	
	void	CalculateProperties(void);
	
};


Body3D::Body3D(void)
{
	int i;

	nFaces = 0;
	nVertices = 0;

	for(i=0; i<MAX_NUM_VERTICES; i++)
	{
		Vertex[i].x = Vertex[i].y = Vertex[i].z = 0;
	}

	for(i=0; i<MAX_NUM_FACES; i++)
	{
		Face[i].a = Face[i].b = Face[i].c = 0;
	}

	Volume = 0;
	Centroid = Vector();

}

void	Body3D::ReadData(char *filename)
{
	FILE	*fptr;
	int		i;

	fptr = fopen(filename, "r");

	fscanf(fptr, "%d\n", &nVertices);	
	for(i=0; i< nVertices; i++)
	{
		fscanf(	fptr, 
				"%f %f %f\n", 
				&(Vertex[i].x), 
				&(Vertex[i].y), 
				&(Vertex[i].z));		
	}

	fscanf(fptr, "%d\n", &nFaces);	
	for(i=0; i< nFaces; i++) 
	{
		fscanf(	fptr, 
				"%d %d %d\n", 
				&(Face[i].a), 
				&(Face[i].b), 
				&(Face[i].c));	// counter clockwise order	
	}

	fclose(fptr);
}

void	Body3D::CalculateProperties(void)
{
	Vector	a = Vector();
	Vector	b = Vector();
	Vector	c = Vector();
	int		i;
	float	dv = 0;
	float	vol = 0;
	Vector	d = Vector();
	Vector	dmom = Vector();

	for(i=0; i<nFaces; i++)
	{
		a.x = Vertex[Face[i].a].x;
		a.y = Vertex[Face[i].a].y;
		a.z = Vertex[Face[i].a].z;

		b.x = Vertex[Face[i].b].x;
		b.y = Vertex[Face[i].b].y;
		b.z = Vertex[Face[i].b].z;

		c.x = Vertex[Face[i].c].x;
		c.y = Vertex[Face[i].c].y;
		c.z = Vertex[Face[i].c].z;

		dv = (TripleScalarProduct(a, b, c)) / 6.0f;
		vol += dv;

		d = ((a + b + c) / 4);
		dmom += (d * dv);		
	}

	Volume = vol;
	Centroid = dmom / vol;
}



//------------------------------------------------------------------------//
//------------------------------------------------------------------------//
// This program's MAIN function
//------------------------------------------------------------------------//
//------------------------------------------------------------------------//

int main(int argc, char* argv[])
{
	Body3D	body = Body3D();
	float	volume = 0;
	int		i;
	Vector	centroid;

	// read the object data
	body.ReadData("hull.txt");

	// echo the data to the console
	printf("Number of vertices = %d\n", body.nVertices);
	for(i=0; i<body.nVertices; i++)
		printf(	"Vertex %d: x=%f y=%f z=%f\n", 
				i, 
				body.Vertex[i].x, 
				body.Vertex[i].y,
				body.Vertex[i].z);

	printf("Number of faces = %d\n", body.nFaces);
	for(i=0; i<body.nFaces; i++)
		printf(	"Face %d: a=%d b=%d c=%d\n", 
				i, 
				body.Face[i].a, 
				body.Face[i].b,
				body.Face[i].c);


	// calculate the volume and centroid
	body.CalculateProperties();

	// display the results to the console
	printf("\n");
	printf("Volume = %f\n", body.Volume);
	printf("\n");	
	printf("Centroid:\n");
	printf("x=%f y=%f z=%f\n", body.Centroid.x, body.Centroid.y, body.Centroid.z);
	printf("\n");

	printf("Done.\n");

	return 0;
}

