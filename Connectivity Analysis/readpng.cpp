/*
                ***** readpng.cpp *****

Read in a PNG image with LodePNG.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures
Date:   Fall 2017
*/

#include <cstdio>
#include <cstring>
#include "lodepng.h"
#include "image.h"

// read PNG image using LodePNG, and return as 2-D array of RGBA pixels
byte **readPNG ( char *filename, unsigned &width,
                 unsigned &height )
{
    // read input PNG file
    byte *pixels;
    unsigned error = lodepng_decode_file ( &pixels, &width,
                                           &height, filename, LCT_RGBA, 8 );
    if ( error )
    {
        printf ( "decoder error while reading file %s\n",
                 filename );
        printf ( "error code %u: %s\n", error,
                 lodepng_error_text ( error ) );
        return NULL;
    }
    printf ( "%s: %d x %d\n", filename, width, height );
    unsigned nbytes = width * 4;

    // make width a multiple of 4, else grayscale image does not display properly in OpenGL
    unsigned pad = 0;
    if ( width % 4 != 0 )
    {
        pad = 4 - width % 4;
    }
    width += pad;

    // flip image as we copy it into 2-D array
    byte **image = alloc2D ( height, width * 4 );
    for ( int row = height - 1; row >= 0;
          --row, pixels += nbytes )
    {
        memcpy ( image[row], pixels, nbytes );
    }

    // finish up
    // free( pixels );  // breaks program, not sure why
    return image;
}

