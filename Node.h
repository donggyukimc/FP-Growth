#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <set>

using namespace std;

class Node;

struct NodeCompare {
	bool operator() (Node*, Node*) const;
};

class Node {

private:
	int id;
	int cnt;
	Node *parent;
	Node *next;
	set<Node*, NodeCompare> children;

public:
	Node();
	Node(int, int, Node*, Node*);
	~Node();

	int getId() const;
	int getCnt() const;
	Node* getParent() const;
	Node* getNext() const;
	set<Node*, NodeCompare>* getChildren();

	void setId(int);
	void setCnt(int);
	void setParent(Node*);
	void setNext(Node*);

	void increase(int);

};

#endif