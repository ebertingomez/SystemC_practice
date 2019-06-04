#include <systemc.h>
#include <stdlib.h> 

SC_MODULE(mod_pgcd) {
    // Inputs
    sc_in<bool> clk;
    sc_in<bool> valid;
    sc_in< sc_uint<8> > A;
    sc_in< sc_uint<8> > B;
    
    // Outputs
    sc_out< bool > ready;
    sc_out< sc_uint<8> > pgcd;

   SC_CTOR(mod_pgcd):valid("valid"),A("A"),B("B"),ready("ready"),pgcd("pgcd")
   {
       SC_CTHREAD(mthread,clk.pos());
   }

    void mthread(){
        unsigned int current_pgcd;
        for(;;){
            wait();
            if (valid.read()){
                current_pgcd = compute_pgcd(A.read().to_int(),B.read().to_int());
                pgcd.write(sc_uint<8>(current_pgcd));
                ready.write(1);
                wait(1);
                ready.write(0);
            }
        }
    }

    int compute_pgcd(unsigned int a,unsigned int b){
        int bigger = (a>b) ? a : b;
        wait(1);
        int smaller = (a<b) ? a : b;
        wait(1);
        int diff;
        do {
            wait(1);
            diff = bigger - smaller;
            wait(1);
            bigger = (diff>smaller) ? diff : smaller;
            wait(1);
            smaller = (diff<smaller) ? diff : smaller;
            wait(1);
        }
        while (diff >0);
        return bigger;
    }
};

int sc_main(int argc, char * argv[])
{
    sc_clock clk("clk",40,SC_NS);
    sc_signal< bool> valid;
    sc_signal< sc_uint<8> > A;
    sc_signal< sc_uint<8> > B;
    
    sc_signal< bool > ready;
    sc_signal< sc_uint<8> > pgcd;

    mod_pgcd module_pgcd("module_pgcd");
    module_pgcd.clk(clk);
    module_pgcd.valid(valid);
    module_pgcd.A(A);
    module_pgcd.B(B);
    module_pgcd.ready(ready);
    module_pgcd.pgcd(pgcd);

    sc_trace_file *trace_f;
    trace_f = sc_create_vcd_trace_file ("pgcd_2");
    trace_f->set_time_unit(10,SC_NS);
    sc_trace(trace_f, module_pgcd.clk, "clk");
    sc_trace(trace_f, module_pgcd.pgcd, "pgcd");
    sc_trace(trace_f, module_pgcd.valid, "valid");
    sc_trace(trace_f, module_pgcd.ready, "ready");
    sc_trace(trace_f, module_pgcd.A, "A");
    sc_trace(trace_f, module_pgcd.B, "B");

    A = rand() % 200 + 1;
    B = rand() % 200 + 1;
    valid = false;
    sc_start(40,SC_NS);
    valid = true;
    sc_start(40,SC_NS);
    valid = false;
    sc_start(40,SC_NS);
    for (int i = 0 ; i<10000 ; i++){
        if (ready){
            cout << "--> @ " << sc_time_stamp() << " pgcd = " << pgcd << endl;
            A = rand() % 200 + 1;
            B = rand() % 200 + 1;
            sc_start(40,SC_NS);
            valid = true;
            sc_start(40,SC_NS);
            valid = false;
            sc_start(40,SC_NS);
        }
        else
            sc_start(20,SC_NS);
        
    }
    sc_close_vcd_trace_file(trace_f);
    return 0;
}