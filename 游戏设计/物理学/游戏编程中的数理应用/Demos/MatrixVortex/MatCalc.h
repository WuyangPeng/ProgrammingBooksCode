// MatCalc.h: interface for the MatCalc class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MATCALC_H_
#define _MATCALC_H_


class MatCalc;
typedef MatCalc* (*Func[5]) (MatCalc *, MatCalc *);

class MatCalc  
{
	friend class OGL_Wrapper;
	
private:
	float *pData;
	int row, col;

	float *getRow(int r) const;
	float *getCol(int c) const;
	float dotRowCol(float *r, float *c) const;

	// An array of function pointers, which does all of our calculations for us
	static Func pf_solve;

public:
	MatCalc(int r, int c, float *pItem = 0);
	MatCalc(const MatCalc &m);
	MatCalc &operator=(const MatCalc &m);
	virtual ~MatCalc();

	static MatCalc *multiply(MatCalc *pOne, MatCalc *pTwo);
	static MatCalc *add(MatCalc *pOne, MatCalc *pTwo);
	static MatCalc *subtract(MatCalc *pOne, MatCalc *pTwo);
	static MatCalc *dot(MatCalc *pOne, MatCalc *pTwo);
	static MatCalc *cross(MatCalc *pOne, MatCalc *pTwo);

	static MatCalc *normalize(MatCalc *pOne);


};

#endif 