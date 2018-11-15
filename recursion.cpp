#include "recursion.h"
/*
E -> T Z ① {I,(}
Z-> a T Z ② {a }|ε ③{),#}
T -> F P ④ {I,(}
P-> b F P ⑤{b}|ε⑥{a,),#}
F -> i ⑦{I} | ( E ) ⑧{(}
*/

Recursion::Recursion()
{
 
  pos = 0;
  mistake = 0;
}

void Recursion::Start()
{
  E();
  if (line[pos] != (tag)6)
    mistake = 1;
    
}

void Recursion::E()
{
  T();
  while (line[pos] == ADD || line[pos] == SUB)
  {
    pos++;
    T();
  }
  
   
}

void Recursion::T()
{
  F();
  while (line[pos] == MUL || line[pos] == DIV)
  {
    ++pos;
    F();
  }
}


void Recursion::F()
{
  if (line[pos] == ID || line[pos] == NUM || line[pos] == REAL)
  {
    pos++;
  }
  else
  {
    if (line[pos] == LSP)
    {
      pos++;
      E();
      if (line[pos] == RSP)
      {
        pos++;
      }
      else
      {
        mistake = 1;
      }
    }
    else
    {
      mistake = 1;

    }
  }
}

