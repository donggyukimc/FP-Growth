#ifndef _TREE_H_
#define _TREE_H_

#include "Node.h"
#include <vector>

class Tree {

private:
	Node *root;
	set<Node*, NodeCompare> header;

public:
	Tree();
	~Tree();

	void makeHeader(vector<int>, int);
	void prune(float);
	void makeTree(vector<int>, int);
	int growth(vector<int>, float, ostream*);
};

#endif