// -------------------------------------------------------------------------
// GET AMC
int getAMC()
{
	char     line[100];
	char     filename[100],name[30];
	FILE    *AMCfile;
	int      frame,dummy;
	bone_td *bptr;
	int      i;
	float    dof[3];

	printf("input AMC file name (e.g. 'Data/sample.AMC'): ");
	scanf("%s",filename);

	while ((strcmp(filename,"quit") && (AMCfile = fopen(filename,"r")) == NULL)) {
		printf("ERROR opening file %s - try again or type 'quit' \n",filename);
		printf("input AMC file name: ");
		scanf("%s",&filename);
	} 

	if (!strcmp(filename,"quit")) exit(0);

	// -------------------------
	// skip down through file to count frames
	numberOfFrames = 0;
	fgets(line,80,AMCfile);                     // get a line from AMC file
	while (!feof(AMCfile)) {
		if (sscanf(line,"%d",&frame)==1) numberOfFrames++;
		fgets(line,80,AMCfile);
	}
	printf("number of Frames: %d\n",numberOfFrames);

	// -------------------------
	// close file and reopen to reread

	fclose(AMCfile);
	AMCfile = fopen(filename,"r");

	// -------------------------
	// go through all bones and allocate float per frame for each DOF

	// first do the root
	root.position[0] = (float *)malloc(sizeof(float)*numberOfFrames);
	root.position[1] = (float *)malloc(sizeof(float)*numberOfFrames);
	root.position[2] = (float *)malloc(sizeof(float)*numberOfFrames);
	root.orientation[0] = (float *)malloc(sizeof(float)*numberOfFrames);
	root.orientation[1] = (float *)malloc(sizeof(float)*numberOfFrames);
	root.orientation[2] = (float *)malloc(sizeof(float)*numberOfFrames);

	// now do the bones
	bptr = bones;
	while (bptr != NULL) {
		// printf("malloc for %s",bptr->name);
		for (i=0; i<bptr->numberOfDOFs; i++) {
			// printf(":%d",i);
			bptr->dofValues[i] = (float *)malloc(sizeof(float)*numberOfFrames);
		}
		// printf("\n");
		bptr = bptr->next;
	}

    // -------------------------
    frame = 0;                                  // use internal count
    // skip down to frame line
    fgets(line,80,AMCfile);                     // get a line from AMC file
    while (sscanf(line,"%d",&dummy)==0) 
      fgets(line,80,AMCfile);

    while (!feof(AMCfile)) {
		fgets(line,80,AMCfile);
		while ( (!feof(AMCfile)) && (sscanf(line,"%d",&dummy)==0) ) {
			sscanf(line,"%s",name);
			if (!(strcmp(name,"root"))) {
				sscanf(line,"%*s %f %f %f %f %f %f",
					&(root.position[0][frame]),
					&(root.position[1][frame]),
					&(root.position[2][frame]),
					&(root.orientation[0][frame]),
					&(root.orientation[1][frame]),
					&(root.orientation[2][frame])       );
			}
			else {
				bptr = findBone(name);
				sscanf(line,"%*s %f %f %f",&(dof[0]),&(dof[1]),&(dof[2]));
				for (i=0; i<bptr->numberOfDOFs; i++) {
					bptr->dofValues[i][frame] = dof[i];
				}
			}
			fgets(line,80,AMCfile);
		}
		sscanf(line,"%d",&dummy);
		frame++;
	}
    return 1;
}

