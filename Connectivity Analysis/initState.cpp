#include "initState.h"
/***************************************************************************//**
 * @brief The initial state event to set the initial state values and store them
 * in the state. It also spins up a set of initial images and displays them to screen
 *
 * @param[in] imgRGBA - RGBA image to be processed
 * @param[in] SetThreshold - default threshold
 * @param[in] SetFilterSize - default filter size
 * @param[in] width - the width of the image, used in Dr. Weiss' psuedocolor function
 * @param[in] height - the height of the image, used in Dr. Weiss' psuedocolor function
 ******************************************************************************/
InitStateEvent::InitStateEvent ( byte **imgRGBA,
                                 int SetThreshold, int SetFilterSize, unsigned int width,
                                 unsigned int height )
{
    Threshold = SetThreshold; //binary threshold of the image
    FilterSize =
                SetFilterSize; //filter size for the initial display
    _Height = height; //height of the png image (used by Dr. Weiss' code)
    _Width = width; //width of the png image (used by Dr. Weiss' code)
    imageRGBA = imgRGBA; //pointer to the original color image
}
/***************************************************************************//**
 * @brief The initial state action function to set all init values in the state
 * structure.
 *
 * @param[in] state - (the current state of the world)
 *
 ******************************************************************************/
void InitStateEvent::action ( State &state )
{
    state.Threshold = Threshold;
    state.FilterSize = FilterSize;
    state.DisplayImageTitles = false;

    state.imageMono = grayscale ( _Width, _Height, imageRGBA );
    state.imageBinThr = binaryThreshold ( _Width, _Height,
                                          state.imageMono, Threshold );
    state.imagePseudo = pseudocolor ( _Width, _Height,
                                      state.imageBinThr );
    state.imageFiltered = pseudocolor ( _Width, _Height,
                                        state.imageBinThr );
    state.RedisplayCount = 0;

    state.height = _Height;
    state.width = _Width;
}

