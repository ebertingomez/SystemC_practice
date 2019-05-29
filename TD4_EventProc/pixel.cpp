#include "pixel.hpp"

void sc_trace( sc_trace_file* _f, const Pixel_t& _Pixel, const std::string& _s )
{
   sc_trace( _f, _Pixel.R, _s + "R" );
   sc_trace( _f, _Pixel.G, _s + "G" );
   sc_trace( _f, _Pixel.B, _s + "B" );
}
