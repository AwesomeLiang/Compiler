#pragma once
#include "symbol.h"
#include <vector>
#include <string>
#include <memory>
#include "semantic_analyzer.h"

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

	int id;
	static int currentId;


public:
	// 默认构造函数
	DagNode() = default;


	// 构造函数
	DagNode(Node identifier, shared_ptr<DagNode> leftSon, shared_ptr<DagNode> rightSon)
		: identifier(identifier), leftSon(leftSon), rightSon(rightSon), id(currentId++), operand(tag(0)) {} 

	// 构造函数
	DagNode(Node identifier, tag op, shared_ptr<DagNode> leftSon, shared_ptr<DagNode> rightSon)
		: identifier(identifier), operand(op), leftSon(leftSon), rightSon(rightSon), id(currentId++) {}

	// 构造函数
	DagNode(quaternary qd) : identifier(qd.arg1), operand(qd.op), leftSon(nullptr), rightSon(nullptr), id(currentId++) {
		addtionalTable.push_back(qd.arg2);
		addtionalTable.push_back(qd.result);
	}


	// 重载 <<
	friend ostream& operator<<(ostream& os, const DagNode& nd);

	void show(); // 输出
	int hasVar(Node& n); // 判断变量是不是在这个结点中
	void insert(Node& n); // 将变量插入结点
	void remove(Node& n); // 将变量移除结点

	Node getIdentifier() { return identifier; } // 获得变量的主标识符
	int getId() { return id; } // 获得结点的编号
	tag getOp() { return operand; } // 获得结点的操作符
	shared_ptr<DagNode> getLeftSon() { return leftSon; } // 获得左儿子
	shared_ptr<DagNode> getRightSon() { return rightSon; } // 获得右儿子
	vector<Node> getTable() { return addtionalTable; } // 获得标识符表

	void setIdentifier(Node &n) {
		identifier = n;
	} // 设置标识符

	bool isLeaf(); // 判断是不是叶子结点

	bool empty(); // 判断是不是空结点 

	bool operator==(const DagNode& dn) {
		return this->id == dn.id;
	}

	bool operator!=(const DagNode& dn) {
		return this->id != dn.id;
	}
	bool operator<(const DagNode& dn) const { return id < dn.id; }

};
