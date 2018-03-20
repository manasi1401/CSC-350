/*************************************************************************//**
 * @file state.h
 * @brief Defines the structure of state which holds images and necessary information for analysis
 *****************************************************************************/
#ifndef _STATE_H
#define _STATE_H

#include <cstdio>
#include "set.h"
#include <iostream>
/*!Typedef byte as an unsigned char*/
typedef unsigned char byte;
/*!
*@brief Contains the state of the program and consists of 4 images and necessary information for analysis
*/
struct State
{
    /*!Threshold of binary image*/
    int Threshold;
    /*!Filter size to be applied to the image*/
    int FilterSize;
    /*!Total number of Groups found in the image for a given threshold*/
    int TotalGroups;
    /*!Boolean determining if teh labels are to be displayed for images*/
    bool DisplayImageTitles;
    /*!Height of the image*/
    unsigned height;
    /*!Width of the image*/
    unsigned width;
    /*!GrayScale image*/
    byte **imageMono;
    /*!Binary Image*/
    byte **imageBinThr;
    /*!Pseudo colorued Image showing connected components*/
    byte **imagePseudo;
    /*!Pseudo colored image showing size filtered connected components*/
    byte **imageFiltered;
    /*!2D array to hold the labels of the image*/
    int **pixelLabels;
    /*!Set to hold equivalencies in group labels*/
    DisjointSet GroupedLabels;
    /*!2D array to hold labels for filtered image*/
    int **FilteredPixelLabels;
    /*!Number of redisplays*/
    int RedisplayCount;
};

#endif
