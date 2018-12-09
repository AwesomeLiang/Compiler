#pragma once
#include <stack>
#include <vector>
#include "symbol.h"
#include "lexical_analyzer.h"

//语法;分析的过程需要用到符号表的部分已经完成了

struct quaternary {
    Index_4D op;
    Index_4D arg1;
    Index_4D arg2;
    Index_4D result
};

struct Index_4D {
    int indexKind;
    int indexDeep;
    int indexFunc;
    int indexItem;
};

class Infer {
public:
    stack<Index_4D> stack_infer;
    vector<quaternary> sequence_temp;
    int num = 0;
    Symbol symbol;
    void work(int index_grammar, vector<Token> token_line, int pos);
    void work_LL(int index_grammar, int pos, stack<int>& stack_state);
};
