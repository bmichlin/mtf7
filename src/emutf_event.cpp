#include "mtf7/emutf_event.h"

void mtf7::emutf_event::clear_event(){

  _l1a = 0;
  _bxn = 0;
  
  _sp_ts   = 0; 
  _sp_ersv = 0; 
  _sp_addr = 0; 
  _tbin    = 0;
   
  _ddm  = false; 
  _spa  = false;
  _rpca = false;
  _skip = false; 
  _rdy  = false; 
  _bsy  = false; 
  _osy  = false; 
  _wof  = false;    
    
  _ME1a = 0;
  _ME1b = 0; 
  _ME2  = 0; 
  _ME3  = 0; 
  _ME4  = 0;
  
  _RPC = 0; 
  _TC  = 0;
  _OC  = 0;

}
