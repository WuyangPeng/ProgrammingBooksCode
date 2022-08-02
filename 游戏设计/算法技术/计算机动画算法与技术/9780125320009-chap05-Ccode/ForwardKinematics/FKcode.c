/* 
  Forward Kinematics

  SAMPLE LINEAR LINKAGE 
  * 3 joints
  * DoFs at the joints of 3-1-1
  * multiple DoF joint uses zero length linkage between virtual joints


// -------------------------------------------------------------------------------------
static float	pose[NUMPOSES][NUMDOFS];			// pose number,DoF,axis
static float	linkLen[NUMDOFS];
static float	axis[NUMDOFS][3];

// -------------------------------------------------------------------------------------
  // number of poses for number of DoFs
  pose[0][0] =   0.0; pose[0][1] =   0.0; pose[0][2] =    0.0; pose[0][3] =   0.0; pose[0][4] =   0.0;
  pose[1][0] =   0.0; pose[1][1] =  90.0; pose[1][2] =    0.0; pose[1][3] =  90.0; pose[1][4] =   60.0;
  pose[2][0] =  90.0; pose[2][1] =   0.0; pose[2][2] =  -90.0; pose[2][3] =  90.0; pose[2][4] =   60.0;
  pose[3][0] =  50.0; pose[3][1] = -60.0; pose[3][2] =   90.0; pose[3][3] = -60.0; pose[3][4] =  60.0;
  pose[4][0] =   0.0; pose[4][1] =   0.0; pose[4][2] =    0.0; pose[4][3] =   0.0; pose[4][4] =   0.0;
  
// -------------------------------------------------------------------------------------
  // axis for each DoF
  axis[0][0] = 1.0; axis[0][1] = 0.0; axis[0][2] = 0.0; 
  axis[1][0] = 0.0; axis[1][1] = 1.0; axis[1][2] = 0.0; 
  axis[2][0] = 0.0; axis[2][1] = 0.0; axis[2][2] = 1.0; 
  axis[3][0] = 0.0; axis[3][1] = 0.0; axis[3][2] = 1.0; 
  axis[4][0] = 0.0; axis[4][1] = 0.0; axis[4][2] = 1.0; 
  
// -------------------------------------------------------------------------------------
  // link length for each DoF
  linkLen[0] = 0.0;
  linkLen[1] = 0.0;
  linkLen[2] = 8.0;
  linkLen[3] = 6.0;
  linkLen[4] = 4.0;


  // to traverse linkage and rotate joints

  glPushMatrix();

  for (i=0; i<NUMDOFS; i++) {  
    glRotatef(a[i],axis[i][0],axis[i][1],axis[i][2]);
    if (linkLen[i] != 0.0) draw_linkage(linkLen[i]);
    glTranslatef(0.0,linkLen[i],0.0);
  }
  
  glPopMatrix();

