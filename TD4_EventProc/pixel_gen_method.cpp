#include <systemc.h>
#include "pixel.cpp"

SC_MODULE(mod_pixel)
{
   sc_in<bool> clock;
   sc_in<bool> r;
   sc_out<Pixel_t> P_out;
   Pixel_t p;

   SC_CTOR(mod_pixel):clock("clock"), P_out("P_out")
   {
      SC_METHOD (add);
      dont_initialize();
      sensitive << clock;
      async_reset_signal_is(r,true);
   }

   void add()
    {
      if (r)
         P_out.write(Pixel_t(0,0,0));
      else {
         p = P_out.read();
         p.inc();
         P_out.write(p);
      }
    }
};

int sc_main(int argc, char * argv[])
{
   sc_clock clock("clock",20,SC_NS);
   sc_signal<Pixel_t> P_out;

   mod_pixel pixel("pixel");
   pixel.clock(clock);
   pixel.P_out(P_out);

   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("pixels_method");
   trace_f->set_time_unit(10,SC_NS);
   sc_trace(trace_f, pixel.P_out, "P_out");
   sc_trace(trace_f, pixel.clock, "clock");
   sc_start(10000,SC_NS);
   sc_close_vcd_trace_file(trace_f);
   return 0;
}