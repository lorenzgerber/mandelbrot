

//============================================================================
// Name        : Fractal.cpp
// Author      : S. Ronnback
// Version     : v 0.1
// Copyright   :
// Description : Mandelbrot calculator using GTK+
//============================================================================


#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <time.h>

#include "ComplexZ.h"
#include "mandelbrot.h"
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif


// Structure that holds the default size of the fractal window

struct sFRACTAL
{
	GdkVisual* pGDKvisual2;
	GdkImage* pGDKimage2;
	GtkWidget* pWindow2;
	GtkWidget* pImage2;

} sFractal={0,0,0,0};

ComplexZ oZmid(-0.6,0.4);
ComplexZ oZxy(2,2);
float zoom = 0.9;

// Forward declaration
bool
bCalc_Fractal( ComplexZ &_oZmid, ComplexZ &_oZxy, double _rScale);



/**
 *  Function that tracks the mouse pointer on the screen
 *
 * @param widget
 * @return
 */
static gboolean time_handler( GtkWidget *widget)
{


	GdkDisplay *pDisplay = gdk_display_get_default ();
	GdkWindow *pWindow = gtk_widget_get_window(widget);

	int iX,iY, jX, jY, iW, iH, realX, realY;
	gdk_display_get_pointer(pDisplay, NULL, &iX, &iY, NULL);
	gdk_window_get_position(pWindow, &jX, &jY);
	gdk_window_get_size(pWindow, &iW, &iH);

	realX = iX - (jX + ((800 - iW)/2));
	if(realX < 0){
		realX = 0;
	} else if (realX > 800){
		realX = 800;
	}
	realY = iY - (jY + ((800 - iH)/2));
	if(realY < 0){
		realY = 0;
	} else if (realY > 800){
		realY = 800;
	}

	printf("X:%d Y:%d x:%d y:%d W:%d H:%d realX:%d realY: %d\n",iX,iY, jX, jY, iW, iH, realX, realY);


	return TRUE;
}



/**
 *
 */
static void fractal_destroy(void)
{
	gtk_main_quit();
}


/**
 *	Function is called when the fractal window is called.
 *
 * @param widget	Calling widget. Box widget.
 * @param data
 */
void fractal_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data)
{


	GdkDisplay *pDisplay = gdk_display_get_default ();
	GdkWindow *pWindow = gtk_widget_get_window(sFractal.pWindow2);


	if (event->type == GDK_BUTTON_PRESS){
		if (event->button == 1){
			printf("Left Button Click\n");

			/* get cursor position */
			int iX,iY, jX, jY, iW, iH, realX, realY;
			gdk_display_get_pointer(pDisplay, NULL, &iX, &iY, NULL);
			gdk_window_get_position(pWindow, &jX, &jY);
			gdk_window_get_size(pWindow, &iW, &iH);


			double step = 1.0/zoom/400.0;
			double xOrigo = oZmid.rRe()- 1/zoom;
			double yOrigo = oZmid.rIm()- 1/zoom;

			realX = (iX - (jX + ((800 - iW)/2)));
			if(realX < 0){
				realX = 0;
			} else if (realX > 800){
				realX = 800;
			}
			realY = (iY - (jY + ((800 - iH)/2)));
			if(realY < 0){
				realY = 0;
			} else if (realY > 800){
				realY = 800;
			}

			oZmid = ComplexZ (xOrigo + (realX * step), yOrigo + (realY * step));

			GtkWidget *child = gtk_bin_get_child(GTK_BIN(sFractal.pWindow2));
			gtk_widget_destroy(child);

			sFractal.pGDKimage2 = NULL;
			sFractal.pGDKvisual2 = NULL;
			sFractal.pImage2 = NULL;

			zoom *=2;
			printf("zoom:%fl x:%fl y:%fl\n", zoom, oZmid.rRe(), oZmid.rIm());
			bCalc_Fractal(oZmid,oZxy,zoom);
		} else if (event->button == 3) {
			printf("Right Button Click\n");

			GtkWidget *child = gtk_bin_get_child(GTK_BIN(sFractal.pWindow2));
			gtk_widget_destroy(child);

			sFractal.pGDKimage2 = NULL;
			sFractal.pGDKvisual2 = NULL;
			sFractal.pImage2 = NULL;

			zoom /=2;
			bCalc_Fractal(oZmid,oZxy,zoom);
		}
	}
}


