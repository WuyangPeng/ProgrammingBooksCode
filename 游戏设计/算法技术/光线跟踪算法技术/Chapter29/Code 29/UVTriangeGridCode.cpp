// This file contains the Grid class member functions for reading triangles from PLY files 
// where each vertex has (u, v) coordinates.
// You will have to add the function declarations to the Grid class declaration in Grid.h



// ----------------------------------------------------------------------------- read_flat_uv_triangles

void												
Grid::read_flat_uv_triangles(char* file_name) {
  	read_uv_ply_file(file_name, flat);
}


// ----------------------------------------------------------------------------- read_smooth_uv_triangles

void												
Grid::read_smooth_uv_triangles(char* file_name) {
  	read_uv_ply_file(file_name, smooth);
  	compute_mesh_normals();
}



// ----------------------------------------------------------------------------- read_uv_ply_File

// Most of this function was written by Greg Turk and is released under the licence agreement at the start of the PLY.h and PLY.c files
// The PLY.h file is #included at the start of this file
// It still has some of his printf statements for debugging
// I've made changes to construct mesh triangles and store them in the grid
// mesh_ptr is a data member of Grid
// objects is a data member of Compound
// triangle_type is either flat or smooth
// Using the one function construct to flat and smooth triangles saves a lot of repeated code
// The ply file is the same for flat and smooth uv triangles

