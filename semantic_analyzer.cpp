#include "semantic_analyzer.h"

//要求开始时addr 的index_length 都置为 - 1     !!!!!!!!!!

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
  if (length == 0)
  {
    str += '0';
    return;
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

void Infer::Increase_Off(Index_4D index_type, int & offset)
{
  
  switch (symbol.table_type[index_type.indexItem].tval)
  {
  case Int:
    offset += 4;
    break;
  case Real:
    offset += 8;
    break;
  case Char:
    offset += 2;
    break;
  case String:
    break;
  case Bool:
    offset += 1;
    break;
  case Array:
    break;
  case Struct:
  {
    int flag = 0;
    int indexDeep = symbol.index_deep_now;
    int indexFunc = symbol.index_func_now;
    while (!flag && indexDeep >= 0)
    {
     
      for (int i = 0; i < (int)symbol.table_id_3[indexDeep][indexFunc].table_id_1.size(); ++i)
      {
        if (symbol.table_id_3[indexDeep][indexFunc].table_id_1[i].point_type.indexItem == index_type.indexItem)
        {
          if (symbol.table_id_3[indexDeep][indexFunc].table_id_1[i].addr.length == -1)
          {
            //error  要求开始时index_length 都置为 -1
          }
          flag = 1;
          offset += symbol.table_id_3[indexDeep][indexFunc].table_id_1[i].addr.length;
          break;
        }
      }
      if (flag == 0)
      {
        int x1 = symbol.table_id_3[indexDeep][indexFunc].parent.indexDeep;
        int x2 = symbol.table_id_3[indexDeep][indexFunc].parent.indexFunc;
        indexDeep = x1;
        indexFunc = x2;
      }
    }
    if (flag == 0)
    {
      //error
    }
  }
    break;
  default:
    break;
  }
}


void Infer::work(int index_grammar, vector<Token> token_line, int pos)
{
  
  pos--;
  switch (index_grammar)
  {
  case 0: ////S->PROGRAM
    break;
  case 1:   //Program->labelTop ExtDefList
    break;
  case 2: //labelTop->VOID
  {

    symbol.index_deep_now = 0;
    symbol.index_func_now = 0;
    Node_Id_2 node_id_2;
    node_id_2.parent.indexDeep = -1;


    if (symbol.space[symbol.index_deep_now] == 0)
    {//未分配空间

      Node_Id_3 node_id_3;
      node_id_3.push_back(node_id_2);
      symbol.table_id_3.push_back(node_id_3);
      symbol.space[symbol.index_deep_now] = 1;

    }
    else
    {//在该动作中应该用不到

      symbol.table_id_3[symbol.index_deep_now].push_back(node_id_2);
    }


  }
  break;
  case 8:  //ExtDecList->VarDec
  {

    Index_4D index_id = stack_infer.top();
    symbol.table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].cat = v;

    stack_infer.pop();
  }
  break;
  case 9: //ExtDeclist->VarDec  ASSIGN Exp
  {
    quaternary quaternary_ASSIGN;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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
    quaternary_ASSIGN.op.init(index_op,symbol);
    quaternary_ASSIGN.arg1.init(index_arg1,symbol) ;
    quaternary_ASSIGN.result.init(index_result,symbol);
    sequence_temp.push_back(quaternary_ASSIGN);

  }
  break;
  case 10: //ExtDecList->ExtDecList  COMMA  VarDec
  {
    Index_4D index_id = stack_infer.top();
    symbol.table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].cat = v;
    stack_infer.pop();
  }
  break;
  case 11: //ExtDeclist->ExtDecList  COMMA  VarDec  ASSIGN Exp 处理后部分的VarDec  InitLable ASSIGN Exp       
  {
    quaternary quaternary_ASSIGN;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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
    quaternary_ASSIGN.op.init(index_op,symbol);
    quaternary_ASSIGN.arg1.init(index_arg1,symbol);
    quaternary_ASSIGN.result.init(index_result,symbol);
    sequence_temp.push_back(quaternary_ASSIGN);

  }
  break;
  case 12: //Specifier->TYPE 这一步是确定了定义的变量的类型
  {

    symbol.catalog = v;
    // symbol.show_TVal(symbol.table_type[symbol.type.indexItem].tval);
    // symbol.show_Cat(symbol.catalog);
  }
  break;
  case 13: //TYPE->INT
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
  case 14: //TYPE->DOUBLE
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
  case 15: // Specifier->StructSpecifier
  {
    symbol.catalog = v;
  }
  break;
  case 16: // StructSpecifier->STRUCT  OptTag  LC  DefList  RC 用于结构体的声明
  {//把从symbol.index_item_now +1 开始的个标识符表都加入到结构体表中

    symbol.mode = 0;

    symbol.table_type[stack_infer.top().indexItem].tpoint.point_struct = symbol.table_struct;
    symbol.type = stack_infer.top();
    stack_infer.pop();

    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1[symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size() - 1].addr.length = symbol.offset;
    symbol.offset = 0;
  }
  break;
  case 17: // StructSpecifier->STRUCT  Tag  用于结构体的定义
    break;
  case 18: // OptTag->ID
  {
    //addr没处理
    symbol.mode = 1;

    Node_Type new_type;
    new_type.tval = Struct;
    symbol.table_type.push_back(new_type);

    Index_4D index_type;
    index_type.indexDeep = -1;
    index_type.indexFunc = -1;
    index_type.indexKind = 6;
    index_type.indexItem = (int)symbol.table_type.size() - 1;
    stack_infer.push(index_type);
    symbol.type = index_type;


    Node_Id_1 node_id_1;
    node_id_1.cat = t;
    node_id_1.name = token_line[pos].lexeme_val.str;
    node_id_1.point_type = index_type;
    symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(node_id_1);


    symbol.offset = 0;

    symbol.table_struct.clear();
  }
  break;
  case 19: // OptTag->VOID
  {
    symbol.mode = 1;
    Node_Type new_type;
    new_type.tval = Struct;
    symbol.table_type.push_back(new_type);
    Index_4D index_type;
    index_type.indexDeep = -1;
    index_type.indexFunc = -1;
    index_type.indexKind = 6;
    index_type.indexItem = (int)symbol.table_type.size() - 1;
    stack_infer.push(index_type);
    symbol.type = index_type;


    symbol.offset = 0;
    symbol.table_struct.clear();
  }
  break;

  case 20: // Tag->ID   没有解决自嵌套定义问题
  {
    int flag = 0;
    int indexDeep = 0;
    int indexFunc = 0;




    //对于新类型的定义只可能在全局作用域中
    for (int i = 0; i < (int)symbol.table_id_3[indexDeep][indexFunc].table_id_1.size(); ++i)
    {
      if (symbol.table_id_3[indexDeep][indexFunc].table_id_1[i].name == token_line[pos].lexeme_val.str)
      {
        symbol.type.indexDeep = -1;
        symbol.type.indexFunc = -1;
        symbol.type.indexKind = 6;
        symbol.type.indexItem = symbol.table_id_3[indexDeep][indexFunc].table_id_1[i].point_type.indexItem;
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      //error
      cout << "case 20 Tag->ID -------------kind no find" << endl;
    }
  }
  break;
  case 21: // VarDec->ID
  {


    if (symbol.mode == 0)
    {//该文法是用于标识符的声明 ， 所以应该先检查重定义

      for (int i = 0; i < (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size(); ++i)
      {
        if (symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1[i].name == token_line[pos].lexeme_val.str)
        {
          //error
          cout << "redefined!!!";
        }
      }

      Node_Id_1 new_node;
      new_node.name = token_line[pos].lexeme_val.str;
      new_node.point_type = symbol.type;
      new_node.cat = symbol.catalog;
      symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.push_back(new_node);
      Index_4D index_id;
      index_id.indexDeep = symbol.index_deep_now;
      index_id.indexFunc = symbol.index_func_now;
      index_id.indexKind = 3;
      index_id.indexItem = (int)symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].table_id_1.size() - 1;
      stack_infer.push(index_id);
      //symbol.stack_node_id.push(new_node);// 忘了有什么用 !!!!!!!!!
    }
    else if(symbol.mode == 1)
    {//没考虑结构体自嵌套定义出错


      for (int i = 0; i < (int)symbol.table_struct.size(); ++i)
      {

        if (symbol.table_struct[i].dname == token_line[pos].lexeme_val.str)
        {
          //error;
          cout << "case 21 dname redefined" << endl;
        }
      }
      Node_Struct node_struct;
      node_struct.dname = token_line[pos].lexeme_val.str;
      node_struct.offset = symbol.offset;
      node_struct.index_tp = symbol.type;
      Increase_Off(symbol.type, symbol.offset);
      symbol.table_struct.push_back(node_struct);

    }
    else if (symbol.mode == 2)
    {
      Node_Param node_param;
      node_param.pname = token_line[pos].lexeme_val.str;
      node_param.pcat = symbol.catalog;
      node_param.ptype = symbol.type;
      symbol.table_param.push_back(node_param);
      symbol.num_f++;

    }

  }
  break;
  case 23: //FunDec->VarDec catF LP  VarList  RP   
  {
    Node_Process node_process;
    node_process.level = 1;
    node_process.numf = symbol.num_f;
    symbol.num_f = 0;
    //off是3是活动记录决定的
    node_process.off = 3;          
    node_process.vparam = symbol.table_param;

    Index_4D index_func = stack_infer.top();
    symbol.table_id_3[index_func.indexDeep][index_func.indexFunc].table_id_1[index_func.indexItem].addr.point_process = node_process;
   
    Index_4D index_id = stack_infer.top();
    symbol.table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].addr.point_process.entry = (int)sequence_temp.size();

    stack_infer.pop();               
  }
    break;
  case 24: // catF->VOID
  {
    symbol.num_f = 0;
    Index_4D index_id = stack_infer.top();
    symbol.table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].cat = f;
    vector<Node_Param> v;
    symbol.table_param = v;


  }
  break;
  case 25://FunDec->VarDec catF LP  RP
  {
    Node_Process node_process;
    node_process.level = 1;
    node_process.numf = symbol.num_f;
    symbol.num_f = 0;
    node_process.off = 3;//固定的
    node_process.vparam = symbol.table_param;

    Index_4D index_func = stack_infer.top();
    symbol.table_id_3[index_func.indexDeep][index_func.indexFunc].table_id_1[index_func.indexItem].addr.point_process = node_process;

    Index_4D index_id = stack_infer.top();
    symbol.table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].addr.point_process.entry = (int)sequence_temp.size();
    stack_infer.pop();//弹出函数名
  }
  break;
  case 26://VarList->VarList  COMMA  ParamDec
    break;
  case 27://VarList->ParamDec
    break;
  case 28://ParamDec->Specifier catVn VarDec
  {
    symbol.mode = 0;
  }
  break;
  case 29: //catVn->VOID
  {
    symbol.catalog = vn;
    symbol.mode = 2; // mode2 用来处理函数
  }
  break;

  case 30:  //CompSt-> DeepInc LC DefList  StmtList  RC
  {
    int x1 = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexDeep;
    int x2 = symbol.table_id_3[symbol.index_deep_now][symbol.index_func_now].parent.indexFunc;
    symbol.index_deep_now = x1;
    symbol.index_func_now = x2;
  }
  break;
  case 31: // DeepInc->VOID
  {

    Node_Id_2 node_id_2;
    node_id_2.parent.indexDeep = symbol.index_deep_now;
    node_id_2.parent.indexFunc = symbol.index_func_now;
    node_id_2.parent.indexKind = 3;
    symbol.index_deep_now++;



    if (symbol.space[symbol.index_deep_now] == 0)
    {
      //未分配空间
      Node_Id_3 node_id_3;
      node_id_3.push_back(node_id_2);
      symbol.table_id_3.push_back(node_id_3);
      symbol.space[symbol.index_deep_now] = 1;

    }
    else
    {
      symbol.table_id_3[symbol.index_deep_now].push_back(node_id_2);
    }
    symbol.index_func_now = (int)symbol.table_id_3[symbol.index_deep_now].size() - 1;

  }
    break;
  case 34://Stmt->Exp  SEMI
  {

    stack_infer.pop();

  }
    break;
  case 37://Stmt->IF  LP  Exp  RP  causeIF   Stmt  Label
    break;
  case 38: // causeIF->void
  {//<IF,EXP,Label1,Label2>

    Index_4D index_exp;
    index_exp = stack_infer.top();
    stack_infer.pop();
   
    Index_4D index_label;
    index_label.indexKind = 0;
    index_label.indexFunc = -1;
    index_label.indexDeep = -1;
    index_label.indexItem = sequence_temp.size();

    
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
    quaternary_if.op.init(index_if,symbol);
    quaternary_if.arg1.init(index_exp,symbol)  ;
    quaternary_if.result.init(index_label,symbol);
    sequence_temp.push_back(quaternary_if);

    
    stack_infer.push(index_label);
  }
    break;
  case 39://Label->void
  {//<Label,,,>

    Index_4D index_label = stack_infer.top();
    stack_infer.pop();

    int index_temp = index_label.indexItem;
    quaternary quaternary_LABEL;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == LABEL)
      {
        index_label.indexItem = i;
        break;
      }
    }
    quaternary_LABEL.op.init(index_label,symbol);
    sequence_temp.push_back(quaternary_LABEL);
    sequence_temp[index_temp].pointJmp = &sequence_temp[(int)sequence_temp.size()-1];
    
  }
  break;
  case 40://Stmt->IF  LP  Exp  RP  causeIF   Stmt bgoto ELSE  Label  Stmt  Label
    break;
  case 41://bgoto->void
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
    
    Index_4D index_label1;
    index_label1.indexKind = 0;
    index_label1.indexFunc = -1;
    index_label1.indexDeep = -1;
    index_label1.indexItem = sequence_temp.size();
    Index_4D index_temp;
    index_temp = stack_infer.top();
    stack_infer.pop();
    stack_infer.push(index_label1);
    stack_infer.push(index_temp);
    quaternary quaternary_bgoto;
    quaternary_bgoto.op.init(index_goto,symbol);
    quaternary_bgoto.arg1.init(index_label1,symbol);
    sequence_temp.push_back(quaternary_bgoto);
  }
  break;
  case 42: //Stmt->fLabel  WHILE  LP  Exp  RP  causeWHILE   Stmt fgoto Label  
    break;
  case 43://causeWHILE -> void
  {
    //<WHILE,EXP,Label1,Label2>
    Index_4D index_exp;
    index_exp = stack_infer.top();
    stack_infer.pop();

   
    Index_4D index_label1;
    index_label1.indexKind = 0;
    index_label1.indexFunc = -1;
    index_label1.indexDeep = -1;
    index_label1.indexItem = sequence_temp.size();


    Index_4D index_temp;
    index_temp = stack_infer.top();
    stack_infer.pop();
    //cout << index_temp.indexKind << endl;
    stack_infer.push(index_label1);
    stack_infer.push(index_temp);

    Index_4D index_while;
    index_while.indexKind = 0;
    index_while.indexDeep = -1;
    index_while.indexFunc = -1;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == WHILE)
      {
        index_while.indexItem = i;
        break;
      }

    }
    quaternary quaternary_WHILE;
    quaternary_WHILE.op.init(index_while,symbol);
    quaternary_WHILE.arg1.init(index_exp,symbol);
    quaternary_WHILE.result.init(index_label1,symbol);
    sequence_temp.push_back(quaternary_WHILE);

  }
  break;
  case 44: // fLabel-> void
  {
    Index_4D index_label;
    index_label.indexKind = 0;
    index_label.indexFunc = -1;
    index_label.indexDeep = -1;
    index_label.indexItem = sequence_temp.size();
    stack_infer.push(index_label);
    quaternary quaternary_LABEL;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == LABEL)
      {
        index_label.indexItem = i;
        break;
      }
    }
    quaternary_LABEL.op.init(index_label,symbol);
    sequence_temp.push_back(quaternary_LABEL);
  }
  break;
  case 45: // fgoto->void
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


    quaternary quaternary_GOTO;
    quaternary_GOTO.op.init(index_goto,symbol);
    quaternary_GOTO.arg1.init(index_temp,symbol);
    quaternary_GOTO.pointJmp = &sequence_temp[index_temp.indexItem];
   
    sequence_temp.push_back(quaternary_GOTO);
  }
  break;
  case 46://DefList->VOID
    break;
  case 47://DefList->DefList  Def
    break;
  case 48://Def->Specifier  DecList  SEMI
    break;
  case 49://DecList->Dec
    break;
  case 50://DecList->DecList  COMMA  Dec
    break;
  case 51://Dec->VarDec
  {
    if (symbol.mode == 0)
    {
      Index_4D index_id = stack_infer.top();
      symbol.table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].cat = v;

      stack_infer.pop();
    }
    else
    {

    }

  }
  break;
  case 52://Dec->VarDec    ASSIGNOP  Exp
  {
    quaternary quaternary_ASSIGN;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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
    quaternary_ASSIGN.op.init(index_op,symbol);
    quaternary_ASSIGN.arg1.init(index_arg1,symbol);
    quaternary_ASSIGN.result.init(index_result,symbol);
    sequence_temp.push_back(quaternary_ASSIGN);

  }
  break;
  case 53://Args->Args  COMMA  Exp
  {
    Index_4D index_exp = stack_infer.top();
    stack_infer.pop();
    Index_4D index_func = stack_infer.top();
    if (symbol.num_f >= symbol.table_id_3[0][0].table_id_1[index_func.indexItem].addr.point_process.numf)
    {
      cout << "case 53://Args->Args  COMMA  Exp-----------error too much num_f" << endl;
    }
    if (symbol.table_id_3[0][0].table_id_1[index_func.indexItem].addr.point_process.vparam[symbol.num_f].ptype.indexItem != symbol.getIdIndexType(index_exp).indexItem)
    {
      cout << "case 53://Args->Args  COMMA  Exp------------ error type" << endl;
    }
   
    quaternary quaternary_PARAM;
    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == PARAM)
      {
        index_op.indexItem = i;
        break;
      }

    }
    Index_4D index_param;
    index_param.indexKind = 8;
    index_param.indexDeep = 0;
    index_param.indexFunc = index_func.indexItem;
    index_param.indexItem = symbol.num_f;
    quaternary_PARAM.op.init(index_op,symbol);
    quaternary_PARAM.arg1.init(index_param, symbol);
    sequence_temp.push_back(quaternary_PARAM);
    //参数的解析 func为定义对应的函数 item为它在param表中的位置，8是种类
    symbol.num_f++;
  }
    break;
  case 54://Args->Exp
  {
    Index_4D index_exp = stack_infer.top();
    stack_infer.pop();
    Index_4D index_func = stack_infer.top();
    if (symbol.num_f >= symbol.table_id_3[0][0].table_id_1[index_func.indexItem].addr.point_process.numf)
    {
      cout << "case 54://Args->Exp-----------error too much num_f" << endl;
    }
    if (symbol.table_id_3[0][0].table_id_1[index_func.indexItem].addr.point_process.vparam[symbol.num_f].ptype.indexItem != symbol.getIdIndexType(index_exp).indexItem)
    {
      cout << "case 54://Args->Exp------------ error type" << endl;
    }
    
    quaternary quaternary_PARAM;
    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == PARAM)
      {
        index_op.indexItem = i;
        break;
      }

    }

    Index_4D index_param;
    index_param.indexKind = 8;
    index_param.indexDeep = 0;
    index_param.indexFunc = index_func.indexItem;
    index_param.indexItem = symbol.num_f;
    quaternary_PARAM.op.init(index_op, symbol);
    quaternary_PARAM.arg1.init(index_param, symbol);
    sequence_temp.push_back(quaternary_PARAM);
    //参数的解析 func为定义对应的函数 item为它在param表中的位置，8是种类
    symbol.num_f++;
  }
    break;
 
  case 55://Exp->LeftVal    ASSIGNOP  Exp
  {
    
    quaternary quaternary_ASSIGN;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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

    quaternary_ASSIGN.op.init(index_op,symbol);
   
    quaternary_ASSIGN.arg1.init(index_arg1,symbol);
    quaternary_ASSIGN.result.init(index_result,symbol);
    sequence_temp.push_back(quaternary_ASSIGN);
    
    

  }
  break;

  case 58://LeftVal->ID
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
      {//该标识符在上级作用域内


        int x1 = symbol.table_id_3[deep_temp][func_temp].parent.indexDeep;
        int x2 = symbol.table_id_3[deep_temp][func_temp].parent.indexFunc;
        deep_temp = x1;
        func_temp = x2;

      }
    }
    if (flag == 0)
    {//error; 该标识符未被定义就使用

      cout << "no defined!!!!!" << endl;
    }
    else
    {
      // cout << "find it" << endl;
      index_leftval.indexDeep = deep_temp;
      index_leftval.indexKind = 3;
      index_leftval.indexFunc = func_temp;
      index_leftval.indexItem = item_temp;

    }
    stack_infer.push(index_leftval);
  }
  break;
  case 61://OrRel->OrRel  OR  AndRel               !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_OR;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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

    switch (index_arg1.indexKind)
    {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:

    default:
      break;
    }

    //需要在这新产生一个临时变量放到符号表中并且压到栈中

    Index_4D index_bool;
    index_bool.indexDeep = -1;
    index_bool.indexFunc = -1;
    index_bool.indexKind = 6;
    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval == Bool)
      {
        cout << "find bool" << endl;
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


    quaternary_OR.op.init(index_op,symbol);
    quaternary_OR.arg1.init(index_arg1,symbol);
    quaternary_OR.arg2.init(index_arg2,symbol);
    quaternary_OR.result.init(index_result,symbol);
    sequence_temp.push_back(quaternary_OR);

  }
  break;
  case 63://AndRel->AndRel  AND  Rel              ！！！！！！！！！！！！！！！！！！！！
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_AND;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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
    TVal tval = symbol.getTVal(index_arg2);
    if (tval != Bool && tval != Int && tval != Real)
    {
      cout << "case 63://AndRel->AndRel  AND  Rel------------- error arg2 type error" << endl;
    }
    Index_4D index_arg1;
    index_arg1 = stack_infer.top();
    stack_infer.pop();
    tval = symbol.getTVal(index_arg1);
    if (tval != Bool && tval != Int && tval != Real)
    {
      cout << "case 63://AndRel->AndRel  AND  Rel------------- error arg2 type error" << endl;
    }
    //需要在这新产生一个临时变量放到符号表中并且压到栈中
    Index_4D index_bool;
    index_bool.indexDeep = -1;
    index_bool.indexFunc = -1;
    index_bool.indexKind = 6;
    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval == Bool)
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

    quaternary_AND.op.init(index_op,symbol);
    quaternary_AND.arg1.init(index_arg1,symbol) ;
    quaternary_AND.arg2.init(index_arg2,symbol);
    quaternary_AND.result.init(index_result,symbol);
    sequence_temp.push_back(quaternary_AND);

  }
  break;
  case 66://Rel->NOT  NotRel
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_NOT;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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
      if (symbol.table_type[i].tval == Bool)
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

    quaternary_NOT.op.init(index_op,symbol);
    quaternary_NOT.arg1.init(index_arg1,symbol);
    quaternary_NOT.result.init(index_result,symbol);
    sequence_temp.push_back(quaternary_NOT);

  }
  break;
  case 67://Add->Add  PLUS  Term
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_OR;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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


    TVal tval_temp = judege(symbol.getTVal(index_arg1), symbol.getTVal(index_arg2)); // 变量一 变量二 仲裁后的类型

    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval == tval_temp)
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

    quaternary_OR.op.init(index_op, symbol);
    quaternary_OR.arg1.init(index_arg1, symbol);
    quaternary_OR.result.init(index_result, symbol);
    sequence_temp.push_back(quaternary_OR);

  }
  break;
  case 68://Add->Add  MINUS  Term
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_ADD;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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

    TVal tval_temp = judege(symbol.getTVal(index_arg1), symbol.getTVal(index_arg2)); // 变量一 变量二 仲裁后的类型

    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval == tval_temp)
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

    quaternary_ADD.op.init(index_op, symbol);
    quaternary_ADD.arg1.init(index_arg1, symbol);
    quaternary_ADD.result.init(index_result, symbol);
    sequence_temp.push_back(quaternary_ADD);

  }
  break;
  case 69://Add->MINUS  Term
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_NOT;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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

    Index_4D index_tval;
    index_tval.indexDeep = -1;
    index_tval.indexFunc = -1;
    index_tval.indexKind = 6;
    int pos1;
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
    else if (index_arg1.indexKind == 7)
    {
      pos1 = symbol.findDnameLink(index_arg1);
      if (pos1 != 0 && pos1 != 1)
        cout << " case 69://Add->MINUS  Term-------------arg1 type error" << endl;
    }
    else
    {
      //error;
    }

    TVal tval_temp = symbol.table_type[pos1].tval;

    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval == tval_temp)
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

    quaternary_NOT.op.init(index_op, symbol);
    quaternary_NOT.arg1.init(index_arg1, symbol);
    quaternary_NOT.result.init(index_result, symbol);
    sequence_temp.push_back(quaternary_NOT);

  }
  break;

  case 71://Term->Term  STAR  Factor
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_MUL;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == MUL)
      {
        cout << "find mul" << endl;
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
    else if (index_arg2.indexKind == 7)
    {
      pos1 = symbol.findDnameLink(index_arg1);
      if (pos1 != 0 && pos1 != 1)
        cout << " case 71://Term->Term  STAR  Factor-------------arg1 type error" << endl;
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
    else if (index_arg2.indexKind == 7)
    {
      pos2 = symbol.findDnameLink(index_arg2);
      if (pos2 != 0 && pos2 != 1)
        cout << " case 71://Term->Term  STAR  Factor-------------arg2 type error" << endl;
    }
    else
    {
      //error;
    }

    TVal tval_temp = judege(symbol.table_type[pos1].tval, symbol.table_type[pos2].tval); // 变量一 变量二 仲裁后的类型

    for (int i = 0; i < (int)symbol.table_type.size(); ++i)
    {
      if (symbol.table_type[i].tval == tval_temp)
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

    quaternary_MUL.op.init(index_op, symbol);
    quaternary_MUL.arg1.init(index_arg1, symbol);
    quaternary_MUL.result.init(index_result, symbol);
    sequence_temp.push_back(quaternary_MUL);

  }
  break;
  case 72://Term->Term  DIV  Factor
  {
    //还需要把新产生的变量放到符号表中
    quaternary quaternary_DIV;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
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
      if (symbol.table_type[i].tval == tval_temp)
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

    quaternary_DIV.op.init(index_op, symbol);
    quaternary_DIV.arg1.init(index_arg1, symbol);
    quaternary_DIV.result.init(index_result, symbol);
    sequence_temp.push_back(quaternary_DIV);

  }
  break;

  case 76://Factor->NUM
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
    {//在常整数表中没有查到该整数， 则把该整数插入到该表中并放在最后一位

      index_num.indexItem = (int)symbol.table_num.size();
      symbol.table_num.push_back(token_line[pos].lexeme_val.num);
    }
    stack_infer.push(index_num);

  }
  break;
  case 77://Factor->REAL
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
        //在常实数表中找到该num
        flag = 1;
        index_real.indexItem = i;
        break;
      }

    }
    if (flag == 0)
    {//在常整数表中没有查到该整数， 则把该整数插入到该表中并放在最后一位

      index_real.indexItem = (int)symbol.table_real.size();
      symbol.table_real.push_back(token_line[pos].lexeme_val.real);
    }
    stack_infer.push(index_real);

  }
  break;
  case 78://Factor->FDec  LP  RP   用于函数
  {
    Index_4D index_func = stack_infer.top();
    symbol.num_f = 0;
    

    quaternary quaternary_CALL;

    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == CALL)
      {
        index_op.indexItem = i;
        break;
      }

    }
    quaternary_CALL.op.init(index_op,symbol);
    quaternary_CALL.arg1.init(index_func,symbol);
    sequence_temp.push_back(quaternary_CALL);
  }
    break;
  case 79://Factor->FDec  LP  Args  RP  用于函数（带参）
  {//先与函数定义时的信息相比较检查是否满足函数
    
    Index_4D index_func = stack_infer.top();
    
    if (symbol.num_f != symbol.table_id_3[0][0].table_id_1[index_func.indexItem].addr.point_process.numf)
    {
      cout << "case 79://Factor->FDec  LP  Args  RP-----------error num_f" << endl;
    }
    symbol.num_f = 0;
   
    
    quaternary quaternary_CALL;
    
    Index_4D index_op;
    index_op.indexDeep = -1;
    index_op.indexFunc = -1;
    index_op.indexKind = 0;
    for (int i = 0; i < (int)symbol.table_key.size(); ++i)
    {
      if (symbol.table_key[i] == CALL)
      {
        index_op.indexItem = i;
        break;
      }

    }
    quaternary_CALL.op.init(index_op, symbol);
    quaternary_CALL.arg1.init(index_func, symbol);
    sequence_temp.push_back(quaternary_CALL);
    
  }
    break;
  case 80://Leftval->SDec  POINT DnameList
  {
    stack_infer.pop();
    Index_4D index_struct;
    index_struct.indexDeep = -1;
    index_struct.indexFunc = -1;
    index_struct.indexKind = 7;
    index_struct.indexItem = (int)symbol.table_link.size() - 1;
    stack_infer.push(index_struct);
  }
  break;
  case 81://SDec->ID
  {
    Index_4D index_id = symbol.findId(token_line[pos].lexeme_val.str, Struct);

    vector<int> v;
    v.push_back(index_id.indexDeep);
    v.push_back(index_id.indexFunc);
    v.push_back(index_id.indexItem);
    symbol.table_link.push_back(v);
    Index_4D index_type = symbol.table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].point_type;
    stack_infer.push(index_type);
  }
  break;
  case 82://DnameList -> Dnamelist Point Dname

    break;
  case 83://DnameList->Dname
    break;
  case 84://Dname->ID
  {
    Index_4D index_type = stack_infer.top();
    stack_infer.pop();
    if (symbol.table_type[index_type.indexItem].tval != Struct)
    {
      cout << "case 84 error ! it's not a struct" << endl;
    }
    symbol.table_struct = symbol.table_type[index_type.indexItem].tpoint.point_struct;

    int index_dname = symbol.findDname(token_line[pos].lexeme_val.str);

    symbol.table_link[(int)symbol.table_link.size() - 1].push_back(index_dname);

    stack_infer.push(symbol.table_struct[index_dname].index_tp);

  }
  break;
  case 85: // Factor->SDec  POINT DnameList
  {
    stack_infer.pop();
    Index_4D index_struct;
    index_struct.indexDeep = -1;
    index_struct.indexFunc = -1;
    index_struct.indexKind = 7;
    index_struct.indexItem = (int)symbol.table_link.size() - 1;
    stack_infer.push(index_struct);
  }
  break;
  case 86:// FDec->ID
  {
    symbol.num_f = 0;
    for (int i = 0; i < (int)symbol.table_id_3[0][0].table_id_1.size(); ++i)
    {
      if (symbol.table_id_3[0][0].table_id_1[i].name == token_line[pos].lexeme_val.str)
      {
        Index_4D index_func;
        index_func.indexKind = 3;
        index_func.indexDeep = 0;
        index_func.indexFunc = 0;
        index_func.indexItem = i;
        stack_infer.push(index_func);
        return;
      }
    }

    cout << "case 86:// FDec->ID ------------- the func has't been defined" << endl;
  }
    break;
  /*
  case://NotRel->Factor
  break;

  case://OrRel->AndRel
  break;

  case://AndRel->Rel
  break;
  case://Rel->Rel  RELOP  Add            //需要完成但是还没想好
  break;
  case://Rel->Add
  break;

  */

  /*
  case://Exp->OrRel
  break;
  case://LeftVal->LeftVal  LB  Add  RB   用于数组
  break;

  case://Term->Factor
  break;
  case://Factor->LP  Exp  RP
  break;
  case://Factor->LeftVal
  break;
  case://Add->Term
  break;
  */
  /*
  case :   //ExtDefList->ExtDef  ExtDefList
  break;
  case :   //ExtDefList->VOID
  break;
  case 3:   //ExtDef->Specifier  ExtDecList  SEMI
  break;
  case 4:   //ExtDef->Specifier  SEMI  用于定义结构体
  break;
  case 5:  //ExtDef->Specifier  FunDec  CompSt
  break;


  case: //TYPE->ID
  {
  int flag = 0;
  int indexDeep = 0;
  int indexFunc = 0;
  int indexItem;
  //对于新类型的定义只可能在全局作用域中
  for (int i = 0; i < (int)symbol.table_id_3[indexDeep][indexFunc].table_id_1.size(); ++i)
  {
  if (symbol.table_id_3[indexDeep][indexFunc].table_id_1[i].name == token_line[pos].lexeme_val.str)
  {
  symbol.type.indexDeep = -1;
  symbol.type.indexFunc = -1;
  symbol.type.indexKind = 6;
  symbol.type.indexItem = symbol.table_id_3[indexDeep][indexFunc].table_id_1[i].point_type.indexItem;
  flag = 1;
  break;
  }
  }
  if (flag == 0)
  {
  //error
  }

  }
  break;



  case 18: // VarDec->VarDec  LB  INT  RB
  break;


  case://StmtList->VOID
  break;
  case://StmtList->StmtList  Stmt
  break;

  case://Stmt->CompSt
  break;
  case://Stmt->RETURN  Exp  SEMI
  break;





  case://InitLabel->VOID
  break;
 
  case://LeftLabel->VOID
  break;
  */


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

