#include "mtf7/emutf_cscmedata_block_operator.h"

const mtf7::word_64bit *mtf7::emutf_cscmedata_block_operator::unpack ( const mtf7::word_64bit *at_ptr ){

  std::cout << "Unpacking cscmedata" << std::endl;
  std::cout << "Error status =  " << *_error_status << std::endl;

  if (*_error_status != mtf7::NO_ERROR) return 0;

  if (at_ptr == 0) { *_error_status = mtf7::NULL_BUFFER_PTR; return 0; }

  std::cout << "pointer " << at_ptr << std::endl;
  std::cout << "pointer value = " << *at_ptr << std::endl;
  std::cout << "word a = " << _16bit_word_a << std::endl;
  std::cout << "word b = " << _16bit_word_b << std::endl;
  std::cout << "word c = " << _16bit_word_c << std::endl;
  std::cout << "word d = " << _16bit_word_d << std::endl;

  std::cout << "input value before break_into_abcd_words =  " << *at_ptr << std::endl;

  break_into_abcd_words( *at_ptr ); at_ptr++;
  std::cout << "pointer " << at_ptr << std::endl;

  std::cout << "word a = " << _16bit_word_a << std::endl;
  std::cout << "word b = " << _16bit_word_b << std::endl;
  std::cout << "word c = " << _16bit_word_c << std::endl;
  std::cout << "word d = " << _16bit_word_d << std::endl;

  if ( (_16bit_word_a & 0x8000 ) != 0x8000 ) *_error_status = mtf7::BLOCK_COUNTER_FORMAT; // check if D15 is 1
  std::cout << "Error status =  " << *_error_status << std::endl;
  if ( (_16bit_word_b & 0x8000 ) != 0x8000 ) *_error_status = mtf7::BLOCK_COUNTER_FORMAT; // check if D15 is 1
  std::cout << "Error status =  " << *_error_status << std::endl;
  if ( (_16bit_word_c & 0x8000 ) != 0x0000 ) *_error_status = mtf7::BLOCK_COUNTER_FORMAT; // check if D15 is 0
  std::cout << "Error status =  " << *_error_status << std::endl;
  if ( (_16bit_word_d & 0x8000 ) != 0x0000 ) *_error_status = mtf7::BLOCK_COUNTER_FORMAT; // check if D15 is 0
  std::cout << "Error status =  " << *_error_status << std::endl;
  if (*_error_status != mtf7::NO_ERROR) return 0;


  _unpacked_event_info -> _csc_clct_pattern = (_16bit_word_a & 0xf); 
  _unpacked_event_info -> _csc_quality = (_16bit_word_a >> 4) & 0xf;
  _unpacked_event_info -> _csc_key_wire_group = (_16bit_word_a >> 8) & 0x7f;

  _unpacked_event_info -> _csc_clct_key_half_strip = (_16bit_word_b & 0xff );
  _unpacked_event_info -> _csc_id = (_16bit_word_b >> 8) & 0xf; _16bit_word_b >>= 12;
  _unpacked_event_info -> _csc_lr = (_16bit_word_b & 0x1); _16bit_word_b >>= 1;
  _unpacked_event_info -> _csc_bxe = (_16bit_word_b & 0x1); _16bit_word_b >>= 1;
  _unpacked_event_info -> _csc_bc0 = (_16bit_word_b & 0x1);

  std::cout <<  "Inside the unpacked from buffer _csc_me_bxn = " << (_16bit_word_c & 0xfff) << std::endl;
  _unpacked_event_info -> _csc_me_bxn = (_16bit_word_c & 0xfff); _16bit_word_c >>= 12;
  std::cout <<  "Inside the unpacked _csc_me_bxn = " << _unpacked_event_info -> _csc_me_bxn << std::endl;
  _unpacked_event_info -> _csc_nit = (_16bit_word_c & 0x1); _16bit_word_c >>= 1;
  _unpacked_event_info -> _csc_cik = (_16bit_word_c & 0x1); _16bit_word_c >>= 1;
  _unpacked_event_info -> _csc_afff = (_16bit_word_c & 0x1);


  _unpacked_event_info -> _csc_tbin_num = (_16bit_word_d & 0x7); _16bit_word_d >>= 3;
  _unpacked_event_info -> _csc_vp = (_16bit_word_d & 0x1); _16bit_word_d >>= 1;
  _unpacked_event_info -> _csc_station = (_16bit_word_d & 0x7); _16bit_word_d >>= 3;
  _unpacked_event_info -> _csc_af = (_16bit_word_d & 0x1); _16bit_word_d >>= 1;
  _unpacked_event_info -> _csc_epc = (_16bit_word_d & 0xf); _16bit_word_d >>= 4;
  _unpacked_event_info -> _csc_sm = (_16bit_word_d & 0x1); _16bit_word_d >>= 1;
  _unpacked_event_info -> _csc_se = (_16bit_word_d & 0x1); _16bit_word_d >>= 1;
  _unpacked_event_info -> _csc_afef = (_16bit_word_d & 0x1);
 

  return at_ptr;

}


