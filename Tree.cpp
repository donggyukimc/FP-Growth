#include "Node.h"
#include "Tree.h"

Tree::Tree() {

}

Tree::~Tree() {
	delete root;
}

void Tree::makeHeader(vector<int> transaction, int cnt) {

	set<Node*, NodeCompare>::iterator iter_header;
	for (int i = 0; i < transaction.size(); i++) {

		Node *n = new Node(transaction.at(i), 0, NULL, NULL);
		iter_header = header.find(n);

		if (iter_header == header.end()) {
			iter_header = header.insert(n).first;
		}
		else {
			delete n;
		}

		(*iter_header)->increase(cnt);

	}
}

void Tree::prune(float threshold) {

	for (set<Node*, NodeCompare>::iterator iter_header = header.begin(); iter_header != header.end(); iter_header++) {

		if ((*iter_header)->getCnt() < threshold) {
			header.erase((*iter_header));
		}

	}

}

void Tree::makeTree(vector<int> transaction, int cnt) {

	Node *parent = NULL;
	set<Node*, NodeCompare> *children = this->root->getChildren();
	set<Node*, NodeCompare>::iterator iter_header;
	set<Node*, NodeCompare>::iterator iter_children;

	for (int i = 0; i < transaction.size(); i++) {

		Node *n = new Node(transaction.at(i), 0, NULL, NULL);

		iter_header = header.find(n);
		if (iter_header == header.end()) {
			delete n;
			continue;
		}

		iter_children = children->find(n);

		if (iter_children == children->end()) {
			n->setParent(parent);
			iter_header = header.find(n);
			n->setNext((*iter_header)->getNext());
			(*iter_header)->setNext(n);
			iter_children = children->insert(n).first;
		}
		else {
			delete n;
		}

		(*iter_children)->increase(cnt);
		parent = (*iter_children);
		children = (*iter_children)->getChildren();

	}

}

int Tree::growth(vector<int> prefix, float threshold, ostream *fOutput) {

	int patterns = 0;
	
	int cnt;
	vector<int> transaction;

	for (set<Node*, NodeCompare>::iterator iter_header = header.begin(); iter_header != header.end(); iter_header++) {

		Tree l_tree;

		for (Node *next = (*iter_header)->getNext(); next != NULL; next = next->getNext()) {
			
			cnt = next->getCnt();
			transaction.clear();
			for (Node *parent = next->getParent(); parent != NULL; parent = parent->getParent()) {

				transaction.push_back(parent->getId());

			}

			l_tree.makeHeader(transaction, cnt);

		}

		l_tree.prune(threshold);

		for (Node *next = (*iter_header)->getNext(); next != NULL; next = next->getNext()) {

			cnt = next->getCnt();
			transaction.clear();
			for (Node *parent = next->getParent(); parent != NULL; parent = parent->getParent()) {

				transaction.push_back(parent->getId());

			}

			l_tree.makeTree(transaction, cnt);

		}

		vector<int> nPrefix = prefix;
		nPrefix.push_back((*iter_header)->getId());
		patterns++;

		patterns += l_tree.growth(nPrefix, threshold, fOutput);

	}

	return patterns;

}