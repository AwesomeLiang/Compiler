#include "grammatical analyzer.h"


//默认生成first集合的时候把空放在最后

///size t和 int的差别
index index_make(int s, string str)
{
  index temp;
  temp.state = s;
  temp.V = str;
  return temp;
}
string str_make(string str,int pos)
{
  string temp;
  //根据点在第pos个位置重写产生式
  
 
  for (int i = 0; i < pos; ++i)
  {
    temp += str[i];
    
  }
  temp += '@';
  
  for (int i = pos; i < (int)str.length(); ++i)
  {
    
    temp += str[i];
  }
  
  
  return temp;
}

int search_item(item t)
{
  return 1;
}


void readch()
{

}

Parser::Parser()
{
  //将空定义成$
  //还没有处理first （要能处理空）
  // 0:S->E 1 : E->E + T 2 : T->T*F 3 : F->(E)4 : F->id
  table_analyse.clear();
  grammar.clear();
  character.clear();
  kind.clear();
  items.clear();
  first.clear();
  grammar.push_back("S->E");
  grammar.push_back("E->E+T");
  grammar.push_back("E->T");
  //grammar.push_back("E->T+");
  grammar.push_back("T->T*F");
  grammar.push_back("T->F");
  grammar.push_back("F->(E)");
  grammar.push_back("F->id");
  first["S"] = "(/id/";
  first["E"] = "(/id/";
  first["T"] = "(/id/";
  first["F"] = "(/id/";
  first["id"] = "id/";
  first["("] = "(/";
  first[")"] = ")/";
  first["*"] = "*/";
  first["+"] = "+/";
  character.push_back("S");
  character.push_back("E");
  character.push_back("T");
  character.push_back("F");

  character.push_back("(");
  character.push_back(")");
  character.push_back("*");
  character.push_back("id");
  character.push_back("+");
  character.push_back("#");
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
  
  //状态一样的也加入了。。
  
}

//没有控制词法分析与语法分析的交互，什么时候词法分析器送来下一个，什么时候语法分析停止
void Parser::action()
{
  
  index temp;
  temp.state = stack_state.top();
  temp.V = ch;
  string A;
  switch (table_analyse[temp].V[0])
  {
  case 's': // move
    stack_state.push(table_analyse[temp].state);
    stack_op.push(ch);
    break;
  case 'r': // reduced  找到产生式，A->β ，连续弹栈length(β)次，接着把栈顶状态和A产生的新状态压入状态栈中，A压入符号栈中 当前输入符号不变
    
    int length;
     // table_analyse[temp].state 这个代表第几个产生式 ,grammar[table_analyse[temp].state] 就代表产生式 grammar[table_analyse[temp].state].length-3就是产生式右部即β的长度（“是否占字节）
    A = grammar[table_analyse[temp].state][0];
    //！！！！！！！！！！！！！！！！！！
    length = grammar[table_analyse[temp].state].length() - 3;//长度还有问题

    for (int i = 0; i < length; ++i)
    {
      stack_state.pop();
      stack_op.pop();
    }
    
    temp.state = stack_state.top();
    temp.V = A;
    if (table_analyse[temp].V[0] != 's')
      return;//error
    stack_state.push(table_analyse[temp].state);
    stack_op.push(A); // 考虑要不要压进去分隔符
    break;
  case 'a': // accept
    break;
  default:
    //error
    break;
  }
}

