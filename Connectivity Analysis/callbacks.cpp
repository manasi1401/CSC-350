/***************************************************************************//**
 * @file callbacks.cpp
 *
 * @par Description
 *
 * @brief This file contains all the functions needed to interface our analysis
 * framework with the Glut main loop and handle user input events (resizing the window,
 * pressing the spacebar, etc). It also has the event dispatcher which calls different events (like displayEvent).
 *
 * @author Manasi Paste, Dakotah Rusley
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 *
 ******************************************************************************/

#include "callbacks.h"

/***************************************************************************//**
 * @brief The event dispatcher relays the current state of the world from
 * the Glut main loop to the appropriate function. There are two main classes
 * of events - DisplayEvent and KeyEvent. A display event is called whenever
 * an image needs to be updated (for example, when the threshold is changed).
 * A keyEvent is called whenever an arrow key / spacebar is pressed, in order
 * to update the current state of the world
 *
 * @param[in] event - some incoming event that needs handled and dispatched
 * appropriately
 *
 *
 ******************************************************************************/
void eventDispatcher ( Event *event )
{
    static State state;
    event->action ( state );
    delete event;
}
/***************************************************************************//**
 * @brief Display, quite simply, clears the screen and calls a new DisplayEvent.
 * This event is then handled by the appropriate action function.
 *
 ******************************************************************************/
void display()
{
    glClear ( GL_COLOR_BUFFER_BIT );
    eventDispatcher ( new DisplayEvent() );
    glFlush(  );
}

/***************************************************************************//**
 * @brief Reshape is needed by Glut in order to handle dynamic window resizing.
 * We also call a new DisplayEvent when the window is resized, in order to ensure
 * our image is persistantly displayed
 *
 * @param[in] w      - the width of the newly reshaped window
 * @param[in] h      - the height of the newly reshaped window
 ******************************************************************************/
void reshape ( int w, int h )
{
    glViewport ( 0, 0, w, h );
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity(  );
    gluOrtho2D ( 0.0, w, 0.0, h );
    eventDispatcher ( new DisplayEvent() );
}

/***************************************************************************//**
 * @brief Keyboard (another standard Glut function) simply handles a keypress.
 * In our case, we only use this for detecting spacebar presses and the escape key
 *
 * @param[in] key - the key that was pressed
 * @param[in] x   - the x-coordinate when the key was pressed
 * @param[in] y   - the y-coordinate when the key was pressed
 ******************************************************************************/
void keyboard ( unsigned char key, int x, int y )
{
    eventDispatcher ( new KeyEvent ( key ) );
}
/***************************************************************************//**
 * @brief ArrowKey is a special function to detect the UP, DOWN, LEFT and
 * RIGHT arrows on the keyboard. It calls the KeyEvent which handles the event relating to
 * the pressed key
 *
 * @param[in] key - the key that was pressed
 * @param[in] x   - the x-coordinate when the key was pressed
 * @param[in] y   - the y-coordinate when the key was pressed
 ******************************************************************************/
void arrowkey ( int key, int x, int y )
{
    eventDispatcher ( new KeyEvent ( key ) );
}
