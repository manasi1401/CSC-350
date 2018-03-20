/*************************************************************************//**
 * @file HuffmanBinaryTree.cpp
 *
 * @brief Defines the functions for the Huffman Binary Tree class. 
 *
 * @author Manasi Paste & Mark Ebarle
 * @par Course:
 *     CSC315 Data Structures
 * @date  Fall 2017
 *
 *****************************************************************************/
#include "HuffmanBinaryTree.h"

/**************************************************************************//**
 * @author Mark Ebarle
 * 
 * @par Description:
 *	
 * This Constructor initializes the huffman binary tree by setting the root to nullptr
 * 
 *****************************************************************************/
HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = nullptr;
}
/**************************************************************************//**
 * @author Mark Ebarle
 * 
 * @par Description:
 *	
 * This Destructor of huffman binary tree
 * 
 *****************************************************************************/
HuffmanBinaryTree::~HuffmanBinaryTree() {}

/**************************************************************************//**
 * @author Manasi Paste, Mark, Ebarle
 * 
 * @par Description:
 * 
 * Sets the huffman table map.
 * 
 * @param[in]  huffTable- The map of huffman codes  
 *****************************************************************************/
void HuffmanBinaryTree::SetHuffmanTable(map <char, string> huffTable)
{
  hoffmantable = huffTable;
}

/**************************************************************************//**
 * @author Manasi Paste, Mark, Ebarle
 * 
 * @par Description:
 *	
 * Returns a map that is the huffman table
 *
 * @return  hoffmantable - The huffman table represented with a map <char, string>

 *****************************************************************************/
map <char, string> HuffmanBinaryTree::GetHuffmanTable()
{
  return hoffmantable;
}

/**************************************************************************//**
 * @author Manasi Paste, Mark, Ebarle
 * 
 * @par Description:
 *	
 * Takes in a node, should be the root node, and proceeds to clear all of the
 * nodes in the huffman binary tree.
 * 
 * @param[in]  node - the current node containing the root of the tree
 *****************************************************************************/
void HuffmanBinaryTree::ClearTheHuffmanBinaryTree(Nodes *node)
{
    if(root == nullptr)
    {
       return;
    }
    
    if(node->leftChild == nullptr && node->rightChild == nullptr){
       delete node;
       return; 
  }

  ClearTheHuffmanBinaryTree(node->leftChild);

  ClearTheHuffmanBinaryTree(node->rightChild);
}
/**************************************************************************//**
 * @author Manasi Paste, Mark, Ebarle
 * 
 * @par Description:
 *	
 * Takes in two nodes and constructs its root
 * 
 * @param[in]  item1- The node from the sorted vector 
 * @param[in]  item2- The node from the sorted vector 

 * @return  temp- Pointer to the root node

 *****************************************************************************/
Nodes* HuffmanBinaryTree::InsertNode(Nodes *item1, Nodes *item2)
{
    //static int size =0;
    Nodes * temp = new Nodes();
    
    temp->key = '*';
    temp->frequency = item1->frequency + item2->frequency;

    if(item1->frequency < item2->frequency)
    {
        temp->leftChild = item1;
        temp->rightChild = item2;
    }
    else
    {
        temp->leftChild = item2;
        temp->rightChild = item1;
    }            

	return temp;
}

/**************************************************************************//**
 * @author Mark, Ebarle
 * 
 * @par Description:
 *	Sets the root of the tree 
 *
 *	@param[in] item - Pointer to the root node of the tree
 *****************************************************************************/
void HuffmanBinaryTree::SetRoot(Nodes* item)
{
    root = item;
}

/**************************************************************************//**
 * @author Mark, Ebarle
 * 
 * @par Description:
 *	Returns the total frequency of the histogram which is stored in the root of tree
 *
 *	@return root->frequency - Total frequency of the histogram
 *****************************************************************************/
int HuffmanBinaryTree::GetTotalFrequency()
{
    return root->frequency;
}

/**************************************************************************//**
 * @author Mark Ebarle, Manasi Paste
 * 
 * @par Description:
 *	
 * Traverses the tree to track the path and sets path string to the key in a map
 * 
 * @param[in]  node- The root of the tree
 * @param[in]  path- Tracks path traversed in the tree
 *
 *****************************************************************************/
void HuffmanBinaryTree::traverse(Nodes * node, string path){
    
    if(node == nullptr)
        return;   

    if(node->leftChild == nullptr && node->rightChild == nullptr){
       hoffmantable[node->key] = path;
       path.pop_back();
       return; 
  }

  traverse(node->leftChild, path+"0");

  traverse(node->rightChild, path+"1");
}

