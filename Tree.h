#ifndef _TREE_H_
#define _TREE_H_

#include "Node.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Tree {

private:
	set<Node*, NodeCompare> root;
	set<Node*, NodeCompare> header;

public:
	Tree();
	~Tree();

	void makeHeader(vector<int>, int);
	void prune(float);
	void makeTree(vector<int>, int);
	int growth(vector<int>, float, ofstream*);
};

#endif