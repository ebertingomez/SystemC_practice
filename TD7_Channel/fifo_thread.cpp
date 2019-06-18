#include <systemc.h>
#include "pixel.hpp"

#define FIFO_LENGTH 10
#define DATA_SENT 20

SC_MODULE(MOD_PRODUCER){
    sc_fifo_out<Pixel_t> out;
    sc_in<bool> clock;
    SC_CTOR(MOD_PRODUCER):out("out"), clock("clock"){
        SC_CTHREAD(f_produce,clock.pos());
    }

    void f_produce(){
        Pixel_t pixel;
        int i = 0;
        bool written;
        for(;;){
            if (i== DATA_SENT ){
                i=0;
                wait(std::rand()%33);
            }
            else {
                i++;
                pixel = Pixel_t(std::rand()%256,std::rand()%256,std::rand()%256);
                written = out.nb_write(pixel);
                if (written) std::cout<< "written: "<<pixel<<std::endl;
                wait(1);
            }
        }
    }
};

SC_MODULE(MOD_CONSUMER){
    sc_fifo_in<Pixel_t> in;
    sc_in<bool> clock;
    SC_CTOR(MOD_CONSUMER):in("in"),clock("clock"){
        SC_CTHREAD(f_consume,clock.pos());
    }
    void f_consume(){
        Pixel_t pixel;
        int sum;
        bool read;
        for(;;){
            read = in->nb_read(pixel);
            if (read) std::cout<<"read: "<<pixel<<std::endl;
            sum = pixel.R + pixel.G + pixel.B;
            if (sum % 2 == 0 )
                wait(2);
            else
                wait(3);
        }
    }
};

int sc_main (int argc, char * argv[]){
    sc_fifo<Pixel_t> fifo(FIFO_LENGTH);
    sc_clock clock("clock",10,SC_NS);

    MOD_PRODUCER producer("producer");
    MOD_CONSUMER consumer("consumer");

    producer.out(fifo);
    producer.clock(clock);

    consumer.in(fifo);
    consumer.clock(clock);

    sc_start(1000,SC_NS);
    
    return 0;
}