#include "lexical analyzer.h"
#include<math.h>

Token token_make(tag t, lexeme_value l, Token &T, int ind)
{
  T.lexeme_type = t;
  T.lexeme_val = l;
  T.index = ind;
  return T;
}

lexeme_value lexeme_str_make(string s, lexeme_value &l)
{
  l.str = s;
  return l;
}
lexeme_value lexeme_num_make(int n, lexeme_value &l)
{
  l.num = n;
  return l;
}
lexeme_value lexeme_real_make(double r, lexeme_value &l)
{
  l.real = r;
  return l;
}
lexeme_value lexeme_char_make(char ch, lexeme_value &l)
{
  l.str = "'";
  l.str += ch;
  l.str += '\'';
  return l;
}

/*void Lexer::insert(int Kind, string str, Token &tok, lexeme_value l, tag t)
{
switch (Kind)
{
case 0:
{

}
break;
case 1;
{

}break;
case 2:
{

}break;
case 3:
{

}break;
case 4:
{

}break;
default:
break;
}
}*/

void Lexer::insert_delimiter(string str, Token &tok, lexeme_value l, tag t)
{
  for (vector<string>::iterator iter = table_delimiter.begin(); iter != table_delimiter.end(); ++iter)
  {
    if (*iter == str)
    {
      token_make(t, lexeme_str_make(str, l), tok, iter - table_delimiter.begin());
      return;
    }

  }
  kind = 4; reserve(lexeme_str_make(str, l)); index_delimiter++;
  token_make(t, lexeme_str_make(str, l), tok, index_delimiter - 1);
}
void Lexer::insert_key(string str, Token &tok, lexeme_value l, tag t)
{
  for (vector<string>::iterator iter = table_key.begin(); iter != table_key.end(); ++iter)
  {
    if (*iter == str)
    {
      
      token_make(t, lexeme_str_make(str, l), tok, iter - table_key.begin());
      return;
    }

  }
 
  kind = 0; reserve(lexeme_str_make(str, l)); index_key++;
  token_make(t, lexeme_str_make(str, l), tok, index_key - 1);
}
void Lexer::insert_id(string str, Token &tok, lexeme_value l, tag t)
{
  for (vector<string>::iterator iter = table_id.begin(); iter != table_id.end(); ++iter)
  {
    if (*iter == str)
    {
      
      token_make(t, lexeme_str_make(str, l), tok, iter - table_id.begin());
      return;
    }

  }
  
  kind = 1; reserve(lexeme_str_make(str, l)); index_id++;
  token_make(t, lexeme_str_make(str, l), tok, index_id - 1);
}
void Lexer::insert_num(int str, Token &tok, lexeme_value l, tag t)
{
  for (vector<int>::iterator iter = table_num.begin(); iter != table_num.end(); ++iter)
  {
    if (*iter == str)
    {
    
      token_make(t, lexeme_num_make(str, l), tok, iter - table_num.begin());
      return;
    }

  }
  
  kind = 2; reserve(lexeme_num_make(str, l)); index_num++;
  token_make(t, lexeme_num_make(str, l), tok, index_num - 1);
}
void Lexer::insert_real(double str, Token &tok, lexeme_value l, tag t)
{
  for (vector<double>::iterator iter = table_real.begin(); iter != table_real.end(); ++iter)
  {
    if (*iter == str)
    {
   
      token_make(t, lexeme_real_make(str, l), tok, iter - table_real.begin());
      return;
    }

  }
  
  kind = 3; reserve(lexeme_real_make(str, l)); index_real++;
  token_make(t, lexeme_real_make(str, l), tok, index_real - 1);
}
void Lexer::insert_str(string str, Token &tok, lexeme_value l, tag t)
{
  for (vector<string>::iterator iter = table_str.begin(); iter != table_str.end(); ++iter)
  {
    if (*iter == str)
    {

      token_make(t, lexeme_str_make(str, l), tok, iter - table_str.begin());
      return;
    }

  }

  kind = 5; reserve(lexeme_str_make(str, l)); index_str++;
  token_make(t, lexeme_str_make(str, l), tok, index_str - 1);
}
void Lexer::insert_char(char str, Token &tok, lexeme_value l, tag t)
{
  for (vector<char>::iterator iter = table_char.begin(); iter != table_char.end(); ++iter)
  {
    if (*iter == str)
    {

      token_make(t, lexeme_char_make(str, l), tok, iter - table_char.begin());
      return;
    }

  }
  kind = 6; reserve(lexeme_char_make(str, l)); index_char++;
  token_make(t, lexeme_char_make(str, l), tok, index_char - 1);
}
double power(int x, int y)
{
  double sum = 1;
  if (y > 0)
  {
    while (y)
    {
      sum *= x*1.0;
      --y;
    }
  }
  else
  {
    //y <= 0
    while (y < 0)
    {
      sum /= x*1.0;
      ++y;
    }
  }

  return sum;
}

