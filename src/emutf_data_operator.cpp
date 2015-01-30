#include <stdlib.h>
#include <cstring>
#include "mtf7/emutf_data_operator.h"
#include "mtf7/emutf_block_operator.h"
#include <iostream>
#include <typeinfo>

//----------------------------------------------------------------------
mtf7::emutf_data_operator::emutf_data_operator( const char *data_release ):
  data_operator(data_release) 
  {  }

//----------------------------------------------------------------------
mtf7::error_value mtf7::emutf_data_operator::unpack( const word_64bit *buffer ){

  const word_64bit *tmp_ptr = buffer;
  
  for (block_operator_iterator iter = _workers -> begin(); 
       iter != _workers -> end(); iter++){
    if (_error_status != NO_ERROR) return _error_status;
    emutf_block_operator * _tmp_block_operator = dynamic_cast<emutf_block_operator *> (*iter);
    std::cout << "Unpacking block number " << std::distance(_workers->begin(),iter) << std::endl;
    // passing the event info to fill to the block operator
    //std::cout << "Type id block = " << typeid(*iter).name() << std::endl;
    //std::cout << "Setting the unapcked event into ptr. " << std::endl;
    _tmp_block_operator -> set_unpacked_event_info_ptr( _unpacked_event_info );
    std::cout << "Pointer before unpack : " << tmp_ptr << std::endl;
    std::cout << "Pointer value before unpack : " << *tmp_ptr << std::endl;
    tmp_ptr = _tmp_block_operator -> unpack (tmp_ptr);
    if(tmp_ptr == 0 ){
      std::cout << "ERR: Error unpacking block number " << std::distance(_workers->begin(),iter) << std::endl;
      std::cout << "ERR: Error value :" << _error_status << std::endl;
      return _error_status;
    }
    std::cout << "Pointer after unpack : " << tmp_ptr << std::endl;
    // std::cout << "Unpacked l1a on loop: " << _unpacked_event_info -> _l1a << std::endl;
    // std::cout << "Unpacked csc_me_bxn on loop: " << _unpacked_event_info -> _csc_me_bxn << std::endl;
    // std::cout << "Pointer to buffer in loop = " << &tmp_ptr << std::endl;
  }

  // std::cout << "Unpacked l1a : " << _unpacked_event_info -> _l1a << std::endl;
  // std::cout << "Unpacked csc_me_bxn: " << _unpacked_event_info -> _csc_me_bxn << std::endl;
  std::cout << "Unpacked!" << std::endl;
  
  return _error_status;
    
}


//----------------------------------------------------------------------
const mtf7::word_64bit *mtf7::emutf_data_operator::pack( ){

  unsigned long total_buffer_size = 0;
  
  std::vector<unsigned long> buffer_sizes;

  _error_status = NO_ERROR;

  std::cout << "######### Packing ######### " << std::endl;
  
  std::cout << " --- Workers size : " << _workers ->size() << std::endl;
  for (block_operator_iterator iter = _workers -> begin(); 
       iter != _workers -> end(); iter++){

    // std::cout << "Packing block operator" << std::endl;
    if (_error_status != NO_ERROR){ free_block_owned_buffers(); return 0; }

    // std::cout << "Pointer casting " << (*iter) << std::endl; 
    emutf_block_operator *tmp_ptr = dynamic_cast<emutf_block_operator*>(*iter);

    // std::cout << "Set event info to pack" << std::endl;
    // std::cout << "Eevnt info l1a 2 = " << _event_info -> _l1a << std::endl;
    // std::cout << "amc13 event l1a = " << _event_info -> _amc13_header_lv1_id << std::endl;
    // std::cout << "csc_me_bxn = " << _event_info -> _csc_me_bxn << std::endl;
    // std::cout << "Type id event = " << typeid(_event_info).name() << std::endl;
    tmp_ptr -> set_event_info_to_pack ( _event_info ); // this is calling the emutf_block_operator

    // std::cout << "Packing" << std::endl;
    unsigned long temp = tmp_ptr -> pack ();
    // std::cout << "Packed!" << std::endl;    

    total_buffer_size += temp;
    buffer_sizes.push_back(temp);

  }

  std::cout << " --- Total buffer size : " << total_buffer_size << std::endl;
  std::cout << " --- buffer_size size : " << buffer_sizes.size() << std::endl;
  for( int i = 0; i < buffer_sizes.size(); ++i) std::cout << " --- buffer " << i << " size " << buffer_sizes.at(i) << std::endl;

  // todo: is this a memory leak? how do I free this buffer in this design?
  mtf7::word_64bit *buffer_ptr = (mtf7::word_64bit *) malloc( total_buffer_size << 3 ); // multipling the total buffer size by 8 to get bits. (size_t has to be in bytes). total_buffer_size is in 64bit words unit.
  
  std::vector <unsigned long>::iterator size_iter = buffer_sizes.begin();
  
  mtf7::word_64bit *temp_ptr = buffer_ptr;
  
  for (block_operator_iterator iter = _workers -> begin(); iter != _workers -> end(); iter++, size_iter++){
    memcpy(temp_ptr, (*iter) -> get_buffer_start_ptr(), (*size_iter) << 3);
    (*iter) -> free_own_buffer();
    temp_ptr += *size_iter;
  }
  std::cout << "buffer ptr B = " << *buffer_ptr <<std::endl;
  
  return buffer_ptr;

}

void mtf7::emutf_data_operator::free_block_owned_buffers(){

  for (block_operator_iterator iter = _workers -> begin(); iter != _workers -> end(); iter++)
    (*iter) -> free_own_buffer();

}
