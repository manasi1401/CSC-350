/***************************************************************************//**
 * @file analysis.h
 *
 * @par Description
 *
 * @brief This file contains the function declarations used to analyze an image for connected
 * components.
 *
 * @author Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 *
 ******************************************************************************/
#ifndef __ANALYSIS_H
#define __ANALYSIS_H

#include <iostream>
#include "event.h"
#include "state.h"
#include <stdlib.h>
#include <cstring>
#include "graphics.h"
#include "image.h"
#include <map>
#include <chrono>
#include <iomanip>

using namespace std;
/*!Class defining an "event", which correlates to an image analysis*/
class AnalysisEvent : public Event {
    public:
        /*!Determines what needs to be displayed*/
        virtual void action ( State &state );
        /*!Reassign the labels and groups them*/
        void GroupingLabels ( State &state );
        /*!Assigns color and filter to the images*/
        void FilterRecolorPseudo ( State &state );

};

#endif
