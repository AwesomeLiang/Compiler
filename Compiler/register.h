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
	vector<Node> stData;  // �洢���ĸ�������������Щ������������һ��������
	unsigned int length; // �Ĵ����ĳ���

public:
	bool empty() { return stData.empty(); } // �ж��ǲ��ǿ�
	void clear() { // ��ռĴ���
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
	void remove(Node &var); // ɾ��ĳһ����
	void remove(unsigned int index);
	bool hasVar(Node var);  // ���Ƿ�洢��ĳһ������
	int size() { return length; }
	const Node getElement(int pos);
	void show();
	bool operator<(const Register& r) { return this->length < r.length ; }
};