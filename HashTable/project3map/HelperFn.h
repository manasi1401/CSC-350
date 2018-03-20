#include "Node.h"
#include <iostream>
#include "math.h"
#include <map>
#include <cstring>

int compareNode(const void* n, const void *m);
int TokenizeText(char *ReadInText, map<string, int> &FrequencyTracker);
Node** BuildSortedNodeTable(map<string, int> FrequencyTracker);
