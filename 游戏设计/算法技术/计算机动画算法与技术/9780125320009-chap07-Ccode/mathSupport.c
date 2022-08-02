// ================================================================
// VECTOR, MATRIX, SPATIAL VECTOR, SPATIAL MATRIX ROUTINES
// ================================================================


#include "support.h"

// -----------------------------------------------------------------------
// DISTANCE
float distance(float *v1,float *v2)
{
	float a,b,c;

    a = v1[0]-v2[0]; 	b= v1[1]-v2[1]; 	c = v1[2]-v2[2]; 	
	return sqrt(a*a+b*b+c*c);
}
	
// -----------------------------------------------------
// AXIS ANGLE ROTATE
void axisAngleRotate(float *pp,float *ax,float angle,float *p)
{
  float		**m;
  float		radians;
  
  radians = angle;
  m = matrix_allocate();
  matrix_setAxisAngleRotate(m,ax,radians);
  vector_matrixMultiply(pp,m,p);
  matrix_deallocate(m);
}

// -----------------------------------------------------
// VECTOR SET ZERO
void vector_setZero(float *v1)
{
  v1[0] = 0.0;
  v1[1] = 0.0;
  v1[2] = 0.0;
}

// -----------------------------------------------------
// VECTOR PRINT
void vector_print(float *v1)
{
  printf(" %f %f %f\n",v1[0],v1[1],v1[2]);
}

// -----------------------------------------------------
// VECTOR COPY
void vector_copy(float *v1, float *v2)
{
  v1[0] = v2[0];
  v1[1] = v2[1];
  v1[2] = v2[2];
}

// -----------------------------------------------------
// VECTOR ASSIGN
void vector_assign(float *v1, float *v2)
{
  v1[0] = v2[0];
  v1[1] = v2[1];
  v1[2] = v2[2];
}

// -----------------------------------------------------
// VECTOR NEGATE
void vector_negate(float *v1, float *v2)
{
  v1[0] = -v2[0];
  v1[1] = -v2[1];
  v1[2] = -v2[2];
}

// -----------------------------------------------------
// VECTOR ADD
void vector_add(float *v1, float *v2,float *v3)
{
  v1[0] = v2[0]+v3[0];
  v1[1] = v2[1]+v3[1];
  v1[2] = v2[2]+v3[2];
}

// -----------------------------------------------------
// VECTOR SUBTRACT
void vector_subtract(float *v1, float *v2,float *v3)
{
  v1[0] = v2[0]-v3[0];
  v1[1] = v2[1]-v3[1];
  v1[2] = v2[2]-v3[2];
}

// -----------------------------------------------------
// VECTOR3 SCALAR MULTIPLY
void vector_scalarMultiply(float *v1,float s,float *v2)
{
  v1[0] = s*v2[0];
  v1[1] = s*v2[1];
  v1[2] = s*v2[2];
}

// -----------------------------------------------------
// VECTOR3 SCALAR MULTIPLY
void vector_matrixMultiply(float *v1, float **M,float *v2)
{
  float   v[3];
  
  if (v1 != v2) {
    v1[0] = M[0][0]*v2[0]+M[0][1]*v2[1]+M[0][2]*v2[2];
    v1[1] = M[1][0]*v2[0]+M[1][1]*v2[1]+M[1][2]*v2[2];
    v1[2] = M[2][0]*v2[0]+M[2][1]*v2[1]+M[2][2]*v2[2]; 
  }
  else {
    v[0] = M[0][0]*v2[0]+M[0][1]*v2[1]+M[0][2]*v2[2];
    v[1] = M[1][0]*v2[0]+M[1][1]*v2[1]+M[1][2]*v2[2];
    v[2] = M[2][0]*v2[0]+M[2][1]*v2[1]+M[2][2]*v2[2]; 
	v1[0] = v[0]; v1[1] = v[1]; v1[2] = v[2];
  }
}

