/*
                ***** image.h *****

Include file for connected components analysis.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures
Date:   Fall 2017
*/

#ifndef IMAGE_H
#define IMAGE_H

// convenience data type
typedef unsigned char byte;

// function prototypes
byte **alloc2D ( int nrows, int ncols );
void free2D ( byte **image );
byte **readPNG ( char *filename, unsigned &width,
                 unsigned &height );
byte **grayscale ( unsigned width, unsigned height,
                   byte **rgba );
byte **binaryThreshold ( unsigned width, unsigned height,
                         byte **image, unsigned thresh );
byte **pseudocolor ( unsigned width, unsigned height,
                     byte **image );
void initOpenGL ( char **filename,  const char *Threshold,
                  const char *filter );

#endif
