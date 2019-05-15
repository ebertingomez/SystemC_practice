#include <systemc.h>
#include "pixel.cpp"

SC_MODULE(mod_pixel)
{
   sc_in<Pixel_t> P_in_1;
   sc_in<Pixel_t> P_in_2;
   sc_out<Pixel_t> P_out;

   SC_CTOR(mod_pixel):P_in_1("P_in_1"), P_in_2("P_in_2"), P_out("P_out")
   {
      SC_THREAD (add);
      dont_initialize();
      sensitive << P_in_1 << P_in_2;
   }

   void add()
    {
      for(;;){
         wait();
         P_out.write(P_in_1.read() + P_in_2.read());
      }
    }
};

int sc_main(int argc, char * argv[])
{
   mod_pixel pixel("pixel");
   sc_signal<Pixel_t> P_in_1;
   sc_signal<Pixel_t> P_in_2;
   sc_signal<Pixel_t> P_out;
   pixel.P_in_1(P_in_1);
   pixel.P_in_2(P_in_2);
   pixel.P_out(P_out);
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("pixel");
   trace_f->set_time_unit(1,SC_NS);

   sc_trace(trace_f, pixel.P_out, "P");
    for (int i = 0 ; i<10 ; i++){
        P_in_1 = P_in_1.read()++;
        P_in_2 = P_in_2.read()++;
        cout << "--> @ " << sc_time_stamp() << " P = " << P_out << endl;
        sc_start(1,SC_NS);
    }
   sc_close_vcd_trace_file(trace_f);
   return 0;
}