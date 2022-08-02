#pragma once

#include <assert.h>

template <class FLTYPE> class Point3
{
	public:

	FLTYPE v[3];

	typedef Point3<FLTYPE> Point3_FT;

  inline FLTYPE &x() {return v[0];} ;
  inline FLTYPE &y() {return v[1];};
	inline FLTYPE &z() {return v[2];};
  inline FLTYPE & operator [] ( const int i ){
			assert(i>=0 && i<3);
			return v[i];
	}
	inline const FLTYPE & operator [] ( const int i ) const {
			assert(i>=0 && i<3);
			return v[i];
	}

  inline Point3<FLTYPE> ( void ) { }
  inline Point3<FLTYPE> ( const FLTYPE nx, const FLTYPE ny, const FLTYPE nz ){
			v[0] = nx; v[1] = ny; v[2] = nz;
	}
	inline Point3<FLTYPE> ( Point3<FLTYPE> const & p)  {   
			v[0]= p.v[0];    v[1]= p.v[1];    v[2]= p.v[2];
	}
	inline Point3<FLTYPE> & operator =( Point3<FLTYPE> const & p){
			v[0]= p.v[0]; v[1]= p.v[1]; v[2]= p.v[2];
			return *this;
	}
  inline Point3<FLTYPE> operator + ( Point3<FLTYPE> const & p) const { 
			return Point3<FLTYPE>( v[0]+p.v[0], v[1]+p.v[1], v[2]+p.v[2] );
	}
  inline Point3<FLTYPE> operator - ( Point3<FLTYPE> const & p) const {
			return Point3<FLTYPE>( v[0]-p.v[0], v[1]-p.v[1], v[2]-p.v[2] );
	}
  inline Point3<FLTYPE> operator * ( const FLTYPE s ) const {
			return Point3<FLTYPE>( v[0] * s, v[1] * s, v[2] * s );
	}
	inline Point3<FLTYPE> operator / ( const FLTYPE s ) const {
			return Point3<FLTYPE>( v[0] / s, v[1] / s, v[2] / s );
	}
  inline FLTYPE operator * ( Point3<FLTYPE> const & p ) const {
			return ( v[0]*p.v[0] + v[1]*p.v[1] + v[2]*p.v[2] );
	}  
  inline Point3<FLTYPE> operator ^ ( Point3<FLTYPE> const & p ) const {
			return Point3<FLTYPE>(
				    v[1]*p.v[2] - v[2]*p.v[1],
						v[2]*p.v[0] - v[0]*p.v[2],
						v[0]*p.v[1] - v[1]*p.v[0]
				);
	}  
  inline Point3<FLTYPE> & operator += ( Point3<FLTYPE> const & p){
			v[0] += p.v[0];    v[1] += p.v[1];     v[2] += p.v[2];
			return *this;
	}
  inline Point3<FLTYPE> & operator -= ( Point3<FLTYPE> const & p){
			v[0] -= p.v[0];    v[1] -= p.v[1];     v[2] -= p.v[2];
			return *this;
	}
  inline Point3<FLTYPE> & operator *= ( const FLTYPE s ){
			v[0] *= s;    v[1] *= s;    v[2] *= s;
			return *this;
	}
  inline Point3<FLTYPE> & operator /= ( const FLTYPE s ){
			v[0] /= s;    v[1] /= s;    v[2] /= s;
			return *this;
	}
  inline FLTYPE Length( void ) const {
      return (FLTYPE)(sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] ));
	}
  inline FLTYPE LengthSquared( void ) const{
			return ( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
	}
  inline Point3<FLTYPE> & Scale( const FLTYPE sx, const FLTYPE sy, const FLTYPE sz );

	inline Point3<FLTYPE> & Normalize( void ){
			FLTYPE n = (FLTYPE)(sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
			if(n>0.0) {	v[0] /= n;	v[1] /= n;	v[2] /= n;  }
			return *this;
	}
  inline bool operator == ( Point3<FLTYPE> const & p ) const {
			return (v[0]==p.v[0] && v[1]==p.v[1] && v[2]==p.v[2]);
	} 
  inline bool operator != ( Point3<FLTYPE> const & p ) const {
			return ( (v[0]!=p.v[0]) || (v[1]!=p.v[1]) || (v[2]!=p.v[2]));
	}
  inline bool operator <  ( Point3<FLTYPE> const & p ) const {
			return	(v[2]!=p.v[2])?(v[2]<p.v[2]):
							(v[1]!=p.v[1])?(v[1]<p.v[1]):
							(v[0]<p.v[0]);
	}
	inline bool operator >  ( Point3<FLTYPE> const & p ) const {
			return	(v[2]!=p.v[2])?(v[2]>p.v[2]):
							(v[1]!=p.v[1])?(v[1]>p.v[1]):
							(v[0]>p.v[0]);
	}

	inline bool operator <= ( Point3<FLTYPE> const & p ) const {
			return	(v[2]!=p.v[2])?(v[2]< p.v[2]):
							(v[1]!=p.v[1])?(v[1]< p.v[1]):
							(v[0]<=p.v[0]);
	}

	inline bool operator >= ( Point3<FLTYPE> const & p ) const {
			return	(v[2]!=p.v[2])?(v[2]> p.v[2]):
							(v[1]!=p.v[1])?(v[1]> p.v[1]):
							(v[0]>=p.v[0]);
	}
  inline FLTYPE Distance( Point3<FLTYPE> const & p ) const{
			return (*this-p).Length();
	}

	inline FLTYPE SquaredDistance( Point3<FLTYPE> const & p ) const {
			return (*this-p).LengthSquared();
	}	

}; // end class definition


template <class FLTYPE>
inline FLTYPE Angle( Point3<FLTYPE> const & p1, Point3<FLTYPE> const & p2 ){
    return (FLTYPE) acos( (p1*p2)/(p1.Length()*p2.Length()) );
}

template <class FLTYPE>
inline Point3<FLTYPE> operator - ( Point3<FLTYPE> const & p ){
    return Point3<FLTYPE>( -p.v[0], -p.v[1], -p.v[2] );
}

template <class FLTYPE>
inline Point3<FLTYPE> operator * ( const FLTYPE s, Point3<FLTYPE> const & p ){
    return Point3<FLTYPE>( p.v[0] * s, p.v[1] * s, p.v[2] * s );
}

template <class FLTYPE>
inline FLTYPE Length( Point3<FLTYPE> const & p ){
		return sqrt( p.v[0]*p.v[0] + p.v[1]*p.v[1] + p.v[2]*p.v[2] );
}

template <class FLTYPE>
inline FLTYPE LengthSquared( Point3<FLTYPE> const & p ){
    return ( p.v[0]*p.v[0] + p.v[1]*p.v[1] + p.v[2]*p.v[2] );
}

template <class FLTYPE>
inline Point3<FLTYPE> & Normalize( Point3<FLTYPE> & p ){
		FLTYPE n = sqrt( p.v[0]*p.v[0] + p.v[1]*p.v[1] + p.v[2]*p.v[2] );
    if(n>0.0) p/=n;
    return p;
}

template <class FLTYPE>
inline FLTYPE Distance( Point3<FLTYPE> const & p1,Point3<FLTYPE> const & p2 ){
    return Length(p1-p2);
}

template <class FLTYPE>
inline Point3<FLTYPE> & RotateZ( Point3<FLTYPE> & p, FLTYPE _angle){
  FLTYPE c=cos(_angle);
	FLTYPE s=sin(_angle);
  FLTYPE cx=c*p.x()-s*p.y();
  p.y()= s*p.x()+c*p.y();
	p.x()= cx;
	return p;
}

typedef Point3<short>  Point3s;
typedef Point3<int>	   Point3i;
typedef Point3<float>  Point3f;
typedef Point3<double> Point3d;

#ifdef __GL_H__
inline void glVertex(Point3<int> const & p)   { glVertex3iv(p.v);};
inline void glVertex(Point3<short> const & p) { glVertex3sv(p.v);};
inline void glVertex(Point3<float> const & p) { glVertex3fv(p.v);};
inline void glVertex(Point3<double> const & p){ glVertex3dv(p.v);};
inline void glNormal(Point3<int> const & p)   { glNormal3iv(p.v);};
inline void glNormal(Point3<short> const & p) { glNormal3sv(p.v);};
inline void glNormal(Point3<float> const & p) { glNormal3fv(p.v);};
inline void glNormal(Point3<double> const & p){ glNormal3dv(p.v);};
inline void glTexCoord(Point3<int> const & p)   { glTexCoord3iv(p.v);};
inline void glTexCoord(Point3<short> const & p) { glTexCoord3sv(p.v);};
inline void glTexCoord(Point3<float> const & p) { glTexCoord3fv(p.v);};
inline void glTexCoord(Point3<double> const & p){ glTexCoord3dv(p.v);};
inline void glTranslate(Point3<float> const & p) { glTranslatef(p.v[0],p.v[1],p.v[2]);};
inline void glTranslate(Point3<double> const & p){ glTranslated(p.v[0],p.v[1],p.v[2]);};
inline void glScale(Point3<float> const & p) { glScalef(p.v[0],p.v[1],p.v[2]);};
inline void glScale(Point3<double> const & p){ glScaled(p.v[0],p.v[1],p.v[2]);};
#endif
