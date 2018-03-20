/*************************************************************************//**
 * @file
 * @brief Defines the function prototypes for the shape class.
 *****************************************************************************/
#ifndef _CALLBACKS_H_
#define _CALLBACKS_H_
#include "graphics.h"
#include <cmath>
//Manasi Paste
/*!
*@brief Contains the functions required for setting and getting shape arguments.
* The private data stores coordinates of the rectangles position.
*/
class Shape {
protected:
/*!The X coordinate of the position*/
 float x;
 /*!The Y coordinate of the position*/
 float y;
 /*!The color of the boundary*/
 float colorBorder[3] ={0,0,0};
  /*!Hold weather or nor fill is selected*/
	bool fill;
  /*!Variable holding distatance from mouse*/
    float distance;
public: 
  Shape(){};
	/*!Constructor for the shape class*/
	Shape(float x, float y, const float *color, bool f= false);
	/*!Deconstructor for the shape class*/
	virtual ~Shape() = 0;
	/*!Get the x coordinate of the position pixel*/
	float getX()const;
	/*!Get the y coordinate of the position pixel*/
	float getY()const; 
	/*!Stores boolean if it is needed to be filled*/ 
	bool getfill(){return fill;}
	/*!get the color array*/
	const float *getColor()const{
	return colorBorder;
	}
	//setter
	/*!Sets the X coordinate*/
	void setX(float num);
	/*!Sets the y coordinate*/
	void setY(float num);
	
	/*!Moves the shape to a new position*/
	virtual void moveshape(float newx, float newy)=0;
	/*!Draws the new shape*/
	virtual void draw()const =0;
	/*!Draws a new filled shape*/
	virtual void drawfilled()const =0;
	/*!Check if the click was inside the shape*/
	virtual bool contains(float, float)=0;
	/*!returns the distance of the center from the mouse click*/
	float getDist()const{return distance;}
	
};

#endif
