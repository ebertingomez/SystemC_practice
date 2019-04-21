#define SC_INCLUDE_FX
#include <systemc.h>
#include <math.h>

#define WL  3
#define IWL 1

void sc_fixed_exemple(){
    double d1 = 0.1;
    double d2 = 0.9;
    double ds = d1 + d2;

    sc_fixed<WL,IWL> f1(d1);
    sc_fixed<WL,IWL> f2 = d2;
    sc_fixed<WL,IWL> fs = f1 + f2;

    double e = ds - double(fs);

    cout 
        << "Double " << ds  << endl 
        << "Fixed  " << fs  << endl 
        << "Error  " << e   << endl;
}

double compare (double d1, double d2)
{
   double ds = d1 + d2;
   sc_fix f1(d1);
   sc_fix f2(d2);
   sc_fix fs = f1 + f2;

   return ds - fs;
}

void sc_fix_exemple(){

   double d1 = 0.1;
   double d2 = 0.9;

   // 1 bit pour la partie entière et 2 bits après la virgule
   sc_fxtype_params param1(3,1);
   // 1 bit pour la partie entière et 4 bits après la virgule
   sc_fxtype_params param2(5,1);
   // 1 bit pour la partie entière et 6 bits après la virgule
   sc_fxtype_params param3(7,1);

   sc_fxtype_context ctxt1(param1);
   cout 
      << "Error  in context " << ctxt1.default_value()
      << " is " <<  compare(d1,d2)  << endl;

   sc_fxtype_context ctxt2(param2);
   cout 
      << "Error  in context " << ctxt1.default_value()
      << " is " <<  compare(d1,d2)  << endl;

   sc_fxtype_context ctxt3(param3);
   cout 
      << "Error  in context " << ctxt1.default_value()
      << " is " <<  compare(d1,d2)  << endl;
}

int find_precision(double precision, int n){
    double ref_value = M_PI * sin (M_PI / 256. * n);
    int bits = 0;
    double error;
    do {
        bits++;
        sc_fxtype_params param(3+bits,3);
        sc_fxtype_context ctxt(param);
        sc_fix comp(ref_value);
        error = abs(ref_value - comp);
     }
     while ( error > precision );
     return bits;
}
int sc_main (int argc, char * argv[])
{
    cout<<"_________Fixed Example________"<<endl;
    sc_fixed_exemple();
    cout<<"_________Fix Example________"<<endl;
    sc_fix_exemple();
    
    int n1 = find_precision(0.01, 1);
    int n2 = find_precision(0.001, 1);
    int n3 = find_precision(0.0001, 1);

    cout<<"_________Precision Example________"<<endl;
    cout
        <<"Bits for 0.01 precision: "<<n1<<endl
        <<"Bits for 0.001 precision: "<<n2<<endl
        <<"Bits for 0.0001 precision: "<<n3<<endl;

    return 0;


}