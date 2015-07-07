#include "BTree.h"
#include <iostream>
#include <queue>

#define DEBUG

BTreeNode::BTreeNode(int t, bool leaf)
{
	this->t = t;
	this->leaf = leaf;
	c = vector<BTreeNode *>(2*t, 0);
	key = vector<int>(2*t-1, 0);
	this->n = 0;
}

BTree::BTree(int t)
{
	this->t = t;
	root = 0;
}

void BTree::traverse()
{
#ifdef DEBUG
	cout<<"B-Tree traverse: \n";
#endif
	if(root==0) return;
	queue<BTreeNode *> Q;
	Q.push(root);
	int numOfNodesPrev = 1;
	while(!Q.empty())
	{
		int numOfNodesCurr = 0;
		while(numOfNodesPrev)
		{
			BTreeNode * node = Q.front();
			Q.pop();
			numOfNodesPrev--;
			for(int i=0; i<node->n; i++)
			{
				cout<<node->key[i]<<" ";
			}
			if(numOfNodesPrev) cout<<"->";
			if(!node->leaf)
			{
				for(int i=0; i<=node->n; i++)
				{
					Q.push(node->c[i]);
					numOfNodesCurr++;
				}
			}
		}
		numOfNodesPrev = numOfNodesCurr;
		cout<<"\n";
	}
}

void BTree::printBTreeNode(BTreeNode *node)
{
	if(node==0)
	{
		cout<<"Node is NULL\n";
	}
	else
	{
		for(int i=0; i<node->n; i++)
		{
			cout<<node->key[i]<<" ";
		}
	}
}

BTreeNode * BTree::search(int val)
{
#ifdef DEBUG
	cout<<"Search for " <<val<<endl;
#endif
	if(root==0) return 0;
	return search(root, val);
}

BTreeNode * BTree::search(BTreeNode * node, int val)
{
	int i = 0;
	while(i<node->n && node->key[i]<val) i++;
	if(node->key[i]==val) return node;
	if(node->leaf) return 0;
	return search(node->c[i], val);
}

void BTree::insert(int val)
{
#ifdef DEBUG
	cout<<"Insert: "<<val<<endl;
#endif
	if(root==0)
	{
		root = new BTreeNode(t);
		root->key[0] = val;
		root->n = 1;
	}
	else
	{
		if(root->n==2*t-1)
		{
			BTreeNode * s = new BTreeNode(t, false);
			s->c[0]=root;
			splitChild(s, 0, root);
			root = s;
			insertNotFull(s, val);
		}
		else
		{
			insertNotFull(root, val);
		}	
	}
}

void BTree::insertNotFull(BTreeNode * x, int val)
{
#ifdef DEBUG
	cout<<"InsertNotFull: ";
	printBTreeNode(x);
	cout<<endl;
#endif
	int i = x->n-1;
	if(x->leaf)
	{	
		while(i>=0 && x->key[i]>val)
		{
			x->key[i+1] = x->key[i];
			i--;
		}
		x->key[i+1] = val;
		x->n = x->n+1;
		//DISK_WRITE(x)
	}
	else
	{	
		while(i>=0 && x->key[i]>val) i--;
		i++;
		//DISK_READ(x->c[i])
		if(x->c[i]->n==2*t-1)
		{
			splitChild(x, i, x->c[i]);
			if(val>x->key[i])
			{
				i++;
			}
		}
		
		insertNotFull(x->c[i], val);
	}
}

void BTree::splitChild(BTreeNode * x, int i, BTreeNode *y)
{
#ifdef DEBUG
	cout<<"Split: panret( ";
	printBTreeNode(x);
	cout<<"); child( ";
	printBTreeNode(y);
	cout<<" )\n";
#endif
	BTreeNode * z = new BTreeNode(t, y->leaf);
	z->n = t-1;
	for(int j=0; j<t-1; j++)
	{
		z->key[j]=y->key[t+j];
	}
	if(!y->leaf)
	{
		for(int j=0; j<t; j++)
		{
			z->c[j] = y->c[j+t];
		}
	}
	y->n = t-1;
	
	for(int j=x->n; j>=i+1; j--)
	{
		x->c[j+1] = x->c[j];
	}
		
	x->c[i+1] = z;
	for(int j=x->n-1; j>=i; j--)
	{
		x->key[j+1]=x->key[j];
	}
	x->key[i] = y->key[t-1];
	x->n = x->n+1;
}

int BTree::findKey(BTreeNode * node, int val)
{
	int index = 0;
	while(index<node->n && node->key[index]<val) index++;
		
	return index;
}

void BTree::remove(int val)
{
#ifdef DEBUG
	cout<<"Remove: "<<val<<endl;
#endif
	if(root == 0) cout<<"B-Tree is empty"<<endl;
	
	remove(root, val);
}

