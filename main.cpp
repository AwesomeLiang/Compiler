#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include "lexical_analyzer.h"
#include "grammatical_analyzer.h"

//#include "LL.h"
//#include "recursion.h"
using namespace std;


void test(vector<vector<int>> &g, vector<tag> &c, vector<int> &k)
{
  //#的tag在lexical 需要修改 ， $的位置需要修改

  /*
  S->E;
  E -> T 1| E + T 2| E - T 3
  T -> F 4| T * F 5| T / F 6
  F -> ID 7| NUM 8| REAL 9|( E ) 10

  */
  
  c.push_back((tag)0);//0  S
  c.push_back((tag)1);//1  E
  c.push_back((tag)2);//2  T
  c.push_back((tag)3);//3  F
  c.push_back(ADD);//4  +
  c.push_back(SUB);//5  -
  c.push_back(MUL);//6  *
  c.push_back(DIV);//7  /
  c.push_back(VOID); // 8 $
  c.push_back(FINISH);//9 #
  c.push_back(REAL);//10  REAL
  c.push_back(LSP);//11  (
  c.push_back(RSP);//12  )
  c.push_back(NUM);//13  num
  c.push_back(ID);//14  id
  c.push_back((tag)4);


  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);


  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(1);





  vector<int> temp_grammar;

  temp_grammar.clear();
  temp_grammar.push_back(0);
  temp_grammar.push_back(1);
  

  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(2);
  g.push_back(temp_grammar);




  /*
  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(1);
  temp_grammar.push_back(4);
  temp_grammar.push_back(2);
  g.push_back(temp_grammar);
  */
  

  
  
  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(15);
  temp_grammar.push_back(1);
  temp_grammar.push_back(5);
  temp_grammar.push_back(2);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(3);
  g.push_back(temp_grammar);
  
  

  

  
  /*
  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(2);
  temp_grammar.push_back(6);
  temp_grammar.push_back(3);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(2);
  temp_grammar.push_back(7);
  temp_grammar.push_back(3);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(14);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(10);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(11);
  temp_grammar.push_back(1);
  temp_grammar.push_back(12);
  g.push_back(temp_grammar);
  */
 

  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(13);
  g.push_back(temp_grammar);


 
  
  
  
  temp_grammar.clear();
  temp_grammar.push_back(15);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);
  
  


  /*
  c.push_back((tag)0);//0  E
  c.push_back((tag)1);//1  E
  c.push_back((tag)2);//2  E
  c.push_back((tag)3);//3  E
  c.push_back((tag)4);//4  E
  c.push_back((tag)5);//5  E
  c.push_back(ADD);//6  E
  c.push_back(MUL);//7  E
  c.push_back((tag)8);//8  E
  c.push_back(FINISH);//9  E
  c.push_back(LSP);//10  E
  c.push_back(RSP);//11 E
  c.push_back(ID);//12  E

  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);

  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);
  k.push_back(0);

  vector<int> temp_grammar;
  temp_grammar.clear();
  temp_grammar.push_back(0);
  temp_grammar.push_back(1);
  g.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(2);
  temp_grammar.push_back(3);
  g.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(6);
  temp_grammar.push_back(2);
  temp_grammar.push_back(3);
  g.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(5);
  temp_grammar.push_back(4);
  g.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(7);
  temp_grammar.push_back(5);
  temp_grammar.push_back(4);
  g.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(12);
  g.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(10);
  temp_grammar.push_back(1);
  temp_grammar.push_back(11);
  g.push_back(temp_grammar);
  */
  
}