unsigned long mtf7::emutf_cscmedata_block_operator::pack(){

  mtf7::word_64bit *buffer = create_buffer ( _nominal_buffer_size );
  
  mtf7::word_64bit *ptr = buffer;
  
  _16bit_word_a = _event_info_to_pack -> _csc_key_wire_group & 0x7f; _16bit_word_a <<= 4;
  _16bit_word_a |= _event_info_to_pack -> _csc_quality & 0xf; _16bit_word_a <<= 4;
  _16bit_word_a |= _event_info_to_pack -> _csc_quality & 0xf;
  _16bit_word_a |= 0x8000;

  _16bit_word_b = _event_info_to_pack -> _csc_bc0 & 0x1; _16bit_word_b <<= 1;
  _16bit_word_b |= _event_info_to_pack -> _csc_bxe & 0x1; _16bit_word_b <<= 1;
  _16bit_word_b |= _event_info_to_pack -> _csc_lr & 0x1; _16bit_word_b <<= 4;
  _16bit_word_b |= _event_info_to_pack -> _csc_id & 0xf; _16bit_word_b <<= 8;
  _16bit_word_b |= _event_info_to_pack -> _csc_clct_key_half_strip & 0xff;
  _16bit_word_b |= 0x8000;

  _16bit_word_c = _event_info_to_pack -> _csc_afff & 0x1; _16bit_word_c <<= 1;
  _16bit_word_c |= _event_info_to_pack -> _csc_cik & 0x1; _16bit_word_c <<= 1;
  _16bit_word_c |= _event_info_to_pack -> _csc_nit & 0x1; _16bit_word_c <<= 12;
  _16bit_word_c |= _event_info_to_pack -> _csc_me_bxn & 0xfff;

  _16bit_word_d = _event_info_to_pack -> _csc_afef & 0x1; _16bit_word_d <<= 1;
  _16bit_word_d |= _event_info_to_pack -> _csc_se & 0x1; _16bit_word_d <<= 1;
  _16bit_word_d |= _event_info_to_pack -> _csc_sm & 0x1; _16bit_word_d <<= 4;
  _16bit_word_d |= _event_info_to_pack -> _csc_epc & 0xf; _16bit_word_d <<= 1;
  _16bit_word_d |= _event_info_to_pack -> _csc_af & 0x1; _16bit_word_d <<=3;
  _16bit_word_d |= _event_info_to_pack -> _csc_station & 0x7; _16bit_word_d <<= 1;
  _16bit_word_d |= _event_info_to_pack -> _csc_vp & 0x1; _16bit_word_d <<= 3;
  _16bit_word_d |= _event_info_to_pack -> _csc_tbin_num & 0x7;

  
  std::cout << "after packing word a = " << _16bit_word_a << std::endl;
  std::cout << "after packing word b = " << _16bit_word_b << std::endl;
  std::cout << "after packing word c = " << _16bit_word_c << std::endl;
  std::cout << "after packing word d = " << _16bit_word_d << std::endl;


  *ptr = merge_abcd_words();

  return _nominal_buffer_size;


}
