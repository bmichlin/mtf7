#ifndef __MTF7_EMU_EVENT__ 
#define __MTF7_EMU_EVENT__ 1

#include "mtf7/types.h"

namespace mtf7{

  class emutf_event{

  public:

    emutf_event(){ clear_event(); };
    void clear_event();

    //---------------------------------
    // event record header information
    //---------------------------------

    word_32bit get_L1A    (){ return _l1a;     }
    word_16bit get_BXN    (){ return _bxn;     }
    word_8bit  get_SP_TS  (){ return _sp_ts;   }
    word_8bit  get_SP_ERSV(){ return _sp_ersv; }
    word_8bit  get_SP_ADDR(){ return _sp_addr; }
    word_8bit  get_TBIN   (){ return _tbin;    }
    word_1bit  get_ddm    (){ return _ddm;     }
    word_1bit  get_spa    (){ return _spa;     }
    word_1bit  get_rpca   (){ return _rpca;    }
    word_1bit  get_skip   (){ return _skip;    }
    word_1bit  get_rdy    (){ return _rdy;     }
    word_1bit  get_bsy    (){ return _bsy;     }
    word_1bit  get_osy    (){ return _osy;     }
    word_1bit  get_wof    (){ return _wof;     }
    
    word_16bit get_ME1a   (){ return _ME1a;    }
    word_16bit get_ME1b   (){ return _ME1b;    }
    word_16bit get_ME2    (){ return _ME2;     }
    word_16bit get_ME3    (){ return _ME3;     }
    word_16bit get_ME4    (){ return _ME4;     }
    
    word_32bit get_RPC    (){ return _RPC;     }
    
    //---------------------------------
    // block counter information
    //---------------------------------

    word_32bit get_TC    (){ return _TC;     }
    word_32bit get_OC    (){ return _OC;     }
    

  protected:
    
    word_32bit _l1a;    
    word_16bit _bxn;    
    word_8bit  _sp_ts, _sp_ersv, _sp_addr, _tbin;   
    word_1bit  _ddm, _spa, _rpca, _skip, _rdy, _bsy, _osy, _wof;    
    
    word_16bit _ME1a, _ME1b, _ME2, _ME3, _ME4;
    word_32bit _RPC, _TC, _OC;

  };

}

#endif
