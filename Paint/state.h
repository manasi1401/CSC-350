/*************************************************************************//**
 * @file
 * @brief Defines the structure of state which holds the list of shapes
 *****************************************************************************/
#ifndef _STATE_H
#define _STATE_H

#include <list>
#include "shape.h"

//Author: Paul Hinker
/*!
*@brief Contains the last state of the mouse and the list of shapes
*/
struct State {
	/*!Coordinates of the last state of the mouse*/
	float downX;
	/*!Coordinates of the last state of the mouse*/
	float downY;
	/*!Coordinates of the last state of the mouse*/
	float upX;
	/*!Coordinates of the last state of the mouse*/
	float upY;
	/*!List conatining the shapes to be displayed on the screen*/
	std::list<Shape*> shapes;
	/*! class holding the shape and color of thee selected*/
	Shape *demo = nullptr;
	/*!An array holding the RGB values for the boarder color*/
	float boarder[3];
	/*!An array holding the RGB values for the fill color*/
	float fill[3];
	/*!Integer holding what shape user selected*/ 
	int shapeSelc;
};
#endif
