#include "dag.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using std::fstream;

using std::cout;
using std::endl;
using std::make_shared;

bool isBinary(tag op) {
	if (op == ADD || op == SUB || op == MUL || op == DIV) {
		return true;
	}
	return false;
}

bool isUnary(tag op) {
	if (op == NOT) {
		return true;
	}
	return false;
}

bool isExchangeable(tag op) {
	if (op == ADD || op == MUL) {
		return true;
	}
	return false;
}

bool isJump(tag op) {
	if (op == IF || op == GOTO || op == WHILE) {
		return true;
	}
	return false;
}

bool notOptimizable(tag op) {
	if (op == DECLAREI || op == DECLAREA || op == DECLARES || op == STARTF || op == RETURN || op == ENDF || op == SHIFT || op == CALL || op == LABEL || isJump(op) || op == PARAM || op == ASM) {
		return true;
	}
	return false;
}

void Dag::init(vector<quaternary> block) {
	for (auto qd : block) {
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
		else {
			
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
			if (dnArg1 == dnRes) {
				continue;
			}
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
		else if (notOptimizable(qd.op)) {
			container.push_back(make_shared<DagNode>(DagNode(qd)));
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
			//cout << "find " << *dgPtr << endl;
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
		cout << *it << endl;
	}
	cout << "table" << endl;
	for (auto it : nodeMap) {
		cout << it.first << "     ";
		cout << *(it.second) << endl;
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
		if (notOptimizable(dnode->getOp())) {
			v.push_back(quaternary(dnode->getOp(), dnode->getIdentifier(), dnode->getTable()[0], dnode->getTable()[1]));
		}
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

void Dag::dot(int i) {
	fstream outfile;
	string filename = "dag" + to_string(i) + ".dot";
	outfile.open(filename, fstream::out);
	outfile << "digraph" << endl;
	outfile << "{" << endl;
	outfile << "node [fontsize=12, font=Courier, shape=plaintext]" << endl;
	for (auto it : container) {
		outfile << "node_" << it->getId() << " [label=\"";
		if (it->getOp() != 0) {
			outfile << it->getOp() << it->getIdentifier();
		}
		else {
			outfile << it->getIdentifier();
		}
		if (!(it->getTable().empty())) {
			outfile << "|";
			for (auto id : it->getTable()) {
				outfile << id << " ";
			}
		}
		outfile << "\"]" << endl;
	}
	for (auto it : container) {
		if (it->getLeftSon()) {
			outfile << "node_" << it->getId() << " -> " << "node_" << (*(it->getLeftSon())).getId() << endl;
		}
		if (it->getRightSon()) {
			outfile << "node_" << it->getId() << " -> " << "node_" << (*(it->getRightSon())).getId() << endl;
		}
	}
	outfile << "}" << endl;
	outfile.close();
	//system("dot -Tpng dag.dot -o dag.png");
}