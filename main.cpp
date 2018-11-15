#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include "lexical analyzer.h"
#include "grammatical analyzer.h"
//#include "LL.h"
//#include "recursion.h"
using namespace std;


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
  ll.line.push_back(lex.scan().lexeme_type);

  }

  if (ll.action() == 1)
  cout << "yes";
  else cout << "no";
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

  

  /*

  for (int i = 0; i < (int)parser.character.size(); ++i)
  {
  cout << parser.character[i] << "\t" << parser.make_first(i)<<endl;

  }

  Parser parser;
  parser.items_make();

  for (int i = 0; i < (int)parser.items.size(); ++i)
  {
  cout << "I" << i << " " << endl;
  for (int j = 0; j < (int)parser.items[i].grammar_item.size(); ++j)
  {
  cout << parser.items[i].grammar_item[j] << endl;
  cout << "tag" << parser.items[i].tag_reduced[j] << endl;
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
  temp.V = parser.character[j];
  cout << "(" << parser.table_analyse[temp].V << "," << parser.table_analyse[temp].state << ")\t";

  }
  cout << endl;
  }
  */
  /*
  string str;
  str = readFileIntoString("test.txt");
  cout << str << endl;
  Lexer lex;
  lex.line = str;
  LL ll;
  while (lex.goon == 1)
  {
  ll.line.push_back(lex.scan().lexeme_type);

  }
  
  if (ll.action() == 1)
  cout << "yes";
  else cout << "no";
  */
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
  
 
  return 0;
}


