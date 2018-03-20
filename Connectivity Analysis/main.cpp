#include <iostream>
#include <GL/freeglut.h>
#include "inputHandler.h"
#include "image.h"
#include "lodepng.h"
#include "callbacks.h"
#include "initState.h"
using namespace std;
/***************************************************************************//**
 * @brief The main function sets default values to threshold and filer size.
 * It also initializes the glut and calls the glutMainLoop.
 *
 * @param[in] argc - number of command line arguments
 * @param[in] argv- 2D char array of commad line arguments
 * @return 0 - successfully exited main function
 ******************************************************************************/
int main ( int argc, char *argv[] )
{

    if ( inputHandler ( argc, argv ) )
    {
        return -1;
    }
    const char *Threshold = "128";
    const char *filterSize = "32";
    if ( argc >= 3 )
    {
        Threshold = argv[2];
    }
    if ( argc == 4 )
    {
        filterSize = argv[3];
    }

    glutInit ( &argc, argv );

    initOpenGL ( argv, Threshold, filterSize );
    glutMainLoop();

    return 0;
}
/***************************************************************************//**
 * @brief It calls the folowing intialization routines
 *   * Initializes the glut system
 *   * Sets the initial display mode
 *   * Sets the initial window size
 *   * Sets the initial window position
 *   * Creates the window and sets the window title
 *   * Sets the DisplayFunc callback
 *   * Sets the KeyboardFunc callback
 *   * Calls the event dispatcher to initialize state
 *
 * @param[in] filename - main function argument consisting input file name
 * @param[in] Threshold- default threshold
 * @param[in] filterSize - default filter Size
 *
 ******************************************************************************/
void initOpenGL ( char **filename, const char *Threshold,
                  const char *filterSize )
{
    unsigned int _width = 0, _height = 0;
    byte **imageRGBA = readPNG ( filename[1], _width, _height );
    eventDispatcher ( new InitStateEvent ( imageRGBA,
                                           atoi ( Threshold ), atoi ( filterSize ), _width,
                                           _height ) );
    glutInitDisplayMode ( GLUT_RGBA |
                          GLUT_SINGLE );        // 32-bit graphics and single buffering

    char *titlecstring = new char[100];
    strcpy ( titlecstring, "Threshold: " );
    strcat ( titlecstring, Threshold );
    strcat ( titlecstring, " Filter Size: " );
    strcat ( titlecstring, filterSize );

    glutInitWindowSize ( 2 * _width,
                         2 * _height );         // initial window size
    glutInitWindowPosition ( 0,
                             0 );                        // initial window  position
    glutCreateWindow (
                titlecstring );                           // window title
    glClearColor ( 0.0, 0.0, 0.0,
                   0.0 );                    // use black for glClear command

    // callback routines
    glutDisplayFunc (
                display );            // how to redisplay window
    glutReshapeFunc (
                reshape );            // how to resize window
    glutKeyboardFunc (
                keyboard );          // how to handle key presses
    glutSpecialFunc ( arrowkey );

    free2D ( imageRGBA );
    delete[] titlecstring; //free the string
}

