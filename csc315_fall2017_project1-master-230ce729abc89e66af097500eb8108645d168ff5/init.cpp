//author Paul Hinker
/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the InitEvent class. 
 *****************************************************************************/
#include "init.h"
#include "rectangle.h"
#include <list>

/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *	
 * This function sets up the pallet for display when the screen in initialized
 * 
 * @param[in]  state - the state the screen is in
 *****************************************************************************/
void InitEvent::action(State &state)
{
	
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
        float height = glutGet(GLUT_WINDOW_HEIGHT)/8;
	float width = height;
	//you can allocate pallet this way
    Rectangle red( 0, 0, width, height, Red, Red );
    red.drawfilled();

   Rectangle white(width, 0, width*2, height, White, White);
   white.drawfilled();
  
   Rectangle green(0, height, width, height*2,White, Green);
   green.drawfilled();
   
   Rectangle yellow(width, height, width*2, height*2,White, Yellow);
   yellow.drawfilled();
   
   Rectangle magenta(0, 2*height, width, height*3,White, Magenta);
   magenta.drawfilled();

	Rectangle cyan(width, 2*height, width*2, height*3,White, Cyan);
	cyan.drawfilled();
	
	Rectangle grey(0, 3*height, width, height*4,White, Grey);
	grey.drawfilled();
	
   Rectangle brown(width, 3*height, width*2, height*4,White, Brown);
   brown.drawfilled();

   Rectangle orange(0, 4*height, width, height*5,White, Orange);
   orange.drawfilled();
  
   Rectangle gold (width, 4*height, width*2, height*5,White, Gold);
   gold.drawfilled();

   Rectangle whitebox1(0, 5*height, width, height*6,White, White);
   whitebox1.draw();

	//inner cirlce
   DrawEllipse(width*(0.3), width*(0.3), width/2, 5.5*height, White);
	//inner filled circle
   DrawFilledEllipse(width*(0.3), width*(0.3), 1.5*width, 5.5*height, Yellow);
   
   Rectangle whitebox2(width, 5*height, width*2, height*6, White, White);
   whitebox2.draw();
   

   Rectangle whitebox3(0, 6*height, width, height*7,White, White);
   whitebox3.draw();
	//inner rectangle
   DrawRectangle(width*(0.2), 6.2*height, width*(0.8), height*(6.8), White);
  
  	Rectangle whitebox4(width, 6*height, width*2, height*7,White, White);
   whitebox4.draw();
  

	//inner filled rectangle
   DrawFilledRectangle(width*(1.2), 6.2*height, width*(1.8), height*(6.8), Yellow);
	//inner line
	Rectangle whitebox5(0, 7*height, width, height*8,White, White);
   whitebox5.draw();
	DrawLine(width*(1.2), height*(7.2), width*(1.8), height*(7.8), White);

   Rectangle whitebox6(width, 7*height, width*2, height*8,White, White);
   whitebox6.draw();
   
   if(state.demo !=nullptr)\
   {
    if(state.demo->getfill())
    { 
    state.demo->drawfilled(); 
    state.demo->draw();
    
    }
	else 
	{
	state.demo->draw();
	}
	}
   //pallet complete
}
