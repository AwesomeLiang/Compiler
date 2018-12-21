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
	bool activeArg1;
	bool activeArg2;
	bool activeRes;
	quaternary* pointJmp = NULL;
	quaternary();


	friend bool isBinary(tag) {}
	friend bool isUnary(tag) {}
	friend bool isExchangeable(tag) {}
	friend bool isJump(tag) {}

  friend ostream& operator<<(ostream& os, const quaternary& qd);

  quaternary(tag op, Node arg1, Node arg2, Node res) : op(op), arg1(arg1), arg2(arg2), result (res) {
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
  void work(int index_grammar,vector<Token> token_line, int pos);
  void work_LL(int index_grammar, int pos,stack<int> & stack_state);
  void showSequence();
};

