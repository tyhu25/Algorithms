#include "RedBlackTree.h"

int main()
{
	RedBlackTreeNode *r1 = new RedBlackTreeNode(1);
	RedBlackTreeNode *r2 = new RedBlackTreeNode(2, COLOR_RED);
	RedBlackTreeNode *r3 = new RedBlackTreeNode(3);
	RedBlackTreeNode *r4 = new RedBlackTreeNode(4, COLOR_RED);
	RedBlackTreeNode *r5 = new RedBlackTreeNode(5);
	r1->left = r2;
	r2->parent = r1;
	r1->right = r3;
	r3->parent = r1;
	r2->left = r4;
	r4->parent = r2;
	r3->right = r5;
	r5->parent = r3;
	
	RedBlackTree rb;
	rb.printHelper(r1);
	
	RedBlackTreeNode *pred = 0;
	cout<<"\nr1->predecessor: ";
	pred = rb.getPredecessor(r1);
	if(pred!=0) pred->print();
	cout<<"\nr2->predecessor: ";
	pred = rb.getPredecessor(r2);
	if(pred!=0) pred->print();
	cout<<"\nr3->predecessor: ";
	pred = rb.getPredecessor(r3);
	if(pred!=0) pred->print();
	cout<<"\nr4->predecessor: ";
	pred = rb.getPredecessor(r4);
	if(pred!=0) pred->print();
	cout<<"\nr5->predecessor: ";
	pred = rb.getPredecessor(r5);
	if(pred!=0) pred->print();
	
	RedBlackTreeNode *succ = 0;
	cout<<"\nr1->successor: ";
	pred = rb.getSuccessor(r1);
	if(pred!=0) pred->print();
	cout<<"\nr2->successor: ";
	pred = rb.getSuccessor(r2);
	if(pred!=0) pred->print();
	cout<<"\nr3->successor: ";
	pred = rb.getSuccessor(r3);
	if(pred!=0) pred->print();
	cout<<"\nr4->successor: ";
	pred = rb.getSuccessor(r4);
	if(pred!=0) pred->print();
	cout<<"\nr5->successor: ";
	pred = rb.getSuccessor(r5);
	if(pred!=0) pred->print();
	
	rb.leftRotate(r1);
	rb.printHelper(r2);
	
	rb.rightRotate(r2);
	rb.printHelper(r1);
	
	return 1;
}