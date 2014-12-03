#include "mtf7/emutf_event_generator.h"
#include <string>

int main(){
	
	mtf7::event_generator mygen;

	//filename withuot extension
	std::string filename("test");
	mygen.setFileName(filename);
	mygen.generateEvents(10);



	return 0;

}