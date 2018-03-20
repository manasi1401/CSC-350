/*
                ***** pseudo.cpp *****

Grayscale, binary thresholding, and random pseudocolor routines for connected components analysis.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures
Date:   Fall 2017
*/

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include "lodepng.h"
#include "image.h"

// generate 8-bit grayscale intensity image from 24/32-bit color image
byte **grayscale ( unsigned width, unsigned height,
                   byte **rgba )
{
    byte **image = alloc2D ( height, width );
    byte *img = *rgba;
    for ( unsigned row = 0; row < height; ++row )
    {
        for ( unsigned col = 0; col < width; ++col )
        {
            int r = *img++;
            int g = *img++;
            int b = *img++;
            img++;      // alpha channel is not used
            image[row][col] = 0.3 * r + 0.6 * g + 0.1 * b + 0.5;
        }
    }
    return image;
}

// generate binary thresholded image from grayscale image
byte **binaryThreshold ( unsigned width, unsigned height,
                         byte **image, unsigned thresh )
{
    unsigned nrows = height;
    unsigned ncols = width;
    byte **binthresh = alloc2D ( nrows, ncols );

    // generate binary thresholded image
    for ( unsigned row = 0; row < nrows; ++row )
        for ( unsigned col = 0; col < ncols; ++col )
        {
            binthresh[row][col] = image[row][col] < thresh ? 0 : 255;
        }

    // return binary thresholded image
    return binthresh;
}

// generate random pseudocolor image from an 8-bit grayscale image
byte **pseudocolor ( unsigned width, unsigned height,
                     byte **image )
{
    // generate random pseudocolor palette
    byte pal[3][256] = { 0 };
    for ( unsigned i = 1; i < 256; ++i )
        for ( unsigned rgb = 0; rgb < 3; ++rgb )
        {
            pal[rgb][i] = rand() % 256;
        }

    // create 32-bit color image (array of RGBA values)
    unsigned nrows = height;
    unsigned ncols = width;
    byte **pseudo = alloc2D ( nrows, ncols * 4 );
    byte *pixels = *pseudo;

    // generate pseudocolored image
    for ( unsigned row = 0; row < nrows; ++row )
        for ( unsigned col = 0; col < ncols; ++col )
        {
            byte pix = image[row][col];
            for ( unsigned rgb = 0; rgb < 3; ++rgb )
            {
                *pixels++ = pal[rgb][pix];
            }
            pixels++;       // skip alpha channel
        }

    // return pseudocolored image
    return pseudo;
}

