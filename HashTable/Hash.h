/***************************************************************************//**
* @file 
* @brief This header defines the function prototypes for the Hash class.
* @author: Nicholas Chmielewski, Manasi Paste
*****************************************************************************/
#include <iostream>
#include <ctype.h>
#include <string.h>
#include "Node.h"
#include "HelperFunctions.h"
#include <vector>
#include <algorithm>
#ifndef _HASH_H_
#define _HASH_H_

/*!
*@brief Functions to construct a hash table and use to it to test word concordance
*/
class Hash
{
	/*!Hash Table*/
	Node **Table=nullptr;

	/*!Size of the inital table*/
	int TableSize= 1009;

	/*!Counter to check numbe ro finserted nodes*/
	int NumberOfInsertedNodes =0;

	/*!Total number of words hashed*/
	int TotalFrequency =0;
	
	public:
	
		/*!Hash Constructor*/
		Hash();
	
		/*!Hash Destructor*/
		~Hash();
	
		/*!Insert the node*/
		void InsertNode(string word);

		/*!Delete a node*/
		void DeleteNode(string word);
	
		/*!Find position of node*/
		int FindPositionOfNode(string word);
	
		/*!Check if the position is occupied*/
		bool IsOccupied(int PositionToBeChecked);

		/*!Generates the hash key*/
		unsigned int HashKeyGenerator(string word);

		/*!creates the hash table*/
		void BuildHashTable( char* text);

		/*!Return the Load Factor*/
		double loadFactor();
		
		/*!Return Table Size*/
		int GetTableSize();
		
		/*!Rehashing function*/
		void Rehashing();

		/*!Returns total frequency*/
		int GetTotalFrequency();

		/*!Returns number of Unique words*/
		int GetNumberOfUniqueWords();
		
		/*!Sort the table of nodes*/
		Node** SortTable();
};

#endif
