/*************************************************************************//**
 * @file
 * @brief Defines the function prototypes for the callbacks class.
 *****************************************************************************/
#ifndef __CALLBACKS_H
#define __CALLBACKS_H
#include <iostream>
#include <GL/freeglut.h>
#include <string>
#include "graphics.h"
#include "event.h"
#include "rectangle.h"
#include "state.h"
#include "init.h"
#include "mouse.h"
#include "state.h"
#include "display.h"
#include "keyboard.h"
#include "shape.h"
using namespace std;

/// A mnemonic name for the ascii value of the escape key
#define ESCAPE_KEY 27
//float clicks[] ={0, 0, 0 ,0};
/*!Maps button number to button name*/
const std::string ButtonName[] = 
{
   "Left", 
   "Middle", 
   "Right", 
   "Trackball Fwd", 
   "Trackball Bkwd"
};

/*!Maps button state# to action*/
const std::string ButtonState[] = 
{
   "Down", 
   "Up"
};
/*!Displays on to the screen*/
void display();
/*!Reads in put from the keyboard*/
void keyboard(unsigned char key, int x, int y);
/*!Reads in put from the mouse*/
void mouseClick(int button, int state, int x, int y);
/*!Reshapes the screen*/
void reshape(int w, int h);
/*!Calls action function for events*/
void eventDispatcher(Event *);

#endif
