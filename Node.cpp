#include "Node.h"

bool NodeCompare::operator() (const Node *left, const Node *right) const {
	return left->getId() > right->getId();
}

Node::Node() {

}

Node::Node(int id, int cnt, Node *parent, Node *next) {

	this->id = id;
	this->cnt = cnt;
	this->parent = parent;
	this->next = next;

}

Node::~Node() {

	if (children.size() > 0)
	{
		for (set<Node*, NodeCompare>::iterator iter_children = children.begin(); iter_children != children.end(); iter_children++)
		{
			delete *(iter_children);
		}
		children.clear();
	}

}

int Node::getId() const {

	return this->id;

}

int Node::getCnt() const {

	return this->cnt;

}

Node* Node::getParent() const {

	return this->parent;

}

Node* Node::getNext() const {

	return this->next;

}

set<Node*, NodeCompare>* Node::getChildren() {

	return &children;

}

void Node::setId(int id) {

	this->id = id;

}

void Node::setCnt(int cnt) {

	this->cnt = cnt;

}

void Node::setParent(Node *parent) {

	this->parent = parent;

}

void Node::setNext(Node *next) {

	this->next = next;

}

void Node::increase(int cnt) {

	this->cnt += cnt;

}