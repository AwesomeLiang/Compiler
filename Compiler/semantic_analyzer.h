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
  int pointJmp = -1;
  quaternary();


  bool activeArg1;
  bool activeArg2;
  bool activeRes;

  friend ostream& operator<<(ostream& out, const quaternary& qd) {
    out << "(" << qd.op << ", " << qd.arg1 << ", " << qd.arg2 << ", " << qd.result
      << ")";
    if (qd.pointJmp != -1) {
      out << " jump->" << qd.pointJmp;
    }
    return out;
  }

  quaternary(tag op, Node arg1, Node arg2, Node res) : op(op), arg1(arg1), arg2(arg2), result(res) {
    activeArg1 = false;
    activeArg2 = false;
    activeRes = false;
  }
};
class Infer
{
public:
  stack<Index_4D> stack_infer;
  vector<quaternary> sequence_temp;
  void Increase_Off(Index_4D index_type, int &offset);
  int num = 0;
  Symbol symbol;
  void work(int index_grammar, vector<Token> token_line, int pos);
  void work_LL(int index_grammar, int pos, stack<int> & stack_state);
  void showSequence(map<tag, string> mapTag);
};

