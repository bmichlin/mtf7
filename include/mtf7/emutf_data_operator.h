#ifndef __MTF7_EMUTF_DATA_OPERATOR__
#define __MTF7_EMUTF_DATA_OPERATOR__

#include "mtf7/data_operator.h"
#include "mtf7/emutf_event.h"

namespace mtf7{

  class emutf_data_operator: public data_operator {

  public:

    emutf_data_operator( const char *dataformat_release );

    virtual error_value       unpack( const word_64bit *buffer );
    virtual const word_64bit   *pack( void *event_void_ptr );

    const emutf_event *get_event_info(){ return &_event; }

  protected:

    emutf_event _event;

  };

}

#endif
