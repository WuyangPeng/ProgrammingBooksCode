/*
  get information from Acclaim .asf file
  includes required support routines
*/

// =============================================================
// GET ASF
int getASF()
{
	char     string[100];
	char     filename[100];
	bone_td *newbone;
	int      i,fileOpen;
	
	printf("input ASF file name (e.g. 'Data/sample.ASF'): ");
	scanf("%s",filename);
	if ((!strcmp(filename,"quit"))) exit(0);

	bones = NULL;
	fileOpen = FALSE;
	while (!fileOpen) {
		if ((ASFfile = fopen(filename,"r")) == NULL) {
			printf("ERROR opening file %s - try again or type 'quit' \n",filename);
			printf("input ASF file name: ");
			scanf("%s",&(filename[6]));
			if (!(strcmp(&(filename[6]),"quit"))) exit(0);
		}
		else fileOpen = TRUE;
	}

	fscanf(ASFfile,"%s",string);
	while (strcmp(string,":units")) {
	  fscanf(ASFfile,"%s",string);
	}
	// skip down to DOCUMENTATION line
	while (strcmp(string,":documentation")) {
	  fscanf(ASFfile,"%s",string);
	}
	// skip down to ROOT line
	while (strcmp(string,":root")) {
	  fscanf(ASFfile,"%s",string);
	}
	// printf(":root\n");
	fscanf(ASFfile,"%s",string);

	while ((!(strcmp(string,"axis")))        || 
		   (!(strcmp(string,"order")))       ||
		   (!(strcmp(string,"position")))    || 
		   (!(strcmp(string,"orientation")))    ) {
		if (!(strcmp(string,"axis"))) {
			fgets(string,80,ASFfile);                    // get rest of line
		}
		if (!(strcmp(string,"order"))) {
			fgets(string,80,ASFfile);                    // get rest of line
		}
		if (!(strcmp(string,"position"))) {
			fgets(string,80,ASFfile);                    // get rest of line
		}
		if (!(strcmp(string,"orientation"))) {
			fgets(string,80,ASFfile);                    // get rest of line
		}
		fscanf(ASFfile,"%s",string);
	}
	// skip down to BONEDATA line
	while (strcmp(string,":bonedata")) {
		fscanf(ASFfile,"%s",string);
	}
	// PROCESS BONES
	numberOfBones = 0;
	while ( (EOF != fscanf(ASFfile,"%s",string) != EOF) && 
			(strcmp(string,":hierarchy"))                   ) {

		if (!(strcmp(string,"begin"))) {      // new bone
			numberOfBones++;
			newbone = (bone_td *)malloc(sizeof(bone_td));
			strcpy(newbone->name,"");
			newbone->length = 1.0;
			newbone->direction[0] = 1.0;
			newbone->direction[1] = 1.0;
			newbone->direction[2] = 1.0;
			// initialize dofs
			strcpy(newbone->dof[0],"NULL");
			strcpy(newbone->dof[1],"NULL");
			strcpy(newbone->dof[2],"NULL");
			newbone->limit[0][0] = -360.0; newbone->limit[0][1] = 360.0; 
			newbone->limit[1][0] = -360.0; newbone->limit[1][1] = 360.0; 
			newbone->limit[2][0] = -360.0; newbone->limit[2][1] = 360.0; 
			// add to sequential list of bones
			newbone->next = bones;
			bones = newbone;
			// init outside of hierarchy
			newbone->child = NULL;
			newbone->sibling = NULL;
			// init global info
			newbone->position[0] = 0.0;
			newbone->position[1] = 0.0;
			newbone->position[2] = 0.0;
			newbone->tucs[0][0] = 1.0;
			newbone->tucs[0][1] = 0.0;
			newbone->tucs[0][2] = 0.0;
			newbone->tucs[1][0] = 0.0;
			newbone->tucs[1][1] = 1.0;
			newbone->tucs[1][2] = 0.0;
			newbone->tucs[2][0] = 0.0;
			newbone->tucs[2][1] = 0.0;
			newbone->tucs[2][2] = 1.0;
			newbone->numberOfDOFs = 0;
			newbone->dofValues[0] = NULL;
			newbone->dofValues[1] = NULL;
			newbone->dofValues[2] = NULL;

			while ( (fscanf(ASFfile,"%s",string) != EOF) &&
					(strcmp(string,"end"))                  ) {
				if (!(strcmp(string,"id"))) {
					fscanf(ASFfile,"%d",&(newbone->id));
				}
				if (!(strcmp(string,"name"))) {
					fscanf(ASFfile,"%s",newbone->name);
				}
				if (!(strcmp(string,"direction"))) {
					fscanf(ASFfile,"%f %f %f",
						&(newbone->direction[0]),
						&(newbone->direction[1]),
						&(newbone->direction[2]));
				}
				if (!(strcmp(string,"length"))) {
					fscanf(ASFfile,"%f",&(newbone->length));
				}
				if (!(strcmp(string,"axis"))) {
					fscanf(ASFfile,"%f %f %f",
						&(newbone->orientation[0]),
						&(newbone->orientation[1]),
						&(newbone->orientation[2]));
					fscanf(ASFfile,"%s",newbone->axisOrder);
				}
				if (!(strcmp(string,"dof"))) {        // got "dof"
					fgets(string,80,ASFfile);
					sscanf(string,"%s %s %s",
						newbone->dof[0],newbone->dof[1],newbone->dof[2]);
					if (strcmp(newbone->dof[2],"NULL")) {
						newbone->numberOfDOFs = 3;
					}
					else if (strcmp(newbone->dof[1],"NULL")) {
						newbone->numberOfDOFs = 2;
					}
					else if (strcmp(newbone->dof[0],"NULL")) {
						newbone->numberOfDOFs = 1;
					}
					else newbone->numberOfDOFs = 0;
				}

				// assumes if any limits are given, then all limits are given
				if (!(strcmp(string,"limits"))) {        // got "dof"
					for (i=0; i<newbone->numberOfDOFs; i++) {
						fscanf(ASFfile," (%f %f)",
							&(newbone->limit[i][0]),&(newbone->limit[i][1]));
					}
				}
			}
		}
	
	}
      
	// get information about hierarchy
	if (!(strcmp(string,":hierarchy"))) {   // found HIERARCHY
		bone_td  *pptr,*cptr;
		char     parent[20];
		char     child[20];
	  
		pptr = NULL;

		// skip to 'begin'
		while ( (EOF != fscanf(ASFfile,"%s",string)) &&
				(strcmp(string,"begin"))               ) { ;}

		while ( (EOF != fscanf(ASFfile,"%s",parent)) &&
				(strcmp(parent,"end"))                   ) { // not 'end'

			if (strcmp(parent,"NULL")) {                 // found a link
				if (strcmp(parent,"root")) {			// if not root, search
					pptr = findBone(parent);			// get pointer to parent bone
				}
				if ( (pptr != NULL) || (!(strcmp(parent,"root"))) ) {  // if root or bone 
					while (fgetword(child) != 0) {					// get name of child
					if ((cptr = findBone(child)) != NULL) {		// found the bone
							if (!(strcmp(parent,"root"))) {		// if child of root
								cptr->sibling = root.child;
								root.child = cptr;
							}
							else {								// child of bone
								cptr->sibling = pptr->child;
								pptr->child = cptr;
							}

						}  // end found bone
						else {
							printf(" ERROR: child bone not found\n");
							exit(0);
						}
					}  // end 'name of child'
					// printf("  no more children\n");
				} // end 'not root or bone'
				else printf("ERROR - no parent found for %s\n",parent);
			} // end found
			else {
				printf("ERROR - parent bone is NULL\n");
			}
		} // end 'not end'
    } // end of hierarchy
    
    return 1;
}

