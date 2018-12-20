#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
//#include<cstring>
//#include<conio>
#include "lexical_analyzer.h"
#include "grammatical_analyzer.h"
#include "dagnode.h"
//#include "LL.h"
//#include "recursion.h"
using namespace std;
using std::string;

/*
ExtDef->Specifier  FunDec  CompSt
FunDec->catF VarDec  LP  RP
catF��λ��

CompSt->LC DeepInc DefList  StmtList  RC
DeepInc��λ��Ӧ��CompSt-> DeepInc LC DefList  StmtList  RC


Stmt->IF  LP  Exp  RP  causeIF Label  Stmt  Label

causeIF Label ��Ҫ����һ��
*/

// todo        �ƽ���Լ��ͻ�Ľ��  Ŀǰ���� 8->264  �ƽ�  69->305 ��Լ ��ͻ�� ѡ���Լ   ����elseѡ���ƽ�
//  catF �ķ��ã� catF��Լ����ܹ�ԼVarDec �����ǽ�VarDecѹջ���ȵ�LP�Ƴ���ʱ��ջȻ�������
//��ݹ���ܻ�������
// Bool ���͵Ĵ����жϻ�ûд  �ָ����͹ؼ��ֵ�������Ҫ������
//��EXP��ʹ�ýṹ���Ա��ûʵ�֣��������Լ�offset��û����

