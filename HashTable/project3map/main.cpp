#include "usage.h"
#include "Node.h"
#include "readandwrite.h"
#include "HelperFn.h"
#include <ctype.h>
#include <iomanip>
#include <string.h>
#include <map>
#include <chrono>
using namespace std;

int main( int argc, char *argv[] )
{
	//Checking the command line arguments
	if ( argc != 2 )
	{
      cout << "ERROR: Must provide 2 command line arguments" << endl;
		printUsage();
      return -1;
	}
	
	ifstream fin;  // input file declaration 
	ofstream foutWrd, foutCsv;		    // output file declarations
	char *inputfilename = argv[1];	
	map<string, int> FrequencyTracker;
	map <double, int> RankFreqMap; 
	string inputFileName;

	chrono::duration<double> elapsedTime;
 	auto startTime = chrono::system_clock::now();
  
   checkAndOpen(fin, foutWrd, foutCsv, inputfilename, inputFileName);

	char* ReadInText = ReadTheFile(fin);
	int TotalNumberOfWords= TokenizeText(ReadInText, FrequencyTracker);
   Node** SortedNodesByFreq = BuildSortedNodeTable(FrequencyTracker);
  
	qsort((void*)SortedNodesByFreq, FrequencyTracker.size(), sizeof(Node*), compareNode);
	WriteToWrdFile(foutWrd, inputFileName,TotalNumberOfWords ,FrequencyTracker.size());

	FindRankAndMakeMap(SortedNodesByFreq, FrequencyTracker.size(), RankFreqMap, foutWrd);
	
	WriteToCsvFile(foutCsv, RankFreqMap, inputFileName, TotalNumberOfWords, FrequencyTracker.size());

	
   auto endTime = chrono::system_clock::now();
   elapsedTime = (endTime - startTime);
	
	writeToScreen(TotalNumberOfWords, FrequencyTracker.size(), (float)elapsedTime.count() *1000, inputFileName);
	
	fin.close();
	foutWrd.close();
	foutCsv.close();

	return 0;
}
