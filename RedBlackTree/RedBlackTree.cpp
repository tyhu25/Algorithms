#include "RedBlackTree.h"

#define CHECK_RB_TREE_ASSUMPTIONS 1

RedBlackTree::RedBlackTree()
{
	nil = new RedBlackTreeNode();
	nil->val = INT_MIN;
	nil->color = COLOR_BLACK;
	nil->left = nil->right = nil->parent = nil;

	root = 0;
}

RedBlackTree::~RedBlackTree()
{
	//TODO: delete tree
}

void RedBlackTree::insert(int v)
{
	RedBlackTreeNode * x = new RedBlackTreeNode(v, COLOR_RED);
	x->left = x->right = nil;
	RedBlackTreeNode * y = 0;
	RedBlackTreeNode * curr = root;
	while(curr!=0 && curr!=nil)
	{
		y = curr;
		if(x->val<curr->val) curr = curr->left;
		else curr = curr->right;
	}
	
	x->parent = y;
	if(y==0) root = x;
	else if(x->val<y->val) y->left = x;
	else y->right = x;
	
	insertFixUp(x);
	
#ifdef CHECK_RB_TREE_ASSUMPTIONS
	checkAssumptions();
#elif defined(DEBUG_ASSERT)
	Assert(nil->color==COLOR_BLACK,"nil not black in RedBlackTree::Insert");
	Assert(root==0 || root->color==COLOR_BLACK,"root not red in RedBlackTree::Insert");
#endif
}

void RedBlackTree::insertFixUp(RedBlackTreeNode *x)
{
	while(x->parent!=0 && x->parent->color==COLOR_RED)
	{
		RedBlackTreeNode *px = x->parent;
		if(px == px->parent->left)
		{
			RedBlackTreeNode *y = px->parent->right;
			if(y->color == COLOR_RED)
			{
				y->color = COLOR_BLACK;
				px->color = COLOR_BLACK;
				px->parent->color = COLOR_RED;
				x = px->parent;
			}
			else 
			{
				if(x==px->right)
				{
					x = px;
					leftRotate(x);
				}
				px->color = COLOR_BLACK;
				px->parent->color = COLOR_RED;
				rightRotate(px->parent);
			}
		}
		else
		{
			RedBlackTreeNode *y = px->parent->left;
			if(y->color==COLOR_RED)
			{
				y->color = COLOR_BLACK;
				px->color = COLOR_BLACK;
				px->parent->color = COLOR_RED;
				x = px->parent;
			}
			else
			{
				if(x==px->left)
				{
					x = px;
					rightRotate(x);
				}
				px->color = COLOR_BLACK;
				px->parent->color = COLOR_RED;
				leftRotate(px->parent);
			}
		} 
	}
	root->color = COLOR_BLACK;
}

RedBlackTreeNode * RedBlackTree::search(int key)
{
	RedBlackTreeNode * res;
	
	return res;
}

void RedBlackTree::checkAssumptions() const 
{
	VERIFY(nil->val == INT_MIN);
	VERIFY(nil->color == COLOR_BLACK);
	VERIFY(root==0 || root->color == COLOR_BLACK);
}

void RedBlackTree::print() const
{
	printHelper(root);
	cout<<endl;
}

void RedBlackTree::printHelper(RedBlackTreeNode *root) const
{
	if(root==0 || root==nil)
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
	if(curr->left!=nil)
	{
		RedBlackTreeNode *res = curr->left;
		while(res->right!=nil) res = res->right;
		return res;
	}
	while(curr->parent!=0 && curr==curr->parent->left) curr = curr->parent;
	
	return curr->parent;
}

RedBlackTreeNode * RedBlackTree::getSuccessor(RedBlackTreeNode * curr) const
{
	if(curr->right!=nil)
	{
		RedBlackTreeNode *res = curr->right;
		while(res->left!=nil) res = res->left;
		return res;
	}
	while(curr->parent!=0 && curr==curr->parent->right) curr = curr->parent;
	return curr->parent;
}

void RedBlackTree::leftRotate(RedBlackTreeNode *x)
{
	RedBlackTreeNode *y = x->right;
	x->right = y->left;

	if(y->left!=nil) y->left->parent = x;

	y->parent = x->parent;
	if(x->parent==0) root = y;
	else if(x==x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	
	x->parent = y;
	y->left = x;
	
#ifdef CHECK_RB_TREE_ASSUMPTIONS
	checkAssumptions();
#elif defined(DEBUG_ASSERT)
	Assert(nil->color==COLOR_BLACK,"nil not black in RedBlackTree::LeftRotate");
#endif
}
	
void RedBlackTree::rightRotate(RedBlackTreeNode *x)
{
	RedBlackTreeNode *y = x->left;
	x->left = y->right;

	if(y->right!=nil) y->right->parent = x;
	y->parent = x->parent;
	
	if(x->parent==0) root = y;
	else if(x==x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	x->parent = y;
	y->right=x;

#ifdef CHECK_RB_TREE_ASSUMPTIONS
	checkAssumptions();
#elif defined(DEBUG_ASSERT)
 	Assert(nil->color==COLOR_BLACK,"nil not black in RedBlackTree::Right");
#endif
}