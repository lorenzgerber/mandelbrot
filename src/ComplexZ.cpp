/**
 * @file	ComplexZ.cpp
 * Source file for the class ComplexZ
 * The class ComplexZ implements functions to handle complex numbers
 *
 * @author Sven Ronnback
 * @version 0.2
 *
 */

#include "ComplexZ.h"


/**
 *	Default constructor for class CompleZ,  z=0.0+í*0.0
 */

ComplexZ::ComplexZ( void)
{
	sZ.re = 0.0;
	sZ.im = 0.0;

}


/**
 *	Constructor for class ComplexZ
 *	Makes a copy of the complex number _oZ.
 *
 * @param[in] _oZ	Creates a new copy of oZ.
 */

ComplexZ::ComplexZ( ComplexZ &_oZ)
{
	sZ.re = _oZ.sZ.re;
	sZ.im = _oZ.sZ.im;
}


/**
 *  Constructor for class ComplexZ
 *  Takes real number and imaginary number as arguments
 *
 * @param[in] _rRe	Real part
 * @param[in] _rIe	Imaginary part
 */

ComplexZ::ComplexZ( double _rRe, double _rIm)
{
	sZ.re =	_rRe;
	sZ.im =	_rIm;
}


/***
 * Complex multiplication with complex number _oZ
 *
 * @param[in] _oZ	Complex number
 */

void
ComplexZ::mult( ComplexZ &_oZ)
{
	sZ.mult( &_oZ.sZ);
}


/**
 * Function returns the real part of the cimplex number
 *
 * @return			Real part of the complex number
 */

double
ComplexZ::rRe( void)
{
	return sZ.re;
}


/**
 * Function returns the imaginary part of the complex number
 *
 * @return			Imaginary part of the complex number
 */

double
ComplexZ::rIm( void)
{
	return sZ.im;
}


/**
 *	Complex subtraction. Result is returned.
 *
 * @param[in] 	_oZ	Complex subtraction, *this - _oZ
 * @return			Returns a the result of the complex subtraction
 */

ComplexZ
ComplexZ::oSub(ComplexZ &_oZ)
{
	ComplexZ oZr(*this);
	oZr.sub(_oZ);
	return oZr;
}


/**
 *	Function computes the squared absolute value, re*re+im*im
 *
 * @return		The squared absolute value for the complex number
 */

double
ComplexZ::rAbsSqr( void)
{
	return sZ.rAbsSqr();
}


/**
 *	Function add the complex number _oZ
 *
 * @param _oZ	Complex number to add
 */

void
ComplexZ::add( ComplexZ &_oZ)
{
	sZ.add( _oZ.sZ);
}


/**
 * 	Function subtracts the complex number _oZ
 *
 *
 * @param[in] _oZ	Subtracts complex number _oZ
 */

void
ComplexZ::sub( ComplexZ &_oZ)
{
	sZ.sub( _oZ.sZ);
}


/**
 *	Function squares the complex number (multiplication with itself)
 *	z*z
 */

void
ComplexZ::sqr( void)
{
	sZ.sqr();
}


/**
 *	Complex multiplication with operator *
 *
 * @param[in] _oZ	Complex multiplication with argument _oZ
 * @return 			Returns the result of the complex multiplication.
 */

ComplexZ
ComplexZ::operator*( ComplexZ &oZ)
{
	ComplexZ oZout(*this);
	oZout.mult(oZ);
	return oZout;
}

/**
 *	Adds two complex numbers
 *
 * @param[in] _oZ	Complex addition
 * @return			Returns the result of complex addition
 */

ComplexZ ComplexZ::operator+( ComplexZ &_oZ)
{
	ComplexZ oZout(*this);
	oZout.add(_oZ);
	return oZout;
}


/**
 *	Subtracts two complex numbers
 *
 * @param[in] _oZ	Subtraction with this complex number.
 * @return			Returns the result of the complex subtraction
 */

ComplexZ
ComplexZ::operator-( ComplexZ &oZ)
{
	ComplexZ oZout(*this);
	oZout.sub(oZ);
	return oZout;
}

/**
 * Returns the angle of the complex number
 *
 * @return		Returns the angle of the complex number. Interval [0..2*pi]
 */

double
ComplexZ::rGetAtan2(void)
{
	double r=sZ.rGetAtan2();
	return (r<0.0)? r+=M_PI:r;
}

/**
 *	Function scale the complex number with the factor d.
 **
 * @param[in] _d	Scale factor _d
 */

void
ComplexZ::scale( double _r)
{
	sZ.re *= _r;
	sZ.im *= _r;
}

/**
 * 	Clones the current complex number
 *
 * @return	 		Returns a copy of the current complex number
 */
ComplexZ
ComplexZ::oClone( void)
{
	ComplexZ _oZ(*this);
	return _oZ;
}

/**
 *	Default destructor for the complex number.
 *	Called with the complex number is destroyed
 *
 */

ComplexZ::~ComplexZ( void)
{
}

