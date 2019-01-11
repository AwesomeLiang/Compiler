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

struct  Asm { // 汇编代码
	string op;
	string arg1;
	string arg2;
	string label;

	Asm(string op, string arg1, string arg2, string label) : op(op), arg1(arg1), arg2(arg2), label(label) {}
};

class Assembler { // 生成目标代码模块
private:
	vector<string> destCode;    // 目标代码
	vector<Register> registers;  // 寄存器组，用于记录寄存器状态
	vector<string> extraSeg;    // extra segment -- ES
	map<Node, string> addressMap; // 记录变量的地址

	// 变量地址描述数组，动态记录各变量现行值的存放位置（寄存器、内存地址、还是都有）
	map<Node, vector<int>> addValue;  
	int tmpLength; // 记录到ebp的位置

	int paraLength; // 记录参数的位置
	vector<Asm> dest; // 目标汇编语言
	map<Register, Node> regValue;
	// 寄存器描述数组，动态记录寄存器的存储信息
	unsigned int data_point;
	int hasVar(Node);
	// 判断是否有哪个寄存器中有某一变量，如果有则返回那个寄存器，如果没有，则返回-1
	int hasEmpty();
	// 判断是否有哪个寄存器是空的，返回空寄存器下标，否则返回-1
	void insert(Node &var);  // 将变量插入活跃表中

	bool isGlobal; // 是不是全局变量
	bool inFunc; // 是不是在函数定义内
	bool isCodeStart; // 是不是在代码段开始
	bool isDataStart; // 是不是在数据段开始

	int stackDepth;

	stack<int> tmpStack; // EBP的临时位置的栈

	map<int, int> labelMap; // 跳转位置表

	map<Node, int> funMap; // 函数标记表
	map<Node, int> asMap; // 结构体和数组的首地址位置
	int jmpTable[1000];
	static int label;
	static int pos;
	static int fun;
public:
	Assembler();

	void partition(vector<quaternary>); // 划分基本块
	map<Node, bool> activeTable;  // 用于每个变量的活跃信息
	int locRegister(Node &n);
	void initTable(vector<quaternary> &block);  // 初始化活跃表
	void fillTable(vector<quaternary> &block);  // 根据基本块填写活跃表的信息
	void arithmetic(quaternary &qd);  // 算术运算
	void logic(quaternary &qd); // 逻辑运算
	void assignment(quaternary &qd);           // 赋值语句的汇编
	void codegen(vector<quaternary> &block);  // 对每个代码块进代码生成
	tuple<int, int, int> getRegister(quaternary &qd);
	void startFunction(); // 调用函数之前的汇编操作 ESP EBP
	void startFunction(int); // 调用函数之前的汇编操作 ESP EBP
	void endFunction(); // 函数调用完成之后的汇编操作

	void callMain(); // 调用Main函数的汇编代码
	
	void endMain(); // 结束Main函数的汇编代码


	void insertCode(Asm);  // 插入汇编代码
	void insertCode(string op, string arg1, string arg2, string label); // 插入汇编代码
	string getAddr(Node & n); // 获得变量的地址
	void declareVn(Node & n); // 声明变量的汇编
	void declare(quaternary & qd); // 声明的汇编
	void declareAS(quaternary & qd); // 声明结构体或者数组变量的汇编
	void showCode(); // 输出汇编代码
	void showCode(ostream & os); // 输出汇编代码到ostream流中
	void show(); // 展示已用的信息

	void clear();  // 清除信息

};