// =================================================================
// FIND BONE
bone_td *findBone(char *name) {
  bone_td  *bptr;

  // printf("  search nodes for: %s\n",name);
  bptr = bones;

  while ( (bptr != NULL) && (strcmp(bptr->name,name)) ) {
    bptr = bptr->next;
  }

  return bptr;  
}

// =================================================================
// FGETWORD
int fgetword(char *word)
{
  static char   c = '\0';
  int    i;

  if (c == '\n') { c = '\0'; return 0; }

  i = 0;
  // skip over white spaces up until newline
  c = fgetc(ASFfile);
  while( (c != '\n')  && ((c == ' ') || (c == '\t'))  ) 
    c = fgetc(ASFfile);

  // record non-white spaces
  while( (c != '\n')  && (c != ' ') && (c != '\t') ) {
    word[i++] = c;
    c = fgetc(ASFfile);
  }

  word[i] = '\0';
  return i;
}

// =================================================================
// FORM XROT MATRIX
void formXrotMatrix(float degrees,matrix A)
{
  float   angle;

  angle = PI*degrees/180;

  A[0][0] = 1.0; A[0][1] =        0.0; A[0][2] =  0.0;
  A[1][0] = 0.0; A[1][1] = cos(angle); A[1][2] = -sin(angle);
  A[2][0] = 0.0; A[2][1] = sin(angle); A[2][2] =  cos(angle);
}

