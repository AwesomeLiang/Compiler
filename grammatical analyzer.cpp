#include "grammatical analyzer.h"


//改变时，注意$ #的位置，和character = # 或 $的地方会出错

//默认生成first集合的时候把空放在最后

//size t和 int的差别


void join(vector<int> &f1, vector<int> f2)
{
  for (int i = 0; i < (int)f2.size(); ++i)
  {
    int flag = 0;
    for (int j = 0; j < (int)f1.size(); ++j)
    {
      if (f2[i] == f1[j])
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      f1.push_back(f2[i]);
      
    }
  }
}


void readch()
{

}

Parser::Parser()
{
  //将空定义成$
  
 
  table_analyse.clear();
  grammar.clear();
  character.clear();
  kind.clear();
  items.clear();
  first.clear();
  line.clear();
  token_line.clear();
  success = 0;
  pos = 0;
  con = 1;


  
 /*
 vector<int> temp_grammar;
 temp_grammar.clear();
 temp_grammar.push_back(0);
 temp_grammar.push_back(1);
 grammar.push_back(temp_grammar);
 temp_grammar.clear();
 temp_grammar.push_back(1);
 temp_grammar.push_back(1);
 temp_grammar.push_back(8);
 temp_grammar.push_back(2);
 grammar.push_back(temp_grammar);
 temp_grammar.clear();
 temp_grammar.push_back(1);
 temp_grammar.push_back(2);
 grammar.push_back(temp_grammar);
 temp_grammar.clear();
 temp_grammar.push_back(2);
 temp_grammar.push_back(2);
 temp_grammar.push_back(6);
 temp_grammar.push_back(3);
 grammar.push_back(temp_grammar);
 temp_grammar.clear();
 temp_grammar.push_back(2);
 temp_grammar.push_back(3);
 grammar.push_back(temp_grammar);
 temp_grammar.clear();
 temp_grammar.push_back(3);
 temp_grammar.push_back(4);
 temp_grammar.push_back(1);
 temp_grammar.push_back(5);
 grammar.push_back(temp_grammar);
 temp_grammar.clear();
 temp_grammar.push_back(3);
 temp_grammar.push_back(7);
 grammar.push_back(temp_grammar);

 character.push_back("S");//0
 character.push_back("E");//1
 character.push_back("T");//2
 character.push_back("F");//3

 character.push_back("(");//4
 character.push_back(")");//5
 character.push_back("*");//6
 character.push_back("id");//7
 character.push_back("+");//8
 character.push_back("#");//9
 //定义11为空
 kind.push_back(1);
 kind.push_back(1);
 kind.push_back(1);
 kind.push_back(1);

 kind.push_back(0);
 kind.push_back(0);
 kind.push_back(0);
 kind.push_back(0);
 kind.push_back(0);
 kind.push_back(0);

 */
  
  

}


