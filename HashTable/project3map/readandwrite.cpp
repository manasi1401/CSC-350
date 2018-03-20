/***************************************************************************//**
 * @file
 ******************************************************************************/

#include "readandwrite.h"
#include <cstring>

char* ReadTheFile(ifstream &fin)
{
    fin.seekg(0, fin.end);
    long long int FileSize =fin.tellg();
	
    fin.seekg(0, fin.beg);
	char *ReadText= (char*) malloc (FileSize+1);
	if(FileSize==0)
	{
		ReadText[0] ='\0';
		return ReadText;
	}
    
    fin.read(ReadText, FileSize);
		ReadText[FileSize] ='\0';
    return ReadText; 
}

void writeToScreen(int TotalWords, int UniqueWords, float RunTime, string input)
{
	cout << "Read " << TotalWords << " words from the file " << input << "." << endl; 
	cout << "Inserted " << UniqueWords << " distinct words into the hash table." << endl;
	cout << "Elapsed time = " << setprecision(1) << fixed << RunTime << " msec" << endl << endl;
}

void FindRankAndMakeMap(Node** SortedNodesByFreq, int SizeOfTable, map<double, int> &RankFreqMap, ofstream &foutWrd)
{
  	int firstRank=0, lastRank= 0, start, end, count, TrackFreq;
  	double averageRank;
	string rank;
	
	foutWrd << "Word Frequencies" << setw(34) << "Ranks" << setw(13) << "Avg Rank" << endl;
	foutWrd << "----------------" << setw(34) << "-----" << setw(13) << "--------" << endl;

	for( int i =0; i < SizeOfTable; )
	{
		firstRank = i+1;
	   	int j = i;
	   	TrackFreq = SortedNodesByFreq[j]->frequency;

		if(TrackFreq == 1)
			foutWrd << "Words occurring once:";
		else
			foutWrd << "Words occurring " << TrackFreq << " times:";
		
	  	while( j <SizeOfTable-1 && SortedNodesByFreq[j]->frequency == SortedNodesByFreq[j+1]->frequency)
	  	{
	    	if(j == i)
	    		lastRank = firstRank;
	    	lastRank++;
	    	j++; 
	  	}
	  	if(lastRank > firstRank)
	  	{
			averageRank = (double)(firstRank + lastRank)/2;
			rank = to_string(firstRank) + '-' + to_string(lastRank);

			if( TrackFreq == 1)
			{
				foutWrd << setw(29) << rank;
			}
			else
			{	
				foutWrd << setw((26 - lengthOfFreq(TrackFreq))) << rank;
			}
			foutWrd << setw(13) << averageRank << endl;
			
			end = lastRank;
			count = 0;
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

void WriteToWrdFile(ofstream &foutWrd, string inputName, int TotalWords, int UniqueWords)
{
	foutWrd << "Zipf's Law: Word Concordance" << endl;
	foutWrd << "----------------------------" << endl;
	foutWrd << "File:" << setw(12) << "" << inputName << endl;
	foutWrd << "Total Words:" << setw(5) << "" << TotalWords << endl;
	foutWrd << "Distinct Words:" << setw(2) << "" << UniqueWords << endl << endl;
}

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
	 		foutCsv << setw(10) << setprecision(1) << fixed << itr->first << "," << setw(9) << itr->second << "," << setw(12) << itr->first * itr->second << endl;
		}
	}
}

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


