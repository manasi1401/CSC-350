/*************************************************************************//**
 * @file
 * @brief Defines the function prototypes for the Event class.
 *****************************************************************************/
#ifndef EVENT_H
#define EVENT_H
#include "state.h"
//Paul Hinker
/*!
*@brief Contains the functions defining the action to be taken during certain event
*/

class Event
{
public:
	/*!Action to be taken when an event is created*/
   virtual void action(State&) =0;
	/*!Destructor of the event class*/
   virtual ~Event(){};
};

#endif
