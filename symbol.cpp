#include "symbol.h"

Node_Type make_node_type(TVal tv, TPoint tp)
{
  Node_Type node_type;
  node_type.tpoint = tp;
  node_type.tval = tv;
  return node_type;
}
TPoint make_TPoint( int v)
{
  TPoint tp;
  tp.Void = v;
  return tp;
}
Symbol::Symbol()
{
  //list_table_id;
  table_array.clear();
  table_num.clear();
  table_real.clear();
  table_length.clear();
  //table_process.clear();
  table_param.clear();
  table_struct.clear();
  table_type.clear();
  table_vall.clear();
  num_t = 0;
  mode = 0;
  for (int i = 0; i < 100; ++i)
  {
    space[i] = 0;
  }
  table_typeInit();
  table_keyInit();
}

void Symbol::table_typeInit()
{
  table_type.push_back(make_node_type(Int,make_TPoint(1)));
  table_type.push_back(make_node_type(Real, make_TPoint(1)));
  table_type.push_back(make_node_type(Char, make_TPoint(1)));
  table_type.push_back(make_node_type(String, make_TPoint(1)));
  table_type.push_back(make_node_type(Bool, make_TPoint(1)));
  
}

void Symbol::table_keyInit()
{
  for (int i = 256; i <= 309; ++i)
  {
    table_key.push_back((tag)i);
  }

}

void Symbol::show_TVal(TVal t)
{
  switch (t)
  {
  case Int:
    cout << "Int" ;
    break;
  case Real:
    cout << "Real" ;
    break;
  case Char:
    cout << "Char" ;
    break;
  case String:
    cout << "String" ;
    break;
  case Bool:
    cout << "Bool";
    break;
  case Array:
    cout << "Array" ;
    break;
  case Struct:
    cout << "Struct" ;
    break;
  
  default:
    cout << "error! no such tval";
    break;
  }
}

void Symbol::show_Cat(Catalog cat)
{
  switch (cat)
  {
    
  case f:
    cout << "func" ;
    break;
  case c:
    cout << "const" ;
    break;
  case t:
    cout << "typedef" ;
    break;
  case d:
    cout << "dname" ;
    break;
  case v:
    cout << "v" ;
    break;
  case vn:
    cout << "vn" ;
    break;
  case vf:
    cout << "vf" ;
    break;
  default:
    break;
  }
}

void Symbol::show_func(Node_Process node_process)
{
  
  cout << "LEVEL" << '\t' << "OFF" << '\t'<<"NUMF"<<'\t'<<"ENTRY"<<endl;
  cout << node_process.level << '\t' << node_process.off << '\t' << node_process.numf<<'\t'<< node_process.entry << endl;
  cout << "pname" << '\t' << "ptval" << '\t' << "pcat" << '\t' << "poffset" << endl;
  for (int i = 0; i < (int)node_process.vparam.size(); ++i)
  {
   
    cout << node_process.vparam[i].pname << '\t';
    show_TVal(table_type[node_process.vparam[i].ptype.indexItem].tval);
    cout << '\t';
    show_Cat(node_process.vparam[i].pcat);
    cout<< '\t' << node_process.vparam[i].poffset << endl;
  }
}

Index_4D Symbol::findId(string idname,TVal tval)
{
  //从该层开始，向上层查找ID
  int deep_temp = index_deep_now;
  int func_temp = index_func_now;
  int item_temp;
  Index_4D index_leftval;
  index_leftval.indexKind = 3;
  int flag = 0;
  while (flag == 0 && deep_temp >= 0)
  {
    for (int i = 0; i < (int)table_id_3[deep_temp][func_temp].table_id_1.size(); ++i)
    {
      if (idname == table_id_3[deep_temp][func_temp].table_id_1[i].name)
      {//在当前的作用域内找到了该标识符
        
        Index_4D index_type = table_id_3[deep_temp][func_temp].table_id_1[i].point_type;
        if (table_type[index_type.indexItem].tval != tval)
        {
          //最邻近的同名id 不是需要找的类型 错误
          cout << "funcFindId------ wrong TVal!!!!!" << endl;
          return index_leftval;
        }
        flag = 1;
        item_temp = i;
        break;
      }

    }
    if (flag == 0)
    {//该标识符在上级作用域内


      int x1 = table_id_3[deep_temp][func_temp].parent.indexDeep;
      int x2 = table_id_3[deep_temp][func_temp].parent.indexFunc;
      deep_temp = x1;
      func_temp = x2;

    }
  }
  if (flag == 0)
  {//error; 该标识符未被定义就使用

    cout << "funcFindId------ id no defined!!!!!" << endl;
  }
  else
  {
    
    index_leftval.indexDeep = deep_temp;
    index_leftval.indexKind = 3;
    index_leftval.indexFunc = func_temp;
    index_leftval.indexItem = item_temp;

  }
  
  return Index_4D(index_leftval);
}

