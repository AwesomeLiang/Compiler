//
// Created by nimrod on 18-12-9.
//

#ifndef COMPILER_ASSEMBLER_H
#define COMPILER_ASSEMBLER_H

#include <string>
#include <vector>
#include "symbol.h"
#include "register.h"

using std::vector;
using std::string;

class Assembler {
private:
    vector<Register> registers; // 寄存器组，用于记录寄存器状态
    vector<string> dest_code; // 目标代码
    vector<string> data_seg; // data segment -- DS
    vector<string> code_seg; // code segment -- CS
    vector<string> stack_seg; // stack segment -- SS
    vector<string> extra_seg; // extra segment -- ES
    unsigned int data_point;
    int has_index(Index_4D); // 判断是否有哪个寄存器中有某一变量，如果有则返回那个寄存器，如果没有，则返回-1
    int has_empty(); // 判断是否有哪个寄存器是空的

public:
    Assembler();
    Register get_register(quaternary qt);
    string assignment(quaternary qt); // 赋值语句的汇编
    string codegen(vector<quaternary> block); // 对每个代码块进代码生成
};

#endif  // COMPILER_ASSEMBLER_H
