#ifndef RED_BLACK_H
#define RED_BLACK_H

#include "Misc.h"
#include <limits>
#include <iostream>

#define COLOR_BLACK 0
#define COLOR_RED 1

using namespace std;

struct RedBlackTreeNode
{
	RedBlackTreeNode()
	:val(0),color(0),parent(0),left(0),right(0)
	{};
	RedBlackTreeNode(int v)
	:val(v),color(0),parent(0),left(0),right(0)
	{};
	RedBlackTreeNode(int v, int c)
	:val(v),color(c),parent(0),left(0),right(0)
	{};
	~RedBlackTreeNode()
	{};
	void print()
	{
		cout<<val<<"(" << (color==COLOR_BLACK?"B":"R") << ")";		
	}
	int val;
	int color; 
	RedBlackTreeNode *parent;
	RedBlackTreeNode *left;
	RedBlackTreeNode *right;
};

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();
	void checkAssumptions() const;
	void print() const;
	void printHelper(RedBlackTreeNode *root) const;

private:
	RedBlackTreeNode *root;
	RedBlackTreeNode *nil;
};

#endif

