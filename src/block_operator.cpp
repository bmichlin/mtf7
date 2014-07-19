#include <stdlib.h>

#include "mtf7/block_operator.h"

//----------------------------------------------------------------------
mtf7::block_operator::block_operator( mtf7::error_value *error_status ): 
  _buffer_start_ptr(0), _i_own_buffer(false), _error_status(error_status)
{}

//----------------------------------------------------------------------
const mtf7::word_64bit *mtf7::block_operator::get_buffer_start_ptr()
{ return _buffer_start_ptr; }

//----------------------------------------------------------------------
void mtf7::block_operator::free_own_buffer()
{  
  if (!_i_own_buffer    ) return;
  if (!_buffer_start_ptr) return;

  free(_buffer_start_ptr);
  _i_own_buffer = false;
}

//----------------------------------------------------------------------
mtf7::error_value mtf7::block_operator::get_error_status()
{ return *_error_status; }
