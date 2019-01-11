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
	Node identifier; // ����ʶ��
	vector<Node> addtionalTable; // ��ʶ���������ǿգ����������ǳ���
	tag operand; // �����

	shared_ptr<DagNode> leftSon;
	shared_ptr<DagNode> rightSon;

	int id;
	static int currentId;


public:
	// Ĭ�Ϲ��캯��
	DagNode() = default;


	// ���캯��
	DagNode(Node identifier, shared_ptr<DagNode> leftSon, shared_ptr<DagNode> rightSon)
		: identifier(identifier), leftSon(leftSon), rightSon(rightSon), id(currentId++), operand(tag(0)) {} 

	// ���캯��
	DagNode(Node identifier, tag op, shared_ptr<DagNode> leftSon, shared_ptr<DagNode> rightSon)
		: identifier(identifier), operand(op), leftSon(leftSon), rightSon(rightSon), id(currentId++) {}

	// ���캯��
	DagNode(quaternary qd) : identifier(qd.arg1), operand(qd.op), leftSon(nullptr), rightSon(nullptr), id(currentId++) {
		addtionalTable.push_back(qd.arg2);
		addtionalTable.push_back(qd.result);
	}


	// ���� <<
	friend ostream& operator<<(ostream& os, const DagNode& nd);

	void show(); // ���
	int hasVar(Node& n); // �жϱ����ǲ�������������
	void insert(Node& n); // ������������
	void remove(Node& n); // �������Ƴ����

	Node getIdentifier() { return identifier; } // ��ñ���������ʶ��
	int getId() { return id; } // ��ý��ı��
	tag getOp() { return operand; } // ��ý��Ĳ�����
	shared_ptr<DagNode> getLeftSon() { return leftSon; } // ��������
	shared_ptr<DagNode> getRightSon() { return rightSon; } // ����Ҷ���
	vector<Node> getTable() { return addtionalTable; } // ��ñ�ʶ����

	void setIdentifier(Node &n) {
		identifier = n;
	} // ���ñ�ʶ��

	bool isLeaf(); // �ж��ǲ���Ҷ�ӽ��

	bool empty(); // �ж��ǲ��ǿս�� 

	bool operator==(const DagNode& dn) {
		return this->id == dn.id;
	}

	bool operator!=(const DagNode& dn) {
		return this->id != dn.id;
	}
	bool operator<(const DagNode& dn) const { return id < dn.id; }

};
