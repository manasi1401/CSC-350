#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <cstdio>
#include <GL/glut.h>
using namespace std;

typedef unsigned char byte;

/*!displays colored images to screen*/
void displayColor ( int x, int y, int w, int h,
                    byte **image );

/*!displays monochrome images to screen*/
void displayMonochrome ( int x, int y, int w, int h,
                         byte **image );

/*!displays strings to screen*/
void DrawTextString ( char *string, int x, int y, byte r,
                      byte g, byte b );

/// symbolic constant
const int ESC = 27;

#endif
