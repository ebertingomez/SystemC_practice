#include <systemc.h>

class my_channel : sc_channel {
    private:
    sc_signal<bool> clk;
    int period;
    sc_time_unit time_unit;

    public:
    sc_export< sc_signal<bool> > clock;

    my_channel(int _period, sc_time_unit _time_unit,sc_module_name name)
                        :sc_channel(name),clock("clock")
    {
        period      = _period;
        time_unit   = _time_unit;
        clk         = false;
        clock(clk);
        SC_THREAD(clock_gen);
    }
    SC_HAS_PROCESS(my_channel);

    void clock_gen(){
        for (;;){
            clk = !clk;
            wait(period,time_unit);
        }
    }
};

SC_MODULE(mod_test){
    sc_in<bool> clk;

    SC_CTOR(mod_test):clk("clk"){
        SC_METHOD(f_test);
        sensitive<<clk;
        dont_initialize();
    }
    void f_test(){
        cout << sc_time_stamp() << endl;
    }
};

int sc_main(int argc, char * argv[]){
    my_channel c(10,SC_NS, "channel");
    mod_test t("t");

    t.clk(c.clock);

    sc_start(2000,SC_NS);

    return 0;
}