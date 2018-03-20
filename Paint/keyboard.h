/*************************************************************************//**
 * @file
 * @brief Defines the function prototypes for the KeyEvent class.
 *****************************************************************************/
#ifndef _KEYBOARD_H
#define _KEYBOARD_H
/*!Escape key*/
#define ESCAPE_KEY 27
#include "event.h"
#include "state.h"
#include "display.h"
#include "callbacks.h"
//Manasi Paste
/*!
*@brief calls action function for keyboard inputs
*/
class KeyEvent :public Event{
	/*!keyboard input*/
	protected: unsigned char key;
	public:
	/*!Stores the last keyboard input*/
	KeyEvent(unsigned char k):key(k){};
	/*!Action to be called on keyboard input*/
	virtual void action(State & state);
};
#endif