int Symbol::findDnameLink(Index_4D index_arg)
{
  Index_4D index_struct;
  index_struct.indexDeep = table_link[index_arg.indexItem][0];
  index_struct.indexFunc = table_link[index_arg.indexItem][1];
  index_struct.indexItem = table_link[index_arg.indexItem][2];

  Index_4D index_type = table_id_3[index_struct.indexDeep][index_struct.indexFunc].table_id_1[index_struct.indexItem].point_type;
  table_struct = table_type[index_type.indexItem].tpoint.point_struct;
  for (int i = 3; i < (int)table_link[index_arg.indexItem].size() - 1; ++i)
  {
    int p = table_link[index_arg.indexItem][i];
    table_struct =table_type[table_struct[p].index_tp.indexItem].tpoint.point_struct;

  }
  int p = table_link[index_arg.indexItem][table_link[index_arg.indexItem].size() - 1];

  return table_struct[p].index_tp.indexItem;
}

int Symbol::findDname(string Dname)
{
  
  for (int i = 0; i < (int)table_struct.size(); ++i)
  {
    if (Dname == table_struct[i].dname)
    {
      
      return i;
      
    }
  }
  cout << "findDname error ! no defined of Dname" << endl;

  return int(0);
}

TVal Symbol::getTVal(Index_4D index_arg1)
{
  int pos1;
  if (index_arg1.indexKind == 3)
  {
    pos1 = table_id_3[index_arg1.indexDeep][index_arg1.indexFunc].table_id_1[index_arg1.indexItem].point_type.indexItem;
    if (pos1 != 0 && pos1 != 1)
      cout << " getIdTVal-------------arg type error" << endl;
  }
  else if (index_arg1.indexKind == 4)
  {
    //操作数1是常整数
    for (int i = 0; i < (int)table_type.size(); ++i)
    {
      if (table_type[i].tval == Int)
      {
        pos1 = i;
        break;
      }
    }

  }
  else if (index_arg1.indexKind == 5)
  {
    //操作数1是常实数
    for (int i = 0; i < (int)table_type.size(); ++i)
    {
      if (table_type[i].tval == Real)
      {
        pos1 = i;
        break;
      }
    }
  }
  else if (index_arg1.indexKind == 7)
  {
    pos1 = findDnameLink(index_arg1);
    if (pos1 != 0 && pos1 != 1)
      cout << " getIdTVal-------------arg type error" << endl;
  }
  else
  {
    //error;
  }
  return TVal(table_type[pos1].tval);
}

Index_4D Symbol::getIdIndexType(Index_4D index_id)
{

  return Index_4D(table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].point_type);
}

Catalog Symbol::getIdCat(Index_4D index_id)
{
  return Catalog(table_id_3[index_id.indexDeep][index_id.indexFunc].table_id_1[index_id.indexItem].cat);
}


Node::Node(int kind, attribute att)
{
	kindNode = kind;
  switch (kind)
  {
  case 0:
  {
    attributeNode.attributeKey = att.attributeKey;
  }
  break;
  case 3:
  {
    attributeNode.attributeId = att.attributeId;
	cout << att.attributeId << endl;
  }
  break;
  case 4:
  {
    attributeNode.attributeInt = att.attributeInt;
  }
  break;
  case 5:
  {
    attributeNode.attributeReal = att.attributeReal;
  }
  break;
  case 7:
  {
    attributeNode.attributeLink = att.attributeLink;
  }
  break;
  case 8:
  {
    attributeNode.attributeParam = att.attributeParam;
  }
  break;

  default:
    cout << "Node::Node --------- error kind" << endl;
    break;
  }
}

void Node::init(int kind, attribute att)
{
	kindNode = kind;
  switch (kind)
  {
  case 0:
  {
    attributeNode.attributeKey = att.attributeKey;
  }
  break;
  case 3:
  {
    attributeNode.attributeId = att.attributeId;
  }
  break;
  case 4:
  {
    attributeNode.attributeInt = att.attributeInt;
  }
  break;
  case 5:
  {
    attributeNode.attributeReal = att.attributeReal;
  }
  break;
  case 7:
  {
    attributeNode.attributeLink = att.attributeLink;
  }
  break;
  case 8:
  {
    attributeNode.attributeParam = att.attributeParam;
  }
  break;

  default:
    cout << "Node::Node --------- error kind" << endl;
    break;
  }
}

void Node::init(Index_4D index,Symbol symbol)
{
  kindNode = index.indexKind;
  switch (index.indexKind)
  {
  case 0:
  {
    attributeNode.attributeKey = symbol.table_key[index.indexItem];
  }
  break;
  case 3:
  {
    attributeNode.attributeId = symbol.table_id_3[index.indexDeep][index.indexFunc].table_id_1[index.indexItem];
  }
  break;
  case 4:
  {
    attributeNode.attributeInt = symbol.table_num[index.indexItem];
  }
  break;
  case 5:
  {
    attributeNode.attributeReal = symbol.table_real[index.indexItem];
  }
  break;
  case 7:
  {
    attributeNode.attributeLink = symbol.table_link[index.indexItem];
  }
  break;
  case 8:
  {
    attributeNode.attributeParam = symbol.table_id_3[0][0].table_id_1[index.indexFunc].addr.point_process.vparam[index.indexItem];
  }
  break;

  default:
    cout << "Node::Init --------- error kind:"<<kindNode << endl;
    break;
  }
}

Node_Type Node::getTypeNode(Index_4D index_type,Symbol symbol)
{
  return symbol.table_type[index_type.indexItem];
}

int Node_Id_1::getLength() {
	return addr.length;
}
