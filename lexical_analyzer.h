#pragma once
#include<iostream>
#include<string>
#include<map>
#include<vector>


using namespace std;
/*
词法分析器要分析的语法类型：
1.数字串。（数字常量）
2.标识符。
3.关键字。
4.界限符。
5.字符串。 value为“ sdasa ”
6.字符。 value为‘a’
*/



typedef enum
{
  AND = 256, BASIC = 257, BREAK = 258, DO = 259, ELSE = 260,
  EQ = 261, FALSE = 262, GE = 263, ID = 264, IF = 265,
  INDEX = 266, LE = 267, MINUS = 268, NE = 269, INT = 270,
  OR = 271, DOUBLE = 272, TEMP = 273, TRUE = 274, WHILE = 275,
  NUM = 276, REAL = 277, BITAND = 278, BITOR = 279, LT = 280,
  GT = 281, NOT = 282, ASSIGN = 283, ERROR = 284, LSP = 285,/*左小括号'(' */
  RSP = 286/*右小括号')' */, LMP = 287/*左中括号'{' */, RMP = 288/*右中括号'}' */,
  RETURN = 289, SEMICOLON = 290,/*分号';' */ COMMA = 291/*逗号*/, LBP = 292, RBP = 293,
  CHAR = 294, STRING = 295, CH = 296, ADD = 297, SUB = 298, INCLUDE = 299, POINT = 300,
  MUL = 301, DIV = 302, FINISH = 303, GOTO = 304, VOID = 305, STRUCT = 306, CALL = 307,
  PARAM = 308, LABEL = 309
  //每次新加入关键字都需要在symbol的key里增加
} tag;
 
struct lexeme_value
{
  string str;
  double real;
  int num;
};


class Token
{
public:
  Token();
  Token(tag t, lexeme_value s);
  float toFloat();
  int toInt();
  tag lexeme_type;
  struct lexeme_value lexeme_val;
  int index;

  //考虑将 这个string 类型的换成结构体 放多种属性

};

class Lexer
{
public:
   int num_line;
   int num_str;
  string line;
  char peek;
  bool goon;
  map<string, Token> words;
  vector<string> table_key;
  vector<string> table_id;
  vector<int> table_num;
  vector<double> table_real;
  vector<string> table_delimiter;
  vector<string> table_str;
  vector<char>   table_char;
  int index_key;
  int index_id;
  int index_num;
  int index_real;
  int index_delimiter;
  int index_char;
  int index_str;
  int kind;
 

  Lexer();
  void insert(int Kind, string str, Token &tok, lexeme_value l, tag t);
  void insert_key(string str, Token &tok, lexeme_value l, tag t);
  void insert_id(string str, Token &tok, lexeme_value l, tag t);
  void insert_num(int str, Token &tok, lexeme_value l, tag t);
  void insert_real(double str, Token &tok, lexeme_value l, tag t);
  void insert_delimiter(string str, Token &tok, lexeme_value l,tag t);
  void insert_str(string str, Token &tok, lexeme_value l, tag t);
  void insert_char(char str, Token &tok, lexeme_value l, tag t);
  void reserve(lexeme_value value);
  void reserve(Token t);
  void readch();
  bool readch(char c);
  Token scan();
  
};
