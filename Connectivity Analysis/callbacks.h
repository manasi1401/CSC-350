/***************************************************************************//**
 * @file callbacks.h
 *
 * @par Description
 *
 * @brief This file contains the function declarations used to interface with Glut
 *
 * @author Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 *
 *
 ******************************************************************************/
#ifndef CALLBACKS_H
#define CALLLABCKS_H

#include <iostream>
#include "state.h"
#include "event.h"
#include "display.h"
#include "keyboard.h"
#include <cstdio>
#include <GL/glut.h>
using namespace std;

/*!Displays on to the screen*/
void display();
/*!Reshapes the screen*/
void reshape ( int w, int h );
/*!Reads in put from the keyboard*/
void keyboard ( unsigned char key, int x, int y );
/*!Calls action function for events*/
void eventDispatcher ( Event *event );
/*!Reads the special keys on the keyboard like direction arrows*/
void arrowkey ( int key, int x, int y );

#endif
