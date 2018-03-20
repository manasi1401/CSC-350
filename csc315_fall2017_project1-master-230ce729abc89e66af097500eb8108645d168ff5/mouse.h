/*************************************************************************//**
 * @file
 * @brief Defines the function prototypes for the mouse event class.
 *****************************************************************************/
#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <cmath>
#include "event.h"
#include "ellipse.h"
#include "rectangle.h"
#include "line.h"
#include "callbacks.h"

using namespace std;
//Paul Hinker
/*!
*@brief inherited class from Event class which contains functions
* that reads in the mouse clicks and calls actions accordingly
*/
class MouseEvent : public Event
{
protected:
	/*! x_pos coordinate*/
   int x_pos;
   /*! y_pos coordinate*/
   int y_pos;
   /*! button left or right */
   int button;
   /*! state up/down*/
   int state;
public:
	/*!Constructor for the Mouse Event class*/
   MouseEvent(int, int, int, int);
   
  /*!make the menu bar to be selected*/
   virtual void action(State &programState);
};

/*!Selects the fill color*/
void MouseFill(int x, int y, int boxD, State &programState);
/*!Selects the boarder color*/
void MouseBoarder(int x, int y, int boxD, State &programState);
#endif

