#include "Growth.h"
#include "Tree.h"
#include "Node.h"

#define MAX_SIZE 1024

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

	
	char buf[MAX_SIZE];
	while (!fInput->eof()) {

		fInput->getline(buf, MAX_SIZE);
		string str;
		str += buf;
		
		int from = 0;
		for (int i = 0; i <str.size(); i++) {

			if (str.at(i) == ' ' || str.at(i) == '\n') {
				name2id.insert(pair<string, int>(str.substr(from, i - from), name2id.size()));
				id2name.insert(pair<int, string>(name2id.size(), str.substr(from, i - from)));
				from = i + 1;
			}
			
		}

	}

	cout << name2id.size() << endl;

}