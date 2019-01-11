#pragma once
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<stack>
using namespace std;

//需要一个自动生成自动机的

//S->aB;

//相当于生成一个语法分析表  ，然后一个输入一个符号串，一步步转化，直到OK状态
//问题转化为如何生成一个语法分析表
// 0:S->E 1:E->E+T 2:T->T*F 3:F->(E) 4:F->id
//初始状态为0 s'->s; 先找到这个产生式， 初始I0 中只有  S'->.S
//然后看当前这个状态的产生式子右边，点后是不是非终极符，若是，依次检索 产生式集合，把以左边为该终极符的产生式右边第一位加点放入。
//分析该项目集的所有产生式，依次查看右边的@后的符号， 比如说S->.aB  那么就把该项目集所有右边点后是a的产生式点往后移一位后加入到第二个项目集，然后在相应的状态表里写下一个结构体，<a,2>;
//如果该项目集存在一个产生式，右边点后面为空，那么在表里写下<r,i> r的意思是规约，i的意思是用第几个产生式规约

/*


项目集的添加规则 ： 遍历本项目集的所有产生式，在最大产生式list搜索左部为 右部点后的第一个非终极符号的产生式，将其->后插入一个@，然后加入到该项目集中 （考虑是否做预处理，即事先生成好），
加入的条件是 加点后的产生式没有在本项目集中。 项目集得到扩大， 重复执行直到没有新的产生式加入。
=> CLOSURE(I)
{
J = I;
repeat
for(J中的每个项[A->a@Bβ，a])
for(G的每个产生式B->γ)
if(项B -> @γ 不在J中)
if(β为空)
将[B -> @γ,a]加入J中。
else
for(first(β)中的每个符号b)
将[B -> @γ,b/]加入J中
else
if(β为空)
将[a/]加入B -> @γ中。
else
for(first(β)中的每个符号b)
将[b/]加入B -> @γ中

until 在某轮中没有新的项加入J中
return J;
}
=> items(G')
{
C = {CLOSURE{[S'->@S]}};
repeat
for(C中的每个项集I)
for(每个文法符号X)
if(GOTO(I,X) 非空且不在C中)
将GOTO(I,X)加入C中
until 在某一轮中没有新的项集加入到C中
}

=> GOTO(I,X)
{
空项集J
repeat
for(I中的每个产生式)
if(产生式右部@的后面为X)
将该产生式@于X交换位置，并加入到J中，归约标记也直接插入
until 遍历完I中的每个产生式
return CLOSURE(J)
}
对每个项集要加上编号信息(状态编号)；
分析表的构造规则： 1.依次访问各个状态（项目集），若果有点在产生式末尾的点，则在该产生式左部follow集（SLR（0）或者是LR（1））对应的那栏里写下<r,i> r的意思是规约，i的意思是用第几个产生式规约


对于项目集I0 S'->S;
for( 0 - lengthof(I0)-1)
nrfisrt = 点后的符号.
search(list)
if(rfirst == nrfirst)
inserttable()

*/


typedef struct ppair
{
  int state;
  string V;
  bool operator < (const ppair &x)const
  {
    if (state < x.state)
    {

      return true;
    }
    if (state == x.state)
    {
      return V < x.V;
    }

    return false;

  }
}index, key;

struct item
{
  vector<string> grammar_item;
  vector<string> tag_reduced;

};



class Parser
{
public:
  Parser();
  void action();  //自动机
  map<index, key> table_analyse;  //分析表
  string ch; //输入部分 可能用char
  vector<string> grammar; // 文法
  vector<string> character; // 文法符号
  vector<int> kind; // 文法符号的类别：0终结符和 1非终结符
  stack<int> stack_state;
  stack<string> stack_op;
  vector<item> items;
  map<string, string> first;
  vector<string> cash;
  void items_make();
  void table_make();
  item CLOSURE(item t);
  item GOTO(int index, string str);
  bool in_items(item t);
  bool in_items(item t, int &n);
  bool next_str(string &str, int from, int k);
  bool next_str(string &str, int from);
  bool match(string aim, string str, int from);
  string mfirst(string str, string add_strz);
  string make_first(int num);
};

