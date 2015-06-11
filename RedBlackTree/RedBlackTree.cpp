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
				//case 1
				y->color = COLOR_BLACK;
				px->color = COLOR_BLACK;
				px->parent->color = COLOR_RED;
				x = px->parent;
			}
			else 
			{
				if(x==px->right)
				{
					//case 2
					x = px;
					leftRotate(x);
				}
				//case 3
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

int RedBlackTree::deleteNode(RedBlackTreeNode *z)
{
	RedBlackTreeNode *x;
	RedBlackTreeNode *y;
	int res = z->val;
	if(z->left==nil||z->right==nil) y = z;
	else y = getSuccessor(z);
	x = ((y->left==nil)?(y->right):(y->left));
	if(x!=nil) x->parent = y->parent;
	if(y->parent==0) root = x;
	else if(y==y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	
	if(y!=z)
	{
		z->val = y->val;
		z->color = y->color;
	}
	
	if(y->color==COLOR_BLACK) deleteFixUp(x);
	
#ifdef CHECK_RB_TREE_ASSUMPTIONS
	checkAssumptions();
#elif defined(DEBUG_ASSERT)
	Assert(nil->color==COLOR_BLACK,"nil not black in RedBlackTree::Insert");
	Assert(root==0 || root->color==COLOR_BLACK,"root not red in RedBlackTree::Insert");
#endif
	return res;
}

void RedBlackTree::deleteFixUp(RedBlackTreeNode *x)
{
	while(x->parent!=0 && x->color==COLOR_BLACK)
	{
		RedBlackTreeNode *w;
		if(x==x->parent->left)
		{
			w = x->parent->right;
			if(w->color==COLOR_RED)
			{
				x->parent->color = COLOR_RED;
				w->color = COLOR_BLACK;
				leftRotate(x->parent);
				w=x->parent->right;
			}
			if(w->left->color==COLOR_BLACK && w->right->color==COLOR_BLACK)
			{
				w->color = COLOR_RED;
				x=x->parent;
			}
			else
			{
				if(w->right->color==COLOR_BLACK)
				{
					w->left->color = COLOR_BLACK;
					w->color = COLOR_RED;
					rightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = COLOR_BLACK;
				w->right->color = COLOR_BLACK;
				leftRotate(x->parent);
				x=root;
			}
		}
		else
		{
			w = x->parent->left;
			if(w->color == COLOR_RED)
			{
				x->parent->color = COLOR_RED;
				w->color = COLOR_BLACK;
				rightRotate(x->parent);
				w = x->parent->left;
			}
			if(w->left->color == COLOR_BLACK && w->right->color == COLOR_BLACK)
			{
				w->color = COLOR_RED;
				x=x->parent;
			}
			else
			{
				if(w->left->color == COLOR_BLACK)
				{
					w->right->color = COLOR_BLACK;
					w->color = COLOR_RED;
					leftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = COLOR_BLACK;
				w->left->color = COLOR_BLACK;
				rightRotate(x->parent);
				x = root;
			}
			
		}
	}
	x->color = COLOR_BLACK;
}

RedBlackTreeNode * RedBlackTree::search(int key)
{
	if(root==0) return 0;
	RedBlackTreeNode *curr=root;
	while(curr!=nil && key!=curr->val)
	{
		if(key<curr->val) curr = curr->left;
		else curr = curr->right;
	}
	
	return curr;
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