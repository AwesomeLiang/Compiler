#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include "register.h"
#include "semantic_analyzer.h"
#include <stack>
#include "dag.h"


using std::stack;
using std::stringstream;
using std::vector;
using std::string;
using std::map;
using std::ostream;
using std::tuple;

static map<tag, string> operatorMap{
	{ADD, "add"},
	{SUB, "sub"},
	{MUL, "imul"},
	{DIV, "idiv"},
	{AND, "and"},
	//{OR, "or"},
	//{XOR, "xor"},
	{NOT, "not"},
	{EQ, "eq"},
	{NE, "ne"},
	{GT, "gt"},
	{GE, "ge"},
	{LT, "lt"},
	{LE, "le"},

};

static vector<string> registerName = { "eax", "ebx", "ecx", "edx" , "memory"};

struct  Asm { // ������
	string op;
	string arg1;
	string arg2;
	string label;

	Asm(string op, string arg1, string arg2, string label) : op(op), arg1(arg1), arg2(arg2), label(label) {}
};

class Assembler { // ����Ŀ�����ģ��
private:
	vector<string> destCode;    // Ŀ�����
	vector<Register> registers;  // �Ĵ����飬���ڼ�¼�Ĵ���״̬
	vector<string> extraSeg;    // extra segment -- ES
	map<Node, string> addressMap; // ��¼�����ĵ�ַ

	// ������ַ�������飬��̬��¼����������ֵ�Ĵ��λ�ã��Ĵ������ڴ��ַ�����Ƕ��У�
	map<Node, vector<int>> addValue;  
	int tmpLength; // ��¼��ebp��λ��

	int paraLength; // ��¼������λ��
	vector<Asm> dest; // Ŀ��������
	map<Register, Node> regValue;
	// �Ĵ����������飬��̬��¼�Ĵ����Ĵ洢��Ϣ
	unsigned int data_point;
	int hasVar(Node);
	// �ж��Ƿ����ĸ��Ĵ�������ĳһ������������򷵻��Ǹ��Ĵ��������û�У��򷵻�-1
	int hasEmpty();
	// �ж��Ƿ����ĸ��Ĵ����ǿյģ����ؿռĴ����±꣬���򷵻�-1
	void insert(Node &var);  // �����������Ծ����

	bool isGlobal; // �ǲ���ȫ�ֱ���
	bool inFunc; // �ǲ����ں���������
	bool isCodeStart; // �ǲ����ڴ���ο�ʼ
	bool isDataStart; // �ǲ��������ݶο�ʼ

	int stackDepth;

	stack<int> tmpStack; // EBP����ʱλ�õ�ջ

	map<int, int> labelMap; // ��תλ�ñ�

	map<Node, int> funMap; // ������Ǳ�
	map<Node, int> asMap; // �ṹ���������׵�ַλ��
	int jmpTable[1000];
	static int label;
	static int pos;
	static int fun;
public:
	Assembler();

	void partition(vector<quaternary>); // ���ֻ�����
	map<Node, bool> activeTable;  // ����ÿ�������Ļ�Ծ��Ϣ
	int locRegister(Node &n);
	void initTable(vector<quaternary> &block);  // ��ʼ����Ծ��
	void fillTable(vector<quaternary> &block);  // ���ݻ�������д��Ծ�����Ϣ
	void arithmetic(quaternary &qd);  // ��������
	void logic(quaternary &qd); // �߼�����
	void assignment(quaternary &qd);           // ��ֵ���Ļ��
	void codegen(vector<quaternary> &block);  // ��ÿ����������������
	tuple<int, int, int> getRegister(quaternary &qd);
	void startFunction(); // ���ú���֮ǰ�Ļ����� ESP EBP
	void startFunction(int); // ���ú���֮ǰ�Ļ����� ESP EBP
	void endFunction(); // �����������֮��Ļ�����

	void callMain(); // ����Main�����Ļ�����
	
	void endMain(); // ����Main�����Ļ�����


	void insertCode(Asm);  // ���������
	void insertCode(string op, string arg1, string arg2, string label); // ���������
	string getAddr(Node & n); // ��ñ����ĵ�ַ
	void declareVn(Node & n); // ���������Ļ��
	void declare(quaternary & qd); // �����Ļ��
	void declareAS(quaternary & qd); // �����ṹ�������������Ļ��
	void showCode(); // ���������
	void showCode(ostream & os); // ��������뵽ostream����
	void show(); // չʾ���õ���Ϣ

	void clear();  // �����Ϣ

};

