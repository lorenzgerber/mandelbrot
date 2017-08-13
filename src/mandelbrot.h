/**
 * @file	Mandelbrot.h
 * Header file for the class Cmandelbrot
 * The class Cmandelbrot implements calculation on Mandelbrot fractal based on complex numbers
 * Fractal equation z(k+1)=z(k)^2+c
 *
 * @author Sven Ronnback
 * @version 0.1
 *
 */
#ifndef MANDELBROT_H_
#define MANDELBROT_H_
#include "Fractal.h"


class Cmandelbrot: public Fractal
{

	inline ComplexZ oEquation( ComplexZ & oZ, ComplexZ &oC);

public:
	Cmandelbrot(int iWindowX, int iWindowY);


};



#endif /* MANDELBROT_H_ */
