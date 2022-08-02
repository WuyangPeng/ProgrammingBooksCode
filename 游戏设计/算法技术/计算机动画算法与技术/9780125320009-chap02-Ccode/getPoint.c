
// ------------------------------------------------------------------------
// GET POINT from pre-computed table
// j is the index of the first entry whose distance is bigger than d
// d is between entry j-1 and j
// ------------------------------------------------------------------------
void getPoint(float *p,int j,float d)
{
  float   f;

  // make sure index is within valid range  
  if ((j<1) || (j>=current)) {
	printf("error at j: %d\n",j);
	exit(2);
  }	
  
  // calc fraction along the way
  f = (d-dd[j-1][0])/(dd[j][0]-dd[j-1][0]);

  // just get closest point
  /*
  if (f < 0.5) { p[0] = dd[j-1][1]; p[1] = dd[j-1][2]; p[2] = dd[j-1][3]; }
  else {         p[0] = dd[j][1];   p[1] = dd[j][2];   p[2] = dd[j][3]; }
  */

  // interpolate between closest entry points
  p[0] = dd[j-1][1] + f*(dd[j][1]-dd[j-1][1]);
  p[1] = dd[j-1][2] + f*(dd[j][2]-dd[j-1][2]);
  p[2] = dd[j-1][3] + f*(dd[j][3]-dd[j-1][3]);
}
