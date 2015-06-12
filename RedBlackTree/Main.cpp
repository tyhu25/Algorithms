#include "RedBlackTree.h"

void testRedBlackTree();

int main()
{
	testRedBlackTree();
	return 1;
}

void testRedBlackTree()
{
	RedBlackTree rb;
	const int cArraySize = 9;
	int insertArray[cArraySize] = { 5,3,7,4,6,1,9,2,8 };
	rb.print();
	for(int i=0; i<cArraySize; i++)
	{
		cout<<"Insert "<<insertArray[i]<<endl;
		rb.insert(insertArray[i]);
		rb.print();
	}
	
	int deleteArray[cArraySize] = { 3, 2, 1, 4, 5, 6, 9, 8, 7};
	for(int i=0; i<cArraySize; i++)
	{
		RedBlackTreeNode * rbNode = rb.search(deleteArray[i]);
		if(rbNode!=0)
		{
			cout<<"Delete " << rb.deleteNode(rbNode)<<endl;
			rb.print();
		}
		else
		{
			cout<<"Unable to find rb node value = " << deleteArray[i]<<endl;
		}
	}
}