bool isDigit(char peek)
{
  if (peek >= '0' && peek <= '9')
    return true;
  return false;

}

bool isLetter(char peek)
{
  if ((peek >= 'a' && peek <= 'z') || (peek >= 'A' && peek <= 'Z') || (peek == '_'))
    return true;
  return false;
}

Token::Token()
{
}

/*
string tostr(int value)
{
//可以考虑转化为2进制逆序
string str;
int i;
i = value;
while (i)
{
str += i % 2 + '0';
i = i / 2;
}


return str;
}

double tofloat(string str)
{
//real 类 str->double 的解析
double value = 0;
int edge;
int i = 0;
double n = 0;
do
{
value = value * 2 + (int)str[i] - '0';
i++;
} while (str[i] != 'e');
i++;
if (str[i] == '+')
{
i++;
do
{
n = n * 2 + (int)str[i] - '0';
i++;
} while (str[i] != '#');
value = value*pow(10, n);
}
else
{
i++;
do
{
n = n * 2 + (int)str[i] - '0';
i++;
} while (str[i] != '#');
value = value/pow(10, n);
}
}
int toint(string str)
{
//NUM 类str -> int 解析
int value = 0;
int i = 0;
do
{
value = value * 2 + (int)str[i] - '0';
i++;
} while (str[i] != '#');
}

*/
Token::Token(tag t, lexeme_value s)
{
  lexeme_type = t;
  lexeme_val = s;
}

Lexer::Lexer()
{
  Token t;
  lexeme_value l;
  table_key.clear();
  table_id.clear();
  table_num.clear();
  table_real.clear();
  table_delimiter.clear();
  table_str.clear();
  table_char.clear();
  words.clear();
  num_line = 1;
  num_str = 0;
  goon = 1;
  peek = ' ';
  index_key = 0;
  index_id = 0;
  index_num = 0;
  index_real = 0;
  index_delimiter = 0;
  index_str = 0;
  index_char = 0;
  kind = -1;
  reserve(token_make(IF, lexeme_str_make("if", l), t, 0));
  reserve(token_make(ELSE, lexeme_str_make("else", l), t, 1));
  reserve(token_make(WHILE, lexeme_str_make("while", l), t, 2));
  reserve(token_make(DO, lexeme_str_make("do", l), t, 3));
  reserve(token_make(BREAK, lexeme_str_make("break", l), t, 4));
  reserve(token_make(TRUE, lexeme_str_make("true", l), t, 5));
  reserve(token_make(FALSE, lexeme_str_make("false", l), t, 6));
  reserve(token_make(INT, lexeme_str_make("int", l), t, 7));
  reserve(token_make(DOUBLE, lexeme_str_make("double", l), t, 8));
  reserve(token_make(STRING, lexeme_str_make("string", l), t, 9));
  reserve(token_make(CHAR, lexeme_str_make("char", l), t, 10));
  reserve(token_make(INCLUDE, lexeme_str_make("include", l), t, 11));
  reserve(token_make(GOTO, lexeme_str_make("goto", l), t, 12));
}