// -----------------------------------------------------
// VECTOR3 CROSS PRODUCT
void vector_crossProduct(float *v1,float *v2,float *v3)
{
  v1[0] = v2[1]*v3[2] - v2[2]*v3[1];
  v1[1] = v2[2]*v3[0] - v2[0]*v3[2];
  v1[2] = v2[0]*v3[1] - v2[1]*v3[0];
}

// -----------------------------------------------------
// MATRIX ALLOCATE
float **matrix_allocate()
{
  float **M;
  int	i;

  M = (float **)malloc((sizeof(float *))*3); 	
  for (i=0; i<3; i++) {
    M[i] = (float *)malloc((sizeof(float))*3);
  }
  return M;
}

// -----------------------------------------------------
// MATRIX ALLOCATE
void matrix_deallocate(float **M)
{
  int	i;

  for (i=0; i<3; i++) free(M[i]);
  free(M);
}

// -----------------------------------------------------
// MATRIX SET IDENTITY
void matrix_setIdentity(float **M)
{
  M[0][0] = 1.0; M[0][1] = 0,0; M[0][2] = 0.0;
  M[1][0] = 0.0; M[1][1] = 1,0; M[1][2] = 0.0;
  M[2][0] = 0.0; M[2][1] = 0,0; M[2][2] = 1.0;
}

// -----------------------------------------------------
// MATRIX COPY
void matrix_copy(float **M1,float **M2)
{
  M1[0][0] = M2[0][0]; M1[0][1] = M2[0][1]; M1[0][2] = M2[0][2];
  M1[1][0] = M2[1][0]; M1[1][1] = M2[1][1]; M1[1][2] = M2[1][2];
  M1[2][0] = M2[2][0]; M1[2][1] = M2[2][1]; M1[2][2] = M2[2][2];
}

// -----------------------------------------------------
// MATRIX ASSIGN
void matrix_assign(float **M1,float **M2)
{
  M1[0][0] = M2[0][0]; M1[0][1] = M2[0][1]; M1[0][2] = M2[0][2];
  M1[1][0] = M2[1][0]; M1[1][1] = M2[1][1]; M1[1][2] = M2[1][2];
  M1[2][0] = M2[2][0]; M1[2][1] = M2[2][1]; M1[2][2] = M2[2][2];
}

// -----------------------------------------------------
// MATRIX SET AXIS ANGLE ROTATE
void matrix_setAxisAngleRotate(float **m,float *ax,float angle)
{
	float	ca,sa;
	float   t,txy,txz,tyz;
	float   x,y,z;
	float	len;
	double	radians;
	
	len = sqrt(ax[0]*ax[0]+ax[1]*ax[1]+ax[2]*ax[2]);
	x = ax[0]/len; y = ax[1]/len; z = ax[2]/len; 
	
	radians = angle;
	ca = cos(radians); sa = sin(radians);
	t = 1.0 - ca;
	txy = t*x*y; txz = t*x*z; tyz = t*y*z;
	m[0][0] = t*x*x+ca; m[0][1] = txy-z*sa; m[0][2] = txz+y*sa;
	m[1][0] = txy+z*sa; m[1][1] = t*y*y+ca; m[1][2] = tyz-x*sa;	
	m[2][0] = txz-y*sa; m[2][1] = tyz+x*sa; m[2][2] = t*z*z+ca;		

}

// -----------------------------------------------------
// MATRIX PRINT
void matrix_print(float **m)
{
  int	i,j;
  for (i=0; i<3; i++) {
    printf("%f %f %f\n",m[i][0],m[i][1],m[i][2]);
  }
}

// -----------------------------------------------------
// MATRIX ADD
void matrix_add(float **m1,float **m2,float **m3)
{
  int	i,j;
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
	  m1[i][j] = m2[i][j] + m3[i][j];
    }
  }
}

// -----------------------------------------------------
// MATRIX SUBTRACT
void matrix_subtract(float **m1,float **m2,float **m3)
{
  int	i,j;
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
	  m1[i][j] = m2[i][j] - m3[i][j];
    }
  }
}

