#ifndef _GROWTH_H_
#define _GROWTH_H_

#include <fstream>
#include <string>
#include <map>
#include "Tree.h"

class Growth {

private:
	Tree g_tree;
	float threshold;

public:
	ifstream *fInput;
	ofstream *fOutput;
	ofstream *fLog;

	map<string, int> name2id;
	map<int, string> id2name;

	Growth(float, string, string, string);
	~Growth();

	void mine();

};
#endif