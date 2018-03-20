/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the DisplayEvent class. 
 *****************************************************************************/
#include "display.h"
#include "init.h"
/**************************************************************************//**
 * @author Manasi Paste
 * 
 * @par Description:
 *
 * Displays the pallet and and the shapes in the list
 * @param[in] state - the current state of the program
 *****************************************************************************/
void DisplayEvent::action(State &state)
{
	
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
  	 static InitEvent event;
   
   // Draw the shapes in the shapes list
  		for (Shape *shape : state.shapes){
  			if(shape->getfill()) {
  				shape->drawfilled(); 
  					shape->draw();}
   			 shape->draw();
    		}
    event.action(state);
}
