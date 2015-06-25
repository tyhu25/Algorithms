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
private:
	BTreeNode * root;
	int t;
		
};
#endif