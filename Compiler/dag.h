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
	vector<shared_ptr<DagNode>> container; // 存储DagNode的变长数组
	map<Node, shared_ptr<DagNode>> nodeMap; // 记录了哪个标识符放在了哪个结点里面的map


public:
	Dag() = default;


	void init(vector<quaternary> block); // 根据基本块生成Dag图
	//int getDagNode(Node &n);
	shared_ptr<DagNode> getDagNode(Node &n);  // 根据map找到对应标识符的结点
	void insert(shared_ptr<DagNode>& nd); // 插入结点
	int find(shared_ptr<DagNode>&); // Dag中给定结点的位置，如果没有返回-1
	shared_ptr<DagNode> find(tag, DagNode&, DagNode&);
	shared_ptr<DagNode> find(tag, DagNode);
	void show(); // 展示
	vector<quaternary> regenerate(vector<quaternary> block); // 重新生成

	void clear(); // 清除Dag
	void dot(int i); // 生成Dot文件
	//~Dag() = default;
};


