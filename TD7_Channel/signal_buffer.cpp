#include <systemc.h>

SC_MODULE(mod_test){
    int counter_signal;
    int counter_buffer;
    sc_in< bool > signal;
    sc_in< bool > buffer;

    SC_CTOR(mod_test):signal("signal"),buffer("buffer")
    {
        counter_buffer = counter_signal = 0;
        SC_METHOD(f_signal);
        sensitive<<signal;
        SC_METHOD(f_buffer);
        sensitive<<buffer;
    }

    void f_signal(){
        counter_signal++;
        std::cout<<"signal counter: "<<counter_signal<<std::endl;
    }

    void f_buffer(){
        counter_buffer++;
        std::cout<<"buffer counter: "<<counter_buffer<<std::endl;
    }
};


int sc_main (int argc, char * argv[])
{

   mod_test test("test");

   sc_signal<bool> signal;
   sc_buffer<bool> buffer;

   test.signal(signal);
   test.buffer(buffer);

   signal = 0;
   buffer = 0;
   std::cout<<"assign: "<<std::endl;
   sc_start(10,SC_NS);
   signal = 1;
   buffer = 1;
   std::cout<<"assign: "<<std::endl;
   sc_start(10,SC_NS);
   signal = 1;
   buffer = 1;
   std::cout<<"assign: "<<std::endl;
   sc_start(10,SC_NS);
   signal = 0;
   buffer = 0;
   std::cout<<"assign: "<<std::endl;
   sc_start(10,SC_NS);

   return 0;
}