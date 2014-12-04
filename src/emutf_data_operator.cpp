#include <stdlib.h>
#include <cstring>
#include "mtf7/emutf_data_operator.h"
#include "mtf7/emutf_block_operator.h"

//----------------------------------------------------------------------
mtf7::emutf_data_operator::emutf_data_operator( const char *data_release ):
  data_operator(data_release)
{ mtf7::clear_emutf_event(&_event_info); }

//----------------------------------------------------------------------
mtf7::error_value mtf7::emutf_data_operator::unpack( const word_64bit *buffer ){

  const word_64bit *tmp_ptr = buffer;
  
  for (block_operator_iterator iter = _workers -> begin(); 
       iter != _workers -> end(); iter++){
    if (_error_status != NO_ERROR) return _error_status;
    tmp_ptr = iter -> unpack (tmp_ptr);
  }
  
  return _error_status;
    
}


//----------------------------------------------------------------------
const mtf7::word_64bit *mtf7::emutf_data_operator::pack( ){

  unsigned long total_buffer_size = 0;
  
  std::vector<unsigned long> buffer_sizes;

  _error_status = NO_ERROR;
  
  for (block_operator_iterator iter = _workers -> begin(); 
       iter != _workers -> end(); iter++){
    
    if (_error_status != NO_ERROR){ free_block_owned_buffers(); return 0; }

    emutf_block_operator *tmp_ptr = (emutf_block_operator *) (&(*iter));
    
    tmp_ptr -> set_event_info_to_pack ( &_event_info );
    unsigned long temp = tmp_ptr -> pack ( );
    
    total_buffer_size += temp;
    buffer_sizes.push_back(temp);
    
  }
    
  mtf7::word_64bit *buffer_ptr = (mtf7::word_64bit *) malloc( total_buffer_size << 3 );
  
  std::vector <unsigned long>::iterator size_iter = buffer_sizes.begin();
  
  mtf7::word_64bit *temp_ptr = buffer_ptr;
  
  for (block_operator_iterator iter = _workers -> begin(); iter != _workers -> end(); iter++, size_iter++){
    memcpy(temp_ptr, iter -> get_buffer_start_ptr(), (*size_iter) << 3);
    iter -> free_own_buffer();
    temp_ptr += *size_iter;
  }
  
  return buffer_ptr;

}

void mtf7::emutf_data_operator::free_block_owned_buffers(){

  for (block_operator_iterator iter = _workers -> begin(); iter != _workers -> end(); iter++)
    iter -> free_own_buffer();

}
