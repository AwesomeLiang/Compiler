#include "dag.h"
#include <iostream>
#include <algorithm>


using std::cout;
using std::endl;
using std::make_shared;

void Dag::init(vector<quaternary> block) {
	for (auto qd : block) {
		if (isJump(qd.op)) {
			continue;
		}
		if (nodeMap.count(qd.arg1) != 1) {
			auto ndArg1 = make_shared<DagNode>(DagNode(qd.arg1, nullptr, nullptr));
			container.push_back(ndArg1);
			nodeMap[qd.arg1] = ndArg1;
		}
		if ((isBinary(qd.op)) && (nodeMap.count(qd.arg2) != 1)) {
			auto ndArg2 = make_shared<DagNode>(DagNode(qd.arg2, nullptr, nullptr));
			container.push_back(ndArg2);
			nodeMap[qd.arg2] = ndArg2;
		}
		if (isBinary(qd.op)) {
			//cout << "#1" << endl;
			auto dnArg1 = getDagNode(qd.arg1);
			auto dnArg2 = getDagNode(qd.arg2);
			shared_ptr<DagNode> dnPtr = find(qd.op, *dnArg1, *dnArg2);
			shared_ptr<DagNode> dnode;
			if (!dnPtr) {
				dnode = make_shared<DagNode>(DagNode(qd.result, qd.op, dnArg1, dnArg2));
				insert(dnode);
			}
			else {
				dnode = dnPtr;
			}
			if (qd.result.isVar() && dnode->getIdentifier().isTempVar()) {
				auto node = dnode->getIdentifier();
				dnode->insert(node);
				dnode->setIdentifier(qd.result);
			}
			else {
				dnode->insert(qd.result);
			}
			auto dnRest = getDagNode(qd.result);
			if (dnRest) {
				dnRest->remove(qd.result);
			}
			nodeMap[qd.result] = dnode;
		}
		else if (isUnary(qd.op)) {
			//cout << "#2" << endl;
			auto dnArg1 = getDagNode(qd.arg1);
			shared_ptr<DagNode> dnPtr = find(qd.op, *dnArg1);
			shared_ptr<DagNode> dnode;
			if (!dnPtr) {
				dnode = make_shared<DagNode>(DagNode(qd.result, qd.op, dnArg1, nullptr));
				insert(dnode);
			}
			else {
				dnode = dnPtr;
			}
			if (qd.result.isVar() && dnode->getIdentifier().isTempVar()) {
				auto node = dnode->getIdentifier();
				dnode->insert(node);
				dnode->setIdentifier(qd.result);
			}
			else {
				dnode->insert(qd.result);
			}
			auto dnRest = getDagNode(qd.result);
			if (dnRest) {
				dnRest->remove(qd.result);
			}
			nodeMap[qd.result] = dnode;
		}
		else if (qd.op == ASSIGN) {
			//cout << "#3" << endl;
			auto dnArg1 = getDagNode(qd.arg1);
			auto dnRes = getDagNode(qd.result);
			if (qd.result.isVar() && dnArg1->getIdentifier().isTempVar()) {
				auto node = dnArg1->getIdentifier();
				dnArg1->insert(node);
				dnArg1->setIdentifier(qd.result);
			}
			else {
				dnArg1->insert(qd.result);
			}
			if (dnRes) {
				dnRes->remove(qd.result);
			}
			nodeMap[qd.result] = dnArg1;
		}
		//show(); // debug”√
	}
}


//int Dag::getDagNode(Node &n) {
//	return nodeMap[n].getId();
//}

shared_ptr<DagNode> Dag::getDagNode(Node &n) {
	if (nodeMap.count(n) == 1) {
		return (nodeMap[n]);
	}
	else {
		return nullptr;
	}
}

void Dag::insert(shared_ptr<DagNode> &nd) {
	container.push_back(nd);
}

shared_ptr<DagNode> Dag::find(tag op, DagNode& dnArg1, DagNode& dnArg2) {
	shared_ptr<DagNode> dgPtr = nullptr;
	for (auto nodeIter = container.begin(); nodeIter != container.end(); ++nodeIter) {
		if ((*nodeIter)->getOp() == op && *((*nodeIter)->getLeftSon()) == dnArg1 && *((*nodeIter)->getRightSon()) == dnArg2) {
			dgPtr = *nodeIter;
			cout << "find " << *dgPtr << endl;
			return dgPtr;
		}
		else {
			//cout << (*nodeIter)->getOp() << "leftson:" << *((*nodeIter)->getLeftSon());
		}
	}
	return dgPtr;
}

shared_ptr<DagNode> Dag::find(tag op, DagNode dnArg1) {
	shared_ptr<DagNode> dgPtr = nullptr;
	for (auto nodeIter = container.begin(); nodeIter != container.end(); ++nodeIter) {
		if ((*nodeIter)->getOp() == op && *((*nodeIter)->getLeftSon()) == dnArg1) {
			dgPtr = *nodeIter;
			return dgPtr;
		}
	}
	return dgPtr;
}

void Dag::show() {
	cout << "graph" << endl;
	for (auto it : container) {
		it->show();
	}
	cout << "table" << endl;
	for (auto it : nodeMap) {
		cout << it.first << "     ";
		cout << *it.second << endl;
	}
}


int Dag::find(shared_ptr<DagNode>& nd) {
	auto it = std::find(container.begin(), container.end(), nd);
	if (it != container.end()) {
		return it - container.begin();
	}
	return -1;
}

vector<quaternary> Dag::regenerate(vector<quaternary> block) {
	vector<quaternary> v;
	for (auto dnode : container) {
		if (dnode->isLeaf() && !(dnode->empty())) {
			for (auto addnode : dnode->getTable()) {
				if (addnode.isVar() && addnode != dnode->getIdentifier()) {
					v.push_back(quaternary(ASSIGN, dnode->getIdentifier(), Node(), addnode));
				}
				else {
					//cout << dnode->getIdentifier();
				}
			}
		}
		//else if (!(dnode->isLeaf()) && !(dnode->empty())) {
		else if (!(dnode->isLeaf())) {

			auto leftSon = dnode->getLeftSon();
			auto rightSon = dnode->getRightSon();
			auto op = dnode->getOp();
			if (leftSon && rightSon && isBinary(op)) { // 
				Node arg1 = leftSon->getIdentifier();
				Node arg2 = rightSon->getIdentifier();
				Node result = dnode->getIdentifier();
				v.push_back(quaternary(op, arg1, arg2, result));
			}
			else if (leftSon && isUnary(op)) {
				v.push_back(quaternary(op, leftSon->getIdentifier(), Node(), dnode->getIdentifier()));
			}
			else {
				//cout << *leftSon << *rightSon << op;
			}
			for (auto addnode : dnode->getTable()) {
				if (addnode.isVar()) {
					if (addnode != dnode->getIdentifier()) {
						v.push_back(quaternary(ASSIGN, dnode->getIdentifier(), Node(), addnode));
					}
				}
			}
		}
	}
	quaternary tmpQd = *(block.end() - 1);
	if (isJump(tmpQd.op)) {
		v.push_back(tmpQd);
	}
	for (auto qd : v) {
		cout << qd << endl;
	} // debug ”√
	return v;
}

void Dag::clear() {
	container.clear();
	nodeMap.clear();
}