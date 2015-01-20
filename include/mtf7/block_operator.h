#ifndef __MTF7_BLOCK_OPERATOR__
#define __MTF7_BLOCK_OPERATOR__

#include <vector>

#include "mtf7/types.h"

namespace mtf7{

  class block_operator{

  public:
    
    block_operator( error_value *error_status );
    
    virtual unsigned long        pack   ()                         = 0; 
    virtual const word_64bit    *unpack (const word_64bit *at_ptr) = 0; 
    
    const word_64bit *get_buffer_start_ptr();
    
    void free_own_buffer();

    error_value get_error_status();
    
    // ikf todo: add get_event_info() to base class?

  protected:

    word_64bit *create_buffer( unsigned long buffer_size );

    const word_64bit *_buffer_start_ptr;
    mtf7_bool  _i_own_buffer;
    error_value *_error_status;

    void break_into_abcd_words ( word_64bit input_value );
    word_64bit merge_abcd_words();

    word_16bit _16bit_word_a, _16bit_word_b, _16bit_word_c, _16bit_word_d;
    
  };

  typedef std::vector<block_operator*>           block_operator_vector;
  typedef block_operator_vector::iterator       block_operator_iterator;
  typedef block_operator_vector::const_iterator block_operator_const_iterator;
  

}

#endif
