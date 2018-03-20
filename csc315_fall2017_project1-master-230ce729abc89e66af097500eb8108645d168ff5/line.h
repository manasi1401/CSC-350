/*************************************************************************//**
 * @file
 * @brief Defines the function prototypes for the Line class.
 *****************************************************************************/
#ifndef _LINE_H
#define _LINE_H
#include "shape.h"
#include "graphics.h"
#include <iostream>
//Manasi Paste
/*!
*@brief Contains the functions required for setting and getting Line arguments.
* The protected data stores second coordinates of the line.
*/
class Line: public Shape
{

protected:
	/*!The X coordinate of the second end*/
	float xcor;
	/*!The Y coordinate of the position*/
	float ycor;
public:
	/*!Constructor of line*/
	Line(float, float, float, float, const float*, bool f = false);
	/*!Draws a line*/
	virtual void draw()const;
	virtual void drawfilled()const;
	/*!Checks if the user clicked on the line*/
	virtual bool contains(float x, float y);	
	virtual void moveshape(float newx, float newy);
};
#endif