void Parser::items_make()
{
  int sum = 1;
  int order = 0;
  item temp;
  string str_temp;
  str_temp = "S->@E";
  temp.grammar_item.push_back(str_temp);
  str_temp = "#/";
  temp.tag_reduced.push_back(str_temp);
  items.push_back(CLOSURE(temp));
  temp = CLOSURE(temp);
  

  while (sum)
  {
    
    for (int j = 0; j < (int)character.size(); ++j)
    {
      temp = GOTO(order, character[j]);
      
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
  index temp1;
  for (int i = 0; i < (int)items.size(); ++i)
  {

    for (int j = 0; j < (int)character.size(); ++j)
    {
      temp1.state = i;
      temp1.V = character[j];
     
      table_analyse[temp1].V = "e";
      table_analyse[temp1].state = -1;
     
    }
  }
  
  for (int i = 0; i < (int)items.size(); ++i)
  {
    
    for (int j = 0 ; j < (int)items[i].grammar_item.size(); ++j)
    {
      if (items[i].grammar_item[j] == "S->E@" && items[i].tag_reduced[j] == "#/")
      {
        //接受状态，表里写s
        index temp;
        temp.state = i;
        temp.V = "#";
        table_analyse[temp].V = "a";
        table_analyse[temp].state = 0;
        
      }
       else if (items[i].grammar_item[j][items[i].grammar_item[j].length() - 1] == '@')
      {
         
        index temp;
        string temp_str;
        int k;
        int m = 0;
        for (k = 0; k < (int)items[i].tag_reduced[j].length(); ++k)
        {
          if (items[i].tag_reduced[j][k] == '/')
          {
            
            //temp_str 是tag中的各个终结符 ，起点是m m的算法是 0 .. k + 1
            //当substr的第二个参数为0是出现意外

            temp_str = items[i].tag_reduced[j].substr(m, k-m);
            
            for (int n = 0; n < (int)character.size(); ++n)
            {
              if (match(character[n], temp_str, 0) && kind[n] == 0)
              {
                
                //把终结符匹配后，把表格对应的栏目填好
                temp.state = i;
                temp.V = character[n]; 
                temp_str = items[i].grammar_item[j].substr(0, items[i].grammar_item[j].length() - 1);
                for (int p = 0; p < (int)grammar.size(); ++p)
                {
                  //找归约的语法是第几个
                  if (temp_str == grammar[p])
                  {
                    table_analyse[temp].state = p;
                    break;
                  }
                }
                table_analyse[temp].V = "r";
                break;
              }
            }
            m = k + 1;
          }
          
        }
        
        
      }
      
    }
    for (int j = 0; j < (int)character.size(); ++j)
    {
      item temp_item;
      index temp_index;
      int temp_int;
      temp_item = GOTO(i, character[j]);
      if (in_items(temp_item, temp_int))
      {
        temp_index.state = i;
        temp_index.V = character[j];
        table_analyse[temp_index].state = temp_int;
        table_analyse[temp_index].V = "s";
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

string Parser::mfirst(string str,string add_str)
{
 
  int from = 0;
  string mystr;
  for (int i = 0; i < (int)character.size(); ++i)
  {
    if (match(character[i], str, from))
    {
      if (kind[i] == 0)
      {
        
        mystr += character[i];
        mystr += '/';
        break;
      }
      if (kind[i] == 1)
      {
        
        int flag = 0;
        string temp_str;

        if (first[character[i]].empty())
        {
          
          first[character[i]] = make_first(i);
        }
        for (int j = 0; j < (int)first[character[i]].length(); ++j)
        {
          //查找first集合里是否有空存在
          
          if (first[character[i]][j] == '$')
          {
            if (j == character[i].length() - 2)
            {
              //如果空在最后，那么删除空和/
              for (int k = 0; k < j; ++k)
              {
                temp_str += character[i][k];
              }
              
              character[i] = temp_str;
            }
            else
            { // 否则把$后面的东西提前
              
              for (int k = 0; k < j; ++k)
              {
                temp_str[k] = character[i][k];
              }
              for (int k = j; k < (int)character[i].length() - 2; ++k)
              {
                temp_str[k] = character[i][k + 2];
              }
              character[i] = temp_str;
            }

            flag = 1;
            break;
          }
          
        }
        if (flag == 1)
        {
          //first集合里有空，那么延展下去
          from += (int)character[i].length() + 1;
          i = 0;
          mystr += temp_str;
          mystr += '/';
          if (from == (int)str.length())
          {
            //如果拓展到最后还是有空存在，就把后缀 tag加入
            mystr += add_str;
            break;
          }
        }
        else
        {
          mystr += first[str];
        }
      }
    }
  }

  return string(mystr);
}

string Parser::make_first(int num)
{
  
  string sfirst;
  if (kind[num] == 0)
    return character[num];
  for (int i = 0; i < (int)grammar.size(); ++i)
  {
    int j;
    for (j = 0; j < (int)grammar[i].length(); ++j)
    {
      if (grammar[i][j] == '-')
        break;
    }
    if (grammar[i].substr(0, j) == character[num])
    {
      string temp = grammar[i];
      next_str(temp, j + 2);
     
      int k;
      for ( k = 0; k < (int)character.size(); ++k)
      {
        if (temp == character[k])
        {
          break;
        }

      }
      if (kind[k] == 0)
      {
        int flag = 0;
        for (int m = 0; m <(int)sfirst.size(); ++m)
        {
          if (match(character[k],sfirst,m) && sfirst[m+character[k].length()] == '/')
          {
            flag = 1;
            break;
          }

        }
        if (flag == 0)
          sfirst += character[k] + '/';

      }
      else
      {
        int temp_flag = 0;
        if (!first[character[k]].empty())
        {
         
          int temp_n = 0;
          string temp_str;
          for (int n = 0; n < (int)first[character[k]].length();n++ )
          {
            if (first[character[k]][n] == '/')
            {
              temp_str = first[character[k]].substr(temp_n, n - temp_n);
              temp_n = n + 1;
              int flag = 0;
              for (int m = 0; m <(int)sfirst.size(); ++k)
              {
                if (match(temp_str, sfirst, m) && sfirst[m + temp_str.length()] == '/')
                {
                  flag = 1;
                  break;
                }

              }
              if (flag == 0)
                sfirst += temp_str + '/';
            }
          }
          
        }
        else
        {
          if (character[num] == character[k])
            continue;
          for (int m = 0; m < (int)cash.size(); ++m)
          {
            if (character[k] == cash[m])
            {
              temp_flag = 1;
              break;
            }
              
          }
          if (temp_flag == 1)
            continue;
          cash.push_back(character[num]);
          sfirst += make_first(k);
          cash.pop_back();
        }
      }
    }
  }
  return sfirst;
}



bool Parser::next_str(string &str,int from,int k)
{
  if (from >= (int)str.length())
    return false;
  int flag = 0;
  int max_length = 0;
  int max_index = 0;
  
  for (int i = 0; i < (int)character.size(); ++i)
  {
    if (match(character[i], str, from) && kind[i] == k)
    {
      if (max_length < (int)character[i].length())    
      {
        max_length = character[i].length();
        max_index = i;
      }
      
      flag = 1;
      
    }
      
  }
  if (flag == 1)
  {

    str = character[max_index];
    return true;
  }
  return false;
}

bool Parser::next_str(string &str, int from)
{
  if (from >= (int)str.length())
    return false;
  int flag = 0;
  int max_length = 0;
  int max_index = 0;

  for (int i = 0; i < (int)character.size(); ++i)
  {
    if (match(character[i], str, from) )
    {
      if (max_length < (int)character[i].length())    
      {
        max_length = character[i].length();
        max_index = i;
      }

      flag = 1;

    }

  }
  if (flag == 1)
  {

    str = character[max_index];
    return true;
  }
  return false;
}

item Parser::CLOSURE(item t)
{
  //if(点后的一个符号是非终结符) （判断的前提是长度足够防止越界）
   //   先看是否已经在项集中 在就不用插入产生式
  //  在tag里加入fisrtβtag
  // 分词，将first该词加入到tag里， 如果first第一个词可以为空 那么继续
  int sum = (int) t.grammar_item.size();
  
  int i = 0;
  while (sum)
  {
    int j;
    for ( j = 0; j < (int)t.grammar_item[i].length(); ++j)
    {
      if (t.grammar_item[i][j] == '@')
        break;
    }
    j++;
    if (j == t.grammar_item[i].length())
    {
      //判断点是否在最后也就是 点后是否还有符号
      sum--;
      i++;
      continue;
    }
    int flag = 1;
   

    string str_temp = t.grammar_item[i]; //str_temp是项目集中的一个产生式
    if (next_str(str_temp, j,1)) //判断点后的符号是不是非终极符，若不是则该产生式不需要拓展，换一个产生式 且str_temp 成了点后的第一个符号
    {
      string new_str;
      //点后的一个符号是非终结符
      //把以该非终结符为左部的产生式加入到项目集中
      for (int k = 0; k < (int)grammar.size(); ++k)
      {
        if (match(str_temp, grammar[k], 0)) //找到点后符号为左部的产生式
        {
         
          new_str = str_make(grammar[k], (int)str_temp.length() + 2 /*str_temp.length()+2 是<- 后的一个字符的开始的位置*/);
          //new_str 是 grammar[k]这个产生式在右部前加入点后的产生式
          flag = 1;
          int p;

          for ( p = 0; p < (int)t.grammar_item.size(); ++p)
          {
            
            if (match(new_str, t.grammar_item[p], 0)) //用new_str == t.grammar_item[p] 替代
            {
              //判断新产生式是不是已经在项目集中，若在则不需要插入，只需要增加tag
              flag = 0;
              break;
            }
          }
          
          if (flag == 1)
          {
            //新产生式不在原项目集中


            string st = t.grammar_item[i];//需要判断 str_temp 后是否还有符号
            
            if (j + (int)str_temp.length() == st.length())//str_temp后无符号
            {
              //str_temp后无符号则直接把t.grammar_item[i]这个产生式的后缀当作新产生式的后缀
              t.tag_reduced.push_back(t.tag_reduced[i]);
            }
            else
            {
              //否则把str_temp即点后符号后的串 （A->·βα后缀）的α+后缀这一个串的first集合当作新的后缀 
              st = t.grammar_item[i].substr(j + (int)str_temp.length());
              t.tag_reduced.push_back(mfirst(st, t.tag_reduced[i]));
            }
          
            //插入新的产生式，该项目集的产生式数量增加
            t.grammar_item.push_back(new_str);
            sum++;
          }
          else
          {
            //新产生式子在原项目集中
            //项目集的第p个产生式是左部为点后符号，于是只要将first(后缀+α)加入到tag里，同时要防止重复
            
            new_str = t.grammar_item[i];
            string str_first;
            if (next_str(new_str, j + (int)str_temp.length()))
            {
              str_first = mfirst(new_str, t.tag_reduced[i]);
            }
            else
            {
              str_first = t.tag_reduced[i];
            }

            
            int temp_o = 0;
            for (int o = 0; o < (int)str_first.length(); ++o)
            {
              string temp_str_first;
              int flag5 = 0;
              if (str_first[o] == '/')
              {
                temp_str_first = str_first.substr(temp_o, o - temp_o);
                int n = 0;
                int temp_m = 0;

                for (int m = 0; m < (int)t.tag_reduced[p].length(); ++m)
                {
                  string temp_str_tag;
                  if (t.tag_reduced[p][m] == '/')
                  {
                    temp_str_tag = t.tag_reduced[p].substr(temp_m, m - temp_m);
                    if (temp_str_tag == temp_str_first)
                    {
                      flag5 = 1;
                      break;
                    }
                    temp_m = m + 1;
                  }
                }
              
                
                if (flag5 == 0)
                {
                  //说明里面没有这个终结符
                  t.tag_reduced[p] += mfirst(new_str, t.tag_reduced[i]);        //是否是//
                }

                temp_o = o + 1;
              }
            }
            
           
          }
        }



      }
    }
    i++;
    sum--;
    
    /*
    for (int k = 0; k < (int)grammar.size(); ++k)
    {
      flag = 1;
      int p;
      for (p = 0; p < (int)grammar[k].length(); ++p)
      {
        if (grammar[k][p] == '<'  && grammar[k][p + 1] == '-') //可能会出bug，若->放到左部就会意外判定
          break;
      }
      if (p > (int)t.grammar_item[i].length() - j)
        continue;
      for (int m = 0; m < p; ++m)
      {
        if (t.grammar_item[i][j + k] != grammar[k][m])
        {
          flag = 0;
          break;
        }
        
      }
      if (flag == 1)
      {
        int m;
        string str;
        int temp_flag = 0;
        for ( m = 0; m < (int)grammar[k].length(); ++m)
        {
          if (grammar[k][m] == '<'  && grammar[k][m + 1] == '-') //可能会出bug，若->放到左部就会意外判定
            break;
        }
        m += 2;
        for (int n = 0; n < m; ++n)
        {
          str[n] = grammar[k][n];
        }
        str[m] = '@';
        for (int n = m; n < (int)grammar[k].length(); ++n)
        {
          str[m + 1] = grammar[k][n];
          m++;
        }
        int n;
        for ( n = 0; n < (int)t.grammar_item.size(); ++n)
        {
          if (str == grammar[n])
          {
            temp_flag = 1;
            break;
          }
        }
        if (temp_flag == 0)
        {
          t.grammar_item.push_back(str);
          string temp_str;
          if ((j + p) == t.grammar_item[i].length())
            t.tag_reduced.push_back(t.tag_reduced[i]);
          else
          {
            int flag1 = 1;
            for (int q = 0; q < (int)character.size(); ++q)
            {
              flag1 = 1;
              if (t.grammar_item[i].length() - j - p < character[q].length())
                continue;
              for (int w = 0; w < (int)character[q].length(); ++w)
              {
                if (t.grammar_item[i][j + p + w] != character[q][w])
                {
                  flag1 = 0;
                }
              }
              if (flag1 == 1)
              {
                temp_str = character[q];
                break;
              }
            }
            t.tag_reduced.push_back(first[temp_str]);
          }
        }
      }
    }
    sum--;
    i++;
    */
  }
  return item(t);
}

item Parser::GOTO(int index, string str)
{
  item temp;
  
  temp.grammar_item.clear();
  temp.tag_reduced.clear();
  for (int i = 0; i < (int)items[index].grammar_item.size(); ++i)
  {
    int j;
    int temp_j;
    for (j = 0; j < (int)items[index].grammar_item[i].length(); ++j)
    {
      if (items[index].grammar_item[i][j] == '@')
      {
        break;
      }
        
    }
    temp_j = j; 
    j++;
    
    //将str和点后的词进行比较
    if (match(str, items[index].grammar_item[i], j))
    {
      //cout << "match" << str <<" "<< items[index].grammar_item[i].substr(j)<<endl;
      //str和点后的词相同，交换点后的词和点的位置
      string str_temp;
      for (int k = 0; k < temp_j; ++k)
      {
        //temp_j是点的位置 ，把文法开头到点之前的东西全都复制
        str_temp += items[index].grammar_item[i][k];
      }
      str_temp += str;
      str_temp += '@';

      for (int k = j+str.length(); k < (int)items[index].grammar_item[i].length(); ++k)
      {
        str_temp += items[index].grammar_item[i][k];
      }
      temp.grammar_item.push_back(str_temp);
      temp.tag_reduced.push_back(items[index].tag_reduced[i]);
    }
    /*
    if ((int)items[index].grammar_item[i].length() - j < (int)str.length())
      continue;
    for (int k = 0;k <  (int)str.length(); ++k)
    {
      if (str[k] != items[index].grammar_item[i][j])
      {
        flag = 0;
        break;
      }
    }
    if (flag == 1)
    {


    }
    */
   
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
