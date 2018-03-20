/***************************************************************************//**
* @file decoder.h
*
* @brief This header contains the functions for the decoder.
*
* @author: Mark Ebarle & Manasi Paste
*
* @par Class: 
* CSC315 Data Structures
*
* @date:   Fall 2017
*
*****************************************************************************/
#include "Nodes.h"
#include "encoder.h"
#include "HuffmanBinaryTree.h"

/*!Opens the input and output file. Calls fucntions redquired to decode*/
int decoder (char inputfile[], char outputfile[], double &encodedBytes, double &decodedBytes);
/*!Builds a tree from the sorted vector of Nodes*/
Nodes* buildTree(vector<Nodes*> sortedMap, HuffmanBinaryTree *huffTree);
/*!Reads the encoded message and decodes it by traversing the tree*/
void ReadAndDecode(ifstream &fin, ofstream &fout, Nodes *root, int pos, int freq, double &encodedBytes, double &decodedBytes);

