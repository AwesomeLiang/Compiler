#include "Optimizer.h"
#include <iostream>

using std::cout;
using std::endl;


bool Jump(tag op) {
	if (op == IF || op == GOTO || op == WHILE) {
		return true;
	}
	return false;
}


// 划分基本块
void Optimizer::partition(vector<quaternary> v) {
	vector<vector<quaternary>::iterator> iterVector;
	/*
	1. 第一个指令
	2. 跳转指令的目标指令
	3. 跳转指令的下一条指令
	*/

	iterVector.push_back(v.begin());
	bool isJump = false;  // 是否是跳转语句 用来将跳转语句
	int pos = 0;
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (isJump) { // 如果上一句是跳转语句
			if (find(iterVector.begin(), iterVector.end(), it) == iterVector.end()) {
				iterVector.push_back(it);
			}
		}
		if ((*it).pointJmp != -1) {
			isJump = true;
			iterVector.push_back(v.begin() + (*it).pointJmp);
			labelTable.push_back(make_tuple(pos++, (*it).pointJmp));
		}
		else {
			isJump = false;
		}
		sort(labelTable.begin(), labelTable.end(), [](const tuple<int, int> &a, const tuple<int, int> &b) {
			return  get<1>(a) < get<1>(b);
		});
		

	}


	sort(iterVector.begin(), iterVector.end());
	if (v.end() - 1 != *(iterVector.end() - 1)) {
		iterVector.push_back(v.end() - 1);
	}
	for (auto it = iterVector.begin(); it != iterVector.end() - 1; ++it) {
		blockVector.push_back(vector<quaternary>(*it, *(it + 1)));
	}
	cout << endl;



}

// 输出
void Optimizer::show() {
	cout << "partition" << endl;
	for (auto block : blockVector) {
		for (auto qd : block) {
			cout << qd << endl;
		}
		cout << endl;
	}
	cout << "optimize" << endl;
	for (auto qt : newBlockVector) {
		cout << qt << endl;
	}
}

void Optimizer::dagOptimize() { // 基于Dag图的优化
	int num = 0;
	int pos = 0;
	for (auto block : blockVector) {
		dag.init(block);
		//dag.show();
		auto v = dag.regenerate(block);
		for (auto qt : v) {
			newBlockVector.push_back(qt);
			if (qt.op == LABEL) {
				newlabelTable.push_back(pos);
			}
			pos++;
		}
		dag.dot(num++);
		dag.clear();
	}

	pos = 0;
	for (auto qt : newBlockVector) {
		if (Jump(qt.op)) {
			for (int i = 0; i < labelTable.size(); i++) {
				if (pos == get<0>(labelTable[i])) {
					qt.pointJmp = newlabelTable[i];
				}
			}
			pos++;
		}
	}

}

