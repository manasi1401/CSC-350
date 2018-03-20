/***************************************************************************//**
 * @file encoder.cpp
 *
 * @brief This is the implementation of the functions defined in encoder.h
 * and these functions are used to encode a supplied file from the running
 * of this program in the command line.
 *
 * @author Mark Ebarle & Manasi Paste
 * @par Course:
 *    CSC315 Data Structures
 * @date  Fall 2017
 * 
 * 
 ******************************************************************************/

#include <iomanip>
#include "encoder.h"
#include <math.h>

/*************************************************************************//**
 * @brief A function that reads in characters from a file until end of file
 * and appends them to a string that gets returned by reference.
 *
 * @par Description
 *   * Reads a file until end of file
 *   * Constructs a string and returns it by reference
 *
 * @param[in] fin - ifstream for input file
 * @param[out] fin - istream for input file
 * @param[in] fullMessage - string passed in by reference to be appended
 * with contents of file
 * @param[out] fullMessage - string containing the contents of the file
 ****************************************************************************/
void CreateFileStringFromFile(ifstream &fin, string &fullMessage)
{
    char holdReadInCharacter;

    while(!fin.eof())
    {
      fin.read( (char*)& (holdReadInCharacter), sizeof(char));
      fullMessage += holdReadInCharacter;
    }
}

/*************************************************************************//**
 * @brief A function that takes in two nodes and compares their frequencies.
 * If the first node is less than the second node we return true, otherwise
 * we return false.
 *
 * @par Description
 *   * Takes two supplied Nodes and compares them
 *
 * @param[in] One - the first Nodes item to be compared
 * @param[in] Two - the second Nodes item to be compared
 *
 * @returns true - the first item frequency is less than second item frequency
 * @returns false - the second item frequency is greater than second item
 * frequency 
 ****************************************************************************/
bool compareNodes(Nodes *One, Nodes *Two)
{
  return (One->frequency < Two->frequency);
}

/*************************************************************************//**
 * @brief A function that takes creates a map that represents the histogram
 * of symbols and their respective frequencies.
 *
 * @par Description
 *   * Creates a map representing a histogram of symbols and frequencies
 *   * Takes in contents of file and runs through all of them
 *
 * @param[in] freq - map representing histogram of symbols/frequencies, empty
 * @param[out] freq - map representing histogram of symbols/frequencies, full
 * @param[in] contents - string holding entire file contents
 ****************************************************************************/
void CreateMapRepresentingHistogramFromFileString(map <char, int> &freq, string contents)
{
    map<char, int>::iterator it;
    int index = 0;
    int messageLength = contents.length();

    for(index = 0; index < messageLength -1; index++)
    {
        it = freq.find(contents[index]);
        
        if(it == freq.end())
        {
            freq[contents[index]] = 1;
        }
        else
        {
            freq[contents[index]]++;
        }
    }
}

/*************************************************************************//**
 * @brief A function that takes a vector of Nodes and inserts them into the
 * huffman binary tree and narrowing down the vector of Nodes until it has
 * one sole item left, the tree.
 *
 * @par Description
 *   * Creates the huffman coding tree
 *
 * @param[in] sortedMap - vector of nodes used to build huffman tree
 * @param[out] sortedMap - vector of nodes returned, should only have one item
 * @param[in] huffTree - pointer to HuffmanBinaryTree, used to insert nodes to
 ****************************************************************************/
