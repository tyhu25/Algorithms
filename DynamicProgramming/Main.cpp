#include "DynamicProgramming.h"

void testMultiplyMatrixChain();

int main()
{
	testMultiplyMatrixChain();
	
	return 1;
}

void testMultiplyMatrixChain()
{
	int A[] = { 30, 35, 15, 5, 10, 20, 25 };
	vector<int> p(A, A + sizeof(A) / sizeof(int));
	DynamicProgramming DP;
	vector< vector<int> > s(p.size()-1, vector<int>(p.size()-1, 0));
		
	cout<< DP.multiplyMatrixChain(p, s)<<endl;
	cout<<"Solution = ";
	DP.printMatrixSolution(s, 0, p.size()-2);
	cout<<endl;
	
}

