/***************************************************************************//**
 * @file Node.h
 * @author Manasi Paste & Nick Chmielewski
 * @brief Defines the node structure for the Hash table
 ******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

#ifndef _NODE_H
#define _NODE_H

/*!@brief Structure of nodes containing words and their frequencies*/
struct Node
{
	/*!string variable to store a word*/
	string word;    	
	/*!int variable to store the freq of the word*/
	int frequency =0;  
};

#endif
