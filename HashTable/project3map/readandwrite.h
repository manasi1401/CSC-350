/***************************************************************************//**
 * @file
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Node.h"
#include <iomanip>
using namespace std;

char* ReadTheFile(ifstream &fin);
void writeToScreen(int TotalWords, int UniqueWords, float Time, string input);
void FindRankAndMakeMap(Node**, int, map<double, int> &, ofstream &fout);
void WriteToWrdFile(ofstream &foutWrd, string inputName, int TotalWords, int UniqueWords);
void WriteToCsvFile(ofstream &foutCsv, map<double, int> &, string inputName, int TotalWords, int UniqueWords);
int lengthOfFreq(int Freq);
