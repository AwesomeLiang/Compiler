#pragma once
#include "symbol.h"
#include <vector>
#include <string>
#include <memory>


using std::vector;
using std::string;
using std::shared_ptr;


class DagNode {
private:
	Node identifier; // 主标识符
	vector<Node> addtionalTable; // 标识符表（可以是空），不允许是常数
	tag operand; // 运算符

	shared_ptr<DagNode> leftSon;
	shared_ptr<DagNode> rightSon;

	//DagNode* leftSon;
	//DagNode* rightSon;

	int id;
	static int currentId;


public:
	DagNode() = default;

	/*DagNode(Node identifier, DagNode* leftSon, DagNode* rightSon)
		: identifier(identifier), leftSon(leftSon), rightSon(rightSon), id(currentId++) {}
	DagNode(Node identifier, string op, DagNode* leftSon, DagNode* rightSon)
		: identifier(identifier), operand(op), leftSon(leftSon), rightSon(rightSon), id(currentId++) {}*/

	DagNode(Node identifier, shared_ptr<DagNode> leftSon, shared_ptr<DagNode> rightSon)
		: identifier(identifier), leftSon(leftSon), rightSon(rightSon), id(currentId++) {}
	DagNode(Node identifier, tag op, shared_ptr<DagNode> leftSon, shared_ptr<DagNode> rightSon)
		: identifier(identifier), operand(op), leftSon(leftSon), rightSon(rightSon), id(currentId++) {}


	friend ostream& operator<<(ostream& os, const DagNode& nd);

	void show();
	int hasVar(Node& n);
	void insert(Node& n);
	void remove(Node& n);

	Node getIdentifier() { return identifier; }
	int getId() { return id; }
	tag getOp() { return operand; }
	shared_ptr<DagNode> getLeftSon() { return leftSon; }
	shared_ptr<DagNode> getRightSon() { return rightSon; }
	vector<Node> getTable() { return addtionalTable; }

	void setIdentifier(Node &n) {
		identifier = n;
	}

	bool isLeaf();

	bool empty();

	bool operator==(const DagNode& dn) {
		return this->id == dn.id;
	}

	bool operator!=(const DagNode& dn) {
		return this->id != dn.id;
	}
	bool operator<(const DagNode& dn) const { return id < dn.id; }

};
