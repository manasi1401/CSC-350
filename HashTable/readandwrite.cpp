/***************************************************************************//**
 * @file
 * @author Nicholas Chmielewski
 * @brief Function definitions required to read and write from file/ screen
 ******************************************************************************/

#include "readandwrite.h"
#include <cstring>

/*************************************************************************//**
 * @brief Reads the information from the file
 *
 * @param[in] fin - input file identifier
 *
 * @return ReadText - a char array with the data from the file
 ****************************************************************************/
char* ReadTheFile(ifstream &fin)
{
	// seek and find the size of the file
    fin.seekg(0, fin.end);
    long long int FileSize =fin.tellg();
	// return to the beginning
    fin.seekg(0, fin.beg);
	// create char array
	char *ReadText= (char*) malloc (FileSize+1);
	if(FileSize==0)
	{
		// if empty set to null
		ReadText[0] ='\0';
		return ReadText;
	}
    
	// read the information in
    fin.read(ReadText, FileSize);
	
	ReadText[FileSize] ='\0';
    return ReadText; 
}

/*************************************************************************//**
 * @brief Writes some information to the terminal screen
 *
 * @param[in] TotalWords - an integer representing the total # of words
 * @param[in] UniqueWords - an integer representing the # of unique words
 * @param[in] input - a string storing the input file name
 * @param[in] TableSize - Size of the hash table
 *
 ****************************************************************************/
void writeToScreen(int TotalWords, int UniqueWords,  string input, int TableSize)
{
	cout << "Read " << TotalWords << " words from the file " << input << "." << endl; 
	cout << "Inserted " << UniqueWords << " distinct words into the hash table of size "<<TableSize << endl;
}

/*************************************************************************//**
 * @brief A function to find the rank and freq of the words and then output them accordingly
 *        to the .wrd file
 *
 * @param[in] SortedNodesByFreq - a pointer to our structure storing the frequencies
 * @param[in] SizeOfTable - an int representing the size of the table
 * @param[in] RankFreqMap - a map storing both the rank and freq
 * @param[in] foutWrd - output file identifier
 *
 ****************************************************************************/
void FindRankAndMakeMap(Node** SortedNodesByFreq, int SizeOfTable, map<double, int> &RankFreqMap, ofstream &foutWrd)
{
	// initialize variables
  	int firstRank=0, lastRank= 0, start, end, count, TrackFreq;
  	double averageRank;
	string rank;
	
	// output the header
	foutWrd << "Word Frequencies" << setw(34) << "Ranks" << setw(13) << "Avg Rank" << endl;
	foutWrd << "----------------" << setw(34) << "-----" << setw(13) << "--------" << endl;

	// for loop runs until table size
	for( int i =0; i < SizeOfTable; )
	{
		// set the first rank
		firstRank = i+1;
	   	int j = i;
		// set the current frequency
	   	TrackFreq = SortedNodesByFreq[j]->frequency;

		// in the case of the first word
		if(TrackFreq == 1)
			foutWrd << "Words occurring once:";
		//otherwise output this
		else 
			foutWrd << "Words occurring " << TrackFreq << " times:";
		
		// while still smaller than the table size and the freq of the next word is still the same
	  	while( j <SizeOfTable-1 && SortedNodesByFreq[j]->frequency == SortedNodesByFreq[j+1]->frequency)
	  	{
			// if j and i are equal just set the ranks equal as well
	    	if(j == i)
	    		lastRank = firstRank;
			// increment j and last rank
	    	lastRank++;
	    	j++; 
	  	}
		// if the last rank is greater than the first
	  	if(lastRank > firstRank)
	  	{
			// we have more than one word, so find the avg
			averageRank = (double)(firstRank + lastRank)/2;
			// find the range of the rank
			rank = to_string(firstRank) + '-' + to_string(lastRank);

			// in the case of the first word
			if( TrackFreq == 1)
			{
				foutWrd << setw(29) << rank;
			}
			// otherwise output this
			else
			{	
				foutWrd << setw((26 - lengthOfFreq(TrackFreq))) << rank;
			}
			foutWrd << setw(13) << averageRank << endl;
			
			end = lastRank;
			count = 0;
			
			// for loop for fancy formatting
			for(start = firstRank-1; start < end; start++)
			{			
				if(lastRank-firstRank >= 5)
				{
					if(count == 5)
					{
						foutWrd << endl;
						start--;
						count = 0;
					}
					else
					{
						foutWrd << setw(15) << left << SortedNodesByFreq[start]->word << right;
						count++;
					}
				}
				else
				{
					foutWrd << setw(15) << left << SortedNodesByFreq[start]->word << right;
				}
			}
			foutWrd << endl << endl;
	  	}
	  	else
	  	{
	   		averageRank = firstRank;
			foutWrd << setw((26 - lengthOfFreq(TrackFreq))) << firstRank;
			foutWrd << setw(13) << fixed << setprecision(1) << averageRank << endl;
			foutWrd << SortedNodesByFreq[j]->word << endl << endl;
	  	}
	  	RankFreqMap[averageRank] = TrackFreq;
	  	i =j +1;
	}
}

