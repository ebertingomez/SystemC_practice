#include <iostream>
using namespace std;

class MyInterface {
public:
   // "=0" veut dire implémentation obligatoire
   virtual void hello()   = 0;
};

class SimpleImpl : virtual public MyInterface {
public:
   void hello()
   {
      cout << "Hi" << endl;
   }
};

class CplxImpl : virtual public MyInterface {
public:
   void hello()
   {
      cout <<  "Hi " << message << endl;
   }
   CplxImpl(string s): message(s) {}

private:
   const string message;
};

int main()
{
   // MyInterface   x; // ceci est une erreur car la classe est abstraite
   
   MyInterface * o[2];

   o[0] =  new SimpleImpl();
   o[1] =  new CplxImpl("folks");

   for (int i=0; i<2; i++)
      o[i]->hello();

   return 0;
}