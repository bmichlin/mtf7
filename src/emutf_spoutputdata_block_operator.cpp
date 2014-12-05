#include "mtf7/emutf_spoutputdata_block_operator.h"

  // SP Output Data Record
    word_32bit _track_pt_lut_address;
    word_16bit _track_phi_inner, _track_phi_outer, _track_eta, _track_pt;
    word_8bit _track_quality, _track_bx, _track_me4_id, _track_me3_id, _track_me2_id, _track_me1_id, _track_tbin_num, _track_me4_tbin, _track_me3_tbin, _track_me2_tbin, _track_me1_tbin;
    word_1bit _track_hl, _track_c, _track_vc, _track_se, _track_bc0; 

bool mtf7::emutf_spoutputdata_block_operator::isd15true ( const mtf7::word_16bit *word ){

if( ( _16bit_word_a & 0x8000 ) == 0x8000 )
  return true;

}

const mtf7::word_64bit *mtf7::emutf_spoutputdata_block_operator::unpack ( const mtf7::word_64bit *at_ptr ){

  if (*_error_status != mtf7::NO_ERROR) return 0;

  if (at_ptr == 0) { *_error_status = mtf7::NULL_BUFFER_PTR; return 0; }


  // 1st 64 bit word
  break_into_abcd_words( *at_ptr ); at_ptr++;
  
  if (isd15true(_16bit_word_a))  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; 
  if (!isd15true(_16bit_word_b))  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; 
  if (isd15true(_16bit_word_c))  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; 
  if (!isd15true(_16bit_word_d))  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; 
  if (*_error_status != mtf7::NO_ERROR) return 0;

  _unpacked_event_info -> _track_phi_innner  = _16bit_word_a & 0xfff; _16bit_word_a >>= 12;
  _unpacked_event_info -> _track_vc = _16bit_word_a & 0x1; _16bit_word_a >>= 1;
  _unpacked_event_info -> _track_c = _16bit_word_a & 0x1; _16bit_word_a >>= 1;
  _unpacked_event_info -> _track_hl = _16bit_word_a & 0x1;

  _unpacked_event_info -> _track_phi_outer = _16bit_word_b & 0xfff; _16bit_word_b >>= 12;
  _unpacked_event_info -> _track_bc0 = _16bit_word_b & 0x1; _16bit_word_b >>= 1;
  _unpacked_event_info -> _track_se = _16bit_word_b & 0x1;

  _unpacked_event_info -> _track_eta = _16bit_word_c & 0x1ff; _16bit_word_c >>= 9;
  _unpacked_event_info -> _track_quality = _16bit_word_c & 0xf;

  _unpacked_event_info -> _track_pt = _16bit_word_d & 0x1ff; _16bit_word_d >>=9 ;
  _unpacked_event_info -> _track_bx = _16bit_word_d & 0x7; 

  // 2nd 64 bit word
  break_into_abcd_words( *at_ptr ); at_ptr++;
  
  if (!isd15true(_16bit_word_a))  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; 
  if (isd15true(_16bit_word_b))  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; 
  if (isd15true(_16bit_word_c))  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; 
  if (!isd15true(_16bit_word_d))  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; 
  if (*_error_status != mtf7::NO_ERROR) return 0;

  _unpacked_event_info -> _track_me1_id = _16bit_word_a & 0x7; _16bit_word_a >>= 3;
  _unpacked_event_info -> _track_me2_id = _16bit_word_a & 0x3; _16bit_word_a >>= 2;
  _unpacked_event_info -> _track_me3_id = _16bit_word_a & 0x3; _16bit_word_a >>= 2;
  _unpacked_event_info -> _track_me4_id = _16bit_word_a & 0x3;

  _unpacked_event_info -> _track_me1_tbin = _16bit_word_b & 0x7; _16bit_word_b >>= 3;
  _unpacked_event_info -> _track_me2_tbin = _16bit_word_b & 0x7; _16bit_word_b >>= 3;
  _unpacked_event_info -> _track_me3_tbin = _16bit_word_b & 0x7; _16bit_word_b >>= 3;
  _unpacked_event_info -> _track_me4_tbin = _16bit_word_b & 0x7; _16bit_word_b >>= 3;
  _unpacked_event_info -> _track_tbin_num = _16bit_word_b & 0x7; 

  _unpacked_event_info -> _track_pt_lut_address = _16bit_word_c & 0x7fff;
  
  _unpacked_event_info -> _track_pt_lut_address |= (_16bit_word_d & 0x7fff) << 15;


  return at_ptr;

}


unsigned long mtf7::emutf_spoutputdata_block_operator::pack(){

  mtf7::word_64bit *buffer = create_buffer ( _nominal_buffer_size );
  
  mtf7::word_64bit *ptr = buffer;
  
  // _16bit_word_a = _event_info_to_pack -> _rpc_prt_delay & 0x7; _16bit_word_a <<= 4;
  // _16bit_word_a |= _event_info_to_pack -> _rpc_partition_num & 0xf; _16bit_word_a <<= 8;
  // _16bit_word_a |= _event_info_to_pack -> _rpc_partition_data & 0xff; 
  
  // _16bit_word_b = _event_info_to_pack -> _rpc_bcn & 0x3f; _16bit_word_b <<= 1;
  // _16bit_word_b |= _event_info_to_pack -> _rpc_eod & 0x1; _16bit_word_b <<= 2;
  // _16bit_word_b |= _event_info_to_pack -> _rpc_lb & 0x3; _16bit_word_b <<= 5;
  // _16bit_word_b |= _event_info_to_pack -> _rpc_link_number & 0x1f;

  // _16bit_word_c = _event_info_to_pack -> _rpc_bc0 & 0x1; _16bit_word_c <<= 14;
  // _16bit_word_c |= _event_info_to_pack -> _rpc_bxn & 0xff;
  // _16bit_word_c |= 0x8000;

  // _16bit_word_d = _event_info_to_pack -> _rpc_tbin & 0x7;

  
  *ptr = merge_abcd_words();

  return _nominal_buffer_size;


}