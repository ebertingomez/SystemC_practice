#include <systemc.h>

int sc_main (int argc, char * argv[])
{
    sc_bv<8> c_2(true);
    sc_lv<8> d_2("xzx1z01x");
    sc_int<10> a = 45;
    sc_uint<8> b = 257;
    sc_uint<8> c = d_2;
    sc_uint<8> d = "13";
    sc_uint<8> e = c_2;


    cout<<"Initializations"<<endl;
     cout<<"Vector: "<< a <<endl;
     cout<<"Vector: "<< b <<endl;
     cout<<"Vector: "<< c <<endl;
     cout<<"Vector: "<< d <<endl;
     cout<<"Vector: "<< e <<endl;

    cout<<"Arithmetic Operations"<<endl;
    cout<<"a + b = "<< (a+b) <<endl;
    cout<<"c - d = "<< (c-d) <<endl;
    cout<<"d * e = "<< (d*e) <<endl;
    cout<<"c / b = "<< (c/b) <<endl;
    cout<<"d % e = "<< (d%e) <<endl;

    cout<<"Logic Operations"<<endl;
    cout<<"a & b = "<< (a&b) <<endl;
    cout<<"c | d = "<< (c|d) <<endl;
    cout<<"d ^ e = "<< (d^e) <<endl;
    cout<<"~ c = "<< (~c) <<endl;
    cout<<"d & d_2 = "<< (d & d_2) <<endl;

   return 0;
}