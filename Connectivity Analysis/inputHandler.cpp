/***************************************************************************//**
 * @file inputHandler.cpp
 *
 * @par Description
 *
 * @brief This file contains the function to handle the command line arguments that
 * were provided by the user. It provides limited error checking, and will inform the
 * user if the input file is unable to be opened.
 *
 * @author Dakotah Rusley, Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 *
 ******************************************************************************/

/***************************************************************************//**
 * @brief inputHandler's sole purpose is to handle the input given by the user.
 * It tests whether or not the input file exists and provides usage instructions
 * in the event that the user doesn't provide an input file
 *
 * @param[in] NumArgs - the number of cmd line arguments that the user entered
 * @param[in] Args - the character array containing the individual command line arguments
 *
 * @returns - Error flag for whether or not the input file was valid
 ******************************************************************************/
#include "inputHandler.h"

int inputHandler ( int NumArgs, char *Args[] )
{

    if ( NumArgs < 2 )
    {
        cerr << "Usage: conncomp image.PNG [binary_threshold] [size_threshold]\n";
        return 1;
    }

    if ( NumArgs == 3 )
    {
        int threshold = stoi ( Args[2] );
        if ( threshold < 0 || threshold > 255 )
        {
            cerr << "Please enter a threshold value between 0-255\n";
            return 2;
        }
    }
    if ( NumArgs == 4 )
    {
        int filter = stoi ( Args[3] );
        if ( filter < 0 )
        {
            cerr << "Please enter a non-negative size filter value\n";
            return 3;
        }
    }
    char *inputFilename = Args[1];

    ifstream fin ( inputFilename );

    if ( !fin )
    {
        cerr << "Error: unable to open " << inputFilename << endl;
        return 3;
    }
    return 0;
}
