/***************************************************************************//**
 * @file readandwrite.h
 * @author Nick Chmielewski
 * @brief Function prototypes required to read and write from file/ screen
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Node.h"
#include <iomanip>
using namespace std;
/*!Reads text from the input file*/
char* ReadTheFile(ifstream &fin);
/*!Write output information to the screen*/
void writeToScreen(int TotalWords, int UniqueWords, string input, int TableSize);
/*!Calculates the Rank and freq of the word and stores them in a map*/
void FindRankAndMakeMap(Node**, int, map<double, int> &, ofstream &fout);
/*!Writes data to the .wrd file*/
void WriteToWrdFile(ofstream &foutWrd, string inputName, int TotalWords, int UniqueWords);
/*!Writes data to the .csv file*/
void WriteToCsvFile(ofstream &foutCsv, map<double, int> &, string inputName, int TotalWords, int UniqueWords);
/*!finds how many digits are in the frequency*/
int lengthOfFreq(int Freq);
