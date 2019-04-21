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
    cout<<"b / c = "<< (b/c) <<endl;
    cout<<"d % e = "<< (d%e) <<endl;

    cout<<"Logic Operations"<<endl;
    cout<<"a & b = "<< (a&b) <<endl;
    cout<<"c | d = "<< (c|d) <<endl;
    cout<<"d ^ e = "<< (d^e) <<endl;
    cout<<"~ a = "<< (~a) <<endl;
    cout<<"d & d_2 = "<< (d & d_2) <<endl;
    cout<<"c >> 2: "<<(c>>2)<<endl;
    cout<<"d << 2: "<<(d<<2)<<endl;
    cout<<"(c(4,1),d(7,4)) : "<<(c(4,1),d(7,4))<<endl;

    cout<<"Reductions"<<endl;
    cout<<"Vector: "<< a <<'\t' << "and_reduce:\t" << a.and_reduce() << endl;
    cout<<"Vector: "<< b <<'\t' << "or_reduce:\t" << b.or_reduce() << endl;
    cout<<"Vector: "<< c <<'\t' << "xor_reduce:\t" << c.xor_reduce() << endl;
    cout<<"Vector: "<< d <<'\t' << "xnor_reduce:\t" << d.xnor_reduce() << endl;

    cout<<"Conversions"<<endl;
    sc_lv<8> f_2("10zxzx01");
    sc_uint<8> f = f_2;
    sc_int<8> g = f_2;
    cout<<"f_2: "<<f_2<<endl;
    cout<<"sc_int g: "<<g<<endl;
    cout<<"sc_uint f: "<<f<<endl;
    cout<<"f_2 to_int : "<<f_2.to_int()<<endl;
    cout<<"f_2 to_uint : "<<f_2.to_uint()<<endl;

   return 0;
}