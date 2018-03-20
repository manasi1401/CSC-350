/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the rectangle class. 
 *****************************************************************************/
#include "rectangle.h"
/**************************************************************************//**
 * @author Paul Hinker
 * 
 * @par Description:
 *	
 * This constructor function initializes the rectangle by setting its location coordinate,
 * its dimension and its boundary color;
 * 
 * @param[in]  x- The x coordinate of the location of the rectangle
 * @param[in]  y- The y coordinate of the location of the rectangle
 * @param[in]  x1 - The top right x coordnite
 * @param[in]  y1 - The top right y coordinate
 * @param[in]  c- The array that contains the color for the boundary
 * @param[in]  colorfill - The array that contains the color of the line
 * @param[in]  f    -   A boolean that tells weather or not there is fill
 *****************************************************************************/

Rectangle::Rectangle(float x, float y, float x1, float y1, const float *c, const float *colorfill, bool f) :
   Shape(x, y, c, f), xcor(x1), ycor(y1) 
   {
   	colorF[0]=colorfill[0];
   	colorF[1]=colorfill[1];
   	colorF[2]=colorfill[2];
   }
/**************************************************************************//**
 * @author Paul Hinker
 * 
 * @par Description:
 *	
 * This function checks if the user has clicked inside the rectangle
 * 
 * @param[in]  locx- The x coordinate of clicked pixel
 * @param[in]  locy- The y coordinate of clicked pixel

 * @return  true- if its clicked inside the rectangle
 * @return false - if its  clicked outside the rectangle
 *****************************************************************************/
bool Rectangle::contains(const float locx, const float locy) 
{

   float xDist = abs(locx -((x+xcor)/2)) ;
   float yDist = abs(locy -((y+ycor)/2));
   distance =sqrt(pow(xDist, 2) +pow(yDist,2));
  if (abs(xcor -x) >= xDist && xDist > 0 &&
      abs(ycor -y)>= yDist && yDist > 0)
     return true;

  return false;
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * This function draws the circle
  *****************************************************************************/
void Rectangle::draw()const 
{
	const float *tempc;
	tempc =getColor();
   DrawRectangle(getX(), getY(), xcor, ycor, tempc);
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * This function draws the filled circle
  *****************************************************************************/
void Rectangle::drawfilled() const
{
	
   DrawFilledRectangle(getX(), getY(), xcor, ycor, colorF);
}
/**************************************************************************//**
 * @author Manasi Paste & Shawn Peterson
 * 
 * @par Description:
 *	
 * The moveshape rectangle function is used to change the center cordinates 
 * of the rectangle while keeping its demensions
 * @param[in] newx  -   A float holding the new x cordinate
 * @param[in] newy  -   A float that holds the new y cordinate
  *****************************************************************************/
void Rectangle::moveshape(float newx, float newy)
{
       float xcenter =(xcor+x)/2, ycenter= (ycor+y)/2;
       float xtend = abs(xcenter-x), ytend=abs(ycenter -y);
       float xup= abs(xcenter-xcor), yup=abs(ycenter-ycor);
        x= newx - xtend;
        y =newy - ytend;
        xcor= newx + xup;
        ycor =newy + yup;
    
  
}
/**************************************************************************//**
 * @author Paul Hinker
 * 
 * @par Description:
 *	
 * This function is the destructor of the rectangle object
  *****************************************************************************/
Rectangle::~Rectangle(){}
