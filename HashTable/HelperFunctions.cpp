/***************************************************************************//**
 * @file HelperFunctions.cpp
 * @author Manasi Paste
 * @brief Function definations to compare nodes and Find next prime number
 ******************************************************************************/
#include "HelperFunctions.h"

/*************************************************************************//**
 * @brief compares two nodes for their frequency. Nodes with same frequencies are 
 * compared alphabetically
 *
 *@param[in] n - first node to be compared
 *@param[in] m - second node to be compared
 *
 * @return second -first - The sign of this difference determines if the swap is necessary or not
 * during the qsort
 ****************************************************************************/
int compareNode(const void* n, const void *m)
{
	// set the first and second nodes
    Node * firstNode = *(Node**)n;
    Node * secondNode= *(Node**)m;

	// set the first and second frequencies
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
/*************************************************************************//**
 * @brief Check if a given integer is prime
 * @param[in] n - integer to be checked
 ****************************************************************************/
bool isPrime(int n)
{
	for(int i =2; i <= sqrt(n)+1; i++)
	{
		if(n%i ==0)
		return false;
	}
	return true;
}
/*************************************************************************//**
 * @brief finds the next prime number
 * @param[in] n - integer whose next prime is to be calculated
 * @return prime - Next prime number to the given parameter
 ****************************************************************************/
int NextPrimeNumber(int n)
{
	int prime = n;
	bool found =false;
	while(!found)
	{
		prime++;
		if(isPrime(prime))
		found = true;
	}

 	return prime;
}

