/***************************************************************************//**
 * @file graphics.h
 *
 * @brief OpenGL graphics program, illustrating use of GLUT and callback functions.
 *
 * @author John M. Weiss, Ph.D.
 * @par Class
 *    CSC300 Data Structures
 * @date Fall 2015
 *
 * Modifications:
 *    * Added doxygen style comments: PJH 9/5/2016
 ******************************************************************************/
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <string>
// the GLUT header automatically includes gl.h and glu.h
#include <GL/freeglut.h>
using namespace std;


/// Define the Black color
const float Black[] = { 0.0, 0.0, 0.0 };
/// Define the Red color
const float Red[]   = { 1.0, 0.0, 0.0 };
/// Define the Green color
const float Green[] = { 0.0, 1.0, 0.0 };
/// Define the Blue color
const float Blue[]  = { 0.0, 0.0, 1.0 };
/// Define the Magenta color
const float Magenta[]   = { 1.0, 0.0, 1.0 };
/// Define the Cyan color
const float Cyan[]  = { 0.0, 1.0, 1.0 };
/// Define the Yellow color
const float Yellow[]    = { 1.0, 1.0, 0.0 };
/// Define the White color
const float White[] = { 1.0, 1.0, 1.0 };
/// Define grey
const float Grey[] ={0.752941,0.752941, 0.752941};
/// Define Brown
const float Brown[] = {0.647059, 0.164706, 0.164706};
/// Define gold
const float Gold[] ={0.8, 0.498039, 0.196078};
/// Define orange
const float Orange[] ={ 1, 0.5, 0.0};
/// Define salmon
const float Salmon[] ={0.435294, 0.258824, 0.258824};

/// DrawLine function
void DrawLine( float x1, float y1, float x2, float y2, const float color[] );
/// DrawRectangle function
void DrawRectangle( float x1, float y1, float x2, float y2, const float color[] );
/// DrawFilledRectangle function
void DrawFilledRectangle( float x1, float y1, float x2, float y2, const float color[] );
/// DrawEllipse function
void DrawEllipse( float xRadius, float yRadius, int x, int y, const float color[] );
/// DrawFilledEllipse function
void DrawFilledEllipse( float xRadius, float yRadius, int x, int y, const float color[] );
/// DrawTextString function
void DrawTextString(string str, int x, int y, const float color[] );

#endif