void
Grid::read_uv_ply_file(char* file_name, const int triangle_type) {
	// Vertex definition 
	
	typedef struct Vertex {
	  float x,y,z;             	// space coordinates
	  float u, v;				// texture coordinates
	} Vertex;
	
	// Face definition. This is the same for all files but is placed here to keep all the defintions together

	typedef struct Face {
	  	unsigned char nverts;    // number of vertex indices in list
	  	int* verts;              // vertex index list 
	} Face;
		
	// list of property information for a vertex - includes the texture coordinates

	PlyProperty vert_props[] = {
	  {"x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,x), 0, 0, 0, 0},
	  {"y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,y), 0, 0, 0, 0},
	  {"z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,z), 0, 0, 0, 0},
	  {"u", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,u), 0, 0, 0, 0},
	  {"v", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,v), 0, 0, 0, 0}
	};

	// list of property information for a face. This is the same for all files
	// there is a single property, which is a list

	PlyProperty face_props[] = { 
	  	{"vertex_indices", PLY_INT, PLY_INT, offsetof(Face,verts),
	   		1, PLY_UCHAR, PLY_UCHAR, offsetof(Face,nverts)}
	};
	
	// local variables
	
	int 			i,j,k;
  	PlyFile*		ply;
  	int 			nelems;		// number of element types: 2 in our case - vertices and faces
  	char**			elist;
	int 			file_type;
	float 			version;
	int 			nprops;		// number of properties each element has
	int 			num_elems;	// number of each type of element: number of vertices or number of faces
	PlyProperty**	plist;
	Vertex**		vlist;
	Face**			flist;
	char*			elem_name;
	int				num_comments;
	char**			comments;
	int 			num_obj_info;
	char**			obj_info;


  	// open a PLY file for reading
  
	ply = ply_open_for_reading(file_name, &nelems, &elist, &file_type, &version);

  	// print what we found out about the file
  
  	printf ("version %f\n", version);
  	printf ("type %d\n", file_type);
  	
  	// go through each kind of element that we learned is in the file
  	// and read them 

  	for (i = 0; i < nelems; i++) {  // there are only two elements in our files: vertices and faces
	    // get the description of the first element 
	    
	    elem_name = elist[i];
	    plist = ply_get_element_description (ply, elem_name, &num_elems, &nprops);

	    // print the name of the element, for debugging
	    
		cout << "element name  " << elem_name << "  num elements = " << num_elems << "  num properties =  " << nprops << endl;

	    // if we're on vertex elements, read in the properties
    
    	if (equal_strings ("vertex", elem_name)) {
	      	// set up for getting vertex elements
	      	// the five properties are the three vertex coordinates and the two texture coordinates
	
			ply_get_property (ply, elem_name, &vert_props[0]);
	      	ply_get_property (ply, elem_name, &vert_props[1]);
		  	ply_get_property (ply, elem_name, &vert_props[2]);
		  	ply_get_property (ply, elem_name, &vert_props[3]);
		  	ply_get_property (ply, elem_name, &vert_props[4]);
		  	
		  	// reserve mesh elements
		  	
		  	mesh_ptr->num_vertices = num_elems;
		  	mesh_ptr->vertices.reserve(num_elems);
		  	mesh_ptr->u.reserve(num_elems);
		  	mesh_ptr->v.reserve(num_elems);

		  	// grab all the vertex elements
		  	
		  	Vertex* vertex_ptr = new Vertex;
		  
		  	for (j = 0; j < num_elems; j++) {
			    // grab an element from the file
		        
				ply_get_element (ply, (void *) vertex_ptr);
								
		  		mesh_ptr->vertices.push_back(Point3D(vertex_ptr->x, vertex_ptr->y, vertex_ptr->z));
		  		mesh_ptr->u.push_back(vertex_ptr->u);
		  		mesh_ptr->v.push_back(vertex_ptr->v);  
		  	}
		  	
		  	delete vertex_ptr;
    	}

	    // if we're on face elements, read them in 
	    
	    if (equal_strings ("face", elem_name)) {
		    // set up for getting face elements
		
			ply_get_property (ply, elem_name, &face_props[0]);   // only one property - a list
			
		  	mesh_ptr->num_triangles = num_elems;
		  	objects.reserve(num_elems);  // triangles will be stored in Compound::objects
		  	
		  	// new code to store the face numbers that are shared by each vertex
		  	
		  	mesh_ptr->vertex_faces.reserve(mesh_ptr->num_vertices);
		  	vector<int> faceList;
		  	
		  	for (j = 0; j < mesh_ptr->num_vertices; j++) 
		  		mesh_ptr->vertex_faces.push_back(faceList); // store empty lists so that we can use [] notation below
		  			
			// grab all the face elements
			
			Face* face_ptr = new Face;
			int count = 0; // the number of faces read
		      
			for (j = 0; j < num_elems; j++) {
			    // grab an element from the file 
			    
			    ply_get_element (ply, (void *) face_ptr);
			    
			    // construct a uv mesh triangle of the specified type
			    
			     if (triangle_type == flat) {
			    	FlatUVMeshTriangle* triangle_ptr = new FlatUVMeshTriangle(mesh_ptr, face_ptr->verts[0], face_ptr->verts[1], face_ptr->verts[2]);
			    	triangle_ptr->compute_normal(reverse_normal);		
					objects.push_back(triangle_ptr); 
				} 
			    	
			    if (triangle_type == smooth) {
			    	SmoothUVMeshTriangle* triangle_ptr = new SmoothUVMeshTriangle(mesh_ptr, face_ptr->verts[0], face_ptr->verts[1], face_ptr->verts[2]);
			    	triangle_ptr->compute_normal(reverse_normal);		
					objects.push_back(triangle_ptr);
					
					mesh_ptr->vertex_faces[face_ptr->verts[0]].push_back(count);
					mesh_ptr->vertex_faces[face_ptr->verts[1]].push_back(count);
					mesh_ptr->vertex_faces[face_ptr->verts[2]].push_back(count);
					count++; 
				} 
			}
			
			delete face_ptr;
			
			if (triangle_type == flat)
				mesh_ptr->vertex_faces.erase (mesh_ptr->vertex_faces.begin(), mesh_ptr->vertex_faces.end());
	    }
    
	    // print out the properties we got, for debugging
	    
	    for (j = 0; j < nprops; j++)
	    	printf ("property %s\n", plist[j]->name);
	
	}  // end of for (i = 0; i < nelems; i++) 


	// grab and print out the comments in the file
	  
	comments = ply_get_comments (ply, &num_comments);
	  
	for (i = 0; i < num_comments; i++)
	    printf ("comment = '%s'\n", comments[i]);

	// grab and print out the object information
	  
	obj_info = ply_get_obj_info (ply, &num_obj_info);
	  
	for (i = 0; i < num_obj_info; i++)
	    printf ("obj_info = '%s'\n", obj_info[i]);

	// close the ply file 
	  
	ply_close (ply);
}