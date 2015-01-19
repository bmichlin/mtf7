#include "mtf7/emutf_amc13_header_block_operator.h"

//----------------------------------------------------------------------
// mtf7::emutf_header_operator::emutf_amc13_header_block_operator( error_value *error_status, emutf_event *event_info ): emutf_block_operator( error_status, event_info ){}

//----------------------------------------------------------------------
const mtf7::word_64bit *mtf7::emutf_amc13_header_block_operator::unpack( const word_64bit *at_ptr ){

   if (*_error_status != mtf7::NO_ERROR) return 0;

   _buffer_start_ptr = at_ptr;

  if (at_ptr== 0){ *_error_status = mtf7::NULL_BUFFER_PTR; return 0; }

  // - - - - - - - - - - - - - - - - - - - - - 
  // process 1st 64-bit word ...
  break_into_abcd_words( *at_ptr); at_ptr++;

  // check format identifiers
  // note: no format identifier for AMC13 header (only in CDF header)

  // set values derived from 1st word
  _unpacked_event_info -> _amc13_header_ufov  =  _16bit_word_a & 0xf; _16bit_word_a >>= 4;
  _unpacked_event_info -> _amc13_header_res  =  _16bit_word_a & 0xf; _16bit_word_a >>= 4;
  _unpacked_event_info -> _amc13_header_namc  =  _16bit_word_a & 0xf;

  // next 16 bits are reserved and set to 0.

  _unpacked_event_info -> _amc13_header_orn = _16bit_word_b & 0xfff0;
  _unpacked_event_info -> _amc13_header_orn |= (_16bit_word_c & 0xffff) << 12;
  _unpacked_event_info -> _amc13_header_orn |= (_16bit_word_a & 0xf) << 28;

  return at_ptr;

}

unsigned long mtf7::emutf_amc13_header_block_operator::pack(){

  mtf7::word_64bit *buffer = create_buffer ( _nominal_buffer_size );

  mtf7::word_64bit *ptr = buffer;

  // pack 1st 64bit word --------------------

  mtf7::word_32bit tmp_l1a = _event_info_to_pack -> _l1a;

  _16bit_word_a = _event_info_to_pack -> _amc13_header_ufov & 0xf; _16bit_word_a <<= 4;
  _16bit_word_a |= _event_info_to_pack -> _amc13_header_res & 0xf; _16bit_word_a <<= 4;
  _16bit_word_a |= _event_info_to_pack -> _amc13_header_namc & 0xf; _16bit_word_a <<= 4;
  _16bit_word_a |= 0x0;

  _16bit_word_b = 0x0000;
  _16bit_word_b |= (_event_info_to_pack -> _amc13_header_orn >> 28) & 0xf;

  _16bit_word_c = (_event_info_to_pack -> _amc13_header_orn >> 12) & 0xffff;
  _16bit_word_d = _event_info_to_pack -> _amc13_header_orn & 0xfff; _16bit_word_d <<= 4;
  _16bit_word_d |= 0x0;


  *ptr = merge_abcd_words(); ptr++;
  
  return _nominal_buffer_size;

}
