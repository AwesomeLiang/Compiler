#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>
#include <tuple>
#include "symbol.h"

using std::vector;
using std::string;
using std::map;
using std::ostream;
using std::tuple;

class Register {
private:
	vector<Node> stData;  // 存储了哪个变量或者是哪些变量，所以用一个容器存
	unsigned int length; // 寄存器的长度

public:
	bool empty() { return stData.empty(); } // 判断是不是空
	void clear() { // 清空寄存器
		stData.clear();
		length = 0;
	}
	void add(Node var) {
		if (hasVar(var)) {
			return;
		}
		stData.push_back(var);
		length++;
	}
	void remove(Node &var); // 删除某一变量
	void remove(unsigned int index);
	bool hasVar(Node var);  // 看是否存储了某一个变量
	int size() { return length; }
	const Node getElement(int pos);
	void show();
	bool operator<(const Register& r) { return this->length < r.length ; }
};