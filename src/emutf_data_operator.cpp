#include "mtf7/emutf_data_operator.h"

mtf7::emutf_data_operator::emutf_data_operator( const char *data_release ):
  data_operator(data_release)
{}

mtf7::error_value mtf7::emutf_data_operator::unpack( const word_64bit *buffer ){

  return mtf7::NO_ERROR;

}


const mtf7::word_64bit   *mtf7::emutf_data_operator::pack( void *event_void_ptr ){

  return 0;

}