void BTree::remove(BTreeNode * node, int val)
{
	int index = findKey(node, val);
	
	if(index<node->n && val == node->key[index])
	{
		if(node->leaf)
		{
			removeFromLeaf(node, index);
		}
		else
		{
			removeFromNonLeaf(node, index);
		}
	}
	else
	{
		if(node->leaf)
		{
			cout<< "The key does not exist in the tree" <<endl;
			return;
		}
		
		bool flag = (index==node->n? true: false);
		
		if(node->c[index]->n < t)
		{
			fill(node, index);
		}
		
		if(flag && index>node->n) remove(node->c[index-1], val);
		else remove(node->c[index], val);
	}
}

void BTree::removeFromLeaf(BTreeNode * node, int index)
{
#ifdef DEBUG
	cout<<"removeFromLeaf: ";
	printBTreeNode(node);
	cout<<endl;
#endif
	for(int i=index; i<node->n-1; i++)
	{
		node->key[i]=node->key[i+1];
	}
	node->n=node->n-1;
}

void BTree::removeFromNonLeaf(BTreeNode * node, int index)
{
#ifdef DEBUG
	cout<<"removeFromNonLeaf: ";
	printBTreeNode(node);
	cout<<endl;
#endif
	int k = node->key[index];
	if(node->c[index]->n>=t)
	{
		int pred = getPred(node, index);
		node->key[index] = pred;
		remove(node->c[index], pred);
	}
	else if(node->c[index+1]->n>=t)
	{
		int succ = getSucc(node, index);
		node->key[index] = succ;
		remove(node->c[index+1], succ);
	}
	else
	{
		merge(node, index);
		remove(node->c[index], k);
	}
}

int BTree::getPred(BTreeNode * node, int index)
{
	BTreeNode * curr = node->c[index];
	while(!curr->leaf) curr = curr->c[curr->n];
	
	return curr->key[curr->n-1];
}

int BTree::getSucc(BTreeNode * node, int index)
{
	BTreeNode * curr = node->c[index+1];
	while(!curr->leaf) curr = curr->c[0];
	
	return curr->key[0];
}

void BTree::fill(BTreeNode *node, int index)
{
	if(index!=0 && node->c[index-1]->n>=t) borrowFromPrev(node, index);
	else if(index!=node->n && node->c[index+1]->n>=t) borrowFromNext(node, index);
	else
	{
		if(index!=node->n) merge(node, index);
		else merge(node, index-1);
	}
}

void BTree::borrowFromPrev(BTreeNode * node, int index)
{
	BTreeNode * child = node->c[index];
	BTreeNode * sibling = node->c[index-1];
	for(int i=child->n-1; i>=0; i--)
	{
		child->key[i+1] = child->key[i];
	}
	if(!child->leaf)
	{
		for(int i=child->n; i>=0; --i)
		{
			child->c[i+1] = child->c[i];
		}
	}
	child->key[0]=node->key[index-1];
	
	if(!node->leaf)
	{
		child->c[0] = sibling->c[sibling->n];
	}
	node->key[index-1] = sibling->key[sibling->n-1];
	child->n=child->n+1;
	sibling->n=sibling->n-1;
}

void BTree::borrowFromNext(BTreeNode * node, int index)
{
	BTreeNode * child = node->c[index];
	BTreeNode * sibling = node->c[index+1];
	
	child->key[child->n] = node->key[index];
	if(!child->leaf)
	{
		child->c[child->n+1] = sibling->c[0];
	}
	node->key[index] = sibling->key[0];
	
	for(int i=1; i<sibling->n; i++) sibling->key[i-1] = sibling->key[i];
	
	if(!sibling->leaf)
	{
		for(int i=1; i<=sibling->n; i++)
		{
			sibling->c[i-1] = sibling->c[i];
		}
	}
	child->n = child->n+1;
	sibling->n = sibling->n-1;
}

void BTree::merge(BTreeNode * node, int index)
{
	BTreeNode * child = node->c[index];
	BTreeNode * sibling = node->c[index+1];
	child->key[t-1] = node->key[index];
	
	for(int i=0; i<sibling->n; i++)
	{
		child->key[i+t] = sibling->key[i];	
	}
	
	if(!child->leaf)
	{
		for(int i=0; i<=sibling->n; ++i)
		{
			child->c[i+t] = sibling->c[i];
		}
	}
	
	for(int i=index+1; i<node->n; i++)
	{
		node->key[i-1] = node->key[i];
	}
	
	for(int i=index+2; i<=node->n; i++)
	{
		node->c[i-1] = node->c[i];
	}
	
	child->n = child->n+sibling->n+1;
	node->n = node->n-1;
	
	delete sibling;
}