void test(vector<vector<int>> &g, vector<tag> &c, vector<int> &k)
{
  c.push_back((tag)0);//Program
  c.push_back((tag)1);//labelTop
  c.push_back((tag)2);//ExtDefList
  c.push_back((tag)3);//ExtDef
  c.push_back((tag)4);//Specifier
  c.push_back((tag)5);//ExtDecList
  c.push_back((tag)6);//FunDec
  c.push_back((tag)7);//CompSt
  c.push_back((tag)8);//VarDec
  c.push_back((tag)9);//Exp
  c.push_back((tag)10);//TYPE
  c.push_back((tag)11);//StructSpecifier
  c.push_back((tag)12);//OptTag
  c.push_back((tag)13);//DefList
  c.push_back((tag)14);//Tag
  c.push_back((tag)15);//LB
  c.push_back((tag)16);//VarList
  c.push_back((tag)17);//ParamDec
  c.push_back((tag)18);//catVn
  c.push_back((tag)19);//DeepInc
  c.push_back((tag)20);//StmtList
  c.push_back((tag)21);//Stmt
  c.push_back((tag)22);//causeIF
  c.push_back((tag)23);//Label
  c.push_back((tag)24);//bgoto
  c.push_back((tag)25);//fLabel
  c.push_back((tag)26);//causeWHILE
  c.push_back((tag)27);//fgoto
  c.push_back((tag)28);//Def
  c.push_back((tag)29);//DecList
  c.push_back((tag)30);//Dec
  c.push_back((tag)31);//Args
  c.push_back((tag)32);//LeftVal
  c.push_back((tag)33);//OrRel
  c.push_back((tag)34);//Add
  c.push_back((tag)35);//NotRel
  c.push_back((tag)36);//Factor
  c.push_back((tag)37);//AndRel
  c.push_back((tag)38);//Rel
  c.push_back((tag)39);//RELOP
  c.push_back((tag)40);//Term




  c.push_back(VOID);//41      VOID
  c.push_back(SEMICOLON);//42      SEMI
  c.push_back(ASSIGN);//43     ASSIGN
  c.push_back(INT);//44     INT
  c.push_back(DOUBLE);//45     DOUBLE
  c.push_back(ID);//46     ID
  c.push_back(STRUCT);//47     STRUCT
  c.push_back(LBP);//48     LC
  c.push_back(RBP);//49     RC
  c.push_back(LMP);//50     LB
  c.push_back(RMP);//51     RB
  c.push_back(LSP);//52     LP
  c.push_back(RSP);//53     RP
  c.push_back(RETURN);//54    RETURN 
  c.push_back(IF);//55     IF
  c.push_back(ELSE);//56     ELSE
  c.push_back(OR);//57     OR
  c.push_back(AND);//58     AND
  c.push_back(NOT);//59  NOT
  c.push_back(ADD);//60  ADD
  c.push_back(SUB);//61  SUB 
  c.push_back(MUL);//62  MUL
  c.push_back(DIV);//63  DIV
  c.push_back(NUM);//64  NUM
  c.push_back(REAL);//65  REAL
  c.push_back(COMMA);//66  COMMA
  c.push_back(WHILE);//67  WHILE
  c.push_back(FINISH);//68 FINISH

  c.push_back((tag)69);//catF
  c.push_back((tag)70);//S
  c.push_back(EQ);//71  EQ
  c.push_back(POINT);//72 POINT
  c.push_back((tag)73);//73 SDec
  c.push_back((tag)74);//74 Dnamelist
  c.push_back((tag)75);//75 Dname
  c.push_back((tag)76);//75 FDec

  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
  k.push_back(1);
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
  k.push_back(1);
  k.push_back(1);

  vector<int> temp_grammar;


  //S->PROGRAM  0
  temp_grammar.clear();
  temp_grammar.push_back(70);
  temp_grammar.push_back(0);
  g.push_back(temp_grammar);

  //Program->labelTop ExtDefList 1
  temp_grammar.clear();
  temp_grammar.push_back(0);
  temp_grammar.push_back(1);
  temp_grammar.push_back(2);
  g.push_back(temp_grammar);

  //labelTop->VOID 2
  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);



  //ExtDefList->ExtDef  ExtDefList 3
  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(3);
  temp_grammar.push_back(2);
  g.push_back(temp_grammar);


  //ExtDefList->VOID 4
  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);


  //ExtDef->Specifier  ExtDecList  SEMI 5
  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(4);
  temp_grammar.push_back(5);
  temp_grammar.push_back(42);
  g.push_back(temp_grammar);


  //ExtDef->Specifier  SEMI 6
  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(4);
  temp_grammar.push_back(42);
  g.push_back(temp_grammar);

  //ExtDef->Specifier  FunDec  CompSt 7
  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(4);
  temp_grammar.push_back(6);
  temp_grammar.push_back(7);
  g.push_back(temp_grammar);

  //ExtDecList->VarDec 8
  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);



  //ExtDeclist->VarDec  ASSIGN Exp 9
  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(8);
  temp_grammar.push_back(43);
  temp_grammar.push_back(9);
  g.push_back(temp_grammar);

  //ExtDecList->ExtDecList  COMMA  VarDec 10
  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(5);
  temp_grammar.push_back(66);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);

  //ExtDeclist->ExtDecList  COMMA  VarDec  ASSIGN Exp 11
  temp_grammar.clear();
  temp_grammar.push_back(5);
  temp_grammar.push_back(5);
  temp_grammar.push_back(66);
  temp_grammar.push_back(8);
  temp_grammar.push_back(43);
  temp_grammar.push_back(9);
  g.push_back(temp_grammar);

  //Specifier->TYPE 12
  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(10);
  g.push_back(temp_grammar);

   
  //TYPE->INT 13
  temp_grammar.clear();
  temp_grammar.push_back(10);
  temp_grammar.push_back(44);
  g.push_back(temp_grammar);

  //TYPE->DOUBLE
  temp_grammar.clear();
  temp_grammar.push_back(10);
  temp_grammar.push_back(45);
  g.push_back(temp_grammar);

  /*
  //TYPE->ID
  temp_grammar.clear();
  temp_grammar.push_back(10);
  temp_grammar.push_back(46);
  g.push_back(temp_grammar);

  ���Ҫʹ�����TYPEDEF  �ں����е�������ʹ�����֮������һ��{}
  �������ƽ���Լ��ͻ �����Զ�������STMT״̬
  */
  
  
  

  // Specifier->StructSpecifier
  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(11);
  g.push_back(temp_grammar);

  // StructSpecifier->STRUCT  OptTag  LC  DefList  RC
  temp_grammar.clear();
  temp_grammar.push_back(11);
  temp_grammar.push_back(47);
  temp_grammar.push_back(12);
  temp_grammar.push_back(48);
  temp_grammar.push_back(13);
  temp_grammar.push_back(49);
  g.push_back(temp_grammar);


  // StructSpecifier->STRUCT  Tag
  temp_grammar.clear();
  temp_grammar.push_back(11);
  temp_grammar.push_back(47);
  temp_grammar.push_back(14);
  g.push_back(temp_grammar);

  // OptTag->ID
  temp_grammar.clear();
  temp_grammar.push_back(12);
  temp_grammar.push_back(46);
  g.push_back(temp_grammar);

  // OptTag->VOID
  temp_grammar.clear();
  temp_grammar.push_back(12);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);

  // Tag->ID
  temp_grammar.clear();
  temp_grammar.push_back(14);
  temp_grammar.push_back(46);
  g.push_back(temp_grammar);


  // VarDec->ID
  temp_grammar.clear();
  temp_grammar.push_back(8);
  temp_grammar.push_back(46);
  g.push_back(temp_grammar);


  // VarDec->VarDec  LB  INT  RB
  temp_grammar.clear();
  temp_grammar.push_back(8);
  temp_grammar.push_back(8);
  temp_grammar.push_back(50);
  temp_grammar.push_back(44);
  temp_grammar.push_back(51);
  g.push_back(temp_grammar);


  //FunDec-> VarDec catF LP  VarList  RP 
  temp_grammar.clear();
  temp_grammar.push_back(6);
  temp_grammar.push_back(8);
  temp_grammar.push_back(69);
  temp_grammar.push_back(52);
  temp_grammar.push_back(16);
  temp_grammar.push_back(53);
  g.push_back(temp_grammar);


  // catF->VOID
  temp_grammar.clear();
  temp_grammar.push_back(69);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);

  //FunDec-> VarDec catF LP  RP
  temp_grammar.clear();
  temp_grammar.push_back(6);
  temp_grammar.push_back(8);
  temp_grammar.push_back(69);
  temp_grammar.push_back(52);
  temp_grammar.push_back(53);
  g.push_back(temp_grammar);

  //VarList->VarList  COMMA  ParamDec
  temp_grammar.clear();
  temp_grammar.push_back(16);
  temp_grammar.push_back(16);
  temp_grammar.push_back(66);
  temp_grammar.push_back(17);
  g.push_back(temp_grammar);

  //VarList->ParamDec
  temp_grammar.clear();
  temp_grammar.push_back(16);
  temp_grammar.push_back(17);
  g.push_back(temp_grammar);


  //ParamDec->Specifier catVn VarDec
  temp_grammar.clear();
  temp_grammar.push_back(17);
  temp_grammar.push_back(4);
  temp_grammar.push_back(18);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);

  //catVn->VOID
  temp_grammar.clear();
  temp_grammar.push_back(18);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);

  //CompSt->DeepInc LC  DefList  StmtList  RC
  temp_grammar.clear();
  temp_grammar.push_back(7);
  temp_grammar.push_back(19);
  temp_grammar.push_back(48);
  temp_grammar.push_back(13);
  temp_grammar.push_back(20);
  temp_grammar.push_back(49);
  g.push_back(temp_grammar);

  // DeepInc->VOID
  temp_grammar.clear();
  temp_grammar.push_back(19);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);

 
  //StmtList->VOID
  temp_grammar.clear();
  temp_grammar.push_back(20);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);


  //StmtList->StmtList  Stmt 
  temp_grammar.clear();
  temp_grammar.push_back(20);
  temp_grammar.push_back(20);
  temp_grammar.push_back(21);
  g.push_back(temp_grammar);


  //Stmt->Exp  SEMI
  temp_grammar.clear();
  temp_grammar.push_back(21);
  temp_grammar.push_back(9);
  temp_grammar.push_back(42);
  g.push_back(temp_grammar);


  //Stmt->CompSt
  temp_grammar.clear();
  temp_grammar.push_back(21);
  temp_grammar.push_back(7);
  g.push_back(temp_grammar);




  //Stmt->RETURN  Exp  SEMI
  temp_grammar.clear();
  temp_grammar.push_back(21);
  temp_grammar.push_back(54);
  temp_grammar.push_back(9);
  temp_grammar.push_back(42);
  g.push_back(temp_grammar);

  //Stmt->IF  LP  Exp  RP  causeIF Label  Stmt  Label
  temp_grammar.clear();
  temp_grammar.push_back(21);
  temp_grammar.push_back(55);
  temp_grammar.push_back(52);
  temp_grammar.push_back(9);
  temp_grammar.push_back(22);
  temp_grammar.push_back(53);
  temp_grammar.push_back(21);
  temp_grammar.push_back(23);
  g.push_back(temp_grammar);

  // causeIF->void
  temp_grammar.clear();
  temp_grammar.push_back(22);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);

  //Label->void
  temp_grammar.clear();
  temp_grammar.push_back(23);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);


  
  //Stmt->IF  LP  Exp  RP  causeIF Label  Stmt bgoto ELSE  Label  Stmt  Label
  temp_grammar.clear();
  temp_grammar.push_back(21);
  temp_grammar.push_back(55);
  temp_grammar.push_back(52);
  temp_grammar.push_back(9);
  temp_grammar.push_back(22);
  temp_grammar.push_back(53);
  temp_grammar.push_back(21);
  temp_grammar.push_back(24);
  temp_grammar.push_back(56);
  temp_grammar.push_back(23);
  temp_grammar.push_back(21);
  temp_grammar.push_back(23);
  g.push_back(temp_grammar);

  //bgoto->void
  temp_grammar.clear();
  temp_grammar.push_back(24);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);
  


  
  
  //Stmt->fLabel  WHILE  LP  Exp  RP  causeWHILE Label  Stmt fgoto Label
  temp_grammar.clear();
  temp_grammar.push_back(21);
  temp_grammar.push_back(25);
  temp_grammar.push_back(67);
  temp_grammar.push_back(52);
  temp_grammar.push_back(9);
  temp_grammar.push_back(53);
  temp_grammar.push_back(26);
  temp_grammar.push_back(21);
  temp_grammar.push_back(27);
  temp_grammar.push_back(23);
  g.push_back(temp_grammar);

  //causeWHILE -> void
  temp_grammar.clear();
  temp_grammar.push_back(26);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);

  // fLabel-> void
  temp_grammar.clear();
  temp_grammar.push_back(25);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);

  // fgoto->void
  temp_grammar.clear();
  temp_grammar.push_back(27);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);
  

  

  //DefList->VOID
  temp_grammar.clear();
  temp_grammar.push_back(13);
  temp_grammar.push_back(41);
  g.push_back(temp_grammar);

  //DefList->DefList  Def
  temp_grammar.clear();
  temp_grammar.push_back(13);
  temp_grammar.push_back(13);
  temp_grammar.push_back(28);
  g.push_back(temp_grammar);


  //Def->Specifier  DecList  SEMI
  temp_grammar.clear();
  temp_grammar.push_back(28);
  temp_grammar.push_back(4);
  temp_grammar.push_back(29);
  temp_grammar.push_back(42);
  g.push_back(temp_grammar);

  //DecList->Dec
  temp_grammar.clear();
  temp_grammar.push_back(29);
  temp_grammar.push_back(30);
  g.push_back(temp_grammar);


  //DecList->DecList  COMMA  Dec
  temp_grammar.clear();
  temp_grammar.push_back(29);
  temp_grammar.push_back(29);
  temp_grammar.push_back(66);
  temp_grammar.push_back(30);
  g.push_back(temp_grammar);

  //Dec->VarDec
  temp_grammar.clear();
  temp_grammar.push_back(30);
  temp_grammar.push_back(8);
  g.push_back(temp_grammar);


  //Dec->VarDec    ASSIGNOP  Exp
  temp_grammar.clear();
  temp_grammar.push_back(30);
  temp_grammar.push_back(8);
  temp_grammar.push_back(43);
  temp_grammar.push_back(9);
  g.push_back(temp_grammar);


  
  //Args->Args  COMMA  Exp
  temp_grammar.clear();
  temp_grammar.push_back(31);
  temp_grammar.push_back(31);
  temp_grammar.push_back(66);
  temp_grammar.push_back(9);
  g.push_back(temp_grammar);

  //Args->Exp
  temp_grammar.clear();
  temp_grammar.push_back(31);
  temp_grammar.push_back(9);
  g.push_back(temp_grammar);
  
 

  //Exp->LeftVal    ASSIGNOP  Exp
  temp_grammar.clear();
  temp_grammar.push_back(9);
  temp_grammar.push_back(32);
  temp_grammar.push_back(43);
  temp_grammar.push_back(9);
  g.push_back(temp_grammar);

  //Exp->LeftVal  EQ  Exp
  temp_grammar.clear();
  temp_grammar.push_back(9);
  temp_grammar.push_back(32);
  temp_grammar.push_back(71);
  temp_grammar.push_back(9);
  g.push_back(temp_grammar);

  //Exp->OrRel
  temp_grammar.clear();
  temp_grammar.push_back(9);
  temp_grammar.push_back(33);
  g.push_back(temp_grammar);

  //LeftVal->ID
  temp_grammar.clear();
  temp_grammar.push_back(32);
  temp_grammar.push_back(46);
  g.push_back(temp_grammar);

  
  //LeftVal->LeftVal  LB  Add  RB
  temp_grammar.clear();
  temp_grammar.push_back(32);
  temp_grammar.push_back(32);
  temp_grammar.push_back(50);
  temp_grammar.push_back(34);
  temp_grammar.push_back(51);
  g.push_back(temp_grammar);

  //NotRel->Factor
  temp_grammar.clear();
  temp_grammar.push_back(35);
  temp_grammar.push_back(36);
  g.push_back(temp_grammar);

  //OrRel->OrRel  OR  AndRel
  temp_grammar.clear();
  temp_grammar.push_back(33);
  temp_grammar.push_back(33);
  temp_grammar.push_back(57);
  temp_grammar.push_back(37);
  g.push_back(temp_grammar);

  //OrRel->AndRel
  temp_grammar.clear();
  temp_grammar.push_back(33);
  temp_grammar.push_back(37);
  g.push_back(temp_grammar);

  //AndRel->AndRel  AND  Rel
  temp_grammar.clear();
  temp_grammar.push_back(37);
  temp_grammar.push_back(37);
  temp_grammar.push_back(58);
  temp_grammar.push_back(38);
  g.push_back(temp_grammar);

  //AndRel->Rel
  temp_grammar.clear();
  temp_grammar.push_back(37);
  temp_grammar.push_back(38);
  g.push_back(temp_grammar);
  
  

  /*
  //Rel->Rel  RELOP  Add
  temp_grammar.clear();
  temp_grammar.push_back(38);
  temp_grammar.push_back(38);
  temp_grammar.push_back(39);
  temp_grammar.push_back(34);
  g.push_back(temp_grammar);
  */
  

  
  //Rel->Add
  temp_grammar.clear();
  temp_grammar.push_back(38);
  temp_grammar.push_back(34);
  g.push_back(temp_grammar);

  //Rel->NOT  NotRel
  temp_grammar.clear();
  temp_grammar.push_back(38);
  temp_grammar.push_back(59);
  temp_grammar.push_back(35);
  g.push_back(temp_grammar);

  //Add->Add  PLUS  Term
  temp_grammar.clear();
  temp_grammar.push_back(34);
  temp_grammar.push_back(34);
  temp_grammar.push_back(60);
  temp_grammar.push_back(40);
  g.push_back(temp_grammar);

  //Add->Add  MINUS  Term
  temp_grammar.clear();
  temp_grammar.push_back(34);
  temp_grammar.push_back(34);
  temp_grammar.push_back(61);
  temp_grammar.push_back(40);
  g.push_back(temp_grammar);

  //Add->MINUS  Term
  temp_grammar.clear();
  temp_grammar.push_back(34);
  temp_grammar.push_back(61);
  temp_grammar.push_back(40);
  g.push_back(temp_grammar);

  //Add->Term
  temp_grammar.clear();
  temp_grammar.push_back(34);
  temp_grammar.push_back(40);
  g.push_back(temp_grammar);

  //Term->Term  STAR  Factor
  temp_grammar.clear();
  temp_grammar.push_back(40);
  temp_grammar.push_back(40);
  temp_grammar.push_back(62);
  temp_grammar.push_back(36);
  g.push_back(temp_grammar);

  //Term->Term  DIV  Factor
  temp_grammar.clear();
  temp_grammar.push_back(40);
  temp_grammar.push_back(40);
  temp_grammar.push_back(63);
  temp_grammar.push_back(36);
  g.push_back(temp_grammar);

  //Term->Factor
  temp_grammar.clear();
  temp_grammar.push_back(40);
  temp_grammar.push_back(36);
  g.push_back(temp_grammar);

  //Factor->LP  Exp  RP
  temp_grammar.clear();
  temp_grammar.push_back(36);
  temp_grammar.push_back(52);
  temp_grammar.push_back(9);
  temp_grammar.push_back(53);
  g.push_back(temp_grammar);

  //Factor->LeftVal
  temp_grammar.clear();
  temp_grammar.push_back(36);
  temp_grammar.push_back(32);
  g.push_back(temp_grammar);

  //Factor->NUM
  temp_grammar.clear();
  temp_grammar.push_back(36);
  temp_grammar.push_back(64);
  g.push_back(temp_grammar);

  //Factor->REAL
  temp_grammar.clear();
  temp_grammar.push_back(36);
  temp_grammar.push_back(65);
  g.push_back(temp_grammar);

  //Factor->FDec  LP  RP
  temp_grammar.clear();
  temp_grammar.push_back(36);
  temp_grammar.push_back(76);
  temp_grammar.push_back(52);
  temp_grammar.push_back(53);
  g.push_back(temp_grammar);

  //Factor->FDec  LP  Args  RP
  temp_grammar.clear();
  temp_grammar.push_back(36);
  temp_grammar.push_back(76);
  temp_grammar.push_back(52);
  temp_grammar.push_back(31);
  temp_grammar.push_back(53);
  g.push_back(temp_grammar);

  
  
  
  
  
  
  //Leftval->SDec  POINT DnameList
  temp_grammar.clear();
  temp_grammar.push_back(32);
  temp_grammar.push_back(73);
  temp_grammar.push_back(72);
  temp_grammar.push_back(74);
  g.push_back(temp_grammar);
  //SDec->ID
  temp_grammar.clear();
  temp_grammar.push_back(73);
  temp_grammar.push_back(46);
  g.push_back(temp_grammar);
  //DnameList -> Dnamelist Point Dname
  temp_grammar.clear();
  temp_grammar.push_back(74);
  temp_grammar.push_back(74);
  temp_grammar.push_back(72);
  temp_grammar.push_back(75);
  g.push_back(temp_grammar);
  //DnameList->Dname
  temp_grammar.clear();
  temp_grammar.push_back(74);
  temp_grammar.push_back(75);
  g.push_back(temp_grammar);
  //Dname->ID
  temp_grammar.clear();
  temp_grammar.push_back(75);
  temp_grammar.push_back(46);
  g.push_back(temp_grammar);
  //Leftval->SDec  POINT DnameList
  temp_grammar.clear();
  temp_grammar.push_back(36);
  temp_grammar.push_back(73);
  temp_grammar.push_back(72);
  temp_grammar.push_back(74);
  g.push_back(temp_grammar);

  //FDec->ID
  temp_grammar.clear();
  temp_grammar.push_back(76);
  temp_grammar.push_back(46);
  g.push_back(temp_grammar);

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

