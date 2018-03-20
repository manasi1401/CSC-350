/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the shape class. 
 *****************************************************************************/
#include "shape.h"

/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * This constructor function initializes the shape by setting its location coordinate
 * and the color of the boundary of the shape
 * 
 * @param[in]  abs- The x coordinate of the location of the shape
 * @param[in]  oor- The y coordinate of the location of the shape
 * @param[in]  colorBoundary- The array that contains the color for the boundary
 * @param[in]  f    -   A boolean that tells weather or not there is fill
 *****************************************************************************/
Shape::Shape(float abs, float oor, const float *colorBoundary, bool f){
	x=abs;
	y=oor;
	colorBorder[0] = colorBoundary[0];
	colorBorder[1] = colorBoundary[1];
	colorBorder[2] = colorBoundary[2];
	fill = f;
}
/**************************************************************************//**
 * @author Peterson, Shawn
 * 
 * @par Description:
 *
 * Destructor
 * 
 *****************************************************************************/
Shape::~Shape()
{
    
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * Gets the x coordinate of the shape postion
 * @returns x - The x coordinate
 *****************************************************************************/
float Shape::getX()const{
	return x;} 
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * Gets the y coordinate of the shape postion
 * @returns y - The y coordinate
 *****************************************************************************/
float Shape::getY()const{
	return y;} 
	

/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * Sets the X coordinate of the shape postion
 *
 * @param[in] num - set the X coordinate to num.
 *****************************************************************************/
void Shape::setX(float num){x=num;}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * Sets the Y coordinate of the shape postion
 *
 * @param[in] num - set the Y coordinate to num.
 *****************************************************************************/
void Shape::setY(float num){y=num;}

/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * Sets the coordinates of the shape position to the new value
 *
 * @param[in] newx - set the X coordinate to new X coordinate.
 *  @param[in] newx - set the Y coordinate to new Y coordinat.
 *****************************************************************************/




