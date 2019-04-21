#include <systemc.h>

int sc_main (int argc, char * argv[])
{

   cout << "hello world" << endl;

   sc_logic a_1 = sc_logic('1');
   sc_logic b_1 = sc_logic('X');
   sc_logic c_1 = sc_logic('z');
   sc_logic d_1 = sc_logic(2);
   sc_logic e_1 = sc_logic(false);

   cout<<"Initializations"<<endl;
   cout<<"a_1 = sc_logic('1') : "<<a_1<<endl;
   cout<<"b_1 = sc_logic('X') : "<<b_1<<endl;
   cout<<"c_1 = sc_logic('z') : "<<c_1<<endl;
   cout<<"d_1 = sc_logic(2) : "<<d_1<<endl;
   cout<<"e_1 = sc_logic(false) : "<<e_1<<endl;

   a_1 = 'Z';
   b_1 = 3;
   c_1 = true;

   cout<<"Change Values"<<endl;
   cout<<"a_1: "<<a_1<<endl;
   cout<<"b_1: "<<b_1<<endl;
   cout<<"c_1: "<<c_1<<endl;
   
   a_1 = ~b_1 & d_1;
   b_1 = (a_1 ^ c_1) | d_1;
   c_1 = d_1 ^ true;

   cout<<"Logic Equations"<<endl;
   cout<<"~b_1 & d_1: "<<a_1<<endl;
   cout<<"(a_1 ^ c_1) | d_1: "<<b_1<<endl;
   cout<<"d_1 ^ true: "<<c_1<<endl;

   return 0;
}