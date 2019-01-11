#include "register.h"



void Register::remove(Node & var) {
	auto it = find(stData.begin(), stData.end(), var);
	if (it != stData.end()) {
		stData.erase(it);
		length--;
	}
}

void Register::remove(unsigned int index) {
	if (index >= length) {
		return;
	}
	else {
		stData.erase(stData.begin() + index);
		length--;
	}
}

bool Register::hasVar(Node var) {
	if (empty()) {
		return false;
	}
	auto it = find(stData.begin(), stData.end(), var);
	if (it != stData.end()) {
		return true;
	}
	return false;
}

const Node Register::getElement(int pos) { return stData[pos]; }

void Register::show() {
	if (empty()) {
		std::cout << "No Data" << endl;
		return;
	}
	for (auto it : stData) {
		std::cout << it << std::endl;
	}
}