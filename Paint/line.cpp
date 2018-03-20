/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the Line class. 
 *****************************************************************************/
#include "line.h"

/**************************************************************************//**
 * @author Manasi Paste
 * @par Description:
 *	
 * This constructor function initializes the line by setting its location coordinate,
 * and its boundary color;
 * 
 * @param[in]  x - The x coordinate of first end of the line
 * @param[in]  y - The y coordinate of first end of the line
 * @param[in]  x1 - The x coordinate of second end of the line
 * @param[in]  y1 - The y coordinate of second end of the line
 * @param[in]  color - The array that contains the color of the line
 * @param[in]  f    -   A boolean that tells weather or not there is fill
 *****************************************************************************/
Line::Line(float x, float y, float x1, float y1, const float* color, bool f):
		Shape(x, y, color, f), xcor(x1), ycor(y1){}
		
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * This function draws the line
  *****************************************************************************/
void Line::draw()const {
	DrawLine(x, y, xcor, ycor, colorBorder);
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * Is not needed for a line has no fill
  *****************************************************************************/
void Line::drawfilled()const{
}
/**************************************************************************//**
 * @author Manasi Paste & Peterson, Shawn
 * 
 * @par Description:
 *	
 * This function checks if the user has clicked on the line
 * 
 * @param[in]  locx- The x coordinate of clicked pixel
 * @param[in]  locy- The y coordinate of clicked pixel

 * @return  true- if its clicked on the line
 * @return false - if its  clicked on the line
 *****************************************************************************/
bool Line::contains(float locx, float locy)
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
 * @author Manasi Paste & Peterson, Shawn
 * 
 * @par Description:
 *	
 * The moveshape line function is used to change the center cordinates of the
 * line to a new position 
 * @param[in] newx  -   A float holding the new x cordinate
 * @param[in] newy  -   A float that holds the new y cordinate
 *****************************************************************************/
void Line::moveshape(float newx, float newy){
       float xcenter =(xcor+x)/2, ycenter= (ycor+y)/2;
       float xtend = abs(xcenter-x), ytend=abs(ycenter -y);
       float xup= abs(xcenter-xcor), yup=abs(ycenter-ycor);
        x= newx - xtend;
        y =newy - ytend;
        xcor= newx + xup;
        ycor =newy + yup;

}
