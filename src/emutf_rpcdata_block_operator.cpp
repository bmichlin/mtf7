#include "mtf7/emutf_rpcdata_block_operator.h"

const mtf7::word_64bit *mtf7::emutf_rpcdata_block_operator::unpack ( const mtf7::word_64bit *at_ptr ){

  if (*_error_status != mtf7::NO_ERROR) return 0;

  if (at_ptr == 0) { *_error_status = mtf7::NULL_BUFFER_PTR; return 0; }

  break_into_abcd_words( *at_ptr ); at_ptr++;
  
  if ( _16bit_word_a & 0x8000 )              *_error_status = mtf7::BLOCK_COUNTER_FORMAT; // check if D15 is 0
  if ( _16bit_word_b & 0x8000 )              *_error_status = mtf7::BLOCK_COUNTER_FORMAT; // check if D15 is 0
  if ( (_16bit_word_c & 0x8000 ) != 0x8000 )  *_error_status = mtf7::BLOCK_COUNTER_FORMAT; // check if D15 is 1
  if ( _16bit_word_d & 0x8000 )              *_error_status = mtf7::BLOCK_COUNTER_FORMAT; // check if D15 is 0
  if (*_error_status != mtf7::NO_ERROR) return 0;


  _unpacked_event_info -> _rpc_partition_data = (_16bit_word_a & 0xff); _16bit_word_a >>= 8; 
  _unpacked_event_info -> _rpc_partition_num = (_16bit_word_a & 0xf); _16bit_word_a >>= 4;
  _unpacked_event_info -> _rpc_prt_delay = (_16bit_word_a & 0x7);

  _unpacked_event_info -> _rpc_link_number = (_16bit_word_b & 0x1f); _16bit_word_b >>= 5;
  _unpacked_event_info -> _rpc_lb = (_16bit_word_b & 0x3); _16bit_word_b >>= 2;
  _unpacked_event_info -> _rpc_eod = (_16bit_word_b & 0x1); _16bit_word_b >>= 1;
  _unpacked_event_info -> _rpc_bcn = (_16bit_word_b & 0x7f);

  _unpacked_event_info -> _rpc_bxn = (_16bit_word_c & 0xfff); _16bit_word_c >>= 12;
  _unpacked_event_info -> _rpc_bc0 = (_16bit_word_c & 0x1);

  _unpacked_event_info -> _rpc_tbin_num = (_16bit_word_d & 0x7);  

  return at_ptr;

}


unsigned long mtf7::emutf_rpcdata_block_operator::pack(){

  mtf7::word_64bit *buffer = create_buffer ( _nominal_buffer_size );
  
  mtf7::word_64bit *ptr = buffer;
  
  // _16bit_word_a = _event_info_to_pack -> _csc_key_wire_group & 0x7f; _16bit_word_a <<= 4;
  // _16bit_word_a |= _event_info_to_pack -> _csc_quality & 0xf; _16bit_word_a <<= 4;
  // _16bit_word_a |= _event_info_to_pack -> _csc_quality & 0xf;
  // _16bit_word_a |= 0x8000;

  // _16bit_word_b = _event_info_to_pack -> _csc_bc0 & 0x1; _16bit_word_b <<= 1;
  // _16bit_word_b |= _event_info_to_pack -> _csc_bxe & 0x1; _16bit_word_b <<= 1;
  // _16bit_word_b |= _event_info_to_pack -> _csc_lr & 0x1; _16bit_word_b <<= 4;
  // _16bit_word_b |= _event_info_to_pack -> _csc_id & 0xf; _16bit_word_b <<= 8;
  // _16bit_word_b |= _event_info_to_pack -> _csc_clct_key_half_strip & 0xff;
  // _16bit_word_b |= 0x8000;

  // _16bit_word_c = _event_info_to_pack -> _csc_afff & 0x1; _16bit_word_c <<= 1;
  // _16bit_word_c |= _event_info_to_pack -> _csc_cik & 0x1; _16bit_word_c <<= 1;
  // _16bit_word_c |= _event_info_to_pack -> _csc_nit & 0x1; _16bit_word_c <<= 12;
  // _16bit_word_c |= _event_info_to_pack -> _csc_me_bxn & 0xfff;

  // _16bit_word_d = _event_info_to_pack -> _csc_afef & 0x1; _16bit_word_d <<= 1;
  // _16bit_word_d |= _event_info_to_pack -> _csc_se & 0x1; _16bit_word_d <<= 1;
  // _16bit_word_d |= _event_info_to_pack -> _csc_sm & 0x1; _16bit_word_d <<= 4;
  // _16bit_word_d |= _event_info_to_pack -> _csc_epc & 0xf; _16bit_word_d <<= 1;
  // _16bit_word_d |= _event_info_to_pack -> _csc_af & 0x1; _16bit_word_d <<=3;
  // _16bit_word_d |= _event_info_to_pack -> _csc_station & 0x7; _16bit_word_d <<= 1;
  // _16bit_word_d |= _event_info_to_pack -> _csc_vp & 0x1; _16bit_word_d <<= 3;
  // _16bit_word_d |= _event_info_to_pack -> _csc_tbin_num & 0x7;

  
  *ptr = merge_abcd_words();

  return _nominal_buffer_size;


}
