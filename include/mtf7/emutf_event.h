#ifndef __MTF7_EMU_EVENT__ 
#define __MTF7_EMU_EVENT__ 1

#include "mtf7/types.h"

namespace mtf7{

  struct emutf_event {

    word_32bit _l1a;    
    word_16bit _bxn;    
    word_8bit  _sp_ts, _sp_ersv, _sp_addr, _tbin;   
    word_1bit  _ddm, _spa, _rpca, _skip, _rdy, _bsy, _osy, _wof;    
    
    word_16bit _ME1a, _ME1b, _ME2, _ME3, _ME4;
    word_32bit _RPC, _TC, _OC;

  };

  static void clear_emutf_event( emutf_event *event_info ){
    
    event_info -> _l1a = 0;
    event_info -> _bxn = 0;
    
    event_info -> _sp_ts   = 0; 
    event_info -> _sp_ersv = 0; 
    event_info -> _sp_addr = 0; 
    event_info -> _tbin    = 0;
    
    event_info -> _ddm  = false; 
    event_info -> _spa  = false;
    event_info -> _rpca = false;
    event_info -> _skip = false; 
    event_info -> _rdy  = false; 
    event_info -> _bsy  = false; 
    event_info -> _osy  = false; 
    event_info -> _wof  = false;    
    
    event_info -> _ME1a = 0;
    event_info -> _ME1b = 0; 
    event_info -> _ME2  = 0; 
    event_info -> _ME3  = 0; 
    event_info -> _ME4  = 0;
    
    event_info -> _RPC = 0; 
    event_info -> _TC  = 0;
    event_info -> _OC  = 0;
    
  }

}

#endif
