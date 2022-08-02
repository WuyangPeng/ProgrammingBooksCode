#include "../Fly3D.h"

void mat4x4::lerp(mat4x4& m1,mat4x4& m2,float t)
{
	quaternion q1(m1),q2(m2),qt;
	qt.lerp(q1,q2,t);
	qt.get_mat(*this);
	m[3][0]=m1.m[3][0]*(1-t)+m2.m[3][0]*t;
	m[3][1]=m1.m[3][1]*(1-t)+m2.m[3][1]*t;
	m[3][2]=m1.m[3][2]*(1-t)+m2.m[3][2]*t;
}

void mat4x4::rotate( float ang,vector& dir )
{
	static mat4x4 m;
	m.set_rotation(ang,dir);
	*this=*this*m;
}

void mat4x4::set_rotation( float ang,vector& dir )
{
	dir.normalize();

	ang*=-PiOver180;

	float fCos=(float)cos( ang );
	float fSin=(float)sin( ang );

    m[0][0] = ( dir.x * dir.x ) * ( 1.0f - fCos ) + fCos;
    m[0][1] = ( dir.x * dir.y ) * ( 1.0f - fCos ) - (dir.z * fSin);
    m[0][2] = ( dir.x * dir.z ) * ( 1.0f - fCos ) + (dir.y * fSin);

    m[1][0] = ( dir.y * dir.x ) * ( 1.0f - fCos ) + (dir.z * fSin);
    m[1][1] = ( dir.y * dir.y ) * ( 1.0f - fCos ) + fCos ;
    m[1][2] = ( dir.y * dir.z ) * ( 1.0f - fCos ) - (dir.x * fSin);

    m[2][0] = ( dir.z * dir.x ) * ( 1.0f - fCos ) - (dir.y * fSin);
    m[2][1] = ( dir.z * dir.y ) * ( 1.0f - fCos ) + (dir.x * fSin);
    m[2][2] = ( dir.z * dir.z ) * ( 1.0f - fCos ) + fCos;
    
    m[0][3] = m[1][3] = m[2][3] = 0;
    m[3][0] = m[3][1] = m[3][2] = 0;
    m[3][3] = 1;
}

quaternion::quaternion(mat4x4 &mat)
{

	float tr,s,q[4];
	int i,j,k;

	int nxt[3] = {1, 2, 0};

	tr = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];

	// check the diagonal
	if (tr > 0.0) 
	{
		s = (float)sqrt(tr + 1.0f);
		w = s/2.0f;
		s = 0.5f/s;
		x = (mat.m[1][2] - mat.m[2][1]) * s;
		y = (mat.m[2][0] - mat.m[0][2]) * s;
		z = (mat.m[0][1] - mat.m[1][0]) * s;
	} 
	else 
	{		
		// diagonal is negative
    	i = 0;
		if (mat.m[1][1] > mat.m[0][0]) i = 1;
		if (mat.m[2][2] > mat.m[i][i]) i = 2;
		j = nxt[i];
		k = nxt[j];

		s=(float)sqrt((mat.m[i][i]-(mat.m[j][j] + mat.m[k][k])) + 1.0);
      
		q[i]=s*0.5f;
            
		if(s!=0.0f) s = 0.5f/s;

		q[3] = (mat.m[j][k] - mat.m[k][j]) * s;
		q[j] = (mat.m[i][j] + mat.m[j][i]) * s;
		q[k] = (mat.m[i][k] + mat.m[k][i]) * s;

		x = q[0];
		y = q[1];
		z = q[2];
		w = q[3];
	}
}

void quaternion::get_mat(mat4x4 &mat)
{
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	// calculate coefficients
	x2 = x + x; 
	y2 = y + y; 
	z2 = z + z;
	xx = x * x2;
	xy = x * y2;   
	xz = x * z2;
	yy = y * y2;   
	yz = y * z2;   
	zz = z * z2;
	wx = w * x2;   
	wy = w * y2;   
	wz = w * z2;

	mat.m[0][0] = 1.0f-(yy+zz); 	
	mat.m[1][0] = xy - wz;
	mat.m[2][0] = xz + wy;		
	mat.m[3][0] = 0.0;

	mat.m[0][1] = xy + wz;		
	mat.m[1][1] = 1.0f-(xx + zz);
	mat.m[2][1] = yz - wx;		
	mat.m[3][1] = 0.0;

	mat.m[0][2] = xz - wy;		
	mat.m[1][2] = yz + wx;
	mat.m[2][2] = 1.0f - (xx + yy);		
	mat.m[3][2] = 0.0;

	mat.m[0][3] = 0;			
	mat.m[1][3] = 0;
	mat.m[2][3] = 0;			
	mat.m[3][3] = 1;
}

quaternion quaternion::operator *(quaternion &q)
{
	float A, B, C, D, E, F, G, H;
	quaternion res;

	A = (q.w + q.x)*(w + x);
	B = (q.z - q.y)*(y - z);
	C = (q.w - q.x)*(y + z); 
	D = (q.y + q.z)*(w - x);
	E = (q.x + q.z)*(x + y);
	F = (q.x - q.z)*(x - y);
	G = (q.w + q.y)*(w - z);
	H = (q.w - q.y)*(w + z);

	res.w = B + (-E - F + G + H) /2;
	res.x = A - (E + F + G + H)/2; 
	res.y = C + (E - F + G - H)/2; 
	res.z = D + (E - F - G + H)/2;

	return res;
}

