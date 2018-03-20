/***************************************************************************//**
* @file encoder.h
*
* @brief This header contains the functions for the encoder.
*
* @author: Mark Ebarle & Manasi Paste
*
* @par Class: 
* CSC315 Data Structures
*
* @date:   Fall 2017
*
*/
#ifndef __ENCODER_H_
#define __ENCODER_H_

#include "HuffmanBinaryTree.h"

/// Makes all function calls to do the encoding portion of huffman coding
void HuffmanCodingEncoder(ifstream &fin, ofstream &fout, string inputFileName, string outputFileName);
/// Creates a string of characters representing the input file
void CreateFileStringFromFile(ifstream &fin, string &fullMessage);
/// Creates a map that represents the histogram of frequencies of symbols of input file
void CreateMapRepresentingHistogramFromFileString(map <char, int> &freq, string contents);
/// Constructs the huffman coding tree
void BuildHuffmanCodingTree(vector<Nodes*> &sortedMap, HuffmanBinaryTree *huffTree);
/// Inserts the nodes from the map into a vector
int PlaceNodesIntoVectorOfNodes(vector<Nodes*> &sortedMap, map <char, int> freq);
/// Prints the histogram of symbol frequencies to an output file
void PrintOutHistogramDataToOutputFile(ofstream &fout, vector<Nodes*> sortedMap, int count);
/// Compares the nodes passed in and return true or false to indcate greater or lesser
bool compareNodes(Nodes *One, Nodes *Two);
/// Prints out statistics of encoding to the commandline
void EncoderSecondPassOutput(map<char, int> freq, HuffmanBinaryTree *huffTree, double &bitPerSymbolResult, double &entropyResult);
/// Creates a bit stream from the huffman coding table constructed for decoding
int CreateBitStreamFromHuffmanCodingTable(string fileContents, HuffmanBinaryTree *huffTree, ofstream &fout);
/// Outputs the statistics calculated on the second pass with the encoder
void OutPutEncoderPassTwoStatistics(int encodedBytes, string outputFileName, int lengthOfFile, double entropyResult, double averageBitPerSymbol, string fileContents);
#endif
