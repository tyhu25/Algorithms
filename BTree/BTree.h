#ifndef B_TREE_H
#define B_TREE_H

#include <vector>

using namespace std;

struct BTreeNode
{
	BTreeNode(int t, bool leaf = true);
	int t; //minimum degree
	int n; //node size
	vector<BTreeNode *> c;
	vector<int> key;
	bool leaf;	
};

class BTree
{
public:
	BTree(int t);
	void traverse();
	void insert(int val);
	void insertNotFull(BTreeNode * r, int val);
	void splitChild(BTreeNode * x, int i, BTreeNode *y);
	BTreeNode * search(int val);
	void printBTreeNode(BTreeNode *node);
private:
	BTreeNode * search(BTreeNode * node, int val);
	BTreeNode * root;
	int t;
		
};
#endif