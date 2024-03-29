#include <systemc.h>
#include <stdint.h>


struct Pixel_t
{
    sc_uint<5> R;
    sc_uint<6> G;
    sc_uint<5> B;

    Pixel_t(sc_uint<5> _R = 0, sc_uint<6> _G = 0, sc_uint<5> _B = 0):
    R(_R),G(_G),B(_B){}


    bool operator == (const Pixel_t &other) const {
      return (R == other.R) && (G == other.G) && (B == other.B);
    }

    friend ostream& operator << ( ostream& o, const Pixel_t& P ) {
      o << "{ R = " << P.R << ", G = " << P.G << ", B = "<< P.B <<" }" ;
      return o;
   }

   void inc(){
      switch(step){
         case 0: R++; step++;break;
         case 1: G++; step++;break;
         case 2: B++; step=0;break;
      }
   }

   Pixel_t operator++ (int) const {
      Pixel_t p = *this;
      p.inc();
      return p;
   }

   Pixel_t& operator++ () {
      inc();
      return *this;
   }

   private:
   int step {0};
};

void sc_trace( sc_trace_file* _f, const Pixel_t& _Pixel, const std::string& _s ) {
   sc_trace( _f, _Pixel.R, _s + "R" );
   sc_trace( _f, _Pixel.G, _s + "G" );
   sc_trace( _f, _Pixel.B, _s + "B" );
}

// Le test
int sc_main (int argc, char * argv[])
{
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("pixel");
   trace_f->set_time_unit(1,SC_NS);

   sc_signal<Pixel_t> P;

   sc_trace(trace_f, P, "P");
    for (int i = 0 ; i<10 ; i++){
        P = P.read()++;
        cout << "--> @ " << sc_time_stamp() << " P = " << P << endl;
        sc_start(1,SC_NS);
    }
   sc_close_vcd_trace_file(trace_f);
   return 0;
}