#include "BTree.h"

BTreeNode::BTreeNode(int t, bool leaf)
{
	this.t = t;
	this.leaf = leaf;
	c = vector<BTreeNode *>(t, 0);
	key = vector<int>(t, 0);
	this.n = 0;
}

BTree::BTree(int t)
{
	this.t = t;
	root = 0;
}