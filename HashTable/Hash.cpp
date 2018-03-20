/*************************************************************************//**
 * @file Hash.cpp
 * @brief Defines the functions for the Hash Class 
 * @author Manasi Paste & Nick Chmielewski 
 *****************************************************************************/
#include "Hash.h"


using namespace std;

/*************************************************************************//**
 * @brief Constructs the hash table
 ****************************************************************************/
Hash::Hash()
{
	// allocate and create a hash table of size, TableSize
	Table = new Node* [TableSize];

	// for loop that initializes all cells to nullptr
	for (int i =0; i <TableSize; i++)
		Table[i] =nullptr;
		
	// output statement for the terminal
	cout<<"Created hash table of size "<< TableSize<<"."<<endl;
}

/*************************************************************************//**
 * @brief Deconstructs the hash table
 ****************************************************************************/
Hash::~Hash()
{
	// for loop that runs until TableSize deleting all cells
	for (int i =0; i < TableSize; i++)
		delete Table[i];
		
	delete [] Table;
}

/*************************************************************************//**
 * @brief Inserts a node into the hash
 * @param[in] word - a word to be inserted
 ****************************************************************************/
void Hash::InsertNode(string word)
{
  
	int key;									// interger to store the current key
	key = HashKeyGenerator(word);				// calls HashKeyGenerator to initialize key
	int location =  FindPositionOfNode(word);	// finds the position of the current node 
	
	// if the location is not -1 then the key exists so just increment that spot
	if(location != -1)
	{
		Table[location]->frequency++;
		return;
	}
	else
	{	
		// otherwise, run through the table
		if(NumberOfInsertedNodes < TableSize)
		{
			// while the cells are occupied get the next key
			while(IsOccupied(key))
			  key = (key+1)%TableSize;
			// insert the node
			Table[key]= new Node();
			Table[key]->word =word;
			Table[key]->frequency++;
			// increment the total # of nodes
			NumberOfInsertedNodes++;
		}
	}
	
	//checks if the load factor is greater than 75%
	if(loadFactor() >0.75)
		Rehashing();	//if so, rehash

	return;
}

/*************************************************************************//**
 * @brief Deletes a node from the hash
 *
 * @param[in] word - word to be deleted
 ****************************************************************************/
void Hash::DeleteNode(string word)
{
	// finds the position of the node wanting to be deleted
	int KeyInTheTable = FindPositionOfNode(word);
	
	if(KeyInTheTable != -1)
	{
		// delete the given node
		delete Table[KeyInTheTable];
		// decrement the total # of nodes	
		NumberOfInsertedNodes--;
		// set that position to nullptr
		Table[KeyInTheTable] =nullptr;
	}
	return;
}

/*************************************************************************//**
 * @brief Finds the postion of a specific node
 *
 * @param[in] word - a word to be searched in the table
 *
 * @return NextKey -The postion of the node you were looking for, if the node was found.
 * @return -1 -If the node is not found
 ****************************************************************************/
int Hash::FindPositionOfNode(string word)
{	
	// find the hash key and set the nextkey
	int HashKey = HashKeyGenerator(word);
	int NextKey = HashKey;

	// while the # of nodes is less than the table size
	if(NumberOfInsertedNodes <TableSize)
	{
			// check if the cell is occupied
			while(IsOccupied(NextKey))
			{
				// check if the next key matches the word youre looking for
				if(Table[NextKey]->word ==word)
					return NextKey;
				// change the next key
				NextKey = (NextKey+1)%TableSize;
			}
	}
	return -1;
}

/*************************************************************************//**
 * @brief A function to check if the given postion is occupied
 *
 * @param[in] PositionToBeChecked - an integer representing the postion to be checked
 *
 * @return true - if occupied
 * @return false - if empty
 ****************************************************************************/
bool Hash::IsOccupied(int PositionToBeChecked)
{
	//return false if empty
	if(Table[PositionToBeChecked] == nullptr)
		return false;
	else return true; //return true if occupied
}

/*************************************************************************//**
 * @brief Hash fucntion which generates the hash key (taken from the text book)
 *
 * @param[in] word - string to be hashed
 *
 * @return HashValue - an integer representing the hash value
 ****************************************************************************/
unsigned int Hash::HashKeyGenerator(string word)
{
  	unsigned int HashValue = 0;
  
	for(char ch: word)
		HashValue = 37*HashValue + ch;
	return HashValue % TableSize;
}

/*************************************************************************//**
 * @brief Hash fucntion which tokeninses the read in text and calls the function 
 * to insert the node in the hash table
 *
 * @param[in] text - char array holding the data from the input file
 *
 ****************************************************************************/
