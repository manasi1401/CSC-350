/*************************************************************************//**
 * @file
 *
 * @brief Contains the main program that peforms the correct list operations
 *
 * @mainpage Program #1 - Paint
 * 
 * @section course_section Course Information
 *
 * @author Manasi Paste, Shawn Peterson
 * 
 * @date Sept 7, 2017
 * 
 * @par Professor:
 *         Dr. Hinker
 * 
 * @par Course:
 *         CSC315 - M001 - 10:00-11:00 AM
 * 
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information 
 * 
 * @details
 * This program allows user to paint like MS paint. Where the user 
 * has 8 colors to choose from and has basic shapes such as lines,    
 * rectangles, ellipses.The selection pallet is on the left bottom
 * side of the window. The user can choose shapes and colours by clicking 
 * on them. Shapes can created anywhere on the window by left clicking and dragging.
 *
 * Shapes can be moved by right clicking near their center of the 
 * desired shape and dragging them to the position the user wishes to 
 * be the new center. When you release the button the shape is  
 * redrawn around the new center position. 
 *
 * To select a boarder color use the left mouse button on the color
 * then select the shape by left clicking too. To select the 
 * fill color go to the color of choice and use the right button
 * on the mouse. To draw the filled shape the filled shape must be
 * selected. A view window is in the top left corner of the screen.
 * The view will show what shape is selected and the colors of the 
 * boarder and fill depending on the shape selected.
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Build: 
 *      @verbatim
 	make ./paint
	@endverbatim
 * 
 * @par Usage:
   @verbatim
  ./main
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * @par Modifications and Development Timeline:
   https://gitlab.mcs.sdsmt.edu/7404855/csc315_fall2017_project1/commits/master
 *
 *****************************************************************************/
#include <iostream>
#include <GL/freeglut.h>
#include "callbacks.h"
#include "graphics.h"
#include "shape.h"
#include "rectangle.h"
#include "mouse.h"
#include "event.h"
#include "state.h"

using namespace std;

void oneTimeInit(int num, char **arrOfStr);

/*************************************************************************//**
 * @brief main function
 *
 * @param[in] argc - number of command line arguments
 * @param[in] argv - array of C strings representing the command line
 *  arguments
 *
 * @return main does not return due to the glutMainLoop function not  
 * returning
 ****************************************************************************/
int main(int argc, char** argv)
{
   // Call the glut functions to initialize everything
   oneTimeInit(argc, argv);
   glutMainLoop();
   return 0;
}

/*************************************************************************//**
 * @brief A function to call the usual set of initialization routines
 *
 * @par Description
 *   * Initializes the glut system
 *   * Sets the initial display mode
 *   * Sets the initial window size
 *   * Sets the initial window position
 *   * Creates the window and sets the window title
 *   * Sets the DisplayFunc callback
 *   * Sets the KeyboardFunc callback 
 *   * Sets the MouseFunc callback
 *   * Sets the clear color
 *
 * @param[in] num      - The number of entries in the arrOfStr parameter
 * @param[in] arrOfStr - The commandline arguments
 *
 ****************************************************************************/
void oneTimeInit(int num, char **arrOfStr)
{
    // Initialize GLUT (OpenGL Utility Toolkit)
    glutInit(&num, arrOfStr);

    // Set the display mode [double buffering, 4-channel red,green,blue,alpha]
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);

    // Make the window 640 columns x 480 rows of pixels
    glutInitWindowSize(900, 800);

    // Start the window at 100 pixels down and 100 pixels right of upper-left
    glutInitWindowPosition(100, 50);

    // Give the window a title
    if (num > 1)
       glutCreateWindow(arrOfStr[1]);
    else
       glutCreateWindow("Simple Example Window Title");

    // Set the function for the glutMainLoop to call when refreshing window
    glutDisplayFunc(display);

    // Set the function to call in response to keyboard events
    glutKeyboardFunc(keyboard);

    // Set the function to call for mouse events
    glutMouseFunc(mouseClick);
	//test
	//glutMouseFunc(onMouse);

    // Set the function to call for reshaping of the window
    glutReshapeFunc(reshape);
    // When the window is cleared, use the color that's 0% red, 100% green,
    // 0% blue, 0% alpha
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}





