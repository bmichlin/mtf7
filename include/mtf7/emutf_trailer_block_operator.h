#ifndef __MTF7_EMUTF_TRAILER_OPERATOR__
#define __MTF7_EMUTF_TRAILER_OPERATOR__


#include "mtf7/types.h"
#include "mtf7/emutf_block_operator.h"

namespace mtf7{

  class emutf_trailer_block_operator: public emutf_block_operator{

  public:

    emutf_trailer_block_operator ( error_value *error_status, emutf_event *unpacked_event_info ): 
	emutf_block_operator( error_status, unpacked_event_info ) {}
    virtual unsigned long        pack   ( );
    virtual const word_64bit    *unpack (const word_64bit *at_ptr);

    static const unsigned int _nominal_buffer_size = 2; // buffer size in 64-bit words
  

  };

}

#endif