void Hash::BuildHashTable( char* text)
{
	// initialize some variables
	int i;
	char *oneWord;
	
	// set all letters to lowercase
	for(i = 0; text[i] != '\0'; i++) 
    	text[i] = tolower(text[i]);
	
	// tokenize the words and store them into oneWord
	oneWord = strtok(text, " ,.-;:()!?*@#$%^&~`[]{}_+=><~`|1234567890\\/\n\r\"\f\t\v\a\b\?\0");
	
	while(oneWord != nullptr)
	{
		// the deal with special cases of single quotes
		while(oneWord[0] =='\'')
			oneWord = oneWord+1;
			
		while(oneWord[strlen(oneWord) -1] =='\'')
		{
			memmove(oneWord, oneWord, strlen(oneWord)-1);
			oneWord[strlen(oneWord)-1] =0;
		}
		
		
		if(*oneWord != '\0' && *oneWord != 127 && strlen(oneWord)!=0)
		{
		 TotalFrequency++;		// increment the total freq
	    string word = oneWord;
	    InsertNode(word);		// insert the node
		}

		// tokenize the next word
		oneWord = strtok(nullptr, " ,.-:;()!?*@#$%^&~`[]{}_+=><~`|1234567890\\/\n\r\"\f\t\v\a\b\?\0");
	}
}


/*************************************************************************//**
 * @brief Hash fucntion which returns the load factor of the hash table
 *
 * @return NumberOfInsertedNodes/TableSize - Load factor of the table is returned
 ****************************************************************************/
double Hash::loadFactor()
{
	return (double) NumberOfInsertedNodes/TableSize;
}
/*************************************************************************//**
 * @brief Hash fucntion which returns the size of the hash table
 *
 * @return TableSize - Table Size
 ****************************************************************************/
int Hash::GetTableSize()
{
  return TableSize;
}

/*************************************************************************//**
 * @brief Hash fucntion which rehashes the Hash table when the load factor exceeds 0.75
 ****************************************************************************/
void Hash::Rehashing()
{
	// find the next prime number
  	 int newTableSize =NextPrimeNumber(2*TableSize);
  
	// output statements for the terminal
    cout<<"WARNING: Hash table (size "<<TableSize<<") is 75% full!"<<endl;
	 cout <<"Rehashing to size "<< newTableSize;
	
	// create a temp node
	Node **temp = Table;
	// find the old table size
	int oldTableSize = TableSize;
	// create the new table
	Table = new (nothrow) Node *[newTableSize];
	int newHashKey;
	// initialize all cells to nullptr
	for(int i =0 ; i < newTableSize; i++)
		Table[i] = nullptr;
	
	// reset the table size
	TableSize = newTableSize;
	
	// for loop copies all items to the new table
	for(int i =0; i < oldTableSize; i ++)
	{
		if(temp[i] != nullptr)
		{
		   newHashKey = HashKeyGenerator(temp[i]->word);
		   while(IsOccupied(newHashKey))
				newHashKey = (newHashKey +1)% TableSize;
			
			//Insert a node if not occupied
			Table[newHashKey] = new Node();
			Table[newHashKey]->word = temp[i]->word;
			Table[newHashKey]->frequency= temp[i]->frequency;
		}
	}
		
	//delete the old table
	for(int j =0; j <oldTableSize; j++) 
		delete temp[j];
		
	delete[] temp;
	cout<<" ...finished!"<<endl;
	return ;
}

/*************************************************************************//**
 * @brief Hash function which returns the Total frequency of words read in (or total number of words in the file)
 *
 * @return TotalFrequency - Number of words read in 
 ****************************************************************************/
int Hash::GetTotalFrequency()
{
	return TotalFrequency;
}

/*************************************************************************//**
 * @brief Hash fucntion which returns number of unqiue words in the file
 *
 * @return NumberOfInsertedNodes - Total Number of Unqiue words in the file
 ****************************************************************************/
int Hash::GetNumberOfUniqueWords()
{
	return NumberOfInsertedNodes;
}

/*************************************************************************//**
 * @brief Hash fucntion which returns Table of Nodes Sorted by Frequency and 
 * nodes with similar frequencies are sorted alphabetically
 *
 * @return TableOfSortedNodes - Table of Sorted Nodes
 ****************************************************************************/
Node** Hash::SortTable()
{
   cout<<"Sorting the hash table ...";
  	Node** TableOfSortedNodes =new Node* [GetNumberOfUniqueWords()];
  	int counter =0;
  	for(int i =0; i < TableSize; i ++)
	  {
		if(IsOccupied(i))
		{
			Node * newNode= new Node();
			newNode->word = Table[i]->word;
			newNode->frequency =Table[i]->frequency;
			TableOfSortedNodes[counter] =newNode;
			counter++;
		}
  	}
		
	qsort((void*)TableOfSortedNodes, GetNumberOfUniqueWords(), 
	    sizeof(Node*), compareNode);
  	cout<<" finished!"<<endl;
	return TableOfSortedNodes;
}
