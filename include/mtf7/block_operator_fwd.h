#ifndef __BLOCK_OPERATOR_FWD__
#define __BLOCK_OPERATOR_FWD__

#include <vector>
#include "mtf7/block_operator.h"

this is bullcrap

namespace mtf7{


  typedef std::vector<block_operator>           block_operator_vector;
  typedef block_operator_vector::iterator       block_operator_iterator;
  typedef block_operator_vector::const_iterator block_operator_const_iterator;

}

#endif
