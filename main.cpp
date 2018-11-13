#include<iostream>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include "lexical analyzer.h"
#include "grammatical analyzer.h"
//#include "LL.h"
using namespace std;

int main()
{
 
  //LL ll;
 
  /*
  
  for (int i = 0; i < (int)parser.character.size(); ++i)
  {
  cout << parser.character[i] << "\t" << parser.make_first(i)<<endl;

  }
  */
 

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
  
  getchar();
  
 
  return 0;
}


