/***************************************************************************//**
* @file main.cpp
*
* @mainpage CSC 315 - Fall 2017
*
* @brief Main function for project 3 - Zipf's Law
*
* @section course_section Course Information
*
* @authors Nicholas Chmielewski, Manasi Paste
* 
* @date 6 November 2017
* 
* @par Professor 
* Dr. Hinker
*
* @par Course
* CSC 315 - Section 1 - Fall 2017
*
*
* @section program_section Program Description
*
* @par Description
*
* Zipf’s Law is a curious observation about the statistical distribution of words 
* in text: the frequency of any word is inversely proportional to its rank
* in the frequency table. Word frequency is the number of times a given word 
* appears in the text. When words are ranked according to frequency, the most frequent 
* word is given rank 1, the next-most-frequent word is given rank 2, etc. Ties are 
* handled by assigning the middle value in a range of ranks. For example, in a 
* two-way tie for most frequent word, each word is given the rank of 1.5.
*
* @section compile_section Compile Section
*
* @par Build
  @verbatim
% make
  @endverbatim
* @par Run
  @verbatim
zipf textfile
  @endverbatim
* @par Usage
*
* - Read in words from a text file, counting their frequency of occurrence. 
* - Store  the  words  and their frequencies  in  a  hash  table  that  you  
*   implement  with  a  hash  table  class. 
* - Use open addressing with linearprobing to resolve collisions.
* - Start with a dynamically-allocated hash table of about 1K entries
* - Whenever  the  hash  table  gets  over 75%  full,  rehash  the  contents  
*   into  a  new  hash table, approximately twice as large as the previous 
*   one. Print a message to the screen, notifying the user when rehashing occurs.
* - Output  the  results  to  two  files,  with  the  same  name  as  the  
*   input text file, but  different  extensions.
*
* @section todo_bugs_modification_section To Do, Bugs, and Modifications
* 
* 
*
* @par Revision History
* git commit history: https://gitlab.mcs.sdsmt.edu/7404855/csc315_fall2017_project3/commits/master
*
*****************************************************************************/
#include "usage.h"
#include "Hash.h"
#include "Node.h"
#include "readandwrite.h"
#include <ctype.h>
#include <iomanip>
#include <string.h>
#include <map>
#include <ctime>
#include <chrono>
using namespace std;

/*************************************************************************//**
 * @brief main function
 *
 * @param[in] argc - number of command line arguments
 * @param[in] argv - array of C strings representing the command line
 *  arguments
 *
 * @return 0
 ****************************************************************************/
int main( int argc, char *argv[] )
{
	//Checking the command line arguments
	if ( argc != 2 )
	{
    cout << "ERROR: Must provide 2 command line arguments" << endl;
		printUsage();
    return -1;
	}
	
	ifstream fin;					    // input file declaration
	ofstream foutWrd, foutCsv;		    // output file declarations
	char *inputfilename = argv[1];	    // argv[1] is the input file name
	Hash HashTable;					    // constructor for the hash table
   map <double, int> RankFreqMap;      // a map to store the avg rank and frequency
	string inputFileName;				// string place holder for the input name
	char* ReadInText;					// char array to store the text that was read in
   int SizeOfTable;					// an int for the size of the hash table
   Node** SortedNodesByFreq;			// pointer to Node
  
	// code used for computing the speed of our program
  chrono::duration<double> elapsedTime;
  auto startTime = chrono::system_clock::now();
 
	// checks if the files are open
  int inputopen =checkAndOpen(fin, foutWrd, foutCsv, inputfilename, inputFileName);
  if(inputopen ==-1)
  { 
    cout<<"Input File didn't open. Exiting"<<endl;
    return -1;
  }
	// reads the information from the input file and stores it in ReadInText
	ReadInText = ReadTheFile(fin);
	
	// creates the initial hash table
	HashTable.BuildHashTable(ReadInText);
	
	// writes the last bit of information to the terminal to confirm that the program ran
	writeToScreen(HashTable.GetTotalFrequency(), HashTable.GetNumberOfUniqueWords(), 
	     inputFileName, HashTable.GetTableSize());
	     
	//Sort the Hash Table
	SortedNodesByFreq = HashTable.SortTable();
	SizeOfTable = HashTable.GetNumberOfUniqueWords();
	
	// write the header to the .wrd file
	WriteToWrdFile(foutWrd, inputFileName, 
	    HashTable.GetTotalFrequency(), HashTable.GetNumberOfUniqueWords());

	// stores the rank and frequency in a map to be used later, and also
	// outputs the word concordance to the .wrd file
	FindRankAndMakeMap(SortedNodesByFreq, SizeOfTable, RankFreqMap, foutWrd);
	
	// writes the output information to the .csv file
	WriteToCsvFile(foutCsv, RankFreqMap, inputFileName, 
	    HashTable.GetTotalFrequency(), HashTable.GetNumberOfUniqueWords());
	
	// stops and calculates the time it took to run
 	auto endTime = chrono::system_clock::now();
 	elapsedTime = (endTime - startTime);

	cout << "Elapsed time = " << setprecision(1) << fixed 
	     << (float)elapsedTime.count() *1000 << " msec" << endl << endl;
	     
	 // Free the allocated char string for text    
	free(ReadInText);
	//Clearing memory for the Sorted Node Table
   for(int j =0; j <HashTable.GetNumberOfUniqueWords(); j++) 
		delete SortedNodesByFreq[j];
	delete[] SortedNodesByFreq;
	
	// ALWAYS CLOSE YOUR FILES!
	fin.close();
	foutWrd.close();
	foutCsv.close();

	return 0;
}
