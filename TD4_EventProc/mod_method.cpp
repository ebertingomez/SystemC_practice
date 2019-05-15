#include <systemc.h>
#include "pixel.cpp"

SC_MODULE(mod_pixel)
{
   sc_in<bool> clk;
   sc_in<bool> rst;
   sc_out<sc_uint<8> > data;

   SC_CTOR(mod_pixel):clk("clk"), data("data")
   {
      cout
         << "module : " << name()      << endl
         << "clk    : " << clk.name()  << endl
         << "rst    : " << rst.name()  << endl
         << "data   : " << data.name() << endl
         ;
   }
};

int sc_main(int argc, char * argv[])
{
   mod_pixel bar("foobar");
   return 0;
}