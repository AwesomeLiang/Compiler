#pragma once
#include<vector>
#include<stack>
#include"lexical analyzer.h"




//语法分析的过程需要用到符号表的部分已经完成了

struct quaternary
{
  Token op;
  Token arg1;
  Token arg2;
  Token result;
};


class Infer
{
public:
  stack<Token> stack_infer;
  vector<quaternary> sequence_temp;
  int num = 0;
  void work(int index_grammar,vector<Token> token_line, int pos);
  void work_LL(int index_grammar, int pos,stack<int> & stack_state);
 
};

