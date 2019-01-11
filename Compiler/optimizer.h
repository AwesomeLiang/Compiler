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
	Dag dag; // dagͼ
	vector<vector<quaternary>> blockVector; // �洢�����������
	vector<quaternary> newBlockVector; // �������Ӻ������ɵĻ�����
	

	vector<tuple<int, int>> labelTable;  // ��¼��תλ�õı�
	vector<int> newlabelTable; // Ϊ���������ӵ�����תλ�õı�

public:
	Optimizer() = default;
	~Optimizer() = default;
	void partition(vector<quaternary> v); // ���ֻ�����
	void dagOptimize(); // ����Dag�Ļ������Ż�
	void show(); // ���

	vector<quaternary> getNewCode() {
		return newBlockVector;
	}
};

