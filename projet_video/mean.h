/**
 * @file mean.h
 * @author Enrique GOMEZ
 * @brief   Ce module se charge d'appliquer un filtre convolutif a une image
 *          d'entrée. Il faut indiquer le type de filtre comme parametre du module
 *          0: MEAN
 *          1: GAUSSIEN
 *          2: SOBEL
 * @version 0.1
 * @date 2019-06-27
 * 
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef MEAN_H
#define MEAN_H
#include <systemc.h>
#include "image.h"

SC_MODULE(MEAN){
    /* Methodes et variables internes */
    private:
    Image image;
    void reception(void);
    void filter_out(void);

    int compute_mean(int position);
    int compute_gauss(int position);
    int compute_sobel(int position);

    int count_in, count_fltr, count_h;

    int MAX_WIDTH, MAX_HEIGHT, counter_reception;
    bool href_was_false, vhref_was_true, href_found;
    bool vref_was_false, vref_found;

    enum {AVG=0,GAUSS,SOBEL} filter_type;
    int filter;


    public:
    /** I/O ports */
    sc_in<bool> clk;
    sc_in<bool> reset_n;

    sc_in<bool> href_in;
    sc_in<bool> vref_in;
    sc_in< unsigned char > pixel_in;

    sc_out<bool> href_out;
    sc_out<bool> vref_out;
    sc_out< unsigned char > pixel_out;

    /* Constructeur du Module */
    MEAN(sc_module_name n, int _filter = AVG,int _width = 720, int _height = 576):
            sc_module(n)
    {
        SC_METHOD(reception);
        sensitive<<clk.pos();
        async_reset_signal_is(reset_n,false);
        dont_initialize();

        SC_METHOD(filter_out);
        sensitive<<clk.pos();
        async_reset_signal_is(reset_n,false);
        dont_initialize();

        MAX_WIDTH = MAX_HEIGHT = 100000;
        href_was_false = vhref_was_true = href_found = false;
        vref_was_false = vref_found = false;

        count_in = count_fltr = count_h = counter_reception = 0;
        filter = _filter;
        image.width = _width;
        image.height = _height;
        image.pixel = (unsigned char *) malloc(image.width * image.height * sizeof(char));
    }
    SC_HAS_PROCESS(MEAN);
};

#endif