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
	vector<shared_ptr<DagNode>> container;
	map<Node, shared_ptr<DagNode>> nodeMap; //


public:
	Dag() = default;


	void init(vector<quaternary> block);
	//int getDagNode(Node &n);
	shared_ptr<DagNode> getDagNode(Node &n);
	void insert(shared_ptr<DagNode>& nd);
	int find(shared_ptr<DagNode>&);
	shared_ptr<DagNode> find(tag, DagNode&, DagNode&);
	shared_ptr<DagNode> find(tag, DagNode);
	void show();
	vector<quaternary> regenerate(vector<quaternary> block);

	void clear();
	//~Dag() = default;
};
