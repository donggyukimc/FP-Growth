#include "Growth.h"
#include "Tree.h"
#include "Node.h"

#define MAX_SIZE 2048	//Max size of inputted transaction

Growth::Growth(float threshold, string ifname, string ofname, string lfname) {

	this->threshold = threshold;
	fInput = new ifstream(ifname.c_str(), ios::in);
	fOutput = new ofstream(ofname.c_str(), ios::out);
	fLog = new ofstream(lfname.c_str(), ios::out);
	
}

Growth::~Growth() {

	fInput->close();
	fOutput->close();
	fLog->close();

	delete fInput;
	delete fOutput;
	delete fLog;
}

void Growth::mine() {

	int tranno = 0;
	char buf[MAX_SIZE];

	cout << "First data scan..." << endl;

	while (!fInput->eof()) {

		fInput->getline(buf, MAX_SIZE);
		string str;
		str += buf;
		
		int from = 0;
		vector<int> transaction;
		map<string, int>::iterator iter_name2id;
		for (int i = 0; i <str.size(); i++) {

			if (str.at(i) == ' ' || str.at(i) == '\n') {

				iter_name2id = name2id.find(str.substr(from, i - from));

				if (iter_name2id == name2id.end()) {
					iter_name2id = name2id.insert(pair<string, int>(str.substr(from, i - from), name2id.size())).first;
					id2name.insert(pair<int, string>(name2id.size(), str.substr(from, i - from)));
				}
				transaction.push_back((*iter_name2id).second);
				from = i + 1;
			}
			
		}

		tranno++;
		
		g_tree.makeHeader(transaction, 1);

	}

	this->threshold = ((float)tranno/100) * this->threshold;
	cout << "threshold\t\t: " << this->threshold << endl;

	g_tree.prune(this->threshold);

	fInput->clear();
	fInput->seekg(0);

	cout << "Second data scan..." << endl;

	tranno = 0;
	while (!fInput->eof()) {

		fInput->getline(buf, MAX_SIZE);
		string str;
		str += buf;

		int from = 0;
		vector<int> transaction;
		map<string, int>::iterator iter_name2id;
		for (int i = 0; i <str.size(); i++) {

			if (str.at(i) == ' ' || str.at(i) == '\n') {

				iter_name2id = name2id.find(str.substr(from, i - from));
				transaction.push_back((*iter_name2id).second);
				from = i + 1;
			}

		}

		g_tree.makeTree(transaction, 1);

	}

	cout << "Mining patterns..." << endl;

	vector<int> prefix;
	int patterns = g_tree.growth(prefix, this->threshold, this->fOutput);

	cout << "Number of patterns\t: " << patterns << endl;

}