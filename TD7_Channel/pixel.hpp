#ifndef PIXEL_HPP
#define PIXEL_HPP
#include <systemc.h>
#include <stdint.h>


struct Pixel_t
{
   sc_uint<8> R;
   sc_uint<8> G;
   sc_uint<8> B;
   int step {0};

   Pixel_t(sc_uint<8> _R = 0, sc_uint<8> _G = 0, sc_uint<8> _B = 0):
    R(_R),G(_G),B(_B){}


   bool operator == (const Pixel_t &other) const {
      return (R == other.R) && (G == other.G) && (B == other.B);
    }

   Pixel_t operator + (const Pixel_t &other) const {
      Pixel_t p;
      p.R = R + other.R;
      p.G = G + other.G;
      p.B = B + other.B;
      return p;
   }

   void operator = (const Pixel_t &other) {
      R = other.R;
      G = other.G;
      B = other.B;
      step = other.step;
   }

   friend ostream& operator << ( ostream& o, const Pixel_t& P ) {
      o << "{ R = " << P.R << ", G = " << P.G << ", B = "<< P.B <<" }" ;
      return o;
   }

   void inc(){
      switch(step){
         case 0: step=(R==255)?++step:0; R++;break;
         case 1: step=(G==255)?++step:0; G++;break;
         case 2: step=0; B++;break;
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
};

void sc_trace( sc_trace_file* _f, const Pixel_t& _Pixel, const std::string& _s );

#endif