/*************************************************************************//**
 * @brief Writes data to the .wrd file
 *
 * @param[in] foutWrd - output file identifier
 * @param[in] inputName - string for the input name
 * @param[in] TotalWords - int representing the total # of words
 * @param[in] UniqueWords - total num of unique words
 *
 ****************************************************************************/
void WriteToWrdFile(ofstream &foutWrd, string inputName, int TotalWords, int UniqueWords)
{
	foutWrd << "Zipf's Law: Word Concordance" << endl;
	foutWrd << "----------------------------" << endl;
	foutWrd << "File:" << setw(12) << "" << inputName << endl;
	foutWrd << "Total Words:" << setw(5) << "" << TotalWords << endl;
	foutWrd << "Distinct Words:" << setw(2) << "" << UniqueWords << endl << endl;
}

/*************************************************************************//**
 * @brief Writes data to the .csv file
 *
 * @param[in] foutCsv - output file identifier
 * @param[in] RankFreqMap - map containing the rank and frequencies
 * @param[in] inputName - string for the input name
 * @param[in] TotalWords - int representing the total # of words
 * @param[in] UniqueWords - total num of unique words
 *
 ****************************************************************************/
void WriteToCsvFile(ofstream &foutCsv, map<double, int> &RankFreqMap, string inputName, int TotalWords, int UniqueWords)
{
	map<double, int>::iterator itr = RankFreqMap.begin();

	foutCsv << "Zipf's Law: Rank * Freq = const" << endl;
	foutCsv << "-------------------------------" << endl;
	foutCsv << "File:" << setw(12) << "" << inputName << endl;
	foutCsv << "Total Words:" << setw(5) << "" << TotalWords << endl;
	foutCsv << "Distinct Words:" << setw(2) << "" << UniqueWords << endl;

	if(!RankFreqMap.empty())
	{
		foutCsv << setw(10) << "Rank," << setw(9) << "Freq," << setw(12) << "R*F"<< endl;
		for(; itr !=RankFreqMap.end(); itr++)
		{
	 		foutCsv << setw(10) << setprecision(1) << fixed << itr->first 
	 			<< "," << setw(9) << itr->second << "," << setw(12) << itr->first * itr->second << endl;
		}
	}
}

/*************************************************************************//**
 * @brief This function finds the number of digits in the freq
 *
 * @param[in] Freq - an integer representing the frequency
 *
 * @return numberOfDigits-1 - how many digits -1 make up the freq
 ****************************************************************************/
int lengthOfFreq(int Freq)
{
	int numberOfDigits = 0;
	while(Freq > 0)
	{
		numberOfDigits++;
		Freq = Freq/10;
	}
	return numberOfDigits - 1;
}
