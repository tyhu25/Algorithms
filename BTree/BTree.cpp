#include "BTree.h"
#include <iostream>
#include <queue>

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

void BTree::insert(int val)
{
	if(root==0)
	{
	}
	else
	{
		
	}
}

void BTree::insertNotFull(BTreeNode * r, int val)
{
	
}

void BTree::splitChild(BTreeNode * x, int i, BTreeNode *y)
{
	
}