//
// Created by nimrod on 18-12-9.
//

#ifndef COMPILER_REGISTER_H
#define COMPILER_REGISTER_H

#include <vector>
#include "symbol.h"

using std::vector;

class Register {
private:
    vector<Index_4D> st_data;  // 存储了哪个变量或者是哪些变量，所以用一个容器存

public:
    bool is_empty() { return st_data.empty(); }
    void clear() { st_data.clear(); }
    void add(Index_4D var) { st_data.push_back(var); }
    bool has_index(Index_4D var);  // 看是否存储了某一个变量
};

#endif  // COMPILER_REGISTER_H
