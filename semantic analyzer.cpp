#include "semantic analyzer.h"

quaternary make_sequence(Token Op, Token Arg1, Token Arg2, Token Result)
{
  quaternary q;
  q.op = Op;
  q.arg1 = Arg1;
  q.arg2 = Arg2;
  q.result = Result;
  return q;
}


void Infer::work(int index_grammar, vector<Token> token_line, int pos)
{
  /*
  S->E 0;
  E -> T 1| E + T 2| E - T 3
  T -> F 4| T * F 5|

  T / F 6
  F -> ID 7| NUM 8| REAL 9|( E ) 10

  */

  /*
  Args->Args  COMMA  Exp
  Args->Exp
  Exp->LeftVal  LeftLabel  ASSIGNOP  Exp
  Exp->OrRel
  LeftVal->ID
  LeftVal->LeftVal  LB  Add  RB
  NotRel->Factor
  OrRel->OrRel  OR  AndRel
  OrRel->AndRel
  AndRel->AndRel  AND  Rel
  AndRel->Rel
  Rel->Rel  RELOP  Add
  Rel->Add
  Rel->NOT  NotRel
  Add->Add  PLUS  Term
  Add->Add  MINUS  Term
  Add->MINUS  Term
  Add->Term
  Term->Term  STAR  Factor
  Term->Term  DIV  Factor
  Term->Factor
  Factor->LP  Exp  RP
  Factor->LeftVal
  Factor->INT
  Factor->FLOAT
  Factor->ID  LP  RP
  Factor->ID  LP  Args  RP
  LeftLabel->VOID


  */


  //除法应该考虑0的报错
  switch (index_grammar)
  {
  case 0: // S->E
    //stack_infer.push(token_line[pos]);
    break;
  case 1: // E->T
    break;
  case 2: // E->E+T
  {
    /*
    Token arg2_token = stack_infer.top();//T
    stack_infer.pop();
    Token arg1_token = stack_infer.top();//E
    stack_infer.pop();
    Token result_token;
    if (arg1_token.lexeme_type == REAL || arg2_token.lexeme_type == REAL)
    {
    result_token.lexeme_type = REAL;

    result_token.lexeme_val.real = (arg1_token.lexeme_type == REAL ? arg1_token.lexeme_val.real : arg1_token.lexeme_val.num) + (arg2_token.lexeme_type == REAL ? arg2_token.lexeme_val.real : arg2_token.lexeme_val.num);
    }
    else
    {
    result_token.lexeme_type = NUM;
    result_token.lexeme_val.num = arg1_token.lexeme_val.num + arg2_token.lexeme_val.num;
    }

    stack_infer.push(result_token);
    Token op_token; // 本来应该在分界符表查询
    op_token.lexeme_type = ADD;
    op_token.lexeme_val.str = "+";
    cout << "<" <<op_token.lexeme_val.str<<"," <<arg1_token.lexeme_val.num << "," <<arg2_token.lexeme_val.num<< "," << result_token.lexeme_val.num<<'>' << endl;
    sequence_temp.push_back(make_sequence(op_token, arg1_token, arg2_token, result_token));
    */
    Token arg2 = stack_infer.top();
    stack_infer.pop();
    Token arg1 = stack_infer.top();
    stack_infer.pop();
    Token op;
    op.lexeme_type = ADD;
    op.lexeme_val.str = "+";
    Token result;
    result.lexeme_type = ID;
    result.lexeme_val.str = "temp";
    result.lexeme_val.str += (char)(num + '0');
    num++;
    stack_infer.push(result);
    sequence_temp.push_back(make_sequence(op, arg1, arg2, result));
    cout << "< +,";
    switch (arg1.lexeme_type)
    {
    case NUM:
      cout << arg1.lexeme_val.num << ",";
      break;
    case REAL:
      cout << arg1.lexeme_val.real << ",";
      break;
    case ID:
      cout << arg1.lexeme_val.str << ",";
      break;

    default:
      break;
    }
    switch (arg2.lexeme_type)
    {
    case NUM:
      cout << arg2.lexeme_val.num << ",";
      break;
    case REAL:
      cout << arg2.lexeme_val.real << ",";
      break;
    case ID:
      cout << arg2.lexeme_val.str << ",";
      break;

    default:
      break;
    }
    cout << result.lexeme_val.str << ">" << endl;
  }
    break;
  case 3: // E->E-T
  {
    Token arg2 = stack_infer.top();
    stack_infer.pop();
    Token arg1 = stack_infer.top();
    stack_infer.pop();
    Token op;
    op.lexeme_type = SUB;
    op.lexeme_val.str = "-";
    Token result;
    result.lexeme_type = ID;
    result.lexeme_val.str = "temp";
    result.lexeme_val.str += (char)(num + '0');
    num++;
    stack_infer.push(result);
    sequence_temp.push_back(make_sequence(op, arg1, arg2, result));
    cout << "< -,";
    switch (arg1.lexeme_type)
    {
    case NUM:
      cout << arg1.lexeme_val.num << ",";
      break;
    case REAL:
      cout << arg1.lexeme_val.real << ",";
      break;
    case ID:
      cout << arg1.lexeme_val.str << ",";
      break;

    default:
      break;
    }
    switch (arg2.lexeme_type)
    {
    case NUM:
      cout << arg2.lexeme_val.num << ",";
      break;
    case REAL:
      cout << arg2.lexeme_val.real << ",";
      break;
    case ID:
      cout << arg2.lexeme_val.str << ",";
      break;

    default:
      break;
    }
    cout << result.lexeme_val.str << ">" << endl;
  }
  break;
  case 4: // T->F
    break;
  case 5://T->T*F
  {
    Token arg2 = stack_infer.top();
    stack_infer.pop();
    Token arg1 = stack_infer.top();
    stack_infer.pop();
    Token op;
    op.lexeme_type = MUL;
    op.lexeme_val.str = "*";
    Token result;
    result.lexeme_type = ID;
    result.lexeme_val.str = "temp";
    result.lexeme_val.str += (char)(num + '0');
    num++;
    stack_infer.push(result);
    sequence_temp.push_back(make_sequence(op, arg1, arg2, result));
    cout << "< *,";
    switch (arg1.lexeme_type)
    {
    case NUM:
      cout << arg1.lexeme_val.num << ",";
      break;
    case REAL:
      cout << arg1.lexeme_val.real << ",";
      break;
    case ID:
      cout << arg1.lexeme_val.str << ",";
      break;

    default:
      break;
    }
    switch (arg2.lexeme_type)
    {
    case NUM:
      cout << arg2.lexeme_val.num << ",";
      break;
    case REAL:
      cout << arg2.lexeme_val.real << ",";
      break;
    case ID:
      cout << arg2.lexeme_val.str << ",";
      break;

    default:
      break;
    }
    cout << result.lexeme_val.str << ">" << endl;
  }
    break;
  case 6: //T->T/F
  {
    Token arg2 = stack_infer.top();
    stack_infer.pop();
    Token arg1 = stack_infer.top();
    stack_infer.pop();
    Token op;
    op.lexeme_type = DIV;
    op.lexeme_val.str = "/";
    Token result;
    result.lexeme_type = ID;
    result.lexeme_val.str = "temp";
    result.lexeme_val.str += (char)(num + '0');
    num++;
    stack_infer.push(result);
    sequence_temp.push_back(make_sequence(op, arg1, arg2, result));
    cout << "< /,";
    switch (arg1.lexeme_type)
    {
    case NUM:
      cout << arg1.lexeme_val.num << ",";
      break;
    case REAL:
      cout << arg1.lexeme_val.real << ",";
      break;
    case ID:
      cout << arg1.lexeme_val.str << ",";
      break;

    default:
      break;
    }
    switch (arg2.lexeme_type)
    {
    case NUM:
      cout << arg2.lexeme_val.num << ",";
      break;
    case REAL:
      cout << arg2.lexeme_val.real << ",";
      break;
    case ID:
      cout << arg2.lexeme_val.str << ",";
      break;

    default:
      break;
    }
    cout << result.lexeme_val.str << ">" << endl;
  }
    break;
  case 7: //F->NUM
  {
    int temp_pos = pos - 1;
    stack_infer.push(token_line[temp_pos]); //和符号表结合的话其实是把指针放到栈里  
  }
  break;
  case 8: //F->NUM
  {
    int temp_pos = pos - 1;
    stack_infer.push(token_line[temp_pos]); //和符号表结合的话其实是把指针放到栈里  
  }
    break;
  case 9: //F->NUM
  {
    int temp_pos = pos - 1;
    stack_infer.push(token_line[temp_pos]); //和符号表结合的话其实是把指针放到栈里  
  }
  break;
  default:
    break;
  }
}

void Infer::work_LL(int index_grammar, int pos, stack<int> & stack_state)
{
  /*
  E -> T Z ① {I,(}
  Z-> + T{GEQ(+)} Z ② {a }|ε ③{),#}
  T -> F P ④ {I,(}
  P-> b F{GEQ(*)} P ⑤{b}|ε⑥{a,),#}
  F -> i{PUSH(i)} ⑦{I} | ( E ) ⑧{(}
  */

  switch (index_grammar)
  {
  case 1:
  {
    if (pos == 2)
    {
      stack_state.push(16);
      
    }
  }
    break;
  case 2:
  {
   
    if (pos == 2)
    {
      stack_state.push(17);
    }
  }
  break;
  case 5:
  {
    if (pos == 2)
    {
      stack_state.push(18);
    }
  }
    
    break;
  case 6:
  {
    if (pos == 2)
    {
      stack_state.push(19);
    }
  }
    break;
  case 7:
    break;
  case 8:
    break;
  case 10:
    break;

  default:
    break;
  }


}
