//
// Created by nimrod on 18-12-9.
//

#include "register.h"
#include <algorithm>

bool Register::has_index(Index_4D var) {
    if(is_empty()) {
        return true;
    }
    auto it = find(st_data.begin(), st_data.end(), var);
    if (it != st_data.end()) {
        return true;
    }
    return false;
}