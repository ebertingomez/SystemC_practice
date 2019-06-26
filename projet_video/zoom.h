#ifndef ZOOM_H
#define ZOOM_H
#include <systemc.h>
#include "image.h"

SC_MODULE(ZOOM){
    private:
    Image image;
    void reception(void);
    void zoom_out(void);
    int idx_recep;
    int count_in, count_h;
    int idx;
    bool pixel_sent, row_sent;

    int MAX_WIDTH, MAX_HEIGHT, counter_reception;
    bool href_was_false, vhref_was_true, href_found;
    bool vref_was_false, vref_found;

    public:
    sc_in<bool> clk;
    sc_in<bool> reset_n;

    sc_in<bool> href_in;
    sc_in<bool> vref_in;
    sc_in< unsigned char > pixel_in;

    sc_out<bool> href_out;
    sc_out<bool> vref_out;
    sc_out< unsigned char > pixel_out;

    ZOOM(sc_module_name n,int _width = 720, int _height = 576):
            sc_module(n)
    {
        SC_METHOD(reception);
        sensitive<<clk.pos();
        async_reset_signal_is(reset_n,false);
        dont_initialize();

        SC_METHOD(zoom_out);
        sensitive<<clk.pos();
        async_reset_signal_is(reset_n,false);
        dont_initialize();

        count_in = count_h = counter_reception = 0;
        idx = _width*_height/4 + _width/4;
        pixel_sent = row_sent = false;

        MAX_WIDTH = MAX_HEIGHT = 100000;
        href_was_false = vhref_was_true = href_found = false;
        vref_was_false = vref_found = false;

        image.width = _width;
        image.height = _height;
        image.pixel = (unsigned char *) malloc(image.width * image.height / 4 * sizeof(char));
    }
    SC_HAS_PROCESS(ZOOM);
};

#endif