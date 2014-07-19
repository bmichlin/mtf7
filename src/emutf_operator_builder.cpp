#include "mtf7/emutf_operator_builder.h"
#include "mtf7/emutf_data_operator.h"

//----------------------------------------------------------------------
mtf7::emutf_data_operator *mtf7::emutf_operator_builder::get_data_operator( const char *data_release ){

  emutf_data_operator *built_dataop = new emutf_data_operator( data_release );

  error_value *error_ptr = &( built_dataop -> _error_status ); 

  built_dataop -> _workers = assemble_block_vector ( data_release, error_ptr );

  return built_dataop;

}

mtf7::block_operator_vector *mtf7::emutf_operator_builder::assemble_block_vector( const char *data_release, mtf7:: error_value *error_ptr ){
  // nothing yet, need to build the block operators first ...
  return 0;

}
