#include "grammatical_analyzer.h"

void test1(vector<vector<int>> &g, vector<string> &c, vector<int> &k, vector<int> &l)
{
  /*
  E -> T Z ① {I,(}
  Z-> a T Z ② {a }|ε ③{),#}
  T -> F P ④ {I,(}
  P-> b F P ⑤{b}|ε⑥{a,),#}
  F -> i ⑦{I} | ( E ) ⑧{(}
  */

  /*
  l.push_back(10);
  l.push_back(10);
  l.push_back(12);
  l.push_back(6);
  l.push_back(12);
  l.push_back(11);
  l.push_back(6);
  l.push_back(12);
  l.push_back(11);
  l.push_back(6);
  l.push_back(12);
  l.push_back(9);

  c.push_back("S");//0  E
  c.push_back("E");//1  E
  c.push_back("T");//2  E
  c.push_back("Z");//3  E
  c.push_back("P");//4  E
  c.push_back("F");//5  E
  c.push_back("a");//6  E
  c.push_back("b");//7  E
  c.push_back("$");//8  E
  c.push_back("#");//9  E
  c.push_back("(");//10  E
  c.push_back(")");//11 E
  c.push_back("i");//12  E

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

void test2(vector<vector<int>> &g, vector<string> &c, vector<int> &k, vector<int> &l)
{
  /*
  Program ->ExtDefList
  ExtDefList->ExtDef ExtDefList|$ 
  ExtDef ->Specifier ExtDecList SEMI
  | Specifier SEMI
  | Specifier FunDec CompSt
  ExtDecList->VarDec
  | VarDec COMMA ExtDecList
  Specifier->TYPE
  VarDec->ID
  | VarDec LB NUM RB
  FunDec->ID LP VarList RP
  | ID LP RP
  VarList->ParamDec COMMA VarList
  | ParamDec
  ParamDec-> Specifier VarDec
  CompSt ->LC DefList StmtList RC
  StmtList ->Stmt StmtList
  |$ 
  Stmt->Exp SEMI
  | CompSt
  | RETURN Exp SEMI
  | IF LP Exp RP Stmt
  | IF LP Exp RP Stmt ELSE Stmt
  | WHILE LP Exp RP Stmt
  */
  
  /*
  l.push_back(7);
  l.push_back(10);
  l.push_back(11);


  l.push_back(9);

  c.push_back("Program");//0  E
  c.push_back("ExtDefList");//1  E
  c.push_back("ExtDef");//2  E
  c.push_back("Specifier");//3  E
  c.push_back("VarDec");//4  E
  c.push_back("ExtDecList");//5  E
  c.push_back("COMMA");//6  E
  c.push_back("TYPE");//7  E
  c.push_back("$");//8  E
  c.push_back("#");//9  E
  c.push_back("ID");//10  E
  c.push_back("SEMI");//11  E
  c.push_back("NUM");//12
  c.push_back("LB");//13
  c.push_back("RB");//14
  c.push_back("FunDec");//15
  c.push_back("CompSt");//16
  c.push_back("LP");//17
  c.push_back("RP");//18
  c.push_back("VarList");//19
  c.push_back("ParamDec");//20
  c.push_back("LC");//21
  c.push_back("RC");//22
  c.push_back("DefList");//23
  c.push_back("StmtList");//24
  c.push_back("Stmt");//25
  c.push_back("Exp");//26
  c.push_back("RETURN");//27
  c.push_back("IF");//28
  c.push_back("ELSE");//29
  c.push_back("WHILE");//30
  

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


  vector<int> temp_grammar;
  temp_grammar.clear();
  temp_grammar.push_back(0);
  temp_grammar.push_back(1);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(2);
  temp_grammar.push_back(1);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(3);
  temp_grammar.push_back(5);
  temp_grammar.push_back(11);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(4);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(4);
  temp_grammar.push_back(6);
  temp_grammar.push_back(5);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(7);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(10);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(13);
  temp_grammar.push_back(12);
  temp_grammar.push_back(14);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(3);
  temp_grammar.push_back(15);
  temp_grammar.push_back(16);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(15);
  temp_grammar.push_back(10);
  temp_grammar.push_back(17);
  temp_grammar.push_back(19);
  temp_grammar.push_back(18);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(15);
  temp_grammar.push_back(10);
  temp_grammar.push_back(17);
  temp_grammar.push_back(18);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(19);
  temp_grammar.push_back(20);
  temp_grammar.push_back(6);
  temp_grammar.push_back(19);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(19);
  temp_grammar.push_back(20);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(20);
  temp_grammar.push_back(3);
  temp_grammar.push_back(4);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(16);
  temp_grammar.push_back(21);
  temp_grammar.push_back(23);
  temp_grammar.push_back(24);
  temp_grammar.push_back(22);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(24);
  temp_grammar.push_back(25);
  temp_grammar.push_back(24);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(24);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(26);
  temp_grammar.push_back(11);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(16);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(27);
  temp_grammar.push_back(26);
  temp_grammar.push_back(11);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(28);
  temp_grammar.push_back(17);
  temp_grammar.push_back(26);
  temp_grammar.push_back(18);
  temp_grammar.push_back(25);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(28);
  temp_grammar.push_back(17);
  temp_grammar.push_back(26);
  temp_grammar.push_back(18);
  temp_grammar.push_back(25);
  temp_grammar.push_back(29);
  temp_grammar.push_back(25);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(30);
  temp_grammar.push_back(17);
  temp_grammar.push_back(26);
  temp_grammar.push_back(18);
  temp_grammar.push_back(25);
  g.push_back(temp_grammar);
  */
  
}

