/***************************************************************************//**
 * @file analysis.cpp
 *
 * @par Description
 *
 * @brief This file contains the functions used to analyze an image for connected
 * components. The functions work through accessing the State structure, which contains
 * all necessary information including the byte arrays and current threshold / size filter
 *
 * @author Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 *
 ******************************************************************************/

#include "analysis.h"

/***************************************************************************//**
 * @brief The action event, when called, walks through the image (represented here
 * as a byte array) and assigns labels to pixels based on the stencil depicted in
 * the program assignment. Because of the inherent nature of this stencil, the first
 * row and column need to be checked independently, along with the very first pixel
 * in cell [0][0]. It also makes use of the chrono> library in order to print
 * accurate timing data to the screen for performance analysis. It makes use
 * of a disjoint set in order to manage the groupings efficiently, utilizing path
 * compression and the weighting rule (joining small groups to large groups)
 *
 * @param[in] state - the current state of the world
 *
 *
 ******************************************************************************/
void AnalysisEvent::action ( State &state )
{

    auto start = chrono::high_resolution_clock::now();

    int u, l;
    int GroupCounter = 0;

    //labels for pseudo image
    state.pixelLabels = new int *[state.height];
    for ( unsigned int i = 0; i < state.height; i++ )
    {
        state.pixelLabels[i] = new int[state.width];
        for ( unsigned int k = 0; k < state.width; k++ )
        {
            state.pixelLabels[i][k] = 0;
        }
    }

    for ( unsigned int i = 0; i < state.height; i++ )
        for ( unsigned int k = 0; k < state.width; k++ )
        {
            state.pixelLabels[i][k] = 0;
        }
    //label the first row
    for ( unsigned int j = 1; j < state.width; j++ )
    {
        if ( state.imageBinThr[0][j] == 255 )
        {
            l = state.pixelLabels[0][j - 1];
            if ( l == 0 )
            {
                state.pixelLabels[0][j] = ++GroupCounter;
                state.GroupedLabels.insertSingle ( state.pixelLabels[0][j],
                                                   j + 1 );
            }
            if ( l != 0 )
            {
                state.pixelLabels[0][j] = l;
            }
        }
    }
    //Label the first column
    for ( unsigned int i = 1; i < state.height; i++ )
    {
        if ( state.imageBinThr[i][0] == 255 )
        {
            u = state.pixelLabels[i - 1][0];
            if ( u == 0 )
            {
                state.pixelLabels[i][0] = ++GroupCounter;
                state.GroupedLabels.insertSingle ( state.pixelLabels[i][0],
                                                   i * state.width + 1 );
            }
            if ( u != 0 )
            {
                state.pixelLabels[i][0] = u;
            }
        }
    }
    //Label the image
    for ( unsigned int i = 1; i < state.height; i++ )
    {
        for ( unsigned int j = 1; j < state.width; j++ )
        {
            if ( state.imageBinThr[i][j] == 255 )
            {
                u = state.pixelLabels[i - 1][j];
                l = state.pixelLabels[i][j - 1];
                if ( u == 0 && l == 0 )
                {
                    state.pixelLabels[i][j] = ++GroupCounter;
                    state.GroupedLabels.insertSingle ( state.pixelLabels[i][j],
                                                       i * state.width + j + 1 );
                }
                else if ( ( u != 0 ) && ( l != 0 ) )
                {
                    state.pixelLabels[i][j] = state.pixelLabels[i - 1][j];
                    state.GroupedLabels.merge ( state.pixelLabels[i - 1][j],
                                                state.pixelLabels[i][j - 1] );
                }
                else if ( u == 0 && l != 0 )
                {
                    state.pixelLabels[i][j] = state.pixelLabels[i][j - 1];
                }

                else if ( u != 0 && l == 0 )
                {
                    state.pixelLabels[i][j] = state.pixelLabels[i - 1][j];
                }
            }
        }
    }
    //Label the first pixel
    if ( state.imageBinThr[0][0] == 255 )
    {
        u = state.pixelLabels[1][0];
        l = state.pixelLabels[0][1];
        if ( u == 0 && l == 0 )
        {
            state.pixelLabels[0][0] = ++GroupCounter;
            state.GroupedLabels.insertSingle ( u, 0 );
        }
        else if ( ( u != 0 ) && ( l != 0 ) )
        {
            state.pixelLabels[0][0] = u;
            state.GroupedLabels.merge ( u, l );
        }
        else if ( u == 0 && l != 0 )
        {
            state.pixelLabels[0][0] = l;
        }

        else if ( u != 0 && l == 0 )
        {
            state.pixelLabels[0][0] = u;
        }
    }

    state.TotalGroups = GroupCounter;
    auto end = std::chrono::high_resolution_clock::now();

    if ( state.RedisplayCount == 1 )
    {
        cout << "Pass 1: Assign Labels  " << setprecision ( 4 ) <<
             chrono::duration_cast<chrono::microseconds>
             ( end - start ).count() / 1000.0 << " ms" << endl;
    }

    GroupingLabels ( state );
}

