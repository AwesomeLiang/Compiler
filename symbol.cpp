#include "symbol.h"

Symbol::Symbol()
{
  //list_table_id;
  table_array.clear();
  table_num.clear();
  table_real.clear();
  table_length.clear();
  table_process.clear();
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
}
