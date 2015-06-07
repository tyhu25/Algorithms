#include "RedBlackTree.h"

int main()
{
	RedBlackTreeNode *r1 = new RedBlackTreeNode(1);
	RedBlackTreeNode *r2 = new RedBlackTreeNode(2, COLOR_RED);
	RedBlackTreeNode *r3 = new RedBlackTreeNode(3);
	RedBlackTreeNode *r4 = new RedBlackTreeNode(4, COLOR_RED);
	RedBlackTreeNode *r5 = new RedBlackTreeNode(5);
	r1->left = r2;
	r1->right = r3;
	r2->left = r4;
	r3->right = r5;
	
	RedBlackTree rb;
	rb.printHelper(r1);
	
	return 1;
}