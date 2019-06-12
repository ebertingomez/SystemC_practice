#include <systemc.h>
#include <stdlib.h> 
#include "wrapper.hpp"
#include "pgcd.hpp"
SC_MODULE(generator) {
    sc_inout<bool> clk;
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
        for(int i=0;i<10000;i++){
            wait();
            if (ready.read()){
                a.write(rand() % 200 + 1);
                b.write(rand() % 200 + 1);
                valid = true;
                wait(1);
                valid = false;
            }
        }
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

SC_MODULE(testeur) {
    // Inputs
    sc_inout<bool> clk;
    sc_in< bool > ready;
    sc_in< sc_uint<8> > pgcd;
    // Outputs
    sc_out<bool> valid;
    sc_out< sc_uint<8> > a;
    sc_out< sc_uint<8> > b;
    // interne
    sc_signal<sc_uint<8>> a_i;
    sc_signal<sc_uint<8>> b_i;
    // sous modules
    generator generator_i;
    verification verification_i;
    SC_CTOR(testeur):generator_i("generator_i"),verification_i("verification_i")
    {
        // connexions aux I/O
        generator_i.clk(clk);
        generator_i.valid(valid);
        generator_i.ready(ready);
        generator_i.a(a);
        generator_i.b(b);
        verification_i.ready(ready);
        verification_i.pgcd(pgcd);
        // connexion interne
        verification_i.a(a);
        verification_i.b(b);
    }

};



int sc_main(int argc, char * argv[])
{
    sc_clock clk("clk",40,SC_NS);
    testeur mod_testeur("mod_testeur");
    Vpgcd VPGCD_0("VPGCD_0");

    mod_testeur.clk(clk);
    mod_testeur.ready(VPGCD.ready);
    mod_testeur.pgcd(VPGCD.pgcd);
    VPGCD.clk(clk);
    VPGCD.valid(mod_testeur.valid);
    VPGCD.a(mod_testeur.a);
    VPGCD.b(mod_testeur.b);
    
    return 0;
}