void test(vector<vector<int>> &g, vector<string> &c, vector<int> &k)
{
  /*
  Program ->ExtDefList
  ExtDefList->ExtDef ExtDefList|$ 
  ExtDef ->Specifier ExtDecList SEMI
  | Specifier SEMI
  | Specifier FunDec CompSt
  ExtDecList->VarDec
  | VarDec COMMA ExtDecList
  Specifier->TYPE
  VarDec->ID
  | VarDec LB NUM RB
  FunDec->ID LP VarList RP
  | ID LP RP
  VarList->ParamDec COMMA VarList
  | ParamDec
  ParamDec-> Specifier VarDec
  CompSt ->LC DefList StmtList RC
  StmtList ->Stmt StmtList
  |$ 
  Stmt->Exp SEMI
  | CompSt
  | RETURN Exp SEMI
  | IF LP Exp RP Stmt
  | IF LP Exp RP Stmt ELSE Stmt
  | WHILE LP Exp RP Stmt
  */

  /*
  l.push_back(7);
  l.push_back(10);
  l.push_back(11);
  l.push_back(7);
  l.push_back(10);
  l.push_back(17);
  l.push_back(7);
  l.push_back(10);
  l.push_back(6);
  l.push_back(7);
  l.push_back(10);
  l.push_back(18);
  l.push_back(21);
  l.push_back(23);
  l.push_back(30);
  l.push_back(17);
  l.push_back(26);
  l.push_back(18);
  l.push_back(25);
  l.push_back(22);


  l.push_back(9);
  */

  /*
  c.push_back("Program");//0  E
  c.push_back("ExtDefList");//1  E
  c.push_back("ExtDef");//2  E
  c.push_back("Specifier");//3  E
  c.push_back("VarDec");//4  E
  c.push_back("ExtDecList");//5  E
  c.push_back("COMMA");//6  E
  c.push_back("TYPE");//7  E
  c.push_back("$");//8  E
  c.push_back("#");//9  E
  c.push_back("ID");//10  E
  c.push_back("SEMI");//11  E
  c.push_back("NUM");//12
  c.push_back("LB");//13
  c.push_back("RB");//14
  c.push_back("FunDec");//15
  c.push_back("CompSt");//16
  c.push_back("LP");//17
  c.push_back("RP");//18
  c.push_back("VarList");//19
  c.push_back("ParamDec");//20
  c.push_back("LC");//21
  c.push_back("RC");//22
  c.push_back("DefList");//23
  c.push_back("StmtList");//24
  c.push_back("Stmt");//25
  c.push_back("Exp");//26
  c.push_back("RETURN");//27
  c.push_back("IF");//28
  c.push_back("ELSE");//29
  c.push_back("WHILE");//30


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
  k.push_back(0);
  k.push_back(0);
  k.push_back(1);
  k.push_back(1);
  k.push_back(0);
  k.push_back(0);
  k.push_back(1);
  k.push_back(1);
  k.push_back(0);
  k.push_back(0);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
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
  temp_grammar.push_back(1);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(3);
  temp_grammar.push_back(5);
  temp_grammar.push_back(11);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(4);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(4);
  temp_grammar.push_back(6);
  temp_grammar.push_back(5);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(7);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(10);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(13);
  temp_grammar.push_back(12);
  temp_grammar.push_back(14);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(3);
  temp_grammar.push_back(15);
  temp_grammar.push_back(16);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(15);
  temp_grammar.push_back(10);
  temp_grammar.push_back(17);
  temp_grammar.push_back(19);
  temp_grammar.push_back(18);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(15);
  temp_grammar.push_back(10);
  temp_grammar.push_back(17);
  temp_grammar.push_back(18);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(19);
  temp_grammar.push_back(20);
  temp_grammar.push_back(6);
  temp_grammar.push_back(19);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(19);
  temp_grammar.push_back(20);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(20);
  temp_grammar.push_back(3);
  temp_grammar.push_back(4);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(16);
  temp_grammar.push_back(21);
  temp_grammar.push_back(23);
  temp_grammar.push_back(24);
  temp_grammar.push_back(22);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(24);
  temp_grammar.push_back(25);
  temp_grammar.push_back(24);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(24);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(26);
  temp_grammar.push_back(11);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(16);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(27);
  temp_grammar.push_back(26);
  temp_grammar.push_back(11);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(28);
  temp_grammar.push_back(17);
  temp_grammar.push_back(26);
  temp_grammar.push_back(18);
  temp_grammar.push_back(25);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(28);
  temp_grammar.push_back(17);
  temp_grammar.push_back(26);
  temp_grammar.push_back(18);
  temp_grammar.push_back(25);
  temp_grammar.push_back(29);
  temp_grammar.push_back(25);
  g.push_back(temp_grammar);

  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(30);
  temp_grammar.push_back(17);
  temp_grammar.push_back(26);
  temp_grammar.push_back(18);
  temp_grammar.push_back(25);
  g.push_back(temp_grammar);

  */
  

}
