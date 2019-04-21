#include <systemc.h>

int sc_main (int argc, char * argv[])
{
    sc_bv<8> a_2 = "10101010";
    sc_lv<8> b_2 = "1010zxxz";
    sc_bv<8> c_2(false);
    sc_lv<8> d_2("xzx1z01x");

    cout<<"Initializations"<<endl;
    cout<<"Bit Vector a_2: "<<a_2<<endl;
    cout<<"Logic Vector b_2: "<<b_2<<endl;
    cout<<"Bit Vector c_2: "<<c_2<<endl;
    cout<<"Logic Vector d_2: "<<d_2<<endl;

    if (a_2 == "10101010") b_2 = 0;

    a_2[1] = false;
    a_2[2] = false;
    a_2[3] = false;
    a_2[4] = false;

    b_2[0] = true;
    b_2[2] = 3;
    b_2[4] = 'Z';
    b_2[6] = '1';

    c_2(1,4) = 14;
    d_2(3,6) = "1zx0";

    cout<<"Element assignation"<<endl;
    cout<<"a_2 : "<<a_2<<endl;
    cout<<"b_2 : "<<b_2<<endl;
    cout<<"c_2(1,4) : "<<c_2<<endl;
    cout<<"d_2(3,6) : "<<d_2<<endl;

    cout<<"Logic Operations"<<endl;
    cout<<"~c_2: "<<~c_2<<endl;
    cout<<"(c_2 & d_2): "<<(c_2 & d_2)<<endl;

    c_2 = c_2>>2;
    d_2 = d_2<<2;
    cout<<"Bit Shifting Operations"<<endl;
    cout<<"c_2>>2: "<<c_2<<endl;
    cout<<"d_2<<2"<<d_2<<endl;

    b_2 = (c_2(1,4),d_2(7,4));

    cout<<b_2<<endl;
    cout<<"Concatenation"<<endl;
    cout<<"(c_2(1,4),d_2(7,4)) : "<<b_2<<endl;

    sc_lv<8> e_2 = "11111111";
    sc_lv<8> f_2 = "11111110";
    cout<<"Reductions"<<endl;
    cout<<"Vector: "<< e_2 <<'\t' << "and_reduce:\t" << e_2.and_reduce() << endl;
    cout<<"Vector: "<< b_2 <<'\t' << "or_reduce:\t" << b_2.or_reduce() << endl;
    cout<<"Vector: "<< c_2 <<'\t' << "xor_reduce:\t" << c_2.xor_reduce() << endl;
    cout<<"Vector: "<< d_2 <<'\t' << "xnor_reduce:\t" << d_2.xnor_reduce() << endl;
    cout<<"Vector: "<< e_2 <<'\t' << "xor_reduce:\t" << e_2.xor_reduce() << endl;
    cout<<"Vector: "<< f_2 <<'\t' << "xor_reduce:\t" << f_2.xor_reduce() << endl;

    cout<<"Conversions"<<endl;
    cout<<"Vector: "<< a_2 <<'\t' << "to_int:\t" << a_2.to_int() << endl;
    cout<<"Vector: "<< b_2 <<'\t' << "to_uint:\t" << b_2.to_uint() << endl;
    cout<<"Vector: "<< c_2 <<'\t' << "to_int64:\t" << c_2.to_int64() << endl;
    cout<<"Vector: "<< d_2 <<'\t' << "to_uint64:\t" << d_2.to_uint64() << endl;
    
   return 0;
}