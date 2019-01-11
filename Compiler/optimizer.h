#pragma once
#include "assembler.h"
#include "dag.h"
#include <vector>
#include <tuple>
#include <map>
using std::vector;
using std::map;
class Optimizer;

struct flowGraphNode {
	int start;
	int end;
};



class Optimizer
{
private:
	Dag dag; // dag图
	vector<vector<quaternary>> blockVector; // 存储基本块的容器
	vector<quaternary> newBlockVector; // 重新连接后新生成的基本块
	

	vector<tuple<int, int>> labelTable;  // 记录跳转位置的表
	vector<int> newlabelTable; // 为了重新连接的新跳转位置的表

public:
	Optimizer() = default;
	~Optimizer() = default;
	void partition(vector<quaternary> v); // 划分基本块
	void dagOptimize(); // 基于Dag的基本块优化
	void show(); // 输出

	vector<quaternary> getNewCode() {
		return newBlockVector;
	}
};

