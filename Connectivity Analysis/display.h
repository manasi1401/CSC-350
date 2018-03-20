/*************************************************************************//**
 * @file display.h
 *
 * @brief Defines the function prototypes for the DisplayEvent class.
 *****************************************************************************/
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <iostream>
#include "event.h"
#include "state.h"
#include <stdlib.h>
#include <cstring>
#include "analysis.h"
#include "graphics.h"
#include "image.h"
#include "callbacks.h"

using namespace std;
//Paul Hinker
/*!
*@brief calls action function for display
*/
class DisplayEvent : public Event {
    public:
        /*!Determines what needs to be displayed*/
        virtual void action ( State &state );
};

#endif
