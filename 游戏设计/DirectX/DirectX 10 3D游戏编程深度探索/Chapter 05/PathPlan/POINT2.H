/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

struct point2
{
	float x, y;

public:

	float Length()
	{
		return (float)sqrt( x*x + y*y );
	}

	point2(){}

	point2( float X, float Y ) : x( X ), y( Y ) {}

	static point2 Midpoint( const point2 &a, const point2 &b )
	{
		point2 out( (a.x + b.x) / 2.f, (a.y + b.y) / 2.f );
		return out;
	}

	static float Dist( const point2 &a, const point2 &b )
	{
		point2 temp( b.x - a.x, b.y - a.y );
		return temp.Length();
	}

	void Normalize(){
		float foo=1/Length();	x*=foo;	y*=foo;
	}
};

//returns point2+point2
inline point2 operator+(point2 const &a, point2 const &b)
{
	return point2(a.x+b.x,a.y+b.y);
}; 


//returns point2-point2
inline point2 operator-(point2 const &a, point2 const &b)
{
	return point2(a.x-b.x,a.y-b.y);
}; 


//returns point2*float
inline point2 operator*(point2 const &a, float const &b)
{
	return point2(a.x*b,a.y*b);
}; 


//returns float*point2
inline point2 operator*(float  const &a, point2 const &b)
{
	return point2(a*b.x,a*b.y);
}; 


//returns point2/float
inline point2 operator/(point2 const &a, float const &b)
{
	return point2(a.x/b,a.y/b);
}; 

// dot product
inline float operator*(point2 const &a, point2 const &b)
{
	return a.x * b.x + a.y * b.y;
}; 
