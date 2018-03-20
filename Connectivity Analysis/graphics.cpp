/*
                ***** graphics.cpp *****

OpenGL/GLUT graphics module for connected components analysis.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures
Date:   Fall 2017
*/
#include "graphics.h"

// display 32-bit color image
/**************************************************************************//**
 * @author John M. Weiss, Ph.D.
 *
 * @par Description: Displays rgb images to the screen
 *
 * @param[in] x - x coordinate of the image position
 * @param[in] y - y coordinate of the image position
 * @param[in] w - width of the image
 * @param[in] h - height of the image
 * @param[in] image - The rgb image to be displayed
 *****************************************************************************/
void displayColor ( int x, int y, int w, int h,
                    byte **image )
{
    glRasterPos2i ( x, y );
    glDrawPixels ( w, h, GL_RGBA, GL_UNSIGNED_BYTE, *image );
}

// display 8-bit monochrome image
/**************************************************************************//**
 * @author John M. Weiss, Ph.D.
 *
 * @par Description: Displays monochrome images to the screen
 *
 * @param[in] x - x coordinate of the image position
 * @param[in] y - y coordinate of the image position
 * @param[in] w - width of the image
 * @param[in] h - height of the image
 * @param[in] image - The gray/binary image to be displayed
 *****************************************************************************/
void displayMonochrome ( int x, int y, int w, int h,
                         byte **image )
{
    glRasterPos2i ( x, y );
    glDrawPixels ( w, h, GL_LUMINANCE, GL_UNSIGNED_BYTE,
                   *image );
}

// write a text string
/**************************************************************************//**
 * @author John M. Weiss, Ph.D.
 *
 * @par Description: Displays monochrome images to the screen
 *
 * @param[in] string - string to be displayed
 * @param[in] x - x coordinate of the string position
 * @param[in] y - y coordinate of the string position
 * @param[in] r - red byte in rgb
 * @param[in] g - green byte in rgb
 * @param[in] b - blue byte in rgb
 *****************************************************************************/
void DrawTextString ( char *string, int x, int y, byte r,
                      byte g, byte b )
{
    glColor3ub ( r, g, b );
    glRasterPos2i ( x, y );
    while ( *string )
    {
        glutBitmapCharacter ( GLUT_BITMAP_HELVETICA_18, *string );
        string++;
    }
}


