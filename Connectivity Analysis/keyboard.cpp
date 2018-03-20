/***************************************************************************//**
 * @file keyboard.cpp
 *
 * @par Description
 *
 * @brief This function interfaces with the state structure to set the
 * current state of the world when the user wants to set the threshold or
 * filter size.
 *
 * @author Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 ******************************************************************************/

#include "keyboard.h"
#include "display.h"
#include "callbacks.h"
#include "analysis.h"
#include <GL/freeglut.h>

/***************************************************************************//**
 * @brief keyEvent's job is to handle key presses by the user, and set the
 * appropriate state variables. It contains a limited level of error checking to ensure
 * that the user cannot set a negative threshold or filter size, or a threshold > 255.
 * The function also handles displaying the titles on the images if the user desires
 *
 * @param[in] key - a character corresponding to the key that was pressed
 *
 ******************************************************************************/
KeyEvent::KeyEvent ( unsigned char key ) : key ( key ) {}

void KeyEvent::action ( State &state )
{
    switch ( key )
    {
        //Escape
        case ESC:
            free2D ( state.imageMono );
            free2D ( state.imageBinThr );
            glutLeaveMainLoop();
            return;
            break;
        //space
        case ' ':
            if ( !state.DisplayImageTitles )
            {
                state.DisplayImageTitles = true;
            }
            else
            {
                state.DisplayImageTitles = false;
            }
            break;
        //left arrow key
        case GLUT_KEY_LEFT:
            if ( state.Threshold < 1 )
            {
                break;
            }
            state.Threshold--;
            break;
        //right arrow key
        case GLUT_KEY_RIGHT:
            if ( state.Threshold > 254 )
            {
                break;
            }
            state.Threshold++;
            break;
        //up arrow key
        case GLUT_KEY_UP:
            state.FilterSize++;
            break;
        //down arrow key
        case GLUT_KEY_DOWN:
            if ( state.FilterSize < 1 )
            {
                break;
            }
            state.FilterSize--;
            break;
    }
    free2D ( state.imageBinThr );
    state.imageBinThr = binaryThreshold ( state.width,
                                          state.height, state.imageMono, state.Threshold );
    //Redisplay the screen
    glClear ( GL_COLOR_BUFFER_BIT |
              GL_DEPTH_BUFFER_BIT ); // Clean the screen and the depth buffer
    glutPostRedisplay();
    //set screen title
    string title = "Threshold: " + to_string (
                               state.Threshold ) + " Filter Size: " + to_string (
                               state.FilterSize );
    const char *titlecstring = title.c_str();
    glutSetWindowTitle ( titlecstring );
}
