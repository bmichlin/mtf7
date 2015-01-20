#include "mtf7/emutf_operator_builder.h"
#include "mtf7/emutf_data_operator.h"
#include "mtf7/emutf_amc13_header_block_operator.h"
#include "mtf7/emutf_header_block_operator.h"
#include <iostream>

//----------------------------------------------------------------------
mtf7::emutf_data_operator *mtf7::emutf_operator_builder::get_data_operator( const char *data_release ){

  emutf_data_operator *built_dataop = new emutf_data_operator( data_release );

  error_value *error_ptr = &( built_dataop -> _error_status ); 

  built_dataop -> _workers = assemble_block_vector ( data_release, error_ptr );

  return built_dataop;

}

//----------------------------------------------------------------------
mtf7::block_operator_vector *mtf7::emutf_operator_builder::assemble_block_vector( const char *data_release, mtf7:: error_value *error_ptr ){

	mtf7::block_operator_vector * _operator_vector;
	mtf7::emutf_event * _event_info; // dummy event info

	// test datarealese
	if(data_release == "test"){

		std::cout << "Building operator builder" << std::endl;
		//amc13 header
		mtf7::emutf_amc13_header_block_operator * amc13_header = new mtf7::emutf_amc13_header_block_operator( error_ptr, _event_info );
		_operator_vector->push_back(amc13_header);
		// header
		mtf7::emutf_header_block_operator * header = new mtf7::emutf_header_block_operator( error_ptr, _event_info );
		_operator_vector->push_back(header);

		return _operator_vector;
	}

	else
		return 0;

}
