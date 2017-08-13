/**
 * @file	Fractal.h
 * Header file for the class Fractal.cpp
 * The class Fractal implements calculation on fractal based on complex number
 * Fractal equation z=(!z)^4+c  where !z is the complex conjugate.
 *
 * @author Sven Ronnback
 * @version 0.1
 *
 */

#ifndef FRACTAL_H_
#define FRACTAL_H_
#include "ComplexZ.h"
#include <math.h>

 // Default window size
#define _iDEFWINDOW_X 800
#define _iDEFWINDOW_Y 800

struct sFRACTALCOLOR
{
	unsigned char ucRed, ucBlue, ucGreen;;

	/**
	 * Function that generates a color for the fractal based on arguments
	 *
	 * @param n			Number of iterations on pixel
	 * @param rSqrAbs	Absolute value of complex number squared
	 * @param rAbsMax	Squared divergence point
	 * @param oZ		Complex number that was iterated
	 */
	void generateColor( int n, int iMaxIterations, double rSqrAbs, double rAbsMax, ComplexZ &oZ)
	{
		unsigned int uiColor =  sqrt(rSqrAbs)*(255.0)/(rAbsMax);
		uiColor += 0x08080 << (n*16)/iMaxIterations;
		ucRed=uiColor;
		ucGreen= uiColor>>8;
		ucBlue= uiColor>>16;
	}

	/**
	 * Retunrs a pixbuf color for the stored color values
	 *
	 * @return
	 */
	unsigned int uiGetColor(void)
	{
		unsigned int uiColor= ucRed<<16;
		uiColor += ucGreen<<8;
		uiColor += ucBlue;
		return uiColor;
	}


};


class Fractal
{
	struct sFRACTALCOLOR *psFractal;
	virtual inline ComplexZ oEquation( ComplexZ & oZ, ComplexZ &oC);

public:
	int iSizeX, iSizeY;					// Size of fractal window
	Fractal(void);
	Fractal(int iWindowX, int iWindowY);
	virtual ~Fractal(void);


	bool bCalc(ComplexZ & oZmid, ComplexZ & oZxy, double rZoom, int iMaxIterations);
	unsigned int uiGetPixBufColor(int iX, int Y);


};


#endif /* FRACTAL_H_ */
