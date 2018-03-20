/*************************************************************************//**
 * @file display.cpp
 *
 * @par Description
 * @brief Defines the functions for the DisplayEvent class.
 *
 * @file display.cpp
 *
 * @brief Contains the action event, used to update all images on the screen
 * when a new analysis event is triggered. Also handles drawing titles on images
 *****************************************************************************/
#include "display.h"
/**************************************************************************//**
 * @author Manasi Paste
 * @par Description: This function calls event dispatcher to analyse the image for labelling, size filtering and pseudo coloring
 * to be displayed. It then displays the 4 processed images along with their labels to the screen.
 * @param[in] state - the current state of the world
 *****************************************************************************/
void DisplayEvent::action ( State &state )
{
    state.RedisplayCount++; 
    eventDispatcher ( new AnalysisEvent() );
    //Dislay 4 processed image to the screen
    displayMonochrome ( 0, 0, state.width, state.height,
                        state.imageMono );
    displayMonochrome ( 0, state.height, state.width,
                        state.height, state.imageBinThr );
    displayColor ( state.width, state.height, state.width,
                   state.height, state.imagePseudo );
    displayColor ( state.width, 0, state.width, state.height,
                   state.imageFiltered );
    // write text labels
    if ( state.DisplayImageTitles )
    {
        char str[257];
        sprintf ( str, "Grayscale Image" );
        DrawTextString ( str, 8, 8, 255, 255, 255 );
        sprintf ( str, "Connected Components Size Filtered" );
        DrawTextString ( str, state.width + 8, 8, 255, 255, 255 );
        sprintf ( str, "Connected Components" );
        DrawTextString ( str, state.width + 8, state.height + 8,
                         255, 255, 255 );
        sprintf ( str, "Binary Thresholding" );
        DrawTextString ( str, 8, state.height + 8, 255, 255, 255 );
    }
}
