#pragma once
#include<vector>
#include<stack>
#include"lexical_analyzer.h"
#include "symbol.h"



struct quaternary
{
  tag op;
  Node arg1;
  Node arg2;
  Node result;
  quaternary* pointJmp  = NULL;
  quaternary();
};
class Infer
{
public:
  stack<Index_4D> stack_infer;
  vector<quaternary> sequence_temp;
  void Increase_Off(Index_4D index_type, int &offset);
  int num = 0;
  Symbol symbol;
  void work(int index_grammar,vector<Token> token_line, int pos);
  void work_LL(int index_grammar, int pos,stack<int> & stack_state);
  void showSequence();
};

