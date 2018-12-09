#pragma once
#include<iostream>
#include<vector>
#include "lexical_analyzer.h"
using namespace std;

/*
E -> T Z ① {I,(}
Z-> a T Z ② {a }|ε ③{),#}
T -> F P ④ {I,(}
P-> b F P ⑤{b}|ε⑥{a,),#}
F -> i ⑦{I} | ( E ) ⑧{(}
*/

class Recursion
{
public:
  vector<tag> line;
  int pos;
  
  int mistake;
  Recursion();
  void Start();

  void E();
  void T();
  
  void F();
  
};
