/*************************************************************************//**
*@file
*@author Mark Ebarle
*@brief Defines structure of nodes of the huffman Binary Tree
******************************************************************************/
#include <iostream>
#include <cstring>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef _NODES_H_
#define _NODES_H_

/*!
*@brief Structure of the Node
*/
struct Nodes{
	/*!Key of the Node*/
    char key;
   /*!Frequency of the key in the message*/
    int frequency;
    /*!Pointer to the Left Child*/
    Nodes *leftChild = nullptr;
    /*!Pointer to the Right Child*/
    Nodes *rightChild = nullptr;
};
#endif
