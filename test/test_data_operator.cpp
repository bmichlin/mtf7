#include "mtf7/emutf_header_block_operator.h"
#include "mtf7/emutf_event_generator.h"
#include "mtf7/emutf_data_operator.h"
#include "mtf7/emutf_operator_builder.h"
#include <string>
#include <iostream>

int main(){
	
	mtf7::event_generator mygen;

	//filename withuot extension
	std::string filename("test");
	mygen.setFileName(filename);
	// this will generate 10 events and write them in a text file and a binary file. 
	mygen.generateEvents(10);


	// ---------------
	// Testing packing using data operator
	// ---------------

	// create the pointer to the event to pack and its error handler
	mtf7::emutf_event * _generated_event = new mtf7::emutf_event();
	mtf7::error_value * err = new mtf7::error_value();
	// fill the event with random information
	mygen.generateEvent(1, _generated_event);
	//std::cout << "l1a = " << event_to_pack -> _l1a << std::endl;

	const mtf7::emutf_event * event_to_pack = &*_generated_event;

//	---- Testing full constructor
	// mtf7::emutf_header_block_operator *header = new mtf7::emutf_header_block_operator(err, event_to_pack);
	// //test in packing
	// header->pack();
	// std::cout << "Header packed!" << std::endl;
//  --- This works!  ---



//	Testing alternative constructor
	// mtf7::emutf_header_block_operator *header = new mtf7::emutf_header_block_operator(err);
	// std::cout << "setting the info" << std::endl;
	// header->set_event_info_to_pack(event_to_pack);
	// std::cout << "packing" << std::endl;
	// header->pack();
	// std::cout << "Header packed!" << std::endl;
//  --- This works!  --- Tohugh it raises a question: why I can't have the "set_event_info as virtual in the block_operator class"


	const char* data_release = "test";

	mtf7::emutf_operator_builder * my_operator = new mtf7::emutf_operator_builder();
	mtf7::emutf_data_operator * my_data_operator = my_operator -> get_data_operator(data_release);

//	mtf7::emutf_data_operator * my_operator = new mtf7::emutf_data_operator(data_release);

	// create the operator for the header block
    //	mtf7::emutf_header_block_operator * my_operator = new mtf7::emutf_header_block_operator( err, event_to_pack );
	// set the event to pack
	// you aways need to set_info_to_pack when you want to pack. look at emutf_block_operator.h
	my_data_operator -> set_event_info_to_pack(event_to_pack);
	// packing the event 
	const mtf7::word_64bit * packed_event = my_data_operator -> pack();
	// // and now unpacking
	my_data_operator->unpack(packed_event);

	return 0;

}
