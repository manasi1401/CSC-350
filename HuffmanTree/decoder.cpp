/***************************************************************************//**
 * @file decoder.cpp
 *
 * @brief This is the implementation of the functions defined in decoder.h
 * and these functions are used to decode a supplied file from the running
 * of this program in the command line and write the decoded message to an output
 * file provided by the command line.
 *
 * @author Mark Ebarle & Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 * 
 * 
 ******************************************************************************/
#include "decoder.h"

/**************************************************************************//**
**@brief A function that opens input and output file to read in characters 
**from a file until end of file. It reads in also keeps track of how many bytes
** were read from encoded file and how many bytes were written in output file. 
 * @par Description:
 *			- opens the input and output files
 *			- reads the histogram
 * 		- Builds the Huffman Tree
 *			- Calls the functions to read encoded message & decode it
 * 
 * @param[in]  inputfile- Name of the input file
 * @param[in]  outputfile- Name of the output file
 * @param[in, out]  encodedBytes - number of bytes in the encoded message
 * @param[in, out]  decodedBytes - number of bytes in the decoded message
 
 * @return -1 - if input or outputfile doesn't open up
 * @return lengthoffile - Total number of bytes in the encoded file 
 *****************************************************************************/
int decoder (char inputfile[], char outputfile[], double &encodedBytes, double &decodedBytes)
{
    ifstream fin; 
    ofstream fout;
    map<char, int>::iterator it;
    map <char, int> freq;
    vector<Nodes*> sortedMap;
    char readInCharacter;
    int readInInteger;  
    int frequencyOfEntireText;
    int PositionInFile;
    int count;
    int lengthoffile;
    HuffmanBinaryTree *huffTree = new HuffmanBinaryTree();
    fin.open(inputfile , ios::binary | ios:: in);
    //check if input open
     if (!fin) 
  	  {
		    cout << "Error" << endl << "Input Binary file didnot open" << endl
		    	<< "Exiting" << endl;
	    	return -1;
	  }
     fout.open(outputfile);
     if (!fout)
	    {
	    	cout << "Error" << endl << "Output binary file didnot open" << endl
		  	<< "Exiting" << endl;
		    return -1;
    	}
    	fin.seekg(0, fin.end);
      lengthoffile = fin.tellg();
    	fin.seekg(0, fin.beg);
    	
    	//read the histogram
    	fin.read( (char*) &count, sizeof(int));
		for(int i =0; i <count; i++)
		{
   	     fin.read( (char*)&readInCharacter, sizeof(char));
    	   fin.read( (char*)&readInInteger, sizeof(int));
     	   freq[readInCharacter] = readInInteger;
	  }
	  // placing Nodes containing char and frequency into a vector<Nodes>
	   PlaceNodesIntoVectorOfNodes(sortedMap, freq);
     Nodes* root = buildTree(sortedMap, huffTree);
     
     frequencyOfEntireText = root->frequency;
     PositionInFile = fin.tellg();
    
     ReadAndDecode(fin, fout, root, PositionInFile, frequencyOfEntireText, encodedBytes, decodedBytes);
     fin.close();
     fout.close();
     huffTree->ClearTheHuffmanBinaryTree(root);
    return lengthoffile;

} 

/**************************************************************************//**
 * @brief A function that takes a vector of Nodes and inserts them into the
 * huffman binary tree and narrowing down the vector of Nodes until it has
 * one sole item left, the tree.
 *
 * @par Description:
 *						- Build a Huffman Binary Tree root node
 *						- Remove used Nodes from the vector
 *						- Add the root node to vector
 *						- Sort the vector
 *						- Repeat the steps
 * 
 * @param[in]  sortedMap - Contains the nodes with the key char and its frequency
 * @param[in, out] huffTree - Huffman Tree in which the nodes are inserted
 *  
 * @return sortedMap[0] - the root of the Huffman Binary Tree 
 *****************************************************************************/

Nodes* buildTree(vector<Nodes*> sortedMap, HuffmanBinaryTree *huffTree)
{
  Nodes* temp;

  sort(sortedMap.begin(), sortedMap.end(), compareNodes);
   while(sortedMap.size() != 1) 
    {
      temp = huffTree->InsertNode(sortedMap[0], sortedMap[1]);
      sortedMap.erase(sortedMap.begin());
      sortedMap.erase(sortedMap.begin());
      sortedMap.push_back(temp);

        if(sortedMap.size() != 1)
        {
        sort(sortedMap.begin(), sortedMap.end(), compareNodes);
        }
  }
  huffTree->SetRoot(sortedMap[0]);
  return sortedMap[0];
}
/**************************************************************************//** 
 * @brief
 *	This function reads the encoded message one char at a time. 
 * It then reads every bit of the char. If its 1 then it moves to right child 
 * if it is 0 then it moves to the left child. As it encounters a leaf it writes it 
 * to the output file and then starts traversing again from the root.
 * 
 *@par Description
 *					- Read encoded char
 *					- Loop through the Byte
 *					- Traverse the Tree
 *					- Write the decoded key to the file 
 *
 * @param[in]  fin - File containing the encoded message
 * @param[in, out]  fout - File to which the decoded message is written
 * @param[in]  root - Root of the huffman tree
 * @param[in]  PositionInFile - Position of cursor in the file
 * @param[in]  freq - Total frequency of charachters in the message
 * @param[in, out]  encodedBytes - number of bytes in the encoded message
 * @param[in, out]  decodedBytes - number of bytes in the decoded message
 *  
 *****************************************************************************/
void ReadAndDecode(ifstream &fin, ofstream &fout, Nodes *root, int PositionInFile, int freq, double &encodedBytes, double &decodedBytes)
{
    unsigned char read;
    unsigned char bitReadIn = 0 ;
    //set bitReadIn to 10000000
    bitReadIn = bitReadIn  | 1;
    bitReadIn = bitReadIn << 7;
     //start at the position where histogram ends
    fin.seekg(PositionInFile, fin.beg);
    Nodes * tempptr = root;
    //read through the encoded message
    while( fin.read((char*)&read, sizeof(char)))
    { encodedBytes++;
      //decrypt every bit from the encoded char
      for(int i = 0; i < 8 && freq != 0; i++)
        {   //0= move to left child
           if((read & bitReadIn) == 0 )
       	      {
        	       tempptr = tempptr->leftChild;
      	      }
      	      //1 = move to right child
     	 	  else if((read & bitReadIn) == bitReadIn)
       	      {
       	        tempptr = tempptr->rightChild;
      	      }
      	      //right shift bitReadIn by 1
      	  bitReadIn = bitReadIn >> 1;
          // If you encounter a child you found the char
       	   if(tempptr->rightChild == nullptr && tempptr->leftChild == nullptr)
       	     {
                freq--;
                decodedBytes++;
        	      fout << tempptr->key;
       	        tempptr = root;
       	     }
        } 
        //resets it to 10000000
			 bitReadIn = bitReadIn  | 1;
   	   bitReadIn = bitReadIn << 7;
    }
}
