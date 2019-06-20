#ifndef MEAN_H
#define MEAN_H
#include <systemc.h>
#include "image.h"

SC_MODULE(MEAN){
    private:
    Image image;
    void filter_in(void);
    void filter_out(void);
    int count_in, count_fltr, count_h;
    int sum, n, idx;

    public:
    sc_in<bool> clk;
    sc_in<bool> reset_n;

    sc_in<bool> href_in;
    sc_in<bool> vref_in;
    sc_in< unsigned char > pixel_in;

    sc_out<bool> href_out;
    sc_out<bool> vref_out;
    sc_out< unsigned char > pixel_out;

    MEAN(sc_module_name n,int _width = 720, int _height = 576):
            sc_module(n)
    {
        SC_METHOD(filter_in);
        sensitive<<clk.pos();
        async_reset_signal_is(reset_n,false);
        dont_initialize();

        SC_METHOD(filter_out);
        sensitive<<clk.pos();
        async_reset_signal_is(reset_n,false);
        dont_initialize();

        count_in = count_fltr = count_h =0;
        image.width = _width;
        image.height = _height;
        image.pixel = (unsigned char *) malloc(image.width * image.height * sizeof(char));
    }
    SC_HAS_PROCESS(MEAN);
};

#endif