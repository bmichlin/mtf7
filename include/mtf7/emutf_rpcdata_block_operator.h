#ifndef __EMUTF_RPCDATA_BLOCK_OPERATOR__
#define __EMUTF_RPCDATA_BLOCK_OPERATOR__

#include "mtf7/types.h"
#include "mtf7/emutf_block_operator.h"

namespace mtf7{

  class emutf_rpcdata_block_operator: public emutf_block_operator{

  public:

  	// Minimal constructor with only error value.
    emutf_rpcdata_block_operator ( error_value *error_status ):
        emutf_block_operator( error_status ) {}

  	// Constructor with event info to unpack for higher level operations.
    emutf_rpcdata_block_operator ( error_value *error_status, emutf_event *unpacked_event_info ):
        emutf_block_operator( error_status, unpacked_event_info ) {}

    // Constructor with event info to pack for higher level operations.
    emutf_rpcdata_block_operator ( error_value *error_status, const emutf_event *event_info_to_pack ):
        emutf_block_operator( error_status, event_info_to_pack ) {}

    virtual unsigned long        pack   ( );
    virtual const word_64bit    *unpack (const word_64bit *at_ptr);

    static const unsigned int _nominal_buffer_size = 1; // buffer size in 64-bit words

  };

}


#endif
