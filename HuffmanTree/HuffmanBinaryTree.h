/*************************************************************************//**
 * @file
 * @brief Defines the function prototypes for the Huffman Binary Tree class.
 *****************************************************************************/
#include "Nodes.h"

#ifndef _HUFFMANBINARYTREE_H_
#define _HUFFMANBINARYTREE_H_
//Manasi Paste, Mark Ebarle
/*!
*@brief Calls functions to build the tree and encode the message.
*/
class HuffmanBinaryTree
{
    private:
    /*!The root of the tree*/
    Nodes *root;
    /*!Huffman code table*/
    map <char, string> hoffmantable;
    public:
    /*!Construtor for the tree*/
    HuffmanBinaryTree();
    /*Destructor for the tree*/
    ~HuffmanBinaryTree();
    /*!Sets the root fo the tree*/
    void SetRoot(Nodes *item);
    /*!Inserts the nodes of the tree*/
    Nodes* InsertNode(Nodes *item1, Nodes *item2);
    /*!Returns total frequency of histogram*/
    int GetTotalFrequency();
    /*!Traverse the tree to build huffman table*/
    void traverse(Nodes  * node, string path);
    /*!Get the huffman table*/
    map <char, string> GetHuffmanTable();
    /*!Set the huffman table*/
    void SetHuffmanTable(map <char, string> huffTable);
    /*!Clears the nodes in the huffman tree*/
    void ClearTheHuffmanBinaryTree(Nodes *node);
};
#endif