void Infer::showSequence()
{
  for (int i = 0; i < (int)sequence_temp.size(); ++i)
  {
    cout <<"("<< sequence_temp[i].op.kindNode << ",";
    switch (sequence_temp[i].op.kindNode)
    {
    case 0: // key
    {
      cout << sequence_temp[i].op.attributeNode.attributeKey << ")";
    }
      
      break;
    case 3://id
    {
      cout << sequence_temp[i].op.attributeNode.attributeId.name << ",";
      symbol.show_Cat(sequence_temp[i].op.attributeNode.attributeId.cat);
      cout << ",";
      symbol.show_TVal(symbol.table_type[sequence_temp[i].op.attributeNode.attributeId.point_type.indexItem].tval);
      cout << ")";
    }
      
      break;
    case 4://int
    {
      cout << sequence_temp[i].op.attributeNode.attributeInt<<")";
    }
      break;
    case 5://real
    {
      cout << sequence_temp[i].op.attributeNode.attributeReal << ")";
    }
      break;
    case 7://link
    {
      for (int i = 0; i < (int)sequence_temp[i].op.attributeNode.attributeLink.size(); ++i)
      {
        cout << sequence_temp[i].op.attributeNode.attributeLink[i] << " ";
      }
      cout << ")";
      
    }
      break;
    case 8://param
    {
      cout << sequence_temp[i].op.attributeNode.attributeParam.pname << ",";
      symbol.show_Cat(sequence_temp[i].op.attributeNode.attributeParam.pcat);
      cout << ",";
      symbol.show_TVal(symbol.table_type[sequence_temp[i].op.attributeNode.attributeParam.ptype.indexItem].tval);
      cout << "," << sequence_temp[i].op.attributeNode.attributeParam.poffset;
      cout << ")";
      
    }
      break;
    default:
      cout << "NULL)";
      break;
    }
    cout << '\t';

    cout << "(" << sequence_temp[i].arg1.kindNode << ",";
    switch (sequence_temp[i].arg1.kindNode)
    {
    case 0: // key
    {
      cout << sequence_temp[i].arg1.attributeNode.attributeKey << ")";
    }

    break;
    case 3://id
    {
      cout << sequence_temp[i].arg1.attributeNode.attributeId.name << ",";
      symbol.show_Cat(sequence_temp[i].arg1.attributeNode.attributeId.cat);
      cout << ",";
      symbol.show_TVal(symbol.table_type[sequence_temp[i].arg1.attributeNode.attributeId.point_type.indexItem].tval);
      cout << ")";
    }

    break;
    case 4://int
    {
      cout << sequence_temp[i].arg1.attributeNode.attributeInt << ")";
    }
    break;
    case 5://real
    {
      cout << sequence_temp[i].arg1.attributeNode.attributeReal << ")";
    }
    break;
    case 7://link
    {
      for (int i = 0; i < (int)sequence_temp[i].arg1.attributeNode.attributeLink.size(); ++i)
      {
        cout << sequence_temp[i].arg1.attributeNode.attributeLink[i] << " ";
      }
      cout << ")";

    }
    break;
    case 8://param
    {
      cout << sequence_temp[i].arg1.attributeNode.attributeParam.pname << ",";
      symbol.show_Cat(sequence_temp[i].arg1.attributeNode.attributeParam.pcat);
      cout << ",";
      symbol.show_TVal(symbol.table_type[sequence_temp[i].arg1.attributeNode.attributeParam.ptype.indexItem].tval);
      cout << "," << sequence_temp[i].arg1.attributeNode.attributeParam.poffset;
      cout << ")";

    }
    break;
    default:
      cout << "NULL)";
      break;
    }
    cout << '\t';

    cout << "(" << sequence_temp[i].arg2.kindNode << ",";
    switch (sequence_temp[i].arg2.kindNode)
    {
    case 0: // key
    {
      cout << sequence_temp[i].arg2.attributeNode.attributeKey << ")";
    }

    break;
    case 3://id
    {
      cout << sequence_temp[i].arg2.attributeNode.attributeId.name << ",";
      symbol.show_Cat(sequence_temp[i].arg2.attributeNode.attributeId.cat);
      cout << ",";
      symbol.show_TVal(symbol.table_type[sequence_temp[i].arg2.attributeNode.attributeId.point_type.indexItem].tval);
      cout << ")";
    }

    break;
    case 4://int
    {
      cout << sequence_temp[i].arg2.attributeNode.attributeInt << ")";
    }
    break;
    case 5://real
    {
      cout << sequence_temp[i].arg2.attributeNode.attributeReal << ")";
    }
    break;
    case 7://link
    {
      for (int i = 0; i < (int)sequence_temp[i].arg2.attributeNode.attributeLink.size(); ++i)
      {
        cout << sequence_temp[i].arg2.attributeNode.attributeLink[i] << " ";
      }
      cout << ")";

    }
    break;
    case 8://param
    {
      cout << sequence_temp[i].arg2.attributeNode.attributeParam.pname << ",";
      symbol.show_Cat(sequence_temp[i].arg2.attributeNode.attributeParam.pcat);
      cout << ",";
      symbol.show_TVal(symbol.table_type[sequence_temp[i].arg2.attributeNode.attributeParam.ptype.indexItem].tval);
      cout << "," << sequence_temp[i].arg2.attributeNode.attributeParam.poffset;
      cout << ")";

    }
    break;
    default:
      cout << "NULL)";
      break;
    }
    cout << '\t';

    cout << "(" << sequence_temp[i].result.kindNode << ",";
    switch (sequence_temp[i].result.kindNode)
    {
    case 0: // key
    {
      cout << sequence_temp[i].result.attributeNode.attributeKey << ")";
    }

    break;
    case 3://id
    {
      cout << sequence_temp[i].result.attributeNode.attributeId.name << ",";
      symbol.show_Cat(sequence_temp[i].result.attributeNode.attributeId.cat);
      cout << ",";
      symbol.show_TVal(symbol.table_type[sequence_temp[i].result.attributeNode.attributeId.point_type.indexItem].tval);
      cout << ")";
    }

    break;
    case 4://int
    {
      cout << sequence_temp[i].result.attributeNode.attributeInt << ")";
    }
    break;
    case 5://real
    {
      cout << sequence_temp[i].result.attributeNode.attributeReal << ")";
    }
    break;
    case 7://link
    {
      for (int i = 0; i < (int)sequence_temp[i].result.attributeNode.attributeLink.size(); ++i)
      {
        cout << sequence_temp[i].result.attributeNode.attributeLink[i] << " ";
      }
      cout << ")";

    }
    break;
    case 8://param
    {
      cout << sequence_temp[i].result.attributeNode.attributeParam.pname << ",";
      symbol.show_Cat(sequence_temp[i].result.attributeNode.attributeParam.pcat);
      cout << ",";
      symbol.show_TVal(symbol.table_type[sequence_temp[i].result.attributeNode.attributeParam.ptype.indexItem].tval);
      cout << "," << sequence_temp[i].result.attributeNode.attributeParam.poffset;
      cout << ")";

    }
    break;
    default:
      cout << "NULL)";
      break;
    }
    cout << endl;
  }
}

quaternary::quaternary()
{
  op.kindNode = -1;
  arg1.kindNode = -1;
  arg2.kindNode = -1;
  result.kindNode = -1;
}
