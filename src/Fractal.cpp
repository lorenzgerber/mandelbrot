/**
 * @file	Fractal.cpp
 * Source file for the class Fractal.cpp
 * The class Fractal implements calculation on fractal based on complex numbers
 * Fractal equation z(k+1)=(z(k))^3+c
 *
 * @author Sven Ronnback
 * @version 0.1
 *
 */

#include "Fractal.h"
#include <stdio.h>





/**
 *		Constructor of Fractal that uses default pixelbuffer size
  */
Fractal::Fractal(void)
{
	iSizeX=_iDEFWINDOW_X;
	iSizeY=_iDEFWINDOW_Y;
	int iSize = iSizeX*iSizeY;
	psFractal =  new struct sFRACTALCOLOR[iSize];
}


/**
 * Construct a fractal with a with and height given as arguments
 *
 * @param iWindowX	With of fractal pixelbuffer
 * @param iWindowY	Height of fractal pixelbuffer
 */
Fractal::Fractal(int iWindowX, int iWindowY)
{
	iSizeX= iWindowX;
	iSizeY= iWindowY;
	int iSize = iSizeX*iSizeY;
	psFractal =  new struct sFRACTALCOLOR[iSize];
}

/**
 *
 */
Fractal::~Fractal(void)
{
	if(psFractal)
		delete psFractal;
}


unsigned int
Fractal::uiGetPixBufColor( int iX, int iY)
{
	unsigned int uiColor=0x00FFFFFF;
	if(iX>=0 && iX<iSizeX && iY>=0 && iY<iSizeY && psFractal){
		uiColor = psFractal[iY+iX*iSizeY].uiGetColor();
	}
	return uiColor;
}





/**
 *
 * @param oZmid
 * @param oZxy
 * @param rZoom
 * @return
 */
bool
Fractal::bCalc(ComplexZ & _oZmid, ComplexZ & _oZxy, double rScale, int iMaxIterations)
{
	bool bRet=false;

	int iNx = iSizeX;
	int iNy = iSizeY;

	const double rAbsMax = 2.0*2.0;


	ComplexZ oZstart= _oZmid;
	ComplexZ oZend= _oZmid;
	ComplexZ oZxy(_oZxy);

	//printf("Scale:%f >",rScale);
	oZxy.scale(0.5/rScale);

	oZstart.sub( oZxy);
	oZend.add( oZxy);
	oZxy=oZend-(oZstart);


	const double rDx = oZxy.rRe()/(double)(iNx-1);
	const double rDy = oZxy.rIm()/(double)(iNy-1);

	ComplexZ oZiter(oZstart);
	ComplexZ oZdx(rDx,0);
	ComplexZ oZdy(0,rDy);

	printf("Startar fraktalberäkning ... \n");
	int iIndex=0;
	bRet=true;
	for (int i=0; i<iNx; i++) {
		oZstart.add(oZdx);

		ComplexZ oC(oZstart);
		//printf("<%d/%d>\n", i,iNx);
		for (int j=0; j<iNy; j++, oC.add(oZdy)) {

			ComplexZ oZ(oC);	   //


			/**
			 * Iterera det komplexa talet C, Z(k+1)=Z(k)^2+C
			 */
			/** Iterate z^2+c  (oZ^2+oC
			 *  Iterate max 255 times
			 *  Stop if the complex number diverges
			 */
			double rAbsSqr=0.0;
			int n=0;
			for(n=0; n<iMaxIterations; n++){
				rAbsSqr= oZ.rAbsSqr();
				if (rAbsSqr < rAbsMax) {
					oZ=oEquation(oZ,oC);			// Calls function that calculates fractal
				}
				else {
					break;	 // If radius diverges, stop iteraton.
				}
			}
			psFractal[ iIndex].generateColor( n, iMaxIterations, rAbsSqr, rAbsMax, oZ);
			iIndex++;
		}
	}
	printf("Fraktalen beräknad\n");
	return bRet;
}

/**
 * Function that  holds equation to generate the fractal
 *  The function defines the fractal
 *
 * @param _oZ  Complex number z in equation z=z^3+c
 * @param _oC  Complex number c in equation z=z^3+c
 * @return
 */
ComplexZ
Fractal::oEquation(ComplexZ & _oZ, ComplexZ & _oC)
{
	//_oZ.conj();
	_oZ=_oZ*_oZ*_oZ+_oC;
	return _oZ;
}


