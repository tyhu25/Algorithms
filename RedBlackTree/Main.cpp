#include "RedBlackTree.h"

int main()
{
	RedBlackTree rb;
	rb.print();
	rb.insert(5);
	rb.print();
	rb.insert(3);
	rb.print();
	rb.insert(7);
	rb.print();
	rb.insert(4);
	rb.print();
	rb.insert(6);
	rb.print();
	rb.insert(1);
	rb.print();
	rb.insert(9);
	rb.print();
	rb.insert(2);
	rb.print();
	rb.insert(8);
	rb.print();
	
	RedBlackTreeNode * n;
	n = rb.search(3);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
	
	n= rb.search(2);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
	
	n= rb.search(1);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
	
	n= rb.search(4);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
	
	n= rb.search(6);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
	
	n = rb.search(9);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
		
	n = rb.search(5);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
		
	n = rb.search(8);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
	
	n = rb.search(7);
	cout << rb.deleteNode(n)<<endl;
	rb.print();
	
	return 1;
}