void readTable(map<index, key> &table, string filename,Parser parser)
{
  
  ifstream fin(filename);
  for (int i = 0; i <= 2123; ++i)
  {
    index temp_index;
    fin >> temp_index.state;
   
    for (int j = 0; j < (int)parser.character.size(); ++j)
    {
      temp_index.V = j;
      fin >> table[temp_index].state;
      char c;
      fin >> c;
      fin >> table[temp_index].V;
     
    }
   

    
  }
}


void testMain() {

	string str;
	string s("test.txt");
	str = readFileIntoString(s);
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

	cout << "over15 -1,over66-2" << endl;
	test(g, c, k);
	parser.init(g, c, k, l, token_line);



	readTable(parser.table_analyse, "table.txt", parser);




	parser.action();
	for (int i = 0; i < (int)parser.infer.symbol.table_id_3.size(); ++i)
	{
		cout << "Deep " << i << " " << endl;
		for (int j = 0; j < (int)parser.infer.symbol.table_id_3[i].size(); ++j)
		{
			cout << "Func" << j << "  " << "PDeep " << parser.infer.symbol.table_id_3[i][j].parent.indexDeep << " " << parser.infer.symbol.table_id_3[i][j].parent.indexFunc << " " << endl;
			cout << "name" << '\t' << "cat" << '\t' << "kind" << '\t' << "addr" << endl;
			for (int k = 0; k < (int)parser.infer.symbol.table_id_3[i][j].table_id_1.size(); ++k)
			{
				cout << parser.infer.symbol.table_id_3[i][j].table_id_1[k].name << '\t';
				parser.infer.symbol.show_Cat(parser.infer.symbol.table_id_3[i][j].table_id_1[k].cat);
				cout << '\t';
				parser.infer.symbol.show_TVal(parser.infer.symbol.table_type[parser.infer.symbol.table_id_3[i][j].table_id_1[k].point_type.indexItem].tval);
				cout << endl;
				if (parser.infer.symbol.table_id_3[i][j].table_id_1[k].cat == f)
				{
					cout << "Node_Process" << endl;
					parser.infer.symbol.show_func(parser.infer.symbol.table_id_3[i][j].table_id_1[k].addr.point_process);
				}
				// cout << '\t'<< parser.infer.symbol.table_id_3[i][j].table_id_1[k].addr;
				cout << endl;
			}
			cout << endl;
		}
	}
	/*
	for (int i = 0; i < (int)parser.infer.sequence_temp.size(); ++i)
	{
	cout << "< (" << parser.infer.sequence_temp[i].op.indexKind << "," << parser.infer.symbol.table_key[parser.infer.sequence_temp[i].op.indexItem] << ")" << '\t';
	cout << "(" << parser.infer.sequence_temp[i].arg1.indexKind << "," << parser.infer.sequence_temp[i].arg1.indexDeep << "," << parser.infer.sequence_temp[i].arg1.indexFunc << "," << parser.infer.sequence_temp[i].arg1.indexItem << ")" << '\t';
	cout << "(" << parser.infer.sequence_temp[i].arg2.indexKind << "," << parser.infer.sequence_temp[i].arg2.indexDeep << "," << parser.infer.sequence_temp[i].arg2.indexFunc << "," << parser.infer.sequence_temp[i].arg2.indexItem << ")" << '\t';
	cout << "(" << parser.infer.sequence_temp[i].result.indexKind << "," << parser.infer.sequence_temp[i].result.indexDeep << "," << parser.infer.sequence_temp[i].result.indexFunc << "," << parser.infer.sequence_temp[i].result.indexItem << ")" << '\t';
	cout << ">" << endl;
	}
	*/
	parser.infer.showSequence();

	cout << "print table_link" << endl;
	for (int i = 0; i < (int)parser.infer.symbol.table_link.size(); ++i)
	{
		for (int j = 0; j < (int)parser.infer.symbol.table_link[i].size(); ++j)
		{
			cout << parser.infer.symbol.table_link[i][j] << " ";
		}
		cout << endl;
	}


}

void testNode() {
	Node n(3, "a", v);
	Node a("a", v), b("b", v), R("R", v), r("r", v), x("x", v), y("y", v);
	Node t1("t1", vt), t2("t2", vt), t3("t3", vt), t4("t4", vt), t5("t5", vt), t6("t6", vt), t7("t7", vt), t8("t8", vt);
	cout << a;
	cout << n;
}

void testDagNode() {
	Node a("a", v), b("b", v), c("c", v), d("d", v), x("x", v), y("y", v);
	DagNode dn1(a, NULL, NULL);
	DagNode dn2 = dn1;
	//DagNode* dn_ptr = &dn1;
	dn1.show();
	dn2.show();
	//DagNode dn3(b, dn_ptr, dn_ptr);
	//dn3.show();
}

int main()
{	
	testDagNode();
	getchar();
	return 0; 
}




