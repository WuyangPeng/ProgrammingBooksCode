//============================================================================
//
// 3D/4D Matrix Classes
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


#include "VectorClasses.h"


class Matrix3D
{
	private:
	
		float	n[3][3];
	
	public:
		
		Matrix3D() {}
		
		C4API Matrix3D(const Vector3D& c1, const Vector3D& c2, const Vector3D& c3);
		C4API Matrix3D(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22);
		
		C4API Matrix3D& Set(const Vector3D& c1, const Vector3D& c2, const Vector3D& c3);
		C4API Matrix3D& Set(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22);
		
		float& operator ()(long i, long j)
		{
			return (n[j][i]);
		}
		
		const float& operator ()(long i, long j) const
		{
			return (n[j][i]);
		}
		
		Vector3D& operator [](long j)
		{
			return (*reinterpret_cast<Vector3D *>(n[j]));
		}
		
		const Vector3D& operator [](long j) const
		{
			return (*reinterpret_cast<const Vector3D *>(n[j]));
		}
		
		Vector3D GetRow(long i) const
		{
			return (Vector3D(n[0][i], n[1][i], n[2][i]));
		}
		
		Matrix3D& SetRow(long i, const Vector3D& row)
		{
			n[0][i] = row.x;
			n[1][i] = row.y;
			n[2][i] = row.z;
			return (*this);
		}
		
		Matrix3D& operator *=(const Matrix3D& m);
		Matrix3D& operator *=(float t);
		Matrix3D& operator /=(float t);
		
		Matrix3D& SetIdentity(void);
		
		friend Matrix3D operator *(const Matrix3D& m1, const Matrix3D& m2);
		friend Matrix3D operator *(const Matrix3D& m, float t);
		friend Matrix3D operator /(const Matrix3D& m, float t);
		friend Vector3D operator *(const Matrix3D& m, const Vector3D& v);
		friend Vector3D operator *(const Matrix3D& m, const Point3D& p);
		friend Vector3D operator *(const Vector3D& v, const Matrix3D& m);
		friend Vector3D operator *(const Point3D& p, const Matrix3D& m);
		friend bool operator ==(const Matrix3D& m1, const Matrix3D& m2);
		friend bool operator !=(const Matrix3D& m1, const Matrix3D& m2);
};


inline Matrix3D operator *(float t, const Matrix3D& m)
{
	return (m * t);
}


float Determinant(const Matrix3D& m);
Matrix3D Inverse(const Matrix3D& m);
Matrix3D Adjugate(const Matrix3D& m);
Matrix3D Transpose(const Matrix3D& m);


class Matrix4D
{
	private:
		
		float	n[4][4];
	
	public:
		
		Matrix4D() {}
		
		Matrix4D(const Vector4D& c1, const Vector4D& c2, const Vector4D& c3, const Vector4D& c4);
		Matrix4D(float n00, float n01, float n02, float n03, float n10, float n11, float n12, float n13, float n20, float n21, float n22, float n23, float n30, float n31, float n32, float n33);
		
		Matrix4D& Set(const Vector4D& c1, const Vector4D& c2, const Vector4D& c3, const Vector4D& c4);
		Matrix4D& Set(float n00, float n01, float n02, float n03, float n10, float n11, float n12, float n13, float n20, float n21, float n22, float n23, float n30, float n31, float n32, float n33);
		
		float& operator ()(long i, long j)
		{
			return (n[j][i]);
		}
		
		const float& operator ()(long i, long j) const
		{
			return (n[j][i]);
		}
		
		Vector4D& operator [](long j)
		{
			return (*reinterpret_cast<Vector4D *>(n[j]));
		}
		
		const Vector4D& operator [](long j) const
		{
			return (*reinterpret_cast<const Vector4D *>(n[j]));
		}
		
		Vector4D GetRow(long i) const
		{
			return (Vector4D(n[0][i], n[1][i], n[2][i], n[3][i]));
		}
		
		Matrix4D& SetRow(long i, const Vector3D& row)
		{
			n[0][i] = row.x;
			n[1][i] = row.y;
			n[2][i] = row.z;
			n[3][i] = 0.0F;
			return (*this);
		}
		
		Matrix4D& SetRow(long i, const Vector4D& row)
		{
			n[0][i] = row.x;
			n[1][i] = row.y;
			n[2][i] = row.z;
			n[3][i] = row.w;
			return (*this);
		}
		
		C4API Matrix4D& operator =(const Matrix3D& m);
		C4API Matrix4D& operator *=(const Matrix4D& m);
		C4API Matrix4D& operator *=(const Matrix3D& m);
		
		C4API Matrix4D& SetIdentity(void);
		
		friend C4API Matrix4D operator *(const Matrix4D& m1, const Matrix4D& m2);
		friend C4API Matrix4D operator *(const Matrix4D& m1, const Matrix3D& m2);
		friend C4API Vector4D operator *(const Matrix4D& m, const Vector4D& v);
		friend C4API Vector4D operator *(const Vector4D& v, const Matrix4D& m);
		friend C4API Vector4D operator *(const Matrix4D& m, const Vector3D& v);
		friend C4API Vector4D operator *(const Vector3D& v, const Matrix4D& m);
		friend C4API Vector4D operator *(const Matrix4D& m, const Point3D& p);
		friend C4API Vector4D operator *(const Point3D& p, const Matrix4D& m);
		friend C4API Vector4D operator *(const Matrix4D& m, const Vector2D& v);
		friend C4API Vector4D operator *(const Vector2D& v, const Matrix4D& m);
		friend C4API Vector4D operator *(const Matrix4D& m, const Point2D& p);
		friend C4API Vector4D operator *(const Point2D& p, const Matrix4D& m);
		friend C4API bool operator ==(const Matrix4D& m1, const Matrix4D& m2);
		friend C4API bool operator !=(const Matrix4D& m1, const Matrix4D& m2);
};


C4API float Determinant(const Matrix4D& m);
C4API Matrix4D Inverse(const Matrix4D& m);
C4API Matrix4D Adjugate(const Matrix4D& m);
C4API Matrix4D Transpose(const Matrix4D& m);