void Lexer::reserve(Token t)
{
  words.insert(pair<string, Token>(t.lexeme_val.str, t));
}

void Lexer::reserve(lexeme_value value)
{
  switch (kind)
  {
  case 0:
    table_key.push_back(value.str); break;
  case 1:
    table_id.push_back(value.str); break;
  case 2:
    table_num.push_back(value.num); break;
  case 3:
    table_real.push_back(value.real); break;
  case 4:
    table_delimiter.push_back(value.str); break;
  case 5:
    table_str.push_back(value.str); break;
  case 6:
    table_char.push_back(value.str[1]); break;
  default:
    break;
  }

}

void Lexer::readch()
{
  peek = line[num_str];
  // cout << "1 " << peek;
  num_str++;

}

bool Lexer::readch(char c)
{

  readch();
  if (peek != c)
    return false;
  peek = ' ';
  return true;
}

Token Lexer::scan()
{
  //分析一个词法单元

  Token tok;
  lexeme_value l;
  /*
  对空格换行符制表符的处理
  第一个读到的是分界符：
  第一个读到的是数字：
  第一个读到的是字母：

  */


  for (;; readch())
  {
   
    if (peek == ' ' || peek == '\t')
      continue;
    else if (peek == '\n')
    {

      num_line += 1;

    }
    else break;
  }

  
  switch (peek)
  {
  case('&'):
    if (readch('&')) { insert_delimiter("&&", tok, l, AND);  return tok; }
    else
    {
      insert_delimiter("&", tok, l, BITAND);  return tok;
    }
   
    if (readch('|')) { insert_delimiter("||", tok, l, OR);  return tok; }
    else
    {
      insert_delimiter("|", tok, l, BITOR);  return tok;
    }
   
  case('<'):
    if (readch('=')) { insert_delimiter("<=", tok, l, LE);  return tok; }
    else
    {
      insert_delimiter("<", tok, l, LT);  return tok;
    }
   
  case('>'):
    if (readch('=')) { insert_delimiter(">=", tok, l, GE);  return tok; }
    else
    {
      insert_delimiter(">", tok, l, GT);  return tok;
    }
    
  case('='):
    if (readch('=')) { insert_delimiter("==", tok, l, EQ);  return tok; }
    else
    {
      insert_delimiter("=", tok, l, ASSIGN);  return tok;
    }
   
  case('!'):
    if (readch('=')) { insert_delimiter("!=", tok, l, NE);  return tok; }
    else
    {
      insert_delimiter("!", tok, l, NOT);  return tok;
    }
   
  }
  if (peek == '.')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, POINT);
    peek = ' ';
    return tok;
  }
  if (peek == '(')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, LSP);
    peek = ' ';
    return tok;
  }
  if (peek == ')')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, RSP);
    peek = ' ';
    return tok;
  }
  if (peek == '[')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, LMP);
    peek = ' ';
    return tok;
  }
  if (peek == ']')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, RMP);
    peek = ' ';
    return tok;
  }
  if (peek == '{')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, LBP);
    peek = ' ';
    return tok;
  }
  if (peek == '}')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, RBP);
    peek = ' ';
    return tok;
  }
  if (peek == ';')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, SEMICOLON);
    peek = ' ';
    return tok;
  }
  if (peek == ',')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, COMMA);
    peek = ' ';
    return tok;
  }
  if (peek == '+')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, ADD);
    peek = ' ';
    return tok;
  }
  if (peek == '-')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, SUB);
    peek = ' ';
    return tok;
  }
  if (peek == '*')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, MUL);
    peek = ' ';
    return tok;
  }
  if (peek == '/')
  {
    string str;
    str += peek;
    insert_delimiter(str, tok, l, DIV);
    peek = ' ';
    return tok;
  }

  if (isDigit(peek))
  {
    string str;
    int val = 0; //尾数
    int t = 1; // 指数阶码的正负 
    int p = 0; //小数位数
    int n = 0; //（不带小数）指数阶码
    int m = 0; // 判断是否是实数

    if (peek == '0')
    {
      readch();
      if (isDigit(peek))
      {
        goon = 0;
        return token_make(ERROR, lexeme_str_make("error", l), tok, -1); //如果读了一个0后还读数字报错
      }

      else
      {
        if (peek == '.')
        {
          m = 1;
          readch();
          do
          {
            val = val * 10 + (int)(peek - '0');
            p++;
            readch();
          } while (isDigit(peek));

        }
        if (peek == 'e')
        {
          m = 1;
          readch();
          if (peek == '-')
          {
            t = -1;
            readch();
          }
          else if (peek == '+')
          {
            readch();
          }
          do
          {
            n += 10 * n + (int)(peek - '0');
            readch();
          } while (isDigit(peek));
        }
      }

    }
    else
    {
      do
      {
        val = val * 10 + (int)(peek - '0');
        readch();
      } while (isDigit(peek));
      if (peek == '.')
      {
        m = 1;
        readch();
        if (!isDigit(peek) && peek != 'e')
          return token_make(ERROR, lexeme_str_make("error", l), tok, -1);
        do
        {
          val = val * 10 + (int)(peek - '0');
          p++;
          readch();
        } while (isDigit(peek));

      }
      if (peek == 'e')
      {
        m = 1;
        readch();
        if (peek == '-')
        {
          t = -1;
          readch();
        }
        else if (peek == '+')
        {
          readch();
        }
        if (!isDigit(peek))
          return token_make(ERROR, lexeme_str_make("error", l), tok, -1);
        do
        {
          n += 10 * n + (int)(peek - '0');
          readch();
        } while (isDigit(peek));
      }
    }

    

    if (m == 1)
    {
      //实数
     
      insert_real(val*1.0*power(10, t*n - p), tok, l, REAL);  return tok;
    }
    else
    {
      //整数
      insert_num(val, tok, l, NUM);  return tok;

    }
    
  }

  
 

  if (isLetter(peek))
  {

    //如果接下来读的还是字母或者数字就加到缓冲区
    if (peek == '_')
    {
      peek = ' ';
      return token_make(ERROR, lexeme_str_make("error", l), tok, -1); //如果第一个字符是非字母那么就报错
    }
      
    string str1;
    str1 += peek;
    readch();

    while (isLetter(peek))
    {
      str1 += peek;
      readch();
    }
    
    //将缓冲区的字符串和关键字比较
    if (words.count(str1))
    {
      insert_key(str1, tok, l, words[str1].lexeme_type);  return tok;

    }
    else
    {

      insert_id(str1, tok, l, ID);  return tok;


    }


  }


  if (peek == '\'')
  {
    
    char temp;
    //没考虑转义字符
    readch();
    temp = peek;
    readch();
    if (peek != '\'')
    {
      while (peek != '\'')
      {
        readch();
      }
      peek = ' ';
      return token_make(ERROR, lexeme_str_make("error", l), tok, -1);
    }
     
    insert_char(temp, tok, l, CH); peek = ' '; return tok;
  }

  if (peek == '\"')
  {
    
    string temp ;
    //没考虑转义字符 只认为 字符串长度超过一行或者换行写为错误
    
    readch();
    while (peek != '\"')
    {
      temp += peek;
      if (peek == '\n')
      {
        while (peek != '\"')
        {
          readch();

        }
        peek = ' ';
        return token_make(ERROR, lexeme_str_make("error", l), tok, -1);
      }
      
      readch();
    }
    
    //cout << temp<<endl;
    insert_str(temp, tok, l, STRING); peek = ' '; return tok;
  }

  if (peek == '#')
  {
    goon = 0;
    return token_make(FINISH, lexeme_str_make("#", l), tok, -1);
  }


  token_make(tag(peek), lexeme_str_make(" ", l), tok, -1);
  peek = ' ';

  return Token(tok);

}

