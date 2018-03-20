/*************************************************************************//**
*@file
*@author Paul Hinker
* @brief Defines the function prototypes for the rectangle class.
******************************************************************************/

#ifndef _RECTANGLE_H
#define _RECTANGLE_H
#include "shape.h"
#include "graphics.h"
#include <iostream>
/*!
*@brief Contains the functions required for drawing a rectangle or
* The protected data stores dimensions of the rectangle.
*/
class Rectangle : public Shape
{
protected:
   /*! length of the rectangle*/
   float xcor;
   /*!Width of the rectangle*/
   float ycor;
    /*!Fill color of the rectangle*/
   float colorF[3]={0,0,0};
public:
	/*!Constructor for the rectangle*/
	
   Rectangle(float x, float y, float xcor, float ycor, const float *color, const float *c =Black, bool f =false);
	/*!Destructor for the rectangle*/
   ~Rectangle();
   /*!Checks if you have clicked inside the rectangle*/
   virtual bool contains(const float, const float);
   /*!Draws the Rectangle*/
   virtual void draw() const;
    /*!Draws the filled Rectangle*/
   virtual void drawfilled() const;
    /*!Draws the moved Rectangle*/
   virtual void moveshape(float newx, float newy);
};

#endif
