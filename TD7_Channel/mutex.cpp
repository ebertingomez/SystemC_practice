#include <systemc.h>

SC_MODULE(MOD_MUTEX){
    sc_mutex m;
    sc_in<bool> clock;
    SC_CTOR(MOD_MUTEX):m("m"),clock("clock"){
        SC_CTHREAD(thread_1,clock.pos());
        SC_CTHREAD(thread_2,clock.pos());
    }

    void thread_1(){
        for(;;){
            m.lock();
            std::cout<<"Thread 1 has the mutex"<<std::endl;
            m.unlock();
            wait(1);
        }
    }

    void thread_2(){
        for(;;){
            m.lock();
            std::cout<<"Thread 2 has the mutex"<<std::endl;
            m.unlock();
            wait(1);
        }
    }
};

int sc_main(int argc, char * argv[]){
    sc_clock clock("clock",10,SC_NS);

    MOD_MUTEX mutex("mutex");
    mutex.clock(clock);

    sc_start(1000,SC_NS);

    return 0;
}