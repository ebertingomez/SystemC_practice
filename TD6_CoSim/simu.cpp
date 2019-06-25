#include <systemc.h>
#include <stdlib.h> 
#include "pgcd.hpp"

#ifdef MTI_SYSTEMC
#include "PGCD.hpp"
#endif
#ifdef VM_SC
#include "VPGCD.h"
#endif

SC_MODULE(generator) {
    sc_in<bool> clk;
    sc_in< bool > ready;
    sc_out<bool> valid;
    sc_out< sc_uint<8> > a;
    sc_out< sc_uint<8> > b;

    SC_CTOR(generator):clk("clk"),valid("valid"),a("a"),b("b"),ready("ready")
    {
        SC_CTHREAD(m_gen,clk.pos());
    }
    void m_gen() {
        a.write(rand() % 200 + 1);
        b.write(rand() % 200 + 1);
        valid.write(false);
        wait(1);
        valid.write(true);
        wait(1);
        valid.write(false);
        for(int i=0;i<100;i++){
            wait();
            if (ready.read()){
                a.write(rand() % 200 + 1);
                b.write(rand() % 200 + 1);
                valid.write(true);
                wait(1);
                valid.write(false);
            }
        }
        sc_stop();
    }

};

SC_MODULE(verification) {
    sc_in< bool > ready;
    sc_in< sc_uint<8> > pgcd;
    sc_in< sc_uint<8> > a;
    sc_in< sc_uint<8> > b;
    SC_CTOR(verification):ready("ready"),pgcd("pgcd"),a("a"),b("b")
    {
        SC_METHOD(m_verif);
        sensitive<<ready.pos();
    }

    void m_verif(){
        if (pgcd.read().to_uint() != 
            compute_pgdc(a.read().to_uint(),b.read().to_uint()))
        {
            std::cout<<"PGCD missmatch"<<std::endl;
            exit(1);
        }
    }

};



int sc_main(int argc, char * argv[])
{
    sc_clock clk("clk",40,SC_NS);
    sc_signal< bool> valid;
    sc_signal< sc_uint<8> > a;
    sc_signal< sc_uint<8> > b;
    sc_signal< bool > ready;
    sc_signal< sc_uint<8> > pgcd;

    generator mod_generator("mod_generator");
    verification mod_verification("mod_verification");
    #ifdef MTI_SYSTEMC
    PGCD PGCD_0("PGCD_0", "PGCD");
    #endif
    #ifdef VM_SC
    VPGCD PGCD_0("PGCD_0");
    #endif    

    mod_generator.clk(clk);
    mod_generator.ready(ready);
    mod_generator.valid(valid);
    mod_generator.a(a);
    mod_generator.b(b);

    mod_verification.ready(ready);
    mod_verification.pgcd(pgcd);
    mod_verification.a(a);
    mod_verification.b(b);

    PGCD_0.clk(clk);
    PGCD_0.ready(ready);
    PGCD_0.valid(valid);
    PGCD_0.pgcd(pgcd);
    PGCD_0.a(a);
    PGCD_0.b(b);

    sc_trace_file *trace_f;
    trace_f = sc_create_vcd_trace_file ("pgcd");
    trace_f->set_time_unit(10,SC_NS);
    sc_trace(trace_f, clk, "clk");
    sc_trace(trace_f, pgcd, "pgcd");
    sc_trace(trace_f, valid, "valid");
    sc_trace(trace_f, ready, "ready");
    sc_trace(trace_f, a, "a");
    sc_trace(trace_f, a, "b");

    sc_start();

    sc_close_vcd_trace_file(trace_f);
    
    return 0;
}

