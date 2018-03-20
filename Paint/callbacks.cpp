/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the callbacks class. 
 *****************************************************************************/
#include "callbacks.h"
/***************************************************************************//**
 * @author Paul Hinker
 *
 * @brief A callback function for refreshing the display
 ******************************************************************************/
void display()
{
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);
    
    //eventDispatcher(new DisplayEvent());
    eventDispatcher(new DisplayEvent());
	
    // Swap the buffers
    glutSwapBuffers();
}

/***************************************************************************//**
 * @author Paul Hinker
 * @brief A callback function for handling keyboard input
 *
 * @param[in] key - the key that was pressed
 * @param[in] x   - the x-coordinate when the key was pressed
 * @param[in] y   - the y-coordinate when the key was pressed
 ******************************************************************************/
void keyboard(unsigned char key, int x, int y)
{
   int ScreenHeight = glutGet(GLUT_WINDOW_HEIGHT);
   y = ScreenHeight - y;

  eventDispatcher(new KeyEvent(key));
      cout << "Key " << (char)key << " press detected at ["
           << x << ", " << y << "]\n";
}

/***************************************************************************//**
 * @author Paul Hinker
 * @brief A callback function for handling reshape events
 *
 * @param[in] w      - the width of the newly reshaped window
 * @param[in] h      - the height of the newly reshaped window
 ******************************************************************************/
void reshape(int w, int h)
{

    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    gluOrtho2D( 0.0, w, 0.0, h );       // make OpenGL coordinates
    glViewport( 0, 0, w, h );           // the same as the screen coordinates
}

/***************************************************************************//**
 * @author Peterson, Shawn
 * @brief A callback function for handleing mouse input
 *
 * @param[in] button      - the width of the newly reshaped window
 * @param[in] state      - the height of the newly reshaped window
 * @param[in] x      - the width of the newly reshaped window
 * @param[in] y      - the height of the newly reshaped window
 ******************************************************************************/
void mouseClick( int button, int state, int x, int y)
{
   int ScreenHeight = glutGet(GLUT_WINDOW_HEIGHT);
   y = ScreenHeight - y;    
   eventDispatcher(new MouseEvent(x, y, button, state));
   cout << "Mouse button " << ButtonName[button] << " went " << ButtonState[state] << " at coordinates [" << x << ", " << y << "]\n"; 
}

/***************************************************************************//**
 * @author Peterson, Shawn
 * @brief The eventDispatcher function that retains state and calls action 
 * function
 *
 * @param[in] event - a class holding the action function   
 ******************************************************************************/
void eventDispatcher(Event* event)
{
    static State state;
    event->action(state);
    delete event;
}

