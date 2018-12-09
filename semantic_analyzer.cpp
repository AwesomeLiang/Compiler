#include "semantic_analyzer.h"


int power(int i, int j)
{
  int sum = 1;
  while (j > 0)
  {

    sum *= i;
    j--;
  }
  return sum;
}

void name_make(int num_t,string &str)
{
  int temp = num_t;
  int length = 0;
  while (temp)
  {
    temp /= 10;
    length++;
  }
  for (int i = length; i >= 1; --i)
  {
    str += (char)(num_t / power(10, (i - 1))) + '0';
    num_t %= power(10, (i - 1));
  }
}

TVal judege(TVal t1, TVal t2)
{
  return t1 > t2 ? t1 : t2;
}

void Infer::work(int index_grammar, vector<Token> token_line, int pos)
{
  //没有做错误处理 比如类型不符， A+3 就看 A的类型和3的表对应的类型是不是一个类型
  //没有完全完成 压入栈但是不用做四元式产生的符号产生的影响 应该列出所有被压入栈中的元素，然后依次检查
  switch (index_grammar)
  {
  case 0:   //Program->ExtDefList
    break;
  case 1:   //ExtDefList->ExtDef, ExtDefList
    break;
  case 2:   //ExtDefList->VOID
    break;
  case 3:   //ExtDef->Specifier  ExtDecList  SEMI


    break;
  case 4:   //ExtDef->Specifier  SEMI
    break;
  case 5:  //ExtDef->Specifier  FunDec  CompSt
    break;
  case 6:  //ExtDecList->VarDec
  {
    Node_Id_1 *temp_node = &symbol.stack_node_id.top();
    symbol.stack_node_id.pop();
    temp_node->cat = v;
    stack_infer.pop();
  }
    break;
  case 7: //ExtDeclist->VarDec InitLable ASSIGN Exp
  {
    quaternary quaternary_ASSIGN;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == ASSIGN)
      {
        index_op.indexItem = i;
        break;
      }

    }

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_result;
    index_result = stack_infer.top();
    stack_infer.pop();
    quaternary_ASSIGN.op = index_op;
    quaternary_ASSIGN.arg1 = index_arg1;
    quaternary_ASSIGN.result = index_result;
    sequence_temp.push_back(quaternary_ASSIGN);

  }
    Node_Id_1 *temp_node = &symbol.stack_node_id.top();
    symbol.stack_node_id.pop();
    temp_node->cat = v;
    break;
  case 8: //ExtDecList->ExtDecList  COMMA  VarDec
    {
      Node_Id_1 *temp_node = &symbol.stack_node_id.top();
      symbol.stack_node_id.pop();
      temp_node->cat = v;
      stack_infer.pop();
    }
    break;
  case 9: //ExtDeclist->ExtDecList  COMMA  VarDec  InitLable ASSIGN Exp
    Node_Id_1 *temp_node = &symbol.stack_node_id.top();
    symbol.stack_node_id.pop();
    temp_node->cat = v;
    //处理后部分的VarDec  InitLable ASSIGN Exp
    {
      quaternary quaternary_ASSIGN;

      Index_4D index_op;
      index_op.indexDeep = -1;
      index_op.indexFunc = -1;
      index_op.indexKind = 2;
      for (int i = 0; i < (int)symbol.table_key.size(); ++i)
      {
        if (symbol.table_key[i] == ASSIGN)
        {
          index_op.indexItem = i;
          break;
        }

      }

      Index_4D index_arg1;
      index_arg1 = stack_infer.top();
      stack_infer.pop();

      Index_4D index_result;
      index_result = stack_infer.top();
      stack_infer.pop();
      quaternary_ASSIGN.op = index_op;
      quaternary_ASSIGN.arg1 = index_arg1;
      quaternary_ASSIGN.result = index_result;
      sequence_temp.push_back(quaternary_ASSIGN);

    }
    break;
  case 10: //Specifier->TYPE
           //这一步是确定了定义的变量的类型
    break;
  case: //TYPE->INT
  {
    
    int flag = 0;
    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval == Int)
      {
        flag = 1;
        symbol.type.indexItem = i;
        symbol.type.indexDeep = -1;
        symbol.type.indexFunc = -1;
        symbol.type.indexKind = 6;
        break;
      }
    }
    if (flag == 0)
    {
      //error;
    }


  }

  break;
  case: //TYPE->DOUBLE
  {

    int flag = 0;
    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval == Real)
      {
        flag = 1;
        symbol.type.indexItem = i;
        symbol.type.indexDeep = -1;
        symbol.type.indexFunc = -1;
        symbol.type.indexKind = 6;
        break;
      }
    }
    if (flag == 0)
    {
      //error;
    }


  }

  break;
  case 11: // Specifier->StructSpecifier
    break;
  case 12: // StructSpecifier->STRUCT  OptTag  LC  DefList  RC
    break;
  case 13: // StructSpecifier->STRUCT  Tag
    break;
  case 14: // OptTag->ID
    break;
  case 15: // OptTag->VOID
    break;
  case 16: // Tag->ID
    break;
  case 17: // VarDec->ID
  {
    //该文法是用于标识符的声明 ， 所以应该先检查重定义
    for (int i = 0; i < (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size(); ++i)
    {
      if (symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1[i].name == token_line[pos].lexeme_val.str)
      {
        //error
      }
    }

    Node_Id_1 new_node;
    new_node.name = token_line[pos].lexeme_val.str;
    new_node.point_type = symbol.type;
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(new_node);
    Index_4D index_id;
    index_id.indexDeep = symbol.index_deep_now;
    index_id.indexFunc = symbol.index_func_now;
    index_id.indexKind = 3;
    index_id.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size() - 1;
    stack_infer.push(index_id);
    symbol.stack_node_id.push(new_node);// 忘了有什么用 !!!!!!!!!
  }
    break;
  case 18: // VarDec->VarDec  LB  INT  RB
    break;
  case 19: //FunDec->ID  LP  VarList  RP
    break;
  case 20://FunDec->ID  LP  RP
    break;
  case 21://VarList->VarList  COMMA  ParamDec
    break;
  case://VarList->ParamDec
    break;
  case://ParamDec->Specifier  VarDec
    break;
  case://CompSt->LC DeepInc DefList  StmtList  RC
  {
    symbol.index_deep_now = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexDeep;
    symbol.index_func_now = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexFunc;
  }
    break;
  case: // DeepInc->VOID
  {
    Node_Id_2 node_id_2;
    node_id_2.parent.indexDeep = symbol.index_deep_now;
    node_id_2.parent.indexFunc = symbol.index_func_now;
    node_id_2.parent.indexKind = 3;
    symbol.index_deep_now++;
    symbol.index_func_now = (int)symbol.table_id_3[symbol.index_deep_now].size();
    symbol.table_id_3[symbol.index_deep_now].push_back(node_id_2);
    
  }
    
    break;
  case://StmtList->VOID
    break;
  case://StmtList->StmtList  Stmt
    break;
  case://Stmt->Exp  SEMI
  {
    stack_infer.pop();
  }
    break;
  case://Stmt->CompSt
    break;
  case://Stmt->RETURN  Exp  SEMI
    break;
  case://Stmt->IF  LP  Exp  RP  causeIF Label  Stmt  Label
  {
    symbol.index_deep_now = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexDeep;
    symbol.index_func_now = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexFunc;
  }
   
    break; 
  case: // causeIF->void
  {
    //<IF,EXP,Label1,Label2>
    Index_4D index_exp;
    index_exp = stack_infer.top();
    stack_infer.pop();
    int num_label;
    num_label = (int)symbol.table_label.size();
    symbol.table_label.push_back(num_label);
    Index_4D index_label1;
    index_label1.indexKind = 1;
    index_label1.indexFunc = -1;
    index_label1.indexDeep = -1;
    index_label1.indexItem = num_label;
    

    num_label = (int)symbol.table_label.size();
    symbol.table_label.push_back(num_label);
    Index_4D index_label2;
    index_label2.indexKind = 1;
    index_label2.indexFunc = -1;
    index_label2.indexDeep = -1;
    index_label2.indexItem = num_label;
    stack_infer.push(index_label2);
    stack_infer.push(index_label1);
    Index_4D index_if;
    index_if.indexKind = 0;
    index_if.indexDeep = -1;
    index_if.indexFunc = -1;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == IF)
      {
        index_if.indexItem = i;
        break;
      }
        
    }
    quaternary quaternary_if;
    quaternary_if.op = index_if;
    quaternary_if.arg1 = index_exp;
    quaternary_if.arg2 = index_label1;
    quaternary_if.result = index_label2;
    sequence_temp.push_back(quaternary_if);

    Node_Id_2 node_id_2;
    node_id_2.parent.indexDeep = symbol.index_deep_now;
    node_id_2.parent.indexFunc = symbol.index_func_now;
    node_id_2.parent.indexKind = 3;
    symbol.index_deep_now++;
    symbol.index_func_now = (int)symbol.table_id_3[symbol.index_deep_now].size();
    symbol.table_id_3[symbol.index_deep_now].push_back(node_id_2);

  }
    break;
  case://Label->void
  {
    //<Label,,,>
    {
      Index_4D index_label;
      index_label = stack_infer.top();
      stack_infer.pop();
      quaternary label;
      label.op = index_label;
      sequence_temp.push_back(label);


    }
  }
    break;
  case://Stmt->IF  LP  Exp  RP  causeIF Label  Stmt bgoto ELSE  Label  Stmt  Label
  {
    symbol.index_deep_now = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexDeep;
    symbol.index_func_now = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexFunc;
  }
    break;
  case://bgoto->void
  {
    Index_4D index_goto;
    index_goto.indexKind = 0;
    index_goto.indexDeep = -1;
    index_goto.indexFunc = -1;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == GOTO)
      {
        index_goto.indexItem = i;
        break;
      }
        
    }
    int num_label;
    num_label = (int)symbol.table_label.size();
    symbol.table_label.push_back(num_label);
    Index_4D index_label1;
    index_label1.indexKind = 1;
    index_label1.indexFunc = -1;
    index_label1.indexDeep = -1;
    index_label1.indexItem = num_label;
    Index_4D index_temp;
    index_temp = stack_infer.top();
    stack_infer.pop();
    stack_infer.push(index_label1);
    stack_infer.push(index_temp);
    quaternary quaternary_bgoto;
    quaternary_bgoto.op = index_goto;
    quaternary_bgoto.arg1 = index_label1;
    sequence_temp.push_back(quaternary_bgoto);
  }
    break;
  case://Stmt->fLabel  WHILE  LP  Exp  RP causeWHILE  Label  Stmt  fgoto Label
  {
    symbol.index_deep_now = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexDeep;
    symbol.index_func_now = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexFunc;
  }
    break;
  case://causeWHILE -> void
  {
    //<WHILE,EXP,Label1,Label2>
    Index_4D index_exp;
    index_exp = stack_infer.top();
    stack_infer.pop();
    int num_label;
    num_label = (int)symbol.table_label.size();
    symbol.table_label.push_back(num_label);
    Index_4D index_label1;
    index_label1.indexKind = 1;
    index_label1.indexFunc = -1;
    index_label1.indexDeep = -1;
    index_label1.indexItem = num_label;
    

    num_label = (int)symbol.table_label.size();
    symbol.table_label.push_back(num_label);
    Index_4D index_label2;
    index_label2.indexKind = 1;
    index_label2.indexFunc = -1;
    index_label2.indexDeep = -1;
    index_label2.indexItem = num_label;
    Index_4D index_temp;
    index_temp = stack_infer.top();
    stack_infer.pop();
    stack_infer.push(index_label2);
    stack_infer.push(index_temp);
    stack_infer.push(index_label1);
    Index_4D index_if;
    index_if.indexKind = 0;
    index_if.indexDeep = -1;
    index_if.indexFunc = -1;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == WHILE)
      {
        index_if.indexItem = i;
        break;
      }
        
    }
    quaternary quaternary_if;
    quaternary_if.op = index_if;
    quaternary_if.arg1 = index_exp;
    quaternary_if.arg2 = index_label1;
    quaternary_if.result = index_label2;
    sequence_temp.push_back(quaternary_if);


    Node_Id_2 node_id_2;
    node_id_2.parent.indexDeep = symbol.index_deep_now;
    node_id_2.parent.indexFunc = symbol.index_func_now;
    node_id_2.parent.indexKind = 3;
    symbol.index_deep_now++;
    symbol.index_func_now = (int)symbol.table_id_3[symbol.index_deep_now].size();
    symbol.table_id_3[symbol.index_deep_now].push_back(node_id_2);
  }
    break;
  case: // fLabel-> void
  {
    int num_label;
    num_label = (int)symbol.table_label.size();
    symbol.table_label.push_back(num_label);
    Index_4D index_label1;
    index_label1.indexKind = 1;
    index_label1.indexFunc = -1;
    index_label1.indexDeep = -1;
    index_label1.indexItem = num_label;
    quaternary label;
    label.op = index_label1;
    sequence_temp.push_back(label);
  }
    break;
  case: // fgoto->void
  {
    Index_4D index_goto;
    index_goto.indexKind = 0;
    index_goto.indexDeep = -1;
    index_goto.indexFunc = -1;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == GOTO)
      {
        index_goto.indexItem = i;
        break;
      }
        
    }
    
    
    Index_4D index_temp;
    index_temp = stack_infer.top();
    stack_infer.pop();
    
    quaternary quaternary_fgoto;
    quaternary_fgoto.op = index_goto;
    quaternary_fgoto.arg1 = index_temp;
    sequence_temp.push_back(quaternary_fgoto);
  }
  break;
  case://DefList->VOID
    break;
  case://DefList->DefList  Def
    break;
  case://Def->Specifier  DecList  SEMI
    //处理catalog
    break;
  case://DecList->Dec
    break;
  case://DecList->DecList  COMMA  Dec
    break;
  case://Dec->VarDec
  {
    stack_infer.pop();
  }
    break;
  case://Dec->VarDec  InitLabel  ASSIGNOP  Exp
  {
    quaternary quaternary_ASSIGN;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == ASSIGN)
      {
        index_op.indexItem = i;
        break;
      }
        
    }

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_result;
    index_result = stack_infer.top();
    stack_infer.pop();
    quaternary_ASSIGN.op = index_op;
    quaternary_ASSIGN.arg1 = index_arg1;
    quaternary_ASSIGN.result = index_result;
    sequence_temp.push_back(quaternary_ASSIGN);

  }
    break;
  case://InitLabel->VOID
    break;
  case://Args->Args  COMMA  Exp
    break;
  case://Args->Exp
    break;
  case://Exp->LeftVal  LeftLabel  ASSIGNOP  Exp
  {
    quaternary quaternary_ASSIGN;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == ASSIGN)
      {
        index_op.indexItem = i;
        break;
      }
       
    }

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_result;
    index_result = stack_infer.top();
    
    quaternary_ASSIGN.op = index_op;
    quaternary_ASSIGN.arg1 = index_arg1;
    quaternary_ASSIGN.result = index_result;
    sequence_temp.push_back(quaternary_ASSIGN);
    
  }
    break;
  case://Exp->OrRel
    break;
  case://LeftVal->ID
  {
    //从该层开始，向上层查找ID
    int deep_temp = symbol.index_deep_now;
    int func_temp = symbol.index_func_now;
    int item_temp;
    Index_4D index_leftval;
    int flag = 0;
    while (flag == 0 && deep_temp >= 0)
    {
      for (int i = 0; i < (int)symbol.table_id_3[deep_temp][func_temp].table_id_1.size(); ++i)
      {
        if (token_line[pos].lexeme_val.str == symbol.table_id_3[deep_temp][func_temp].table_id_1[i].name)
        {
          //在当前的作用域内找到了该标识符
          flag = 1;
          item_temp = i;
          break;
        }

      }
      if (flag == 0)
      {
        //该标识符在上级作用域内
        deep_temp = symbol.table_id_3[deep_temp][func_temp].parent.indexDeep;
        func_temp = symbol.table_id_3[deep_temp][func_temp].parent.indexFunc;
      }
    }
    if (flag == 0)
    {
      //error; 该标识符未被定义就使用
    }
    else
    {
      
      index_leftval.indexDeep = deep_temp;
      index_leftval.indexKind = 3;
      index_leftval.indexFunc = func_temp;
      index_leftval.indexItem = item_temp;
      
    }
    stack_infer.push(index_leftval);
  }
    
    break;
  case://LeftVal->LeftVal  LB  Add  RB   用于数组
    break;
  case://NotRel->Factor
    break;
  case://OrRel->OrRel  OR  AndRel               !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_OR;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == OR)
      {
        index_op.indexItem = i;
        break;
      }
        
    }

    Index_4D index_arg2;
    index_arg2 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_bool;
    index_bool.indexDeep = -1;
    index_bool.indexFunc = -1;
    index_bool.indexKind = 6;
    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval = Bool)
      {
        index_bool.indexItem = i;
        break;
      }

    }
    Node_Id_1 temp_id;
    temp_id.name = "t";
    name_make(symbol.num_t,temp_id.name);
    symbol.num_t++;
    temp_id.point_type = index_bool;
    temp_id.cat = v;
    Index_4D index_temp;
    index_temp.indexDeep = symbol.index_deep_now;
    index_temp.indexFunc = symbol.index_func_now;
    index_temp.indexKind = 3;
    index_temp.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size();
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(temp_id);
    stack_infer.push(index_temp);

    Index_4D index_result;
    index_result = stack_infer.top();
    
   
    quaternary_OR.op = index_op;
    quaternary_OR.arg1 = index_arg1;
    quaternary_OR.arg2 = index_arg2;
    quaternary_OR.result = index_result;
    sequence_temp.push_back(quaternary_OR);

  }

    break;
  case://OrRel->AndRel
    break;
  case://AndRel->AndRel  AND  Rel              ！！！！！！！！！！！！！！！！！！！！
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_AND;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == AND)
      {
        index_op.indexItem = i;
        break;
      }
       
    }

    Index_4D index_arg2;
    index_arg2 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_bool;
    index_bool.indexDeep = -1;
    index_bool.indexFunc = -1;
    index_bool.indexKind = 6;
    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval = Bool)
      {
        index_bool.indexItem = i;
        break;
      }

    }
    Node_Id_1 temp_id;
    temp_id.name = "t";
    name_make(symbol.num_t, temp_id.name);
    symbol.num_t++;
    temp_id.point_type = index_bool;
    temp_id.cat = v;
    Index_4D index_temp;
    index_temp.indexDeep = symbol.index_deep_now;
    index_temp.indexFunc = symbol.index_func_now;
    index_temp.indexKind = 3;
    index_temp.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size();
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(temp_id);
    stack_infer.push(index_temp);


    Index_4D index_result;
    index_result = stack_infer.top();

    quaternary_AND.op = index_op;
    quaternary_AND.arg1 = index_arg1;
    quaternary_AND.arg2 = index_arg2;
    quaternary_AND.result = index_result;
    sequence_temp.push_back(quaternary_AND);

  }
    break;
  case://AndRel->Rel
    break;
  case://Rel->Rel  RELOP  Add            //需要完成但是还没想好
    break;
  case://Rel->Add
    break;
  case://Rel->NOT  NotRel
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_NOT;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == NOT)
      {
        index_op.indexItem = i;
        break;
      }
        
    }


    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_bool;
    index_bool.indexDeep = -1;
    index_bool.indexFunc = -1;
    index_bool.indexKind = 6;
    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval = Bool)
      {
        index_bool.indexItem = i;
        break;
      }

    }
    Node_Id_1 temp_id;
    temp_id.name = "t";
    name_make(symbol.num_t, temp_id.name);
    symbol.num_t++;
    temp_id.point_type = index_bool;
    temp_id.cat = v;
    Index_4D index_temp;
    index_temp.indexDeep = symbol.index_deep_now;
    index_temp.indexFunc = symbol.index_func_now;
    index_temp.indexKind = 3;
    index_temp.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size();
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(temp_id);
    stack_infer.push(index_temp);

    Index_4D index_result;
    index_result = stack_infer.top();

    quaternary_NOT.op = index_op;
    quaternary_NOT.arg1 = index_arg1;
    quaternary_NOT.result = index_result;
    sequence_temp.push_back(quaternary_NOT);

  }
    break;
  case://Add->Add  PLUS  Term
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_OR;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == ADD)
      {
        index_op.indexItem = i;
        break;
      }
       
    }

    Index_4D index_arg2;
    index_arg2 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_tval;
    index_tval.indexDeep = -1;
    index_tval.indexFunc = -1;
    index_tval.indexKind = 6;
    int pos1;
    int pos2;
    if (index_arg1.indexKind == 3)
    {
       pos1 = symbol.table_id_3[index_arg1.indexDeep][index_arg1.indexFunc].table_id_1[index_arg1.indexItem].point_type.indexItem;
    }
    else if (index_arg1.indexKind == 4)
    {
      //操作数1是常整数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Int)
        {
          pos1 = i;
          break;
        }
      }
      
    }
    else if (index_arg1.indexKind == 5)
    {
      //操作数1是常实数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Real)
        {
          pos1 = i;
          break;
        }
      }
    }
    else
    {
      //error;
    }
    if (index_arg2.indexKind == 3)
    {
      pos2 = symbol.table_id_3[index_arg2.indexDeep][index_arg2.indexFunc].table_id_1[index_arg2.indexItem].point_type.indexItem;
    }
    else if (index_arg2.indexKind == 4)
    {
      //操作数1是常整数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Int)
        {
          pos2 = i;
          break;
        }
      }

    }
    else if (index_arg2.indexKind == 5)
    {
      //操作数1是常实数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Real)
        {
          pos2 = i;
          break;
        }
      }
    }
    else
    {
      //error;
    }
    
    TVal tval_temp = judege(symbol.table_type[pos1].tval, symbol.table_type[pos2].tval); // 变量一 变量二 仲裁后的类型
    
    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval = tval_temp)
      {
        index_tval.indexItem = i;
        break;
      }

    }
    Node_Id_1 temp_id;
    temp_id.name = "t";
    name_make(symbol.num_t, temp_id.name);
    symbol.num_t++;
    temp_id.point_type = index_tval;
    temp_id.cat = v;
    Index_4D index_temp;
    index_temp.indexDeep = symbol.index_deep_now;
    index_temp.indexFunc = symbol.index_func_now;
    index_temp.indexKind = 3;
    index_temp.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size();
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(temp_id);
    stack_infer.push(index_temp);



    Index_4D index_result;
    index_result = stack_infer.top();

    quaternary_OR.op = index_op;
    quaternary_OR.arg1 = index_arg1;
    quaternary_OR.arg2 = index_arg2;
    quaternary_OR.result = index_result;
    sequence_temp.push_back(quaternary_OR);

  }
    break;
  case://Add->Add  MINUS  Term
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_OR;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == SUB)
      {
        index_op.indexItem = i;
        break;
      }
        
    }

    Index_4D index_arg2;
    index_arg2 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_tval;
    index_tval.indexDeep = -1;
    index_tval.indexFunc = -1;
    index_tval.indexKind = 6;
    int pos1;
    int pos2;
    if (index_arg1.indexKind == 3)
    {
      pos1 = symbol.table_id_3[index_arg1.indexDeep][index_arg1.indexFunc].table_id_1[index_arg1.indexItem].point_type.indexItem;
    }
    else if (index_arg1.indexKind == 4)
    {
      //操作数1是常整数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Int)
        {
          pos1 = i;
          break;
        }
      }

    }
    else if (index_arg1.indexKind == 5)
    {
      //操作数1是常实数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Real)
        {
          pos1 = i;
          break;
        }
      }
    }
    else
    {
      //error;
    }
    if (index_arg2.indexKind == 3)
    {
      pos2 = symbol.table_id_3[index_arg2.indexDeep][index_arg2.indexFunc].table_id_1[index_arg2.indexItem].point_type.indexItem;
    }
    else if (index_arg2.indexKind == 4)
    {
      //操作数1是常整数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Int)
        {
          pos2 = i;
          break;
        }
      }

    }
    else if (index_arg2.indexKind == 5)
    {
      //操作数1是常实数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Real)
        {
          pos2 = i;
          break;
        }
      }
    }
    else
    {
      //error;
    }

    TVal tval_temp = judege(symbol.table_type[pos1].tval, symbol.table_type[pos2].tval); // 变量一 变量二 仲裁后的类型

    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval = tval_temp)
      {
        index_tval.indexItem = i;
        break;
      }

    }
    Node_Id_1 temp_id;
    temp_id.name = "t";
    name_make(symbol.num_t, temp_id.name);
    symbol.num_t++;
    temp_id.point_type = index_tval;
    temp_id.cat = v;
    Index_4D index_temp;
    index_temp.indexDeep = symbol.index_deep_now;
    index_temp.indexFunc = symbol.index_func_now;
    index_temp.indexKind = 3;
    index_temp.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size();
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(temp_id);
    stack_infer.push(index_temp);


    Index_4D index_result;
    index_result = stack_infer.top();

    quaternary_OR.op = index_op;
    quaternary_OR.arg1 = index_arg1;
    quaternary_OR.arg2 = index_arg2;
    quaternary_OR.result = index_result;
    sequence_temp.push_back(quaternary_OR);

  }
    break;
  case://Add->MINUS  Term
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_NOT;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == SUB)
      {
        index_op.indexItem = i;
        break;
      }
        
    }


    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_result;
    index_result = stack_infer.top();

    quaternary_NOT.op = index_op;
    quaternary_NOT.arg1 = index_arg1;
    quaternary_NOT.result = index_result;
    sequence_temp.push_back(quaternary_NOT);

  }
    break;
  case://Add->Term
    break;
  case://Term->Term  STAR  Factor
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_OR;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == MUL)
      {
        index_op.indexItem = i;
        break;
      }
        
    }

    Index_4D index_arg2;
    index_arg2 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_tval;
    index_tval.indexDeep = -1;
    index_tval.indexFunc = -1;
    index_tval.indexKind = 6;
    int pos1;
    int pos2;
    if (index_arg1.indexKind == 3)
    {
      pos1 = symbol.table_id_3[index_arg1.indexDeep][index_arg1.indexFunc].table_id_1[index_arg1.indexItem].point_type.indexItem;
    }
    else if (index_arg1.indexKind == 4)
    {
      //操作数1是常整数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Int)
        {
          pos1 = i;
          break;
        }
      }

    }
    else if (index_arg1.indexKind == 5)
    {
      //操作数1是常实数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Real)
        {
          pos1 = i;
          break;
        }
      }
    }
    else
    {
      //error;
    }
    if (index_arg2.indexKind == 3)
    {
      pos2 = symbol.table_id_3[index_arg2.indexDeep][index_arg2.indexFunc].table_id_1[index_arg2.indexItem].point_type.indexItem;
    }
    else if (index_arg2.indexKind == 4)
    {
      //操作数1是常整数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Int)
        {
          pos2 = i;
          break;
        }
      }

    }
    else if (index_arg2.indexKind == 5)
    {
      //操作数1是常实数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Real)
        {
          pos2 = i;
          break;
        }
      }
    }
    else
    {
      //error;
    }

    TVal tval_temp = judege(symbol.table_type[pos1].tval, symbol.table_type[pos2].tval); // 变量一 变量二 仲裁后的类型

    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval = tval_temp)
      {
        index_tval.indexItem = i;
        break;
      }

    }
    Node_Id_1 temp_id;
    temp_id.name = "t";
    name_make(symbol.num_t, temp_id.name);
    symbol.num_t++;
    temp_id.point_type = index_tval;
    temp_id.cat = v;
    Index_4D index_temp;
    index_temp.indexDeep = symbol.index_deep_now;
    index_temp.indexFunc = symbol.index_func_now;
    index_temp.indexKind = 3;
    index_temp.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size();
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(temp_id);
    stack_infer.push(index_temp);


    Index_4D index_result;
    index_result = stack_infer.top();

    quaternary_OR.op = index_op;
    quaternary_OR.arg1 = index_arg1;
    quaternary_OR.arg2 = index_arg2;
    quaternary_OR.result = index_result;
    sequence_temp.push_back(quaternary_OR);

  }
    break;
  case://Term->Term  DIV  Factor
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_OR;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 2;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == DIV)
      {
        index_op.indexItem = i;
        break;
      }
        
    }

    Index_4D index_arg2;
    index_arg2 = stack_infer.top();
    stack_infer.pop();

    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();

    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_tval;
    index_tval.indexDeep = -1;
    index_tval.indexFunc = -1;
    index_tval.indexKind = 6;
    int pos1;
    int pos2;
    if (index_arg1.indexKind == 3)
    {
      pos1 = symbol.table_id_3[index_arg1.indexDeep][index_arg1.indexFunc].table_id_1[index_arg1.indexItem].point_type.indexItem;
    }
    else if (index_arg1.indexKind == 4)
    {
      //操作数1是常整数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Int)
        {
          pos1 = i;
          break;
        }
      }

    }
    else if (index_arg1.indexKind == 5)
    {
      //操作数1是常实数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Real)
        {
          pos1 = i;
          break;
        }
      }
    }
    else
    {
      //error;
    }
    if (index_arg2.indexKind == 3)
    {
      pos2 = symbol.table_id_3[index_arg2.indexDeep][index_arg2.indexFunc].table_id_1[index_arg2.indexItem].point_type.indexItem;
    }
    else if (index_arg2.indexKind == 4)
    {
      //操作数1是常整数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Int)
        {
          pos2 = i;
          break;
        }
      }

    }
    else if (index_arg2.indexKind == 5)
    {
      //操作数1是常实数
      for (int i = 0; i < (int)symbol.table_type.size(); ++i)
      {
        if (symbol.table_type[i].tval == Real)
        {
          pos2 = i;
          break;
        }
      }
    }
    else
    {
      //error;
    }

    TVal tval_temp = judege(symbol.table_type[pos1].tval, symbol.table_type[pos2].tval); // 变量一 变量二 仲裁后的类型

    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval = tval_temp)
      {
        index_tval.indexItem = i;
        break;
      }

    }
    Node_Id_1 temp_id;
    temp_id.name = "t";
    name_make(symbol.num_t, temp_id.name);
    symbol.num_t++;
    temp_id.point_type = index_tval;
    temp_id.cat = v;
    Index_4D index_temp;
    index_temp.indexDeep = symbol.index_deep_now;
    index_temp.indexFunc = symbol.index_func_now;
    index_temp.indexKind = 3;
    index_temp.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size();
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(temp_id);
    stack_infer.push(index_temp);


    Index_4D index_result;
    index_result = stack_infer.top();

    quaternary_OR.op = index_op;
    quaternary_OR.arg1 = index_arg1;
    quaternary_OR.arg2 = index_arg2;
    quaternary_OR.result = index_result;
    sequence_temp.push_back(quaternary_OR);

  }
    break;
  case://Term->Factor 
    break;
  case://Factor->LP  Exp  RP
    break;
  case://Factor->LeftVal
    break;
  case://Factor->NUM
  {
    Index_4D index_num;
    index_num.indexDeep = -1;
    index_num.indexFunc = -1;
    index_num.indexKind = 4;
    int flag = 0;
    for (int i = 0; i < (int)symbol.table_num.size(); ++i)
    {
      if (symbol.table_num[i] == token_line[pos].lexeme_val.num)
      {
        //在常整数表中找到该num
        flag = 1;
        index_num.indexItem = i;
        break;
      }
      
    }
    if (flag == 0)
    {
      //在常整数表中没有查到该整数， 则把该整数插入到该表中并放在最后一位
      index_num.indexItem = (int)symbol.table_num.size();
      symbol.table_num.push_back(token_line[pos].lexeme_val.num);
    }
    stack_infer.push(index_num);
    
  }
    break;
  case://Factor->REAL
  {
    Index_4D index_real;
    index_real.indexDeep = -1;
    index_real.indexFunc = -1;
    index_real.indexKind = 5;
    int flag = 0;
    for (int i = 0; i < (int)symbol.table_real.size(); ++i)
    {
      if (symbol.table_real[i] == token_line[pos].lexeme_val.real)
      {
        //在常整数表中找到该num
        flag = 1;
        index_real.indexItem = i;
        break;
      }

    }
    if (flag == 0)
    {
      //在常整数表中没有查到该整数， 则把该整数插入到该表中并放在最后一位
      index_real.indexItem = (int)symbol.table_real.size();
      symbol.table_real.push_back(token_line[pos].lexeme_val.real);
    }
    stack_infer.push(index_real);

  }
    break;
  case://Factor->ID  LP  RP   用于函数
    break;
  case://Factor->ID  LP  Args  RP  用于函数（带参）
    break;
  case://LeftLabel->VOID
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
