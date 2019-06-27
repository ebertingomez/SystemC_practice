/**
 * @file video_out.h
 * @author Enrique Gomez
 * @brief Ce module se charge de lire une serie de pixels est les stocker dans un
 *          fichier png lorsque la reception soit finie.
 * @version 0.1
 * @date 2019-06-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#define VIDEO_OUT_H
#include <systemc.h>
#include "image.h"

SC_MODULE(VIDEO_OUT){
    /* Methodes et variables internes */
    private:
    int counter;
    int nb_images;
    Image image;

    void read_pixels();
    void print_image(Image image);

    public:
    /** I/O ports */
    sc_in<bool> clk;
    sc_in<bool> reset_n;
    sc_in<bool> href;
    sc_in<bool> vref;

    sc_in< unsigned char > pixel_in;
    

    /* Constructeur du Module */
    VIDEO_OUT(sc_module_name n,int _width = 720, int _height = 576):
        sc_module(n)
    {
        SC_METHOD(read_pixels);
        sensitive<<clk.pos();
        async_reset_signal_is(reset_n,false);
        dont_initialize();
        image.width = _width;
        image.height = _height;
        image.pixel = (unsigned char *) malloc(image.width * image.height * sizeof(char));
        counter = 0;
        nb_images = 0;
    }
    SC_HAS_PROCESS(VIDEO_OUT);

};



#endif