/**
 *	Function that calculates a fractal and shows it in a GTK+ pixbuf
 *
 * @param[in] 	_oZmid		Center coordinate for the Mandelbrot fractal
 * @param[in] 	_oZxy		Size of the Mandelbrot window
 * @param[in] 	_rZoomFactor	Zoom factor ( Deduces the size of the window)
 * @return		Returns true success, otherwise false
 */
bool
bCalc_Fractal( ComplexZ &_oZmid, ComplexZ &_oZxy, double _rScale)
{
	// Create fractal
	int iSizeX=800;
	int iSizeY=800;
	Fractal  *poFractal= new Cmandelbrot( iSizeX, iSizeY);
	//Fractal  *poFractal= new Fractal( iSizeX, iSizeY);

	if(!poFractal)
			return false;

	bool bRet=poFractal->bCalc(_oZmid,_oZxy,_rScale, 255);

	if (sFractal.pGDKimage2 == NULL ) {
		sFractal.pGDKvisual2 = gdk_visual_get_system();
		sFractal.pGDKimage2= gdk_image_new( GDK_IMAGE_NORMAL, sFractal.pGDKvisual2, poFractal->iSizeX,poFractal->iSizeY);
	}

	if (sFractal.pGDKimage2 == NULL ) {
		fprintf( stderr, "Not able to create gdkimage object\n");
		return FALSE;
	}

	if(sFractal.pWindow2== NULL){
		sFractal.pWindow2= gtk_window_new(GTK_WINDOW_TOPLEVEL);
	}
	if(sFractal.pImage2==NULL){
		sFractal.pImage2= gtk_image_new_from_image( sFractal.pGDKimage2, NULL );
	}

	for (int i=0; i<poFractal->iSizeX; i++) {
		for (int j=0; j<poFractal->iSizeY; j++) {
			unsigned int uiColor = poFractal->uiGetPixBufColor(i,j);
			gdk_image_put_pixel( sFractal.pGDKimage2, i, j,(int) uiColor); //65535*rAbsSqr/rMax);
		}
	}
	GtkWidget *pEvent_box = gtk_event_box_new ();
	gtk_container_add (GTK_CONTAINER (pEvent_box), sFractal.pImage2);


	gtk_container_add(GTK_CONTAINER (sFractal.pWindow2), pEvent_box);

	gtk_widget_show_all(sFractal.pWindow2);
	gtk_window_set_title (GTK_WINDOW (sFractal.pWindow2), "Mandelbrotfraktal");


	gtk_signal_connect(GTK_OBJECT (sFractal.pWindow2), "destroy",GTK_SIGNAL_FUNC (fractal_destroy), NULL);
	/*
	g_timeout_add(500, (GSourceFunc) time_handler, (gpointer) sFractal.pWindow2);
	*/

	g_signal_connect (G_OBJECT (pEvent_box),"button_press_event",G_CALLBACK (fractal_clicked), NULL);

	if(poFractal)
		delete poFractal;

	return bRet;
}




/**
 *	Main function of Fractal program
 *
 * @param argc		Holds number of arguments
 * @param argv		String array with arguments
 * @return			returns 0 in success
 */

int main(int argc,char *argv[])
{

	gtk_init(&argc, &argv);

	clock_t begin = clock();
	bool bRet=bCalc_Fractal(oZmid,oZxy,zoom);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time spent calculating: %fl\n", time_spent);

	gtk_main();

	return bRet?0:1;
}

