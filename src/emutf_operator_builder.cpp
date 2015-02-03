#include "mtf7/emutf_operator_builder.h"
#include "mtf7/emutf_data_operator.h"
#include "mtf7/emutf_amc13_header_block_operator.h"
#include "mtf7/emutf_header_block_operator.h"
#include "mtf7/emutf_counter_block_operator.h"
#include "mtf7/emutf_cscmedata_block_operator.h"
#include "mtf7/emutf_rpcdata_block_operator.h"
#include "mtf7/emutf_spoutputdata_block_operator.h"
#include "mtf7/emutf_trailer_block_operator.h"
#include "mtf7/emutf_amc13_trailer_block_operator.h"
#include "mtf7/emutf_debug.h"
#include <iostream>

//----------------------------------------------------------------------
mtf7::emutf_data_operator *mtf7::emutf_operator_builder::get_data_operator( const char *data_release ){

  emutf_data_operator *built_dataop = new emutf_data_operator( data_release );

  error_value *error_ptr = &( built_dataop -> _error_status ); 

  MTF7_DEBUG_MSG( std::cout,  "######### Building _workers #########" );
  built_dataop -> _workers = assemble_block_vector ( data_release, error_ptr );

  return built_dataop;

}

//----------------------------------------------------------------------
mtf7::block_operator_vector *mtf7::emutf_operator_builder::assemble_block_vector( const char *data_release, mtf7:: error_value *error_ptr ){

	mtf7::block_operator_vector * _operator_vector = new mtf7::block_operator_vector();

	const char * test = "test";
	MTF7_DEBUG( std::cout, data_release );
	// test datarealese
	if(*data_release == *test){

		//amc13 header
		MTF7_DEBUG_MSG( std::cout, " --- AMC13 header");
		// MTF7_DEBUG_MSG( std::cout,  " --- AMC13 header" );
		mtf7::emutf_amc13_header_block_operator * amc13_header = new mtf7::emutf_amc13_header_block_operator( error_ptr );
		_operator_vector->push_back( amc13_header );

		// header
		MTF7_DEBUG_MSG( std::cout, " --- header" );
		mtf7::emutf_header_block_operator * header = new mtf7::emutf_header_block_operator( error_ptr );
		_operator_vector->push_back( header );

		//block of counters
		MTF7_DEBUG_MSG( std::cout, " --- counters");
		mtf7::emutf_counter_block_operator * counters = new mtf7::emutf_counter_block_operator( error_ptr );
		_operator_vector->push_back( counters );

		// csc me data block
		MTF7_DEBUG_MSG( std::cout,  " --- csc me data block" );
		mtf7::emutf_cscmedata_block_operator * cscmedata = new mtf7::emutf_cscmedata_block_operator( error_ptr );
		_operator_vector->push_back( cscmedata );

		// rpc data record
		MTF7_DEBUG_MSG( std::cout,  " --- rpc data block" );
		mtf7::emutf_rpcdata_block_operator * rpcdata = new mtf7::emutf_rpcdata_block_operator( error_ptr );
		_operator_vector->push_back( rpcdata );

		// sp output data record
		MTF7_DEBUG_MSG( std::cout,  " --- sp output data block" );
		mtf7::emutf_spoutputdata_block_operator * spoutputdata = new mtf7::emutf_spoutputdata_block_operator( error_ptr );
		_operator_vector->push_back( spoutputdata );

		// event trailer
		MTF7_DEBUG_MSG( std::cout,  " --- event trailer block" );
		mtf7::emutf_trailer_block_operator * trailer = new mtf7::emutf_trailer_block_operator( error_ptr );
		_operator_vector->push_back( trailer );

		// amc13 trailer
		MTF7_DEBUG_MSG( std::cout,  " --- amc13 trailer block" );
		mtf7::emutf_amc13_trailer_block_operator * amc13trailer = new mtf7::emutf_amc13_trailer_block_operator( error_ptr );
		_operator_vector->push_back( amc13trailer );

		return _operator_vector;
	}

	else
		return 0;

}