void quaternion::normalize()
{
	float factor = 1.0f/(float)sqrt(x*x+y*y+z*z+w*w);

	x*=factor;
	y*=factor;
	z*=factor;
	w*=factor;
}

void quaternion::get_rotate(float &angle, vector &axis)
{
	angle=(float)acos(w)*2*PiUnder180;

	float f=(float)sin(angle*PiOver180*0.5f);

	axis.x=x/f;
	axis.y=x/f;
	axis.z=x/f;
}

void quaternion::lerp(quaternion& q1,quaternion& q2,float t)
{
    float v;        // complement to t
    float o;        // complement to v (t)
    float theta;    // angle between q1 & q2
    float sin_t;    // sin(theta)
    float cos_t;    // cos(theta)
    float phi;      // spins added to theta
    int flip;       // flag for negating q2

    cos_t = q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];

    if (cos_t < 0.0)
    {
        cos_t = -cos_t;
	flip = TRUE;
    }
    else flip = FALSE;

    if (1.0 - cos_t < 1e-6)
    {
        v = 1.0f - t;
    }
    else
    {
        theta = (float)acos(cos_t);
        phi = theta;
        sin_t = (float)sin(theta);
        v = (float)sin(theta - t * phi) / sin_t;
        o = (float)sin(t * phi) / sin_t;
    }
    if (flip) o = -o;

    x = v * q1[0] + o * q2[0];
    y = v * q1[1] + o * q2[1];
    z = v * q1[2] + o * q2[2];
    w = v * q1[3] + o * q2[3];
}

void local_system::align_z(vector& z)
{
	if (fabs(z.z)>=0.99f)
		{
		Y.x=-z.y*z.x;
		Y.y=1-z.y*z.y;
		Y.z=-z.y*z.z;

		Y.normalize();
		X.cross(Y,z);
		}
	else 
		{
		Y.x=-z.z*z.x;
		Y.y=-z.z*z.y;
		Y.z=1-z.z*z.z;

		Y.normalize();
		X.cross(Y,z);
		}

	Z=z;

	update_mat();
}

void local_system::update_mat()
{
	memset(&mat,0,sizeof(mat));

	mat.m[0][0]=X.x;
	mat.m[0][1]=X.y;
	mat.m[0][2]=X.z;

	mat.m[1][0]=Y.x;
	mat.m[1][1]=Y.y;
	mat.m[1][2]=Y.z;

	mat.m[2][0]=Z.x;
	mat.m[2][1]=Z.y;
	mat.m[2][2]=Z.z;
	
	mat.m[3][3]=1;

	int i,j;
	for( i=0;i<4;i++ )
		for( j=0;j<4;j++ )
			mat_t.m[i][j]=mat.m[j][i];

}

void local_system::rotate(vector &v, vector &u, float maxang)
{
	vector c;
	float f;
	c.cross(v, u);
	f=c.length();
	if(f>0.01)
	{
		c.x/=f; c.y/=f; c.z/=f;
		f=(float)acos(vec_dot(v, u))*180.0f/M_Pi;

		if(f>maxang)
			f=maxang;
		else if(f<-maxang)
			f=-maxang;

		rotate(f, c);
	}
}

void local_system::rotate(vector& rot)
{
	static mat4x4 m;

	m.set_rotation(rot.x,X);
	m.rotate(rot.y,Y);
	m.rotate(rot.z,Z);

	X=X*m;
	Y=Y*m;
	Z=Z*m;
	
	update_mat();
}

void local_system::rotate(float ang,vector& v)
{
	static mat4x4 m;

	m.set_rotation(ang,v);

	X=X*m;
	Y=Y*m;
	Z=Z*m;
	
	update_mat();
}

void boundbox::add_point(vector& p)
{
	if (p.x>max.x)
		max.x=p.x;
	if (p.y>max.y)
		max.y=p.y;
	if (p.z>max.z)
		max.z=p.z;

	if (p.x<min.x)
		min.x=p.x;
	if (p.y<min.y)
		min.y=p.y;
	if (p.z<min.z)
		min.z=p.z;
}

void boundbox::add_point(float x,float y,float z)
{
	if (x>max.x)
		max.x=x;
	if (y>max.y)
		max.y=y;
	if (z>max.z)
		max.z=z;

	if (x<min.x)
		min.x=x;
	if (y<min.y)
		min.y=y;
	if (z<min.z)
		min.z=z;
}

int boundbox::ray_intersect(vector& ro,vector& rd,float& tnear,float& tfar)
{
    static float *rd_,*ro_,*min_,*max_,t1,t2,t;

    rd_=&rd.x;
    ro_=&ro.x;
    min_=&min.x;
    max_=&max.x;
    tnear=-BIG;
    tfar=BIG;

    int a;
    for( a=0;a<3;a++ )
     {
      if (rd_[a]>-SMALL && rd_[a]<SMALL)
         if (ro_[a]<min_[a] || ro_[a]>max_[a])
            return 0;
         else ;
      else {
            t1=(min_[a]-ro_[a])/rd_[a];
            t2=(max_[a]-ro_[a])/rd_[a];
            if (t1>t2)
               { t=t1; t1=t2; t2=t; }
            if (t1>tnear)
               tnear=t1;
            if (t2<tfar)
               tfar=t2;
			if (tnear>tfar || tfar<SMALL)
			   return 0;
           }
     }
    if (tnear>tfar || tfar<SMALL)
       return 0;
	return 2;
}