void runLr()
{
  /*
  Parser parser;
  parser.items_make();



  for (int i = 0; i < (int)parser.items.size(); ++i)
  {
  cout << "I" << i << " " << endl;
  for (int j = 0; j < (int)parser.items[i].grammar_item.size(); ++j)
  {
  for (int k = 0; k < (int)parser.grammar[parser.items[i].grammar_item[j].index_grammar].size(); ++k)
  {
  if (k == parser.items[i].grammar_item[j].pos_point)
  cout << "@";
  cout << parser.character[parser.grammar[parser.items[i].grammar_item[j].index_grammar][k]];
  if (k == 0)
  cout << "->";

  }
  if (parser.items[i].grammar_item[j].pos_point == (int)parser.grammar[parser.items[i].grammar_item[j].index_grammar].size())
  {
  cout << "@";
  }
  cout << endl;
  cout << "tag:";
  for (int k = 0; k < (int)parser.items[i].tag_reduced[j].size(); ++k)
  {
  cout << parser.character[parser.items[i].tag_reduced[j][k]] << '/';
  }
  cout << endl;

  }

  }
  parser.table_make();
  cout << "\t";
  index temp;
  for (int i = 0; i < (int)parser.character.size(); ++i)
  {
  cout << parser.character[i] << "\t";
  }
  cout << endl;
  for (int i = 0; i < (int)parser.items.size(); ++i)
  {
  cout << i << "\t";
  for (int j = 0; j < (int)parser.character.size(); ++j)
  {
  temp.state = i;
  temp.V = j;
  char ch;
  switch (parser.table_analyse[temp].V)
  {
  case 997:
  ch = 's';
  break;
  case 998:
  ch = 'a';
  break;
  case 999:
  ch = 'r';
  break;
  case 1000:
  ch = 'e';
  break;
  default:
  ch = 'e';
  break;
  }
  cout << "(" << ch << "," << parser.table_analyse[temp].state << ")\t";

  }
  cout << endl;
  }


  getchar();

  */
}
void runLr_new()
{
  /*
  string str;
  str = readFileIntoString("test.txt");
  cout << str << endl;
  Lexer lex;
  lex.line = str;

  Parser parser;

  vector<vector<int>> g;
  vector<tag> c;
  vector<int> k;
  vector<tag> l;
  vector<Token> token_line;
  while (lex.goon == 1)
  {
  Token temp;
  temp = lex.scan();
  token_line.push_back(temp);
  l.push_back(temp.lexeme_type);

  }



  test(g, c, k);
  parser.init(g, c, k, l, token_line);
  parser.items_make();
  for (int i = 0; i < (int)parser.items.size(); ++i)
  {
  cout << "I" << i << " " << endl;
  for (int j = 0; j < (int)parser.items[i].grammar_item.size(); ++j)
  {
  for (int k = 0; k < (int)parser.grammar[parser.items[i].grammar_item[j].index_grammar].size(); ++k)
  {
  if (k == parser.items[i].grammar_item[j].pos_point)
  cout << "@";
  cout << parser.character[parser.grammar[parser.items[i].grammar_item[j].index_grammar][k]];
  if (k == 0)
  cout << "->";

  }
  if (parser.items[i].grammar_item[j].pos_point == (int)parser.grammar[parser.items[i].grammar_item[j].index_grammar].size())
  {
  cout << "@";
  }
  cout << endl;
  cout << "tag:";
  for (int k = 0; k < (int)parser.items[i].tag_reduced[j].size(); ++k)
  {
  cout << parser.character[parser.items[i].tag_reduced[j][k]] << '/';
  }
  cout << endl;

  }

  }
  parser.table_make();
  cout << "\t";
  index temp;
  for (int i = 0; i < (int)parser.character.size(); ++i)
  {
  cout << parser.character[i] << "\t";
  }
  cout << endl;
  for (int i = 0; i < (int)parser.items.size(); ++i)
  {
  cout << i << "\t";
  for (int j = 0; j < (int)parser.character.size(); ++j)
  {
  temp.state = i;
  temp.V = j;
  char ch;
  switch (parser.table_analyse[temp].V)
  {
  case 997:
  ch = 's';
  break;
  case 998:
  ch = 'a';
  break;
  case 999:
  ch = 'r';
  break;
  case 1000:
  ch = 'e';
  break;
  default:
  ch = 'e';
  break;
  }
  cout << "(" << ch << "," << parser.table_analyse[temp].state << ")\t";

  }
  cout << endl;
  }

  parser.action();
  getchar();
  */
  

}
void runLL()
{
  /*
  string str;
  str = readFileIntoString("test.txt");
  cout << str << endl;
  Lexer lex;
  lex.line = str;
  LL ll;
  while (lex.goon == 1)
  {
    Token temp_token = lex.scan();
    ll.line.push_back(temp_token.lexeme_type);
    ll.token_line.push_back(temp_token);
  }

  if (ll.action() == 1)
    cout << "yes";
  else cout << "no";
  getchar();
  */
}


string readFileIntoString(string filename)
{
  ifstream ifile(filename);
  ostringstream buf;
  char ch;
  while (buf&&ifile.get(ch))
  {
    buf.put(ch);
  }
  return buf.str();
}

int main()
{
  string str;
  str = readFileIntoString("test.txt");
  cout << str << endl;
  Lexer lex;
  lex.line = str;

  Parser parser;

  vector<vector<int>> g;
  vector<tag> c;
  vector<int> k;
  vector<tag> l;
  vector<Token> token_line;
  while (lex.goon == 1)
  {
    Token temp;
    temp = lex.scan();
    token_line.push_back(temp);
    l.push_back(temp.lexeme_type);

  }



  test(g, c, k);
  parser.init(g, c, k, l, token_line);
  parser.items_make();
  for (int i = 0; i < (int)parser.items.size(); ++i)
  {
    cout << "I" << i << " " << endl;
    for (int j = 0; j < (int)parser.items[i].grammar_item.size(); ++j)
    {
      for (int k = 0; k < (int)parser.grammar[parser.items[i].grammar_item[j].index_grammar].size(); ++k)
      {
        if (k == parser.items[i].grammar_item[j].pos_point)
          cout << "@";
        cout << parser.character[parser.grammar[parser.items[i].grammar_item[j].index_grammar][k]];
        if (k == 0)
          cout << "->";

      }
      if (parser.items[i].grammar_item[j].pos_point == (int)parser.grammar[parser.items[i].grammar_item[j].index_grammar].size())
      {
        cout << "@";
      }
      cout << endl;
      cout << "tag:";
      for (int k = 0; k < (int)parser.items[i].tag_reduced[j].size(); ++k)
      {
        cout << parser.character[parser.items[i].tag_reduced[j][k]] << '/';
      }
      cout << endl;

    }

  }
  parser.table_make();
  cout << "\t";
  index temp;
  for (int i = 0; i < (int)parser.character.size(); ++i)
  {
    cout << parser.character[i] << "\t";
  }
  cout << endl;
  for (int i = 0; i < (int)parser.items.size(); ++i)
  {
    cout << i << "\t";
    for (int j = 0; j < (int)parser.character.size(); ++j)
    {
      temp.state = i;
      temp.V = j;
      char ch;
      switch (parser.table_analyse[temp].V)
      {
      case 997:
        ch = 's';
        break;
      case 998:
        ch = 'a';
        break;
      case 999:
        ch = 'r';
        break;
      case 1000:
        ch = 'e';
        break;
      default:
        ch = 'e';
        break;
      }
      cout << "(" << ch << "," << parser.table_analyse[temp].state << ")\t";

    }
    cout << endl;
  }

  parser.action();
  getchar();
  return 0;
}


