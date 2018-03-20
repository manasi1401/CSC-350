#include "HelperFn.h"

int compareNode(const void* n, const void *m)
{
    Node * firstNode = *(Node**)n;
    Node * secondNode= *(Node**)m;


  	int first = firstNode->frequency;
  	int second = secondNode->frequency;

  	if((first -second)==0)
  	{
    	if(firstNode->word.compare(secondNode->word) <= 0)
	  		return -1;
	  	if(firstNode->word.compare(secondNode->word)> 0)
	  		return 1;
  	}
    return second -first;
}

int TokenizeText(char *ReadInText, map<string, int> &FrequencyTracker)
{
    int TotalNumberOfWords =0;
    string x;
  	char *oneWord;
	for(int i = 0; ReadInText[i] != '\0'; i++) 
    	ReadInText[i] = tolower(ReadInText[i]);

	oneWord = strtok(ReadInText, " ,.-;:()!?*@#$%^&~`[]{}_+=><~`|1234567890\\/\n\r\"\f\t\v\a\b\?\0");

	while(oneWord != nullptr)
	{
  	while(oneWord[0] =='\'')
		{
			oneWord = oneWord+1;
		}
		while(oneWord[strlen(oneWord) -1] =='\'')
		{
			memmove(oneWord, oneWord, strlen(oneWord)-1);
			oneWord[strlen(oneWord)-1] =0;
		}
		
		if(*oneWord != '\0' && *oneWord != 127)
		{
			TotalNumberOfWords++;
			x= oneWord;
			if(FrequencyTracker.find(x) == FrequencyTracker.end())
					FrequencyTracker[x] =1;
			else
					FrequencyTracker[x]++;
		}
		oneWord = strtok(nullptr, " ,.-:;()!?*@#$%^&~`[]{}_+=><~`|1234567890\\/\n\r\"\f\t\v\a\b\?\0");
	}
	return TotalNumberOfWords;
}

Node** BuildSortedNodeTable(map<string, int> FrequencyTracker)
{
    int counter =0;
    Node** SortedNodesByFreq =new Node* [FrequencyTracker.size()];
    map<string, int>::iterator it;
	for(it = FrequencyTracker.begin(); it!= FrequencyTracker.end(); it++)
	{
		Node *newNode = new Node();
		newNode->word = it->first;
		newNode->frequency = it->second;
		SortedNodesByFreq[counter] = newNode;
		counter++;
	}
	return SortedNodesByFreq;
}
