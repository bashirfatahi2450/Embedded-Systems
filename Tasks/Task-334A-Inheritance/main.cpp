#include "DoubleNumber.hpp"
#include "ComplexNumber.hpp"

int main()
{
    //Constructor Function overloading 
    ComplexNumber c0(1.0, 2.0);
    DoubleNumber  d0(3.0);
    ComplexNumber c1;
    DoubleNumber  d1;
    
    //This uses the operator= function
    d1 = 5.0;

    //Write the value as a string
    cout << d1.asString() << endl;

    //DANGER! THIS IS NOT AS IT LOOKS
    //By default, the compiler creates an = operator!
    c1 = c0;

    //Write as a string, but note asString() comes from the parent class
    cout << c1.asString() << endl;
    

    //The plus will work, but it will be the DoubleNumber version
    cout << (c0 + c1 + d0 + d1).asString();

    // Note how this works with both types, but only on the real parts
    DoubleNumber sum1 = c0 + c1 + d0 + d1;
    cout << sum1 << endl;

    while (true) {

    }
}

