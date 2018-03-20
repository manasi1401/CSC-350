/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the KeyEvent class. 
 *****************************************************************************/
#include "keyboard.h"
/**************************************************************************//**
 * @author Manasi Paste 
 * 
 * @par Description:
 *
 * This function is used to turn the input from the keyboard into output on 
 * the screen
 * @param[in] state - the current state of the program
 *****************************************************************************/
void KeyEvent::action(State & state)
{	
	if (key == ESCAPE_KEY)
      glutLeaveMainLoop();
   else if(key =='q')
		glutLeaveMainLoop();
	else if(key =='d'){
			if(state.shapes.size()!=0){
	  			state.shapes.pop_back();
	  			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
				glLoadIdentity();	
				glutPostRedisplay();
				}
		}
	else if(key =='c'){
		while(state.shapes.size()!=0)
		{
		    delete state.shapes.back();
  			state.shapes.pop_back();
		}
		glutPostRedisplay();
	}		
}
