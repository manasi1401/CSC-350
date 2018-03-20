/***************************************************************************//**
 * @file usage.cpp
 * @author Nicholas Chmielewski
 * @brief Function definitions for print usage and checkandopen functions
 ******************************************************************************/
#include "usage.h"

/**************************************************************************//** 
 * @author Nick Chmielewski
 * 
 * @par Description: 
 * Prints a usage message explaining how to use the command line arguments
 * 
 *****************************************************************************/
void printUsage()
{
    //if there is an error opening a file this message will be printed
	cout << "_____________________________________________________________" <<
         endl;
    cout << "|                                                           |" <<
         endl;
    cout << "|                     HOW TO RUN THE FILE                   |" <<
         endl;
    cout << "|-----------------------------------------------------------|" <<
         endl;
    cout << "|c:\\zipf textfile                                           |" <<
         endl;
    cout << "|-----------------------------------------------------------|" <<
         endl;
    cout << "|                DESCRIPTION OF THE ARGUMENTS               |" <<
         endl;
    cout << "|-----------------------------------------------------------|" <<
         endl;
    cout << "|zipf - name of the executable which is stored in           |" <<
         endl;
    cout << "|       argv[0].                                            |" <<
         endl;
	cout << "|                                                           |" <<
         endl;
	cout << "|textfile - Some text file of any size that the program     |" <<
         endl;
    cout << "|           will run which is stored in argv[1].            |" <<
         endl;
    cout << "|___________________________________________________________|" <<
         endl;
}

/**************************************************************************//** 
 * @brief A function to check if the file can be opened
 * 
 * @param[in, out] fin - an identifier for the input file stream
 * @param[in, out] foutWrd - output file identifier
 * @param[in, out] foutCsv - output file identifier
 * @param[in, out] input - input filename stored in arv[1]
 * @param[in, out] inputFileName - string for the input name
 * 
 * @return 0 - input file opened successfully
 * @return -1 - input file failed to open
 *****************************************************************************/
int checkAndOpen(ifstream &fin, ofstream &foutWrd, ofstream &foutCsv, char  *input, string &inputFileName)
{
	string outputNameWrd;
	string outputNameCsv;
	string intputtest = input;
	string fileNametemp;
	char * TobeTokenizedFileName;
	size_t slashpos = intputtest.find_last_of("/");
	inputFileName = strtok(input, "");
	if(slashpos == string::npos)
	{
	  
  	  outputNameWrd = strtok(input, ".");

	  outputNameCsv = outputNameWrd;
	  outputNameWrd += ".wrd";
	  outputNameCsv += ".csv";
  }
  else
  {
    fileNametemp=intputtest.substr(slashpos+1,intputtest.length() );
    TobeTokenizedFileName = new char[fileNametemp.size()+1];
    strcpy(TobeTokenizedFileName, fileNametemp.c_str());
	outputNameWrd = strtok(TobeTokenizedFileName, ".");
    
	outputNameCsv = intputtest.substr(0, slashpos+1) + outputNameWrd;
	outputNameWrd =intputtest.substr(0, slashpos+1)+outputNameWrd;
	outputNameWrd += ".wrd";
	outputNameCsv += ".csv";
    free(TobeTokenizedFileName);
  }

	fin.open( inputFileName, ios::binary );
	if( !fin )
	{
		cout << "Error opening " << &input << endl;
		printUsage();
		fin.close();
		return -1;
	}

	foutWrd.open( outputNameWrd, ios::binary );
	if( !foutWrd )
	{
		cout << "Error opening " << outputNameWrd << endl;
		printUsage();
		foutWrd.close();
	}

	foutCsv.open( outputNameCsv, ios::binary );
	if( !foutCsv )
	{
		cout << "Error opening " << outputNameCsv << endl;
		printUsage();
		foutCsv.close();
	}
	return 0;
}