// -----------------------------------------------------
// MATRIX SCALAR MULTIPLY
void matrix_scalarMultiply(float **m1,float s,float **m2)
{
  int	i,j;
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
	  m1[i][j] = s*m2[i][j];
    }
  }
}

// -----------------------------------------------------
// MATRIX TRANSPOSE - handles m1==m2
void matrix_transpose(float **m1,float **m2)
{
  float	t;
  
  if (m1 != m2) {
    m1[0][0] = m2[0][0]; m1[0][1] = m2[1][0]; m1[0][2] = m2[2][0];
    m1[1][0] = m2[0][1]; m1[1][1] = m2[1][1]; m1[1][2] = m2[2][1];
    m1[2][0] = m2[0][2]; m1[2][1] = m2[1][2]; m1[2][2] = m2[2][2];
  }
  else {
	t = m1[0][1]; m1[0][1] = m1[1][0]; m1[1][0] = t;
	t = m1[0][2]; m1[0][2] = m1[2][0]; m1[2][0] = t;
	t = m1[1][2]; m1[1][2] = m1[2][1]; m1[2][1] = t;
  }
}

// -----------------------------------------------------
// MATRIX TRANSPOSE - handles m1==m2
void matrix_multiply(float **m1,float **m2,float **m3)
{
  int   i,j,k;
  float **m;
  
  if ((m1 != m2) && (m1 != m3)) {
    for (i=0; i<3; i++) {
	  for (j=0; j<3; j++) {
	    m1[i][j] = 0.0;
		for (k=0; k<3; k++) m1[i][j] += m2[i][k]*m3[k][j];
	  }
	}
  }
  else {
    m = matrix_allocate();
    for (i=0; i<3; i++) {
	  for (j=0; j<3; j++) {
	    m[i][j] = 0.0;
		for (k=0; k<3; k++) m[i][j] += m2[i][k]*m3[k][j];
	  }
	}
    for (i=0; i<3; i++) {
	  for (j=0; j<3; j++) {
	    m1[i][j] = m[i][j];
	  }
	}
  }
}

// -----------------------------------------------------
// SPATIAL VECTOR ZERO
void spatialVector_setZero(float *v1)
{
  v1[0] = 0.0;
  v1[1] = 0.0;
  v1[2] = 0.0;
  v1[3] = 0.0;
  v1[4] = 0.0;
  v1[5] = 0.0;
}

// -----------------------------------------------------
// SPATIAL VECTOR TRANSPOSE
void spatialVector_transpose(float *v1, float *v2)
{
  v1[0] = v2[3];
  v1[1] = v2[4];
  v1[2] = v2[5];
  v1[3] = v2[0];
  v1[4] = v2[1];
  v1[5] = v2[2];
}

// -----------------------------------------------------
// SPATIAL VECTOR ADD
// v1 = v2 + v3
void spatialVector_add(float *v1,float *v2,float *v3)
{
  v1[0] = v2[0]+v3[0];
  v1[1] = v2[1]+v3[1];
  v1[2] = v2[2]+v3[2];
  v1[3] = v2[3]+v3[3];
  v1[4] = v2[4]+v3[4];
  v1[5] = v2[5]+v3[5];
}


// -----------------------------------------------------
// SPATIAL VECTOR SUBTRACT
// v1 = v2 - v3
void spatialVector_subtract(float *v1, float *v2,float *v3)
{
  v1[0] = v2[0]-v3[0];
  v1[1] = v2[1]-v3[1];
  v1[2] = v2[2]-v3[2];
  v1[3] = v2[3]-v3[3];
  v1[4] = v2[4]-v3[4];
  v1[5] = v2[5]-v3[5];
}

