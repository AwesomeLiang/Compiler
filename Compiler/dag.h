#pragma once
#include <map>
#include <vector>
#include "dagnode.h"
#include <memory>
#include "semantic_analyzer.h"


using std::map;
using std::vector;
using std::shared_ptr;



class Dag {
private:
	vector<shared_ptr<DagNode>> container; // �洢DagNode�ı䳤����
	map<Node, shared_ptr<DagNode>> nodeMap; // ��¼���ĸ���ʶ���������ĸ���������map


public:
	Dag() = default;


	void init(vector<quaternary> block); // ���ݻ���������Dagͼ
	//int getDagNode(Node &n);
	shared_ptr<DagNode> getDagNode(Node &n);  // ����map�ҵ���Ӧ��ʶ���Ľ��
	void insert(shared_ptr<DagNode>& nd); // ������
	int find(shared_ptr<DagNode>&); // Dag�и�������λ�ã����û�з���-1
	shared_ptr<DagNode> find(tag, DagNode&, DagNode&);
	shared_ptr<DagNode> find(tag, DagNode);
	void show(); // չʾ
	vector<quaternary> regenerate(vector<quaternary> block); // ��������

	void clear(); // ���Dag
	void dot(int i); // ����Dot�ļ�
	//~Dag() = default;
};


