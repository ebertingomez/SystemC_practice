#include <systemc.h>

int sc_main (int argc, char * argv[])
{
   sc_time t1(3.51, SC_NS);
   cout << "---> " << t1.value() << ", " << t1 << endl;

   sc_time t2 = 2*t1;
   cout << "---> " << t2.value() << ", " << t2 << endl;

   cout << "La durée t" ;
   if (t1>t2)
      cout << "t1";
   else
      cout << "t2";
   cout << " est plus grande" << endl;

   cout << "---> " << SC_ZERO_TIME.value() << ", " << SC_ZERO_TIME << endl;

   return 0;
}