/***************************************************************************//**
 * @brief This function, having been provided a byte array with labeled pixels,
 * walks through and filters the groups based on their size. This allows the
 * program to produce a much less noisy image. This filter size is stored in
 * the state structure.
 *
 * @param[in] state - the current state of the world
 *
 *
 ******************************************************************************/
void AnalysisEvent::GroupingLabels ( State &state )
{
    state.FilteredPixelLabels = new int *[state.height];
    for ( unsigned int i = 0; i < state.height; i++ )
    {
        state.FilteredPixelLabels[i] = new int[state.width];
        for ( unsigned int k = 0; k < state.width; k++ )
        {
            state.FilteredPixelLabels[i][k] = 0;
        }
    }
    auto start = std::chrono::high_resolution_clock::now();
    //Initialize Filteredpseudo labels to zero
    for ( unsigned int i = 0; i < state.height; i++ )
        for ( unsigned int k = 0; k < state.width; k++ )
        {
            state.FilteredPixelLabels[i][k] = 0;
        }

    //reassign the labels
    for ( unsigned int i = 0; i < state.height; i++ )
        for ( unsigned int j = 0; j < state.width; j++ )
            if ( state.pixelLabels[i][j] != 0 )
            {
                state.pixelLabels[i][j] = state.GroupedLabels.find (
                                                      state.pixelLabels[i][j] );
            }
   

    //Checking the size of each blob represented by its label for size filtering
    //Creating the image histogram;
    map<int, int> ImageHistogram;
    for ( unsigned int i = 0; i < state.height; i++ )
        for ( unsigned int j = 0; j < state.width; j++ )
        {
            if ( ImageHistogram.find ( state.pixelLabels[i][j] ) ==
                 ImageHistogram.end() )
            {
                ImageHistogram[state.pixelLabels[i][j]] = 1;
            }
            else
            {
                ImageHistogram[state.pixelLabels[i][j]]++;
            }
        }

    //If number of pixels that group are less than filter size leave it zero
    for ( unsigned int i = 0; i < state.height; i++ )
        for ( unsigned int j = 0; j < state.width; j++ )
            if ( ImageHistogram[state.pixelLabels[i][j]] >
                 state.FilterSize )
            {
                state.FilteredPixelLabels[i][j] = state.pixelLabels[i][j];
            }
 auto end = std::chrono::high_resolution_clock::now();

    FilterRecolorPseudo ( state );
    ImageHistogram.clear();

    if ( state.RedisplayCount == 1 )
    {
        cout << "Pass 2: Label Blobs & Size Filter " << setprecision ( 4 ) <<
             chrono::duration_cast<chrono::microseconds>
             ( end - start ).count() / 1000.0 << " ms" << endl << endl;
    }

}

/***************************************************************************//**
 * @brief The Recolor member function creates a randomized pallete of colors
 * that then are assigned to the individual groups of pixels. This allows
 * us as users to better visualize the connected components.
 *
 * @param[in] state - the current state of the world
 *
 *
 ******************************************************************************/
void AnalysisEvent::FilterRecolorPseudo ( State &state )
{
    //Make a pallete
    byte **pal = new byte * [3];
    for ( unsigned int i = 0; i < 3; i++ )
    {
        pal[i] = new byte[state.TotalGroups + 1];
        for ( int k = 0; k < state.TotalGroups + 1; k++ )
        {
            pal[i][k] = 0;
        }
    }
    //Fill in random colors in the Pallet
    for ( int i = 1; i < state.TotalGroups + 1; ++i )
        for ( unsigned rgb = 0; rgb < 3; ++rgb )
        {
            pal[rgb][i] = rand() % 256;
        }

    //Get the pointers to the  image
    byte *pixels = *state.imagePseudo;
    byte *filterpixel = *state.imageFiltered;

    //Add the colors to the image
    for ( unsigned int i = 0; i < state.height; i++ )
    {
        for ( unsigned int j = 0; j < state.width; j++ )
        {
            int pix = state.pixelLabels[i][j];
            int fpix = state.FilteredPixelLabels[i][j];
            for ( unsigned rgb = 0; rgb < 3; ++rgb )
            {
                *pixels++ = pal[rgb][pix];
                *filterpixel++ = pal[rgb][fpix];
            }
            pixels++;
            filterpixel++;
        }
    }

    //Clearing the labels and pallates
    state.GroupedLabels.clearForest();
    //Free memory
    for ( unsigned int i = 0; i < 3; i++ )
    {
        delete [] pal[i];
    }

    delete [] pal;
    for ( unsigned int i = 0; i < state.height; i++ )
    {
        delete [] state.FilteredPixelLabels[i];
        delete [] state.pixelLabels[i];
    }
    delete [] state.pixelLabels;
    delete [] state.FilteredPixelLabels;
    return;
}
