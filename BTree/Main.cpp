#include "BTree.h"

int main()
{
	BTree bt(3);
	bt.insert(10);
	bt.insert(20);
	bt.insert(5);
	bt.insert(6);
	bt.insert(12);
	bt.insert(30);
	bt.insert(7);
	bt.insert(17);
	
	bt.traverse();
	
	
	return 1;
}