#include "RedBlackTree.h"

// #define CHECK_RB_TREE_ASSUMPTIONS 1

RedBlackTree::RedBlackTree()
{
	//both nil and root are sentinel
	nil = new RedBlackTreeNode();
	nil->val = INT_MIN;
	nil->color = COLOR_BLACK;
	nil->left = nil->right = nil->parent = nil;
	
	root = new RedBlackTreeNode();
	root->val = INT_MAX;
	root->color = COLOR_BLACK;
	root->parent = root->left = root->right = nil;
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
	//TODO: Check equality with nil
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

RedBlackTreeNode * RedBlackTree::getPredecessor(RedBlackTreeNode * curr) const
{
	//TODO: Check equality with nil
	if(curr->left!=0)
	{
		RedBlackTreeNode *res = curr->left;
		while(res->right!=0) res = res->right;
		return res;
	}
	while(curr->parent!=0 && curr==curr->parent->left) curr = curr->parent;
	
	return curr->parent;
}

RedBlackTreeNode * RedBlackTree::getSuccessor(RedBlackTreeNode * curr) const
{
	if(curr->right!=0)
	{
		RedBlackTreeNode *res = curr->right;
		while(res->left!=0) res = res->left;
		return res;
	}
	while(curr->parent!=0 && curr==curr->parent->right) curr = curr->parent;
	return curr->parent;
}

void RedBlackTree::leftRotate(RedBlackTreeNode *x)
{
	RedBlackTreeNode *y = x->right;
	x->right = y->left;
	
	//TODO: nil
	if(y->left!=nil) y->left->parent = x;

	y->parent = x->parent;
	if(x==x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	
	x->parent = y;
	y->left = x;
	
/*
#ifdef CHECK_RB_TREE_ASSUMPTIONS
  CheckAssumptions();
#elif defined(DEBUG_ASSERT)
  Assert(!nil->red,"nil not black in RedBlackTree::LeftRotate");
#endif
*/
}
	
void RedBlackTree::rightRotate(RedBlackTreeNode *x)
{
	RedBlackTreeNode *y = x->left;
	x->left = y->right;
	
	//TODO:
	if(y->right!=nil) y->right->parent = x;
	y->parent = x->parent;
	if(x==x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	x->parent = y;
	y->right=x;

/*
#ifdef CHECK_RB_TREE_ASSUMPTIONS
	CheckAssumptions();
#elif defined(DEBUG_ASSERT)
  Assert(!nil->red,"nil not black in RedBlackTree::Right");
#endif
*/
}