void BuildHuffmanCodingTree(vector<Nodes*> &sortedMap, HuffmanBinaryTree *huffTree)
{
    while(sortedMap.size() != 1)
    {
      Nodes *temp;
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
}

/*************************************************************************//**
 * @brief A function that takes a map which is the histogram of the symbols
 * and frequencies of the input file and puts them into a vector of Nodes*
 * by creating the Nodes and inserting them.
 *
 * @par Description
 *   * Reads a file until end of file
 *   * Constructs a string and returns it by reference
 *
 * @param[in] sortedMap - empty vector of Nodes
 * @param[out] sortedMap - vector of Nodes which contain the histogram map 
 * containing symbols and their respective frequencies
 * @param[in] freq - map which is the histogram, used to iterate through and
 * insert values Nodes into the vector
 *
 * @returns count - returns the number of unique symbols in the histogram
 ****************************************************************************/
int PlaceNodesIntoVectorOfNodes(vector<Nodes*> &sortedMap, map<char, int> freq)
{
    map<char,int>::iterator it;
    int count = 0;
    Nodes *temp;
   
    for(it = freq.begin(); it !=freq.end(); it++)
    {
    	count++; //number of unique values in the histogram
        temp = new Nodes;
        temp->key = it->first;
        temp->frequency = it->second;
        sortedMap.push_back(temp);
    }
    
    return count;
}

/*************************************************************************//**
 * @brief A function that takes in a vector of Nodes* that will be printed out
 * to an output file that has been opened in main and passed here with an
 * ofstream variable.
 *
 * @par Description
 *   * Prints out histogram data to the provided output file
 *
 * @param[in] fout - ofstream variable that writes out to output file
 * @param[out] fout - ofstream variable that writes out to output file
 * @param[in] sortedMap - vector of Nodes that has sorted map of symbols and
 * frequencies sorted by frequencies
 * @param[in] count - the number of unique characters in the input file
 ****************************************************************************/
void PrintOutHistogramDataToOutputFile(ofstream &fout, vector<Nodes*> sortedMap, int count)
{
    vector<Nodes*>::iterator vit;

    fout.write( (char*) &count, sizeof(int));

    for(vit = sortedMap.begin(); vit != sortedMap.end(); vit++)
    {
      fout.write( (char*)&(**vit).key, sizeof(char));
      fout.write( (char*)&(**vit).frequency, sizeof(int));
    }
}

/*************************************************************************//**
 * @brief A function that takes in a map representing the histogram of
 * symbols and their frequencies and the huffman binary tree and uses them to 
 * output the ASCII values, percentage of that ASCII value found in the file,
 * and the huffman code for the ASCII value.
 *
 * @par Description
 *   * Outputs the ASCII values and their statistics to the command line
 *
 * @param[in] freq - map representing symbol frequency histogram
 * @param[in] huffTree - huffman binary tree object passed from main
 * @param[in] bitPerSymbolResult - passes in the double to hold result
 * for the average number of bits per symbol
 * @param[out] bitPerSymbolResult - holds the calculated double that represents
 * the average number of bits per symbol
 * @param[in] entropyResult - passes in the double to hold the result for the
 * entropy of the encoding
 * @param[in] entropyResult - holds the calculated double that represents the
 * entropy of the encoding
 ****************************************************************************/
void EncoderSecondPassOutput(map<char, int> freq, HuffmanBinaryTree *huffTree, double &bitPerSymbolResult, double &entropyResult)
{
    char currentCharacter;
    map<char, int>::iterator intIt;
    double probability;
    int length;
    map<char, string> hoffmantable = huffTree->GetHuffmanTable();
    for(const auto& sm_pair : hoffmantable)
    {
        currentCharacter = sm_pair.first;

        if(currentCharacter == '\n')
        {
            cout << " " << (int)currentCharacter << " ( " << "\\n" << " ) ";
        }
        else
        {
        cout << " " << (int)currentCharacter << " ( " << currentCharacter << " ) ";
        }

        cout << "\t\t";

        intIt = freq.find(currentCharacter);

        probability = (double)intIt->second / (double)huffTree->GetTotalFrequency();

        cout << setprecision(2) << fixed << probability * 100.00;

        cout << "\t\t\t" << sm_pair.second << endl;

        length = sm_pair.second.length();

        bitPerSymbolResult += probability * (double)length;

        entropyResult += probability * log2 (probability);
    }
    cout << endl << endl << endl;
}

/*************************************************************************//**
 * @brief A function that takes in a string holding the file contents, the
 * huffman binary tree, and the ofstream object that holds the opened output
 * file and then writes to that file the bitstream of the input file created
 * from the constructed huffman binary tree.
 *
 * @par Description
 *   * Reads a file until end of file
 *   * Constructs a string and returns it by reference
 *
 * @param[in] fileContents - string holding the contents of the input file
 * @param[in] huffTree - pointer to the huffman binary tree class object
 * @param[in] fout - ofstream object for writing the bit stream representation
 * @param[out] fout - ofstream object for writing the bit stream
 * representation
 * 
 * @returns numberOfBytesEncoded - the number of encoded bytes written to the
 * compressed file
 ****************************************************************************/
int CreateBitStreamFromHuffmanCodingTable(string fileContents, HuffmanBinaryTree *huffTree, ofstream &fout)
{
    int numberOfBytesEncoded = 0;
    int messageLength = fileContents.length();
    unsigned char bitRepresentationCharacter;
    int count = 0;
    map<char, string> hoffmantable = huffTree->GetHuffmanTable();
    for(int j = 0; j < messageLength; j++)
    {
    	for(unsigned int i =0; i < hoffmantable[fileContents[j]].length(); i++)
        {
    		if(hoffmantable[fileContents[j]][i]=='0')
    			{
                    bitRepresentationCharacter = bitRepresentationCharacter << 1;
                    count++;
    			}
    		else
    		    {
    				bitRepresentationCharacter = bitRepresentationCharacter << 1;
    			    bitRepresentationCharacter = bitRepresentationCharacter | 1;
                    count++;
    			}

            if((count) % 8  == 0)
                {
                    numberOfBytesEncoded++;
                    fout.write( (char*)&bitRepresentationCharacter, sizeof(char));
                    bitRepresentationCharacter =0;
                }
    	}
    }
		
    if((count) % 8 != 0)
    { 
        numberOfBytesEncoded++;
  		int check = (count) % 8;
		bitRepresentationCharacter = bitRepresentationCharacter << (8-check);  
        fout.write( ( char*)&bitRepresentationCharacter, sizeof(char));
    }

    return numberOfBytesEncoded;
}

/*************************************************************************//**
 * @brief A function that takes in all needed variables in order to calculate
 * statistics for the encoding of the passed in file. This function outputs
 * the compression ratio, the entropy, the average bits per symbol in the 
 * Huffman coding, and the coding efficiency.
 *
 * @par Description
 *   * Takes in encodedBytes to print the number of bytes written
 *   * Takes in outputFileName to write out the name of the outputfile
 *   * Takes in the lengthOfFile in order to print the number of bytes written
 *   * Takes in entropyResult to properly format and print out the entropy
 *     of the encoding
 *   * Takes in averageBitPerSymbol to properly format and print out the 
 *   * average bit per symbol in the encoded file
 *   * Calculates the coding efficiency
 *
 * @param[in] encodedBytes - the number of bytes that were read in and encoded
 * to the file 
 * @param[in] outputFileName - the name of the output file supplied by the 
 * user at the command line
 * @param[in] lengthOfFile - the total length of the written output file in
 * bytes
 * @param[in] entropyResult - the result of the summation of entropy calculated
 * in the encoder second pass
 * @param[in] averageBitPerSymbol - the result of calculating the average number
 * of bits in the file representation by multiplying the probability of the 
 * character and it's bit representation
 * @param[in] fileContents - contains the contents of the input file that has
 * been placed into this string
 ****************************************************************************/
void OutPutEncoderPassTwoStatistics(int encodedBytes, string outputFileName, int lengthOfFile, double entropyResult, double averageBitPerSymbol, string fileContents)
{
    double codingEfficiency = entropyResult / averageBitPerSymbol * (double)-100;

    cout << "Huffman Encoder Pass 2" << endl;
    cout << "----------------------" << endl;
    cout << "Wrote " << encodedBytes << " encoded bytes to " << outputFileName << "(" << lengthOfFile << " bytes including histogram)" << endl;

    cout << "Huffman Coding Statistics" << endl;
    cout << "-------------------------" << endl;
    cout << "Compression ratio = " << setprecision(2) << fixed <<  (double)encodedBytes /(double)(fileContents.length() - 1) * 100.00 << "%" <<  endl;
    cout << "Entropy = " << setprecision(2) << fixed << entropyResult * (double)-1 << endl;
    cout << "Average bits per symbol in Huffman coding = " << averageBitPerSymbol << endl;
    cout << "Coding efficiency = " << setprecision(2) << fixed << codingEfficiency << "%" << endl;
}



/*************************************************************************//**
 * @brief A function that takes in an ifstream that has opened input file, an
 * ofstream that has the opened output file for compression, and a string
 * containing the name of the input file given at the command line. 
 * This function makes all the proper calls within the encoder to do the
 * entire encoding process.
 *
 * @par Description
 *   * Takes in input file and creates a histogram of the symbols
 *     and the corresponding frequencies
 *   * Uses the histogram to construct a huffman binary tree
 *   * Uses the huffman binary tree to construct a huffman coding table
 *     which will be used to compress the input file
 *   * Takes the huffman coding table and proceeds to create the bit
 *     representation of the input file and writes it to the output file
 *
 * @param[in] fin - ifstream object holding the opened input file for 
 * compression
 * @param[out] fin - ifstream object holding the opened input file for
 * compression
 * @param[in] fout - ofstream object holding opened output file that
 * will hold the histogram and binary representation of the input file
 * @param[out] fout - ofstream object holding opened output file that
 * will hold the histogram and binary representation of the input file
 * @param[in] inputFileName - the name of the input file passed in from 
 * the command line
 * @param[in] outputFileName - the name of the output file passed in from 
 * the command line
 ****************************************************************************/
void HuffmanCodingEncoder(ifstream &fin, ofstream &fout, string inputFileName, string outputFileName)
{
    map <char, int> freq;
    map <double, double>::iterator it;
    vector<Nodes*> sortedMap;
    int count = 0;
    int encodedBytes;
    int lengthOfFile;
    double averageBitPerSymbol = 0;
    double entropyResult = 0;
    string fileContents = "";
    string path= "";
    HuffmanBinaryTree *huffmanEncoded = new HuffmanBinaryTree();

    cout << endl << endl << "Huffman Encoder Pass 1" << endl;
    cout << "----------------------" << endl;

    CreateFileStringFromFile(fin, fileContents);

    
    CreateMapRepresentingHistogramFromFileString(freq, fileContents);

    count = PlaceNodesIntoVectorOfNodes(sortedMap,freq);

    // subtract one in fileContents.length() to account for end line character
    cout << "Read " << fileContents.length() - 1 << " bytes from " << inputFileName << 
        ", found " << count << " code words" << endl << endl;

    cout << "Huffman Code Table" << endl;
    cout << "------------------" << endl;    
    
    sort(sortedMap.begin(), sortedMap.end(), compareNodes);

    cout << "ASCII Code\t\t" << "Probability (%)\t\t" << "Huffman Code" << endl;

    PrintOutHistogramDataToOutputFile(fout, sortedMap, count);

    BuildHuffmanCodingTree(sortedMap, huffmanEncoded);

    huffmanEncoded->SetRoot(sortedMap[0]);
  
    huffmanEncoded->traverse(sortedMap[0], path);

    EncoderSecondPassOutput(freq, huffmanEncoded, averageBitPerSymbol, entropyResult);

    fin.close();
    fin.open(inputFileName);

    encodedBytes = CreateBitStreamFromHuffmanCodingTable(fileContents, huffmanEncoded, fout);

    fout.seekp(0, fin.end);
    lengthOfFile = fout.tellp();

    OutPutEncoderPassTwoStatistics(encodedBytes, outputFileName, lengthOfFile, entropyResult, averageBitPerSymbol, fileContents);
    
    huffmanEncoded->ClearTheHuffmanBinaryTree(sortedMap[0]);
}
