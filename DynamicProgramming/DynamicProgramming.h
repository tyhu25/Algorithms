#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class DynamicProgramming
{
public:
	int multiplyMatrixChain(vector<int> p, vector< vector<int> > &s);
	void printMatrixSolution(const vector< vector<int> > &s, int start, int end);
};

#endif