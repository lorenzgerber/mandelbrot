/**
 * @file	ComplexZ.h
 * Header file for the class ComplexZ
 * The class ComplexZ implements functions to handle complex numbers
 *
 * @author Sven Ronnback
 * @version 0.2
 *
 */
#include <math.h>

#ifndef COMPLEXZ_H_
#define COMPLEXZ_H_


/**
 *
 */
struct MY_COMPLEX
{
	double re;
	double im;

	/**
	 *
	 * @return
	 */
	inline double rAbsSqr(void)
	{
		return re*re+im*im;
	}

/**
 *
 */
	inline void sqr( void)
	{
		double r = re*re-im*im;
		im = 2.0*re*im;
		re=r;
	}


/**
 *
 *
 * @param[in]	_z		complex structure to add.
 */
	inline void add( MY_COMPLEX &_z)
	{
		re +=_z.re;
		im +=_z.im;

	}

/**
 * 	Add complex number _rX+i*_rY to existing structure
 *
 * @param[in] _rX	Real part of complex number.
 * @param[in] _rY	Imaginary part of complex number;
 */
	inline void add( double _rRe, double _rIm)
	{
		re +=	_rRe;
		im +=	_rIm;

	}

/**
 *  Get the angle of the complex number.
 *
 * @return		The angle in the interval 0-2*pi is returned
 */
	inline double rGetAtan2(void)
	{
		return atan2(im,re);
	}

/**
 *	Subtract the complex number _c from the structure.
 *
 * @param[in] 	c 	Subtract the complex number z from the structure
 */
	inline void sub( MY_COMPLEX &_z)
	{
		re -=	_z.re;
		im -=	_z.im;
	}

/**
 *	Multiplicates the complex number pointed my _p to the current structure
 *
 * @param[in]	_p	Pointer to complex structure
 */
	inline void mult( MY_COMPLEX *_p)
	{
		double _x1 =	re;
		double _y1 =	im;
		double _x2 =	_p->re;
		double _y2 =	_p->im;

		re=	_x1*_x2-_y1*_y2;
		im= _x1*_y2+_y1*_x2;

	}

};


/**
 *
 */
class ComplexZ
{
	MY_COMPLEX sZ;

public:
	ComplexZ(void);
	ComplexZ( ComplexZ &oZ);
	ComplexZ(double rRe, double rIm);

	void mult( ComplexZ &oZ);
	void add( ComplexZ &oZ);
	void sub( ComplexZ &oZ);
	void scale( double r);
	inline void conj( void) { sZ.im = -sZ.im;}
	inline void add( double rX, double rY){ sZ.add(rX,rY);}
	void sqr(void);

	double rAbsSqr( void);
	double rRe(void);
	double rIm(void);

	ComplexZ oSub( ComplexZ &oZ);
	ComplexZ operator*( ComplexZ &oZ);
	ComplexZ operator+( ComplexZ &oZ);
	ComplexZ operator-( ComplexZ &oZ);

	double rGetAtan2(void);
	ComplexZ oClone( void);
	virtual ~ComplexZ();
};

#endif /* COMPLEXZ_H_ */
