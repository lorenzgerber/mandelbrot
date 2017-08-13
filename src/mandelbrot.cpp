/*
 * mandelbrot.cpp
 *
 *  Created on: May 8, 2012
 *      Author: sr
 */

#include "mandelbrot.h"

/**
 * Constructor for Mandelbrot fractal. Argument is windowsize
 *
 * @param iWindowX		Argument is width of fractal window
 * @param iWindowY		Argument is height of fractal window
 */
Cmandelbrot::Cmandelbrot( int iWindowX, int iWindowY) : Fractal( iWindowX, iWindowY)
{
}


/**
 * Function to compute the Madelbrot fractal z*z+c
 *
 * @param _oZ 	Complex number z in equation z*z+c
 * @param _oC	Complex number c in equation z*z+c
 * @return		Returns computed value in equation z*z+c
 */
ComplexZ
Cmandelbrot::oEquation(ComplexZ & _oZ, ComplexZ & _oC)
{
	_oZ=_oZ*_oZ+_oC;
	return _oZ;
}


