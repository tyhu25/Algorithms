#include <iostream>
#include "BTree.h"

void testBTree();

int main()
{
	testBTree();
	
	return 1;
}

void testBTree()
{
	BTree bt(3);
	bt.insert(3);
	bt.insert(4);
	bt.insert(5);
	bt.insert(1);
	bt.insert(2);
	bt.traverse();
	bt.insert(7);
	bt.insert(6);
	bt.insert(9);
	bt.insert(8);
	bt.insert(10);
	bt.insert(11);
	bt.insert(12);
	bt.insert(13);
	bt.insert(15);
	bt.insert(16);
	bt.insert(17);
	bt.insert(18);
	bt.insert(19);
	bt.insert(20);
	bt.insert(21);
	bt.insert(22);
	bt.traverse();
	bt.insert(14);
	bt.traverse();
	
	BTreeNode * node = 0;
	node = bt.search(5);
	bt.printBTreeNode(node);
	cout<<endl;
	node = bt.search(22);
	bt.printBTreeNode(node);
	cout<<endl;	
	node = bt.search(23);
	bt.printBTreeNode(node);
	cout<<endl;
	
	bt.remove(9);
	bt.traverse();
	
	bt.remove(12);
	bt.traverse();
	
}