void Parser::action()
{
  
  
  stack_state.push(0);
  //stack_op.push(9);
  
  while (pos <= (int)line.size() - 1 && con == 1)
  {
   
    index temp_index;
    
    temp_index.state = stack_state.top();
   
    int t;
    for ( t = 0; t < (int)character.size(); ++t)
    {
      if (character[t] == line[pos])
        break;
    }
    temp_index.V = t;
   
    int A;
    switch (table_analyse[temp_index].V)
    {
    case 997: // move
      
      stack_state.push(table_analyse[temp_index].state);
      
      stack_op.push(t);
      pos++;
      break;
    case 999: // reduced  找到产生式，A->β ，连续弹栈length(β)次，接着把栈顶状态和A产生的新状态压入状态栈中，A压入符号栈中 当前输入符号不变

      infer.work(table_analyse[temp_index].state, token_line, pos);
      
      if (grammar[table_analyse[temp_index].state][1] != 8) // 8是$
      {
        int length;
        // table_analyse[temp].state 这个代表第几个产生式 ,grammar[table_analyse[temp].state] 就代表产生式 grammar[table_analyse[temp].state].length-3就是产生式右部即β的长度（“是否占字节）
        length = (int)grammar[table_analyse[temp_index].state].size() - 1;
        A = grammar[table_analyse[temp_index].state][0];
        //！！！！！！！！！！！！！！！！！！

        for (int i = 0; i < length; ++i)
        {
          stack_state.pop();
          stack_op.pop();
        }



        temp_index.state = stack_state.top();
        temp_index.V = A;
       
        if (table_analyse[temp_index].V != 997)
        {
          //error
          success = 0;
          con = 0;
          break;
        }

        stack_state.push(table_analyse[temp_index].state);
      
        stack_op.push(A);
      }
      else
      {
        //要归约的产生式是A->空 不弹栈
        
        // table_analyse[temp].state 这个代表第几个产生式 ,grammar[table_analyse[temp].state] 就代表产生式 grammar[table_analyse[temp].state].length-3就是产生式右部即β的长度（“是否占字节）
        int length;
        length = (int)grammar[table_analyse[temp_index].state].size() - 1;
        A = grammar[table_analyse[temp_index].state][0];
        //！！！！！！！！！！！！！！！！！！

        



        temp_index.state = stack_state.top();
        temp_index.V = A;
        if (table_analyse[temp_index].V != 997)
        {
          //error
          success = 0;
          con = 0;
          break;
        }

        stack_state.push(table_analyse[temp_index].state);
        
        stack_op.push(A);
      }
      
      break;
    case 998: // accept
      pos++;
      success = 1;
      break;
    case 1000: // error
      success = 0;
      con = 0;
      break;
    default:
      //error
      success = 0;
      con = 0;
      break;
    }
    if (success == 1 && pos != (int)line.size() )
    {
      
      success = 0;
      break;
    }
      
  }

  if (success == 1)
    cout << "yes"<<endl;
  else cout << "no"<<endl;

}

void Parser::init(vector<vector<int>> g, vector<tag> c, vector<int> k, vector<tag> l,vector<Token> t)
{
  grammar = g;
  character = c;
  kind = k;
  line = l;
  token_line = t;
}

void Parser::items_make()
{
  int sum = 1;
  int order = 0;
  item temp;
  ip temp_ip;
  vector<int> temp_tag;

  temp_tag.push_back(9);//9是#
  temp_ip.index_grammar = 0;
  temp_ip.pos_point = 1;
  temp.grammar_item.push_back(temp_ip);
  //str_temp = "#/" str_temp;
  temp.tag_reduced.push_back(temp_tag);
  items.push_back(CLOSURE(temp));
  temp = CLOSURE(temp);
  

  while (sum)
  {
    
    for (int j = 0; j < (int)character.size(); ++j)
    {
      if (character[j] == (tag)8)//tag(8)是$
        continue;
      temp = GOTO(order, j);
      
      if (!temp.grammar_item.empty() && !in_items(temp))
      {
        items.push_back(temp);
        sum++;
      }
    }
    order++;
    sum--;
  }
  
}

void Parser::table_make()
{
  vector<int> temp_tag;
  temp_tag.push_back(9);//9是#
  index temp1;
  for (int i = 0; i < (int)items.size(); ++i)
  {
    for (int j = 0; j < (int)character.size(); ++j)
    {
      temp1.state = i;
      temp1.V = j;

      table_analyse[temp1].V = 1000; //1000是e
      table_analyse[temp1].state = -1;
    }
    
  }
  
  for (int i = 0; i < (int)items.size(); ++i)
  {
    for (int j = 0; j < (int)items[i].grammar_item.size(); ++j)
    {
      if (items[i].grammar_item[j].index_grammar == 0 && items[i].grammar_item[j].pos_point == 2 && items[i].tag_reduced[j] == temp_tag)
      {
        //接受状态，表里写a
        index temp;
        temp.state = i;
        temp.V = 9; //9是#
        table_analyse[temp].V = 998; // 998是a
        table_analyse[temp].state = 0;

      }
      else if (items[i].grammar_item[j].pos_point == (int)grammar[items[i].grammar_item[j].index_grammar].size() || grammar[items[i].grammar_item[j].index_grammar][1] == 8)//8 是 $
      {

        index temp;
        string temp_str;

        int m = 0;
        for (int k = 0; k < (int)items[i].tag_reduced[j].size(); ++k)
        {
          temp.state = i;
          temp.V = items[i].tag_reduced[j][k];
          table_analyse[temp].state = items[i].grammar_item[j].index_grammar;
          table_analyse[temp].V = 999; // 999是r；
        }

      }

    }
    for (int j = 0; j < (int)character.size(); ++j)
    {
      if (character[j] == (tag)8)//tag(8)是$
        continue;
      item temp_item;
      index temp_index;
      int temp_int;
      temp_item = GOTO(i, j);
      if (in_items(temp_item, temp_int))
      {
        temp_index.state = i;
        temp_index.V = j;
        table_analyse[temp_index].state = temp_int;
        table_analyse[temp_index].V = 997; //997是S
      }
    }
  }
  


}


bool Parser::match(string aim, string str, int from)
{
  if (str.length() - from < aim.length())
    return false;
  for (int i = 0; i < (int)aim.length(); ++i)
  {
    if (aim[i] != str[from + i])
      return false;
  }
  return true;
}


vector<int> Parser::mfirst(int from_first,int index_g,vector<int> add_tag)
{
 
  
  vector<int> mytag;
  mytag.clear();
  if (kind[grammar[index_g][from_first]] == 0)
  {
    //点后非终结符后的第一个文法符号是终结符，那么直接返回该终结符
    mytag.push_back(grammar[index_g][from_first]);
    return mytag;
  }//点后非终结符后的第一个文法符号是非终结符，那么求他的first集合，分别处理带空和不带空的情况
  else
  {
    
    vector<int> temp_first;
    int i;
    for ( i = from_first; i < (int)grammar[index_g].size(); ++i)
    {
      int temp_flag = 0;
      if (first[grammar[index_g][i]].empty())
      {
        first[grammar[index_g][i]] = make_first(grammar[index_g][i]);
        
      }
      temp_first = first[grammar[index_g][i]];
      for (int j = 0; j < (int)first[grammar[index_g][i]].size(); ++j)
      {
        if (first[grammar[index_g][i]][j] == 8) //8是$
        {

          vector<int>::iterator iter = temp_first.begin() + j; //可能出bug
          temp_first.erase(iter);
          temp_flag = 1;
          break;
        }
      }
      
      join(mytag, temp_first);
      if (temp_flag == 0)
      {
        //说明first中没空
        break;
      }
      
    }
    if (i == (int)grammar[index_g].size())
    {
      
      //空拓展到了最后，说明要把addtag也加入到mytag中
      
      join(mytag, add_tag);
    }
    return mytag;
  }
  
}

vector<int> Parser::make_first(int num)
{
  
  string sfirst;
  vector<int> temp_first;
  
  if (kind[num] == 0)
  {
    
    temp_first.push_back(num);
    return temp_first;
  }
  
  for (int i = 0; i < (int)grammar.size(); ++i)
  {
    if (grammar[i][0] == num)
    {
      //找到产生式的左部是要求的非终结符号,那么就找右部的第一个符号
      if (kind[grammar[i][1]] == 0)
      {
        if(!in_vector(grammar[i][1],temp_first))
          temp_first.push_back(grammar[i][1]);
      }
      else
      {
        //右部第一个符号是非终结符，防止递归
        if (!first[grammar[i][1]].empty())
        {
          join(temp_first, first[grammar[i][1]]);
        }
        else
        {
          if (num == grammar[i][1])
          {
            continue;
          }
          int temp_flag = 0;
          for (int j = 0; j < (int)cash.size(); ++j)
          {
            if (grammar[i][1] == cash[j])
            {
              temp_flag = 1;
              break;
            }
          }
          if (temp_flag == 1)
            continue;
          cash.push_back(num);
          join(temp_first, make_first(grammar[i][1]));
          cash.pop_back();
        }
      }
    }
  }
 
      
  return temp_first;
}


item Parser::CLOSURE(item t)
{
  //没有考虑点后是空的情况
  int sum = (int)t.grammar_item.size();
  int i = 0;
  while (sum)
  {

    //找到点的位置
    if (grammar[t.grammar_item[i].index_grammar][1] == 8)//8是$
    {
      sum--;
      i++;
      continue;
    }
    if (t.grammar_item[i].pos_point == (int)grammar[t.grammar_item[i].index_grammar].size())
    {
      //判断点是否在最后也就是 点后是否还有符号
      sum--;
      i++;
      continue;
    }
    int flag = 1;

    int afterpoint = grammar[t.grammar_item[i].index_grammar][t.grammar_item[i].pos_point];
    if (kind[afterpoint] == 1)
    {
      for (int j = 0; j < (int)grammar.size(); ++j)
      {
        if (grammar[j][0] == afterpoint)
        {
          ip temp_ip;
          temp_ip.index_grammar = j;
          temp_ip.pos_point = 1;
          int flag0 = 0;
          vector<int> temp_tag;
          temp_tag.clear();
          int k;
          
          
          
         
          //temp_tag的生成
          if (t.grammar_item[i].pos_point + 1 == grammar[t.grammar_item[i].index_grammar].size())
          {
            //若点后的非终极符是文法的最后一个符号,那么直接把该产生式的tag插入到新产生式中
            
            join(temp_tag, t.tag_reduced[i]);
          }
          else
          {




            join(temp_tag, mfirst(t.grammar_item[i].pos_point + 1, t.grammar_item[i].index_grammar, t.tag_reduced[i]));

          }
          

          for (k = 0; k < (int)t.grammar_item.size(); ++k)
          {

            if (t.grammar_item[k].index_grammar == temp_ip.index_grammar && t.grammar_item[k].pos_point == temp_ip.pos_point&&t.tag_reduced[k] == temp_tag )
            {
              //判断新产生式是不是已经在项目集中，若在则不需要插入，只需要增加tag
              
              flag0 = 1;
              break;

            }
          }

          if (flag0 != 1)
          {
            t.grammar_item.push_back(temp_ip);
            t.tag_reduced.push_back(temp_tag);
            sum++;

          }
         
         
        }
      }
    }

    

    i++;
    sum--;
  }
  for (int k = (int)t.grammar_item.size() - 1; k >= 0; --k)
  {
    for (int m = 0; m < k; ++m)
    {
      if (t.grammar_item[m].index_grammar == t.grammar_item[k].index_grammar && t.grammar_item[m].pos_point == t.grammar_item[k].pos_point)
      {
        join(t.tag_reduced[m], t.tag_reduced[k]);
        t.grammar_item.erase(t.grammar_item.begin() + k);
        t.tag_reduced.erase(t.tag_reduced.begin() + k);
        break;
      }
    }
  }
  
  return item(t);
}

item Parser::GOTO(int index, int index_str)
{
  
  item temp;
  
  temp.grammar_item.clear();
  temp.tag_reduced.clear();
  for (int i = 0; i < (int)items[index].grammar_item.size(); ++i)
  {
    
    
    if (items[index].grammar_item[i].pos_point == grammar[items[index].grammar_item[i].index_grammar].size())
    {
      continue;
    }
    int afterpoint = grammar[items[index].grammar_item[i].index_grammar][items[index].grammar_item[i].pos_point];
   
    if (afterpoint == index_str)
    {
      ip temp_ip;
      temp_ip.index_grammar = items[index].grammar_item[i].index_grammar;
      temp_ip.pos_point = items[index].grammar_item[i].pos_point + 1;
      temp.grammar_item.push_back(temp_ip);
      temp.tag_reduced.push_back(items[index].tag_reduced[i]);
    }
    
   
  }

  
  return item(CLOSURE(temp));
}

bool Parser::in_items(item t)
{
  for (int i = 0; i < (int)items.size(); ++i)
  {
    
    if (t.grammar_item == items[i].grammar_item && t.tag_reduced == items[i].tag_reduced)
    {
      
      return true;
    }
      
  }
  return false;
}
bool Parser::in_items(item t,int &n)
{
  for (int i = 0; i < (int)items.size(); ++i)
  {
    if (t.grammar_item == items[i].grammar_item && t.tag_reduced == items[i].tag_reduced)
    {
      n = i;
      return true;
    }
      
  }
  return false;
}
bool Parser::in_vector(int aim, vector<int> v)
{
  for (int i = 0; i < (int)v.size(); ++i)
  {
    if (v[i] == aim)
    {
      return true;
    }
  }
  return false;
}