// -----------------------------------------------------
// SPATIAL VECTOR SCALAR MULTIPLY
// v1 = s * v3
void spatialVector_scalarMultiply(float *v1,float s,float *v2)
{
  v1[0] = s*v2[0];
  v1[1] = s*v2[1];
  v1[2] = s*v2[2];
  v1[3] = s*v2[3];
  v1[4] = s*v2[4];
  v1[5] = s*v2[5];
}

// -----------------------------------------------------
// SPATIAL VECTOR MATRIX MULTIPLY
// spatialVector = matrix * spatialVector
void spatialVector_matrixMultiply(float *v1, float **M,float *v2)
{
  int   i,j;

  for (i=0; i<6; i++) {
    v1[i] = 0.0;
    for (j=0; j<6; j++) {
      v1[i] += M[i][j]*v2[j];
    }
  }
}

// -----------------------------------------------------
// SPATIAL VECTOR INNER PRODUCT
float spatialVector_innerProduct(float *v1,float *v2)
{
  return (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3]+v1[4]*v2[4]+v1[5]*v2[5]);
}

// -----------------------------------------------------
// SPATIAL VECTOR OUTER PRODUCT
// spatialMatrix = spatialVector * spatialVector
void spatialVector_outerProduct(float **M, float *v1,float *v2)
{
  int	i,j;

  for (i=0; i<6; i++) {
    for (j=0; j<6; j++) {
      M[i][j] = v1[i]*v2[j];
    }
  }
}


// -----------------------------------------------------
// SPATIAL MATRIX ALLOCATE
float **spatialMatrix_allocate()
{
  float **M;
  int	i;

  M = (float **)malloc((sizeof(float *))*6); 	
  for (i=0; i<6; i++) {
    M[i] = (float *)malloc((sizeof(float))*6);
  }
  return M;
}

// -----------------------------------------------------
// SPATIAL MATRIX DEALLOCATE
void spatialMatrix_deallocate(float **M)
{
  int	i;

  for (i=0; i<6; i++) free(M[i]);
  free(M);
}

// -----------------------------------------------------
// SPATIAL MATRIX ZERO
void spatialMatrix_setZero(float **m)
{
  int	i,j;
  for (i=0; i<6; i++) {
    for (j=0; j<6; j++) {
	  m[i][j] = 0.0;
	}
  }
}

// -----------------------------------------------------
// SPATIAL MATRIX MULTIPLY
void spatialMatrix_print(float **m)
{
  int	i;
  for (i=0; i<6; i++) {
    printf(" %f %f %f %f %f %f\n",m[i][0],m[i][1],m[i][2],m[i][3],m[i][4],m[i][5]);
  }
}

// -----------------------------------------------------
// SPATIAL MATRIX MULTIPLY
void spatialMatrix_multiply(float **m1,float **m2, float **m3)
{
  int	i,j,k;

  for (i=0; i<6; i++) {
    for (j=0; j<6; j++) {
      m1[i][j] = 0.0;
      for (k=0; k<6; k++) m1[i][j] += m2[i][k]*m3[k][j];
    }
  }
}

// -----------------------------------------------------
// SPATIAL MATRIX SCALAR MULTIPLY
void spatialMatrix_scalarMultiply(float **m1,float s, float **m2)
{
  int	i,j;

  for (i=0; i<6; i++) {
    for (j=0; j<6; j++) {
      m1[i][j] = s*m2[i][j];
    }
  }
}

// -----------------------------------------------------
// SPATIAL MATRIX ADD
void spatialMatrix_add(float **m1,float **m2, float **m3)
{
  int	i,j;

  for (i=0; i<6; i++) {
    for (j=0; j<6; j++) {
      m1[i][j] = m2[i][j] + m3[i][j];
    }
  }
}

// -----------------------------------------------------
// SPATIAL MATRIX SUBTRACT
void spatialMatrix_subtract(float **m1,float **m2, float **m3)
{
  int	i,j;

  for (i=0; i<6; i++) {
    for (j=0; j<6; j++) {
      m1[i][j] = m2[i][j] - m3[i][j];
    }
  }
}