// =================================================================
// FORM YROT MATRIX
void formYrotMatrix(float degrees,matrix A)
{
  float   angle;

  angle = PI*degrees/180;

  A[0][0] =  cos(angle); A[0][1] = 0.0; A[0][2] =  sin(angle);
  A[1][0] =         0.0; A[1][1] = 1.0; A[1][2] =         0.0;
  A[2][0] = -sin(angle); A[2][1] = 0.0; A[2][2] =  cos(angle);
}

// =================================================================
// FORM ZROT MATRIX
void formZrotMatrix(float degrees,matrix A)
{
  float   angle;

  angle = PI*degrees/180;

  A[0][0] =  cos(angle); A[0][1] = -sin(angle); A[0][2] =  0.0;
  A[1][0] =  sin(angle); A[1][1] =  cos(angle); A[1][2] =  0.0;
  A[2][0] =         0.0; A[2][1] =         0.0; A[2][2] =  1.0;
}

// =================================================================
// SET IDENTITY
void setIdentity(matrix A)
{
  A[0][0] =  1.0; A[0][1] = 0.0; A[0][2] =  0.0;
  A[1][0] =  0.0; A[1][1] = 1.0; A[1][2] =  0.0;
  A[2][0] =  0.0; A[2][1] = 0.0; A[2][2] =  1.0;
}

// =================================================================
// COPY MATRIX A = B
void copyMatrix(matrix A,matrix B)
{
  A[0][0] =  B[0][0]; A[0][1] = B[0][1]; A[0][2] =  B[0][2];
  A[1][0] =  B[1][0]; A[1][1] = B[1][1]; A[1][2] =  B[1][2];
  A[2][0] =  B[2][0]; A[2][1] = B[2][1]; A[2][2] =  B[2][2];
}

// =================================================================
// MATRIX MULTIPLY A = B x C
void matrixMultiply(matrix A, matrix B, matrix C)
{
  int  i,j,k;
  matrix T;

  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
      T[i][j] = 0.0;
      for (k=0; k<3; k++) T[i][j] += B[i][k]*C[k][j];
    }
  }

  A[0][0] =  T[0][0]; A[0][1] = T[0][1]; A[0][2] =  T[0][2];
  A[1][0] =  T[1][0]; A[1][1] = T[1][1]; A[1][2] =  T[1][2];
  A[2][0] =  T[2][0]; A[2][1] = T[2][1]; A[2][2] =  T[2][2];
}


