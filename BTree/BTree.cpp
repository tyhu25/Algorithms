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
		while(i>=0 && x->key[i]>val)
		{
			x->key[i+1] = x->key[i];
			i--;
		}
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