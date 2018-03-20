/*************************************************************************//**
*@file
*@author Manasi Paste
* @brief Defines the function prototypes for the ellipse class.
******************************************************************************/
#ifndef _ELLIPSE_H
#define _ELLIPSE_H
#include "shape.h"
#include "graphics.h"
#include <iostream>
//Manasi Paste
/*!
*@brief Contains the functions required for setting and getting Ellipse arguments.
* The private data stores coordinates of the ellipse radii and fillcolor.
*/
class Ellipse :public Shape
{
protected: 
	/*!center X coordinate of ellipse*/
	float centerXcor;
	/*!center Y coordinate of ellipse*/
	float centerYcor;
	/*!Fill color of ellipse*/
	float colorFill[3]= {0,0,0};
public:
	/*!Constructor of the Ellipse*/
	Ellipse(float, float, float, float, const float*, const float* c= Black, bool f = false);
	/*!Checks if user has clicked inside the ellipse*/
	virtual bool contains(const float, const float) ;
	/*!Draw an unfilled ellipse*/
	virtual void draw() const ;
	/*!Draw a filled ellipse*/
   virtual void drawfilled() const ;
   /*!move the shape*/
   virtual void moveshape(float, float);
};

#endif
