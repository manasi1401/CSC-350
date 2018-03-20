/***************************************************************************//**
 * @file keyboard.h
 *
 * @par Description
 *
 * @brief This header file contains the function declaration to handle the
 * keyboard inputs. This changes the threshold, filter size, and title display
 *
 * @author Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 *
 ******************************************************************************/

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>
#include "event.h"
#include "state.h"
#include <cstring>
#include <string.h>
#include "graphics.h"

using namespace std;

/*!Class defining the key event*/
class KeyEvent : public Event {
    protected:
        /*!Key clicked on keyboard*/
        unsigned char key;

    public:
        /*!Initialize KeyEvent Class*/
        KeyEvent ( unsigned char key );
        /*!Determines what needs to be displayed*/
        virtual void action ( State &state );

};

#endif
