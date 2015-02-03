#ifndef __EMUTF_CSCMEDATA_BLOCK_OPERATOR__
#define __EMUTF_CSCMEDATA_BLOCK_OPERATOR__

#include "mtf7/types.h"
#include "mtf7/emutf_block_operator.h"

namespace mtf7{

  class emutf_cscmedata_block_operator: public emutf_block_operator{

  public:

    emutf_cscmedata_block_operator ( error_value *error_status ):
        emutf_block_operator( error_status ) {}

    emutf_cscmedata_block_operator ( error_value *error_status, emutf_event *unpacked_event_info ):
        emutf_block_operator( error_status, unpacked_event_info ) {}
    
    emutf_cscmedata_block_operator ( error_value *error_status, const emutf_event *_event_info_to_unpack ):
        emutf_block_operator( error_status, _event_info_to_unpack ) {}

    virtual unsigned long        pack   ( );
    virtual const word_64bit    *unpack (const word_64bit *at_ptr);

    static const unsigned int _nominal_buffer_size = 1; // buffer size in 64-bit words

  };

}


#endif
