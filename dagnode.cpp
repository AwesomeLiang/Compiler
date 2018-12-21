#include "DagNode.h"
#include <iostream>
#include <algorithm>

using std::find;
using std::cout;
using std::endl;

int DagNode::currentId;


ostream& operator<<(ostream& out, const DagNode& dn) {
	if (dn.operand) {
		out << dn.operand << " ";
	}
	out << dn.id << ": " << dn.identifier << "|";
	for (auto it : dn.addtionalTable) {
		out << it << ", ";
	}
	return out;
}

void DagNode::show() {
	cout << id << ": " << identifier << "|";
	for (auto it : addtionalTable) {
		cout << it << ", ";
	}
	if (!isLeaf()) {
		cout << "L:" << leftSon->getId() << "R:" << rightSon->getId();
	}
	cout << endl;
}

int DagNode::hasVar(Node &n) {
	auto index = find(addtionalTable.begin(), addtionalTable.end(), n);
	if (index != addtionalTable.end()) {
		return index - addtionalTable.begin();
	}
	else {
		return -1;
	}
}

void DagNode::insert(Node& n) {
	if (hasVar(n) == -1) {
		addtionalTable.push_back(n);
	}
}

void DagNode::remove(Node& n) {
	int index = hasVar(n);
	if (index != -1) {
		addtionalTable.erase(addtionalTable.begin() + index);
	}
}

bool DagNode::isLeaf() {
	if (leftSon || rightSon) { // 如果是存在儿子结点
		return false;
	}
	return true;
}

bool DagNode::empty() {
	return addtionalTable.empty();
}
