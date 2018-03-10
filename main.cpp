#include "Growth.h"

int main() {

	Growth FPGrowth(0.01, "retail.txt", "output.txt", "log.txt");

	FPGrowth.mine();

	int x;
	cin >> x;

	return 0;

}