/***************************************************************************//**
 * @file usage.h
 * @author Nicholas Chmielewski
 * @brief Function prototypes required for usage.cpp
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

/*!prints out information about how to run the encoder*/
void printUsage();

/*!checks to make sure the file can be opened*/
int checkAndOpen(ifstream &fin, ofstream &foutWrd, ofstream &foutCsv, char * input, string &inputFileName);
