#ifndef _SCGENMOD_PGCD_
#define _SCGENMOD_PGCD_

#include "systemc.h"

class PGCD : public sc_foreign_module
{
public:
    sc_in<bool> clk;
    sc_in<bool> valid;
    sc_in<sc_uint<8> > a;
    sc_in<sc_uint<8> > b;
    sc_out<bool> ready;
    sc_out<sc_uint<8> > pgcd;


    PGCD(sc_module_name nm, const char* hdl_name)
     : sc_foreign_module(nm),
       clk("clk"),
       valid("valid"),
       a("a"),
       b("b"),
       ready("ready"),
       pgcd("pgcd")
    {
        elaborate_foreign_module(hdl_name);
    }
    ~counter()
    {}

};

#endif