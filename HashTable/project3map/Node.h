/***************************************************************************//**
 * @file
 ******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

#ifndef _NODE_H
#define _NODE_H

/*!Structure of nodes containing words and their frequencies*/
struct Node{
	
	string word;    /*!string variable to store a word*/
	int frequency =0;  /*!int variable to store the freq of the word*/

};

#endif
