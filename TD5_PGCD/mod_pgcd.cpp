#include <systemc.h>

SC_MODULE(mod_pgcd) {
    // Inputs
    sc_in<bool> clk;
    sc_in<bool> valid;
    sc_in< sc_uint<8> > A;
    sc_in< sc_uint<8> > B;
    
    // Outputs
    sc_out< bool > ready;
    sc_out< sc_uint<8> > pgcd;

    void mthread(){
        unsigned int current_pgcd;
        for(;;){
            wait();
            if (valid.read()){
                current_pgcd = pgcd(A.read().to_int,B.read().to_int);
                pgcd.write(sc_uint<8>(current_pgcd));
                ready = 1;
                wait(1);
                ready = 0;
            }
        }
    }

    int pgcd(unsigned int a,unsigned int b){
        int bigger = (a>b) ? a : b;
        int smaller = (a<b) ? a : b;
        int diff;
        do {
            diff = bigger - smaller;
            bigger = (diff>smaller) ? diff : smaller;
            smaller = (diff<smaller) ? diff : smaller;
        }
        while (diff >0);
        return bigger;
    }

   SC_CTOR(mod_pgcd):A("A"),B("B"),pgcd("pgcd"),ready("ready"),valid("valid")
   {
       SC_CTHREAD(mthread,clk.pos());
   }
};

int sc_main(int argc, char * argv[])
{
    sc_clock clk("clk",10,SC_NS);
    sc_signal<bool> valid;
    sc_uint<8> A;
    sc_uint<8> B;
    
    sc_signal< bool > ready;
    sc_uint<8> pgcd;


    mod_pgcd mod_pgcd("pgcd");
    mod_pgcd.clk(clk);
    mod_pgcd.valid(valid);
    mod_pgcd.A(A);
    mod_pgcd.B(B);
    mod_pgcd.ready(ready);
    mod_pgcd.pgcd(pgcd);

    sc_trace_file *trace_f;
    trace_f = sc_create_vcd_trace_file ("pgcd_1");
    trace_f->set_time_unit(5,SC_NS);
    sc_trace(trace_f, mod_pgcd.pgcd, "pgcd");
    sc_trace(trace_f, mod_pgcd.clk, "clk");
    sc_trace(trace_f, mod_pgcd.valid, "valid");
    sc_trace(trace_f, mod_pgcd.ready, "ready");
    A = 45;
    B = 225;
    sc_start(100,SC_NS);
    valid = true;
    sc_start(10,SC_NS);
    valid = false;
    sc_start(100,SC_NS);
    A = 60;
    B = 36;
    sc_start(100,SC_NS);
    A = 3072;
    B = 96;
    valid = true;
    sc_start(10,SC_NS);
    valid = false;
    sc_start(100,SC_NS);
    sc_close_vcd_trace_file(trace_f);
    return 0;
}