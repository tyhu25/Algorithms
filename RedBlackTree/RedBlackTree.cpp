#include "RedBlackTree.h"

// #define CHECK_RB_TREE_ASSUMPTIONS 1

RedBlackTree::RedBlackTree()
{
	nil = new RedBlackTreeNode();
	nil->val = INT_MIN;
	nil->color = COLOR_BLACK;
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	
	root = new RedBlackTreeNode();
	root->val = INT_MAX;
	root->color = COLOR_BLACK;
	root->left = nil;
	root->right = nil;
	root->parent = nil;
}

RedBlackTree::~RedBlackTree()
{
	//TODO: delete tree
}

void RedBlackTree::checkAssumptions() const 
{
	VERIFY(nil->val == INT_MIN);
	VERIFY(root->val == INT_MAX);
	VERIFY(nil->color == COLOR_BLACK);
	VERIFY(root->color == COLOR_BLACK);
}

void RedBlackTree::print() const
{
	printHelper(root);
}

void RedBlackTree::printHelper(RedBlackTreeNode *root) const
{
	if(root==0)
	{
		cout<<"#(B)";
		return;
	}
	printHelper(root->left);
	cout<<", ";
	root->print();
	cout<<", ";
	printHelper(root->right);
}
 