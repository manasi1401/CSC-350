/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the Ellipse class. 
 *****************************************************************************/
#include "shape.h"
#include "ellipse.h"
#include "graphics.h"
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * This constructor function initializes the ellipse by setting its location coordinate,
 * its dimension and its boundary & fill color;
 * 
 * @param[in]  locx- The x coordinate of the location of the ellipse
 * @param[in]  locy- The y coordinate of the location of the ellipse
 * @param[in]  cenX - the smaller radius of ellipse
 * @param[in]  cenY - Bigger radius of the ellipse
 * @param[in]  colorB - The array that contains the color for the boundary
 * @param[in]  colorF - The array that contains the color for the fill
 * @param[in]  f    -   A boolean that tells weather or not there is fill
 *****************************************************************************/
Ellipse::Ellipse(float locx, float locy, float cenX, float cenY,
						 const float* colorB, const float*colorF, bool f): Shape(locx, locy, colorB, f), 
						 centerXcor(cenX), centerYcor(cenY) 
{
	colorFill[0]=colorF[0];
	colorFill[1]=colorF[1];
	colorFill[2]=colorF[2];
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * This function draws unfilled ellipse
 *****************************************************************************/						 
				
void Ellipse::draw() const
{
	DrawEllipse(x, y, centerXcor, centerYcor, colorBorder);
}
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * This function draws filled ellipse
 *****************************************************************************/		
void Ellipse::drawfilled() const
{
	DrawFilledEllipse(x,y, centerXcor, centerYcor, colorFill);
}
/**************************************************************************//**
 * @author Manasi Paste & Peterson, Shawn
 * 
 * @par Description:
 *	
 * This function checks if user has clicked inside the ellipse
 * @param[in] locx - X coordinate of the position user clicked on
 * @param[in] locy - Y coordinate of the postion user clicked on 
 * @return true - if the click is inside the ellipse
 * @return false - if the click is outside the ellipse
 *****************************************************************************/		
bool Ellipse::contains(float locx, float locy) {

   float xDist = abs(locx -centerXcor) ;
   float yDist = abs(locy -centerYcor);
   distance =sqrt(pow(xDist, 2) +pow(yDist,2));
  
  if (abs(x) >= xDist && xDist > 0 &&
      abs(y)>= yDist && yDist > 0)
     return true;

  return false;
}

/**************************************************************************//**
 * @author Peterson, Shawn
 * 
 * @par Description:
 *	
 * This function is used to set the new center points of a shape when moved
 * @param[in] newx - X coordinate for the new center of the shape
 * @param[in] newy - Y coordinate for the new center of the shape
 *****************************************************************************/		
void Ellipse::moveshape(float newx, float newy){
  
        centerXcor= newx;
        centerYcor= newy;

}
