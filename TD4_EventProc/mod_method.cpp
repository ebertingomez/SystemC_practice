#include <systemc.h>
#include "pixel.cpp"

SC_MODULE(mod_pixel)
{
   sc_in<Pixel_t> P_in_1;
   sc_in<Pixel_t> P_in_2;
   sc_out<Pixel_t> P_out;

   SC_CTOR(mod_pixel):P_in_1("P_in_1"), P_in_2("P_in_2"), P_out("P_out")
   {
      SC_METHOD (add);
      dont_initialize();
      sensitive << P_in_1 << P_in_2;
   }

   void add()
    {
      P_out.write(P_in_1.read() + P_in_2.read());
    }
};

int sc_main(int argc, char * argv[])
{
   sc_signal<Pixel_t> P_in_1;
   sc_signal<Pixel_t> P_in_2;
   sc_signal<Pixel_t> P_out;

   mod_pixel pixel("pixel");
   pixel.P_in_1(P_in_1);
   pixel.P_in_2(P_in_2);
   pixel.P_out(P_out);

   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("pixel_method");
   trace_f->set_time_unit(1,SC_NS);
   Pixel_t p;
   sc_trace(trace_f, pixel.P_out, "P_out");
   for (int i = 0 ; i<30 ; i++){
      p = pixel.P_in_1.read();
      p.inc();
      P_in_1 = p;
      p = pixel.P_in_2.read();
      p.inc();
      P_in_2 = p;
      cout << "--> @ " << sc_time_stamp() << " P_out = " << P_out << endl;
      sc_start(1,SC_NS);
    }
   sc_close_vcd_trace_file(trace_f);
   return 0;
}