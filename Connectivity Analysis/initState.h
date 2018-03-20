/***************************************************************************//*
 * @file initState.h
 *
 * @par Description
 *
 * @brief This file contains the function declarations used to initilize the state
 * structure, so we can display an image the first time around the horn
 *
 * @author Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 *
 *****************************************************************************/
#ifndef INITSTATE_H
#define INITSTATE_H
#include "state.h"
#include "event.h"
#include "image.h"
using namespace std;

/*!Defines an unsigned char as a byte*/
typedef unsigned char byte;
/*!Class defining the initial state, declaring the necessary variables*/
class InitStateEvent : public
    Event { 
    protected:
        /*!the threshold for the binary thresholding*/
        int Threshold;
        /*!the desired filter size*/
        int FilterSize;
        /*!flag for whether or not to display titles*/
        bool DisplayImageTitles;
        /*!height of the image*/
        unsigned _Height;
        /*!width of the image*/
        unsigned _Width;
        /*!The original color image*/
        byte **imageRGBA;

    public:
        /*!Determines what needs to be displayed*/
        InitStateEvent ( byte **imgRGBA, int Threshold,
                         int FilterSize, unsigned int width, unsigned int height );
        /*!Call actions for the event*/
        virtual void action ( State &state );
};
#endif
