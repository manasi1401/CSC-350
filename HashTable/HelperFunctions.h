/***************************************************************************//**
 * @file HelperFunctions.h
 * @author Manasi Paste
 * @brief Function prototypes required to compare nodes and Find next prime number
 ******************************************************************************/
#include <iostream>
#include "math.h"
#include "Node.h"

using namespace std;
/*!Compare two Nodes wrt frequencies*/
int compareNode(const void* n, const void *m);
/*!Check if the integer is prime*/
bool isPrime(int n);
/*!Calculate the next prime integer to a given integer*/
int NextPrimeNumber(int n);

