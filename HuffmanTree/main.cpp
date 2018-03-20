/*************************************************************************//**
 * @file main.cpp
 * @mainpage CSC 315 - Fall 2017
 *
 * @brief Main function for project 2- Huffman Coding
 *
 * @section course_section Course Information
 *
 * @authors Mark Ebarle, Manasi Paste
 *
 * @date Oct. 16, 2017
 *
 * @par Professor: Dr. Hinker
 *
 * @par Course:  CSC 315 - Section 1 - Fall 2017
 * @section program_section Program Description
 *
 * @par Description
 *
 * This program compresses input files using huffman coding. At run with
 * the encoder switch the program takes an input file and then compresses it
 * using a huffman binary tree and translating the input file into a bit stream
 * using the constructed huffman binary tree.  Now the file is compressed containing
 * the information for the histogram (symbols and corresponding frequencies) and
 * it is followed by the bit representation of the input file.
 *
 * At run with the decoder switch the program takes an encoded file and then
 * writes out the decompressed file using the provided histogram of symbols and 
 * correpsonding frequencies and the provided bit stream.
 * 
 * @section compile_section Compile Section
 *
 * @par Build
  @verbatim
% make -f makefile.mk
   @endverbatim
 * @par Run
 * @verbatim
% ./huffman -e inputFile encodedFile
% ./huffman -d encodedFile outputFile
   @endverbatim
 * @par Usage
 *
 *  * Running the program with -e in the second command line argument will cause
 *    the encoder to be chosen so you must provide an input file and a file
 *    or name a new file for the output that holds the compressed file
 *  * Running the program with the -d in the second command line argument
 *    cause the decoder to be chosen so you must provide a compressed file
 *    created using this program and the name or file of an output file
 *    that you would like to contain the decompressed file
 *
 * @section todo_bugs_modification_section To Do, Bugs, and Modifications
 * @par Revision History
 * 
 * <a href="https://gitlab.mcs.sdsmt.edu/7404855/csc315_fall2017_project2/commits/master">Commit History</a>
 ****************************************************************************/

#include "HuffmanBinaryTree.h"
#include "decoder.h"
#include "encoder.h"
#include <iomanip>
/**************************************************************************//**
 * @par Description:
 *	
 * This function :
 *			- Encoder: Opens the files, Calls the function to encode the message
 *			- Decoder: Prints out the statistics of decoder & calls function to decode
 * 
 * @param[in]  argc - number of charachter strings(arguments) in the command line
 * @param[in]  argv - Arguments in the command line stored as 2D charachter array
 *  
 * @return -2 - If wrong flag was invoked
 * @return -1 - If input and/or outputfile didn't open
 * @return 0 - if the program executes successfully 
 *****************************************************************************/
int main(int argc, char* argv[]){
  
    ifstream fin; 
    ofstream fout;
    map <char, int> freq;
    
    if(argc !=4)
    {
      cout<<"Usage: -e/-d input output"<<endl;
      return -1;
    }

    // encoder
    if( strcmp ( argv[1] , "-e") == 0 )
    {
        fin.open(argv[2]);

        if(!fin) 
	    {
		    cout << "Error" << endl << "Input Binary file didnot open" << endl
		   	<< "Exiting" << endl;
		    return - 1;
	    }

        fout.open(argv[3], ios::binary | ios::out);

        if (!fout)
	    {
		    cout << "Error" << endl << "Output binary file didnot open" << endl
			<< "Exiting" << endl;
		    return -1;
	    }

    HuffmanCodingEncoder(fin, fout, argv[2], argv[3]);

    fin.close();
    fout.close();
    return 0;
  }
  
  //decoder
  else if(strcmp(argv[1], "-d")==0)
    {
      cout<< "Huffman Decoder"<<endl;
      cout<<"----------------"<<endl;
      double encodedbytes =0, decodedbytes =0;
      int checkfiles= decoder(argv[2], argv[3], encodedbytes, decodedbytes);
      if(checkfiles==-1)
      {
        return -1;
      }
      cout<< "Read "<< encodedbytes<< " encoded bytes from "<< argv[2]
          << " (" << checkfiles<< " bytes including histogram)" <<endl;
      cout<< "Wrote "<< decodedbytes<< " decoded bytes to "<< argv[3]<<endl;
      cout<< "Compression ratio: "<< setprecision (2)<<fixed<<(encodedbytes/decodedbytes) *100
      << " %" <<endl;

	return 0;
	}
  else{
  cout<<"Wrong flag for invoking encoder or decoder"<<endl;
  return -2;
  }

 
}



