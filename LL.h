#pragma once
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<stack>
using namespace std;

typedef struct pppair
{
  string state;
  string V;
  bool operator < (const pppair &x)const
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
class LL
{
public:
  LL();
  int action();  //自动机
  map<index, int> table_analyse;  //分析表
  string ch; //输入部分 可能用char
  vector<string> line;
  int pos;
  vector<vector<int>> grammar; // 文法 一个二维数组 每个元素是一个character的序号
  vector<string> character; // 文法符号
  vector<int> kind; // 文法符号的类别：0终结符和 1非终结符
  stack<int> stack_state;
  map<int, vector<int>> first;
  map<int, vector<int>> follow;
  map<int, vector<int>>select;

  void table_make();

  void mfirst(vector<int> f);
  bool next_str(string &str, int from, int k);
  bool next_str(string &str, int from);
  bool match(string aim, string str, int from);
  void make_first(int index);
  void make_follow(int index);
  void join(vector<int> &f1,vector<int> f2);

};
