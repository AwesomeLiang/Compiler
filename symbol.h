#pragma once
#include<iostream>
#include<list>
#include<vector>
#include "lexical_analyzer.h"
#include<stack>

using namespace std;

typedef enum  {f = 0, c = 1, t = 2, d = 3, v = 4, vn = 5, vf = 6}Catalog;
typedef enum  {Int = 0/*int*/ ,Real = 1/*real*/ , Char = 2 /*char*/, String = 3/*string*/,Bool = 4/*bool*/, Array = 5/*array*/, Struct = 6/*struct*/}TVal;


struct Index_4D
{
  int indexKind;
  int indexDeep;
  int indexFunc;
  int indexItem;

};


struct Node_Array;
struct Node_Struct;
struct Node_Param;
struct Node_Type;


struct  TPoint
{
  Node_Array *point_array; // 用于多维数组
  vector<Node_Struct> point_struct;//数组的单个元素是结构体
  void *Null; // 数组的单个元素是int这类的基本类型
};

struct Node_Type
{
  TVal tval; // 类型代码
  TPoint tpoint; // 类型指针
};



 struct Node_Array
{
  int low; //数组下界
  int up;//数组上届
  Node_Type *ctp;//数组元素类型
  int clen; // 数组元素长度
};



 struct Node_Struct
{
  string dname; //结构的域名
  int offset;//区距
  Index_4D index_tp; // 指向id域成分类型

};
 /*
 对于一个类型为结构体的变量，将类型指向类型表，类型表中填下d,指针指向结构体表，addr指向Lenth表，length表中填写的是结构体的总长度，应该最后填
 结构体表里填的是结构体的域名，区距和每个域名的类型（指回类型表）（按c的语法来说，这里的类型都已经是定义好的，能直接在类型表中找到）


 */

 struct Node_Process
{
  int level;//函数静态层次嵌套号 （可能是用来查符号list）
  int off;//区距
  int numf;//参数个数
  Node_Param* param; //指向函数形参表的指针
  int entry;//函数目标程序首地址（运行时填写）
};







 typedef int Node_Num;
 typedef int Node_Real;
 typedef int Node_Length;

 struct Node_Vall
{

};


 struct Node_Param
{

};


struct  Addr
{
  vector<Node_Vall> *point_vall;  //活动记录表的指针
  vector<Node_Num> *point_num; // 常整数表的指针
  vector<Node_Real> *point_real; // 常实数表的指针
  int length; //结构体长度
  vector<Node_Process> *point_process; // 函数表的指针
};

struct Node_Id_1
{
  string name; // 标识符名字
  Index_4D point_type; // 标识符类型 对应table_type的位置
  Catalog cat; // 标识符种类
  Addr addr;
  int state;
};
//typedef vector<Node_Id> Table_Id;



/*
关键字表类型为0
label表的类型为1
分隔符表类型为2（+ - * / or and !）
id 表类型为3
常整数表类型为4
常实数表类型为5
type表类型为6
*/

struct Node_Id_2
{
  vector<Node_Id_1> table_id_1;
  Index_4D parent;
  
};

typedef vector<Node_Id_2> Table_Id_2,Node_Id_3;
typedef vector<Node_Id_3> Table_Id_3;



class Symbol
{
public:
  Table_Id_3 table_id_3; // 这是一个三维表，第一维是deep，第二维func , 第三维item
  vector<Node_Array> table_array;
  vector<Node_Num> table_num;
  vector<Node_Real> table_real;
  vector<Node_Length> table_length;
  vector<Node_Process> table_process;
  vector<Node_Param> table_param;
  vector<Node_Struct> table_struct;
  vector<Node_Type> table_type;
  vector<Node_Vall> table_vall;
  vector<int> table_label;
  vector<tag> table_key;
  Index_4D type;
  Catalog catalog;
  int offset;//用于计算域名区距
  int num_t;
  int mode; // 用于区分结构体的表创建和id表 1 是结构体表
  int index_deep_now;
  int index_func_now;
  int index_item_now;
  int space[100]; //最多分配100层空间
  stack<Node_Id_1> stack_node_id;
  Symbol();

};
