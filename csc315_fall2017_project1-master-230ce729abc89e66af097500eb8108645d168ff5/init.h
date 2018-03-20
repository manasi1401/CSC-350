//Author Paul Hinker
/*************************************************************************//**
 * @file
 * @brief Defines the function prototypes for the InitEvent class.
 *****************************************************************************/
#ifndef INIT_H
#define INIT_H

#include <iostream>
#include "event.h"
#include "graphics.h"
#include "rectangle.h"
#include "ellipse.h"
#include "state.h"
#include "line.h"

using namespace std;
/*!
*@brief Contains the function required to display on initiation of screen
*/
class InitEvent : public Event
{
public:
	/*!Pallet set up for Display on initiation of screen*/
   void action(State&);
};
#endif
