//
// Created by nimrod on 18-12-9.
//

#include <algorithm>
#include "assembler.h"

Assembler::Assembler() {
    Register ra, rb;
    registers.push_back(ra);
    registers.push_back(rb);
}

int Assembler::has_index(Index_4D var) {
    for(auto it = registers.begin(); it != registers.end(); ++it) {
        if((*it).has_index(var)) {
            return it - registers.begin();
        }
    }
    return -1;
}

int Assembler::has_empty() {
    for(auto it = registers.begin(); it != registers.end(); ++it) {
        if((*it).is_empty()) {
            return it - registers.begin();
        }
    }
    return -1;
}

//
Register Assembler::get_register(quaternary qt) {
    int index = has_index(qt.arg1);
    int empty = has_empty();
    if(index != -1) { // 没有寄存器存储了arg1的值
        return registers[i];
    } else if(empty != -1) { // 有空寄存器
        return registers[empty];
    } else {

    }
}

string Assembler::codegen(vector<quaternary> block) {
    for(auto it = block.begin(); it != block.end(); it++) {

    }
}

