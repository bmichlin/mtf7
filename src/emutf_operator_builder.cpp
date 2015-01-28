#include "mtf7/emutf_operator_builder.h"
#include "mtf7/emutf_data_operator.h"
#include "mtf7/emutf_amc13_header_block_operator.h"
#include "mtf7/emutf_header_block_operator.h"
#include "mtf7/emutf_cscmedata_block_operator.h"
#include <iostream>

//----------------------------------------------------------------------
mtf7::emutf_data_operator *mtf7::emutf_operator_builder::get_data_operator( const char *data_release ){

  emutf_data_operator *built_dataop = new emutf_data_operator( data_release );

  error_value *error_ptr = &( built_dataop -> _error_status ); 

  std::cout << "Building _workers..." << std::endl;
  built_dataop -> _workers = assemble_block_vector ( data_release, error_ptr );

  return built_dataop;

}

//----------------------------------------------------------------------
mtf7::block_operator_vector *mtf7::emutf_operator_builder::assemble_block_vector( const char *data_release, mtf7:: error_value *error_ptr ){

	mtf7::block_operator_vector * _operator_vector = new mtf7::block_operator_vector();

	const char * test = "test";
	std::cout << "Data release = " << data_release << std::endl;
	// test datarealese
	if(*data_release == *test){

		std::cout << "Building operator builder" << std::endl;



		// header
		std::cout << "header" << std::endl;
		mtf7::emutf_header_block_operator * header = new mtf7::emutf_header_block_operator( error_ptr );
		_operator_vector->push_back( header );

		//amc13 header
		std::cout << "AMC13 header" << std::endl;		
		mtf7::emutf_amc13_header_block_operator * amc13_header = new mtf7::emutf_amc13_header_block_operator( error_ptr );
		std::cout << "AMC13 header push back" << std::endl;
		_operator_vector->push_back( amc13_header );


		// csc me data block
		std::cout << "csc me data block" << std::endl;
		mtf7::emutf_cscmedata_block_operator * cscmedata = new mtf7::emutf_cscmedata_block_operator( error_ptr );
		_operator_vector->push_back( cscmedata );


		return _operator_vector;
	}

	else
		return 0;

}
