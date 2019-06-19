#include <systemc.h>
#include "pixel.hpp"

#define FIFO_LENGTH 10
#define DATA_SENT 20

SC_MODULE(MOD_PRODUCER){
    private:
    Pixel_t pixel;
    int i {0};
    bool written;

    int cycles_wait {0};
    int cycles_count {0};

    public:
    sc_fifo_out<Pixel_t> out;
    sc_in<bool> clock;
    
    SC_CTOR(MOD_PRODUCER):out("out"), clock("clock"){
        SC_METHOD(f_produce);
        sensitive<<clock.pos();
    }

    void f_produce(){
        if (cycles_count < cycles_wait){
            cycles_count++;
        }
        else {
            cycles_count = 0;
            if (i == DATA_SENT ){
                i=0;
                cycles_wait = std::rand()%33;
            }
            else {
                i++;
                pixel = Pixel_t(std::rand()%256,std::rand()%256,std::rand()%256);
                written = out.nb_write(pixel);
                if (written) std::cout<< "written: "<<pixel<<std::endl;
                cycles_wait = 1;
            }
        }
    }
};

SC_MODULE(MOD_CONSUMER){
    sc_fifo_in<Pixel_t> in;
    sc_in<bool> clock;
    SC_CTOR(MOD_CONSUMER):in("in"),clock("clock"){
        SC_METHOD(f_consume);
        sensitive<<clock.pos();
    }

    Pixel_t pixel;
    int sum;
    bool read;

    int cycles_wait = 0;
    int cycles_count = 0;

    void f_consume(){
        if (cycles_count < cycles_wait){
            cycles_count++;
        }
        else {
            cycles_count = 0;
            read = in->nb_read(pixel);
            if (read) std::cout<<"read: "<<pixel<<std::endl;
            sum = pixel.R + pixel.G + pixel.B;
            if (sum % 2 == 0 )
                cycles_wait=2;
            else
                cycles_wait=3;
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