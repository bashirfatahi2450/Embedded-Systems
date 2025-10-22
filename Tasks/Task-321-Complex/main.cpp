#include "mbed.h"
#include "ComplexNumber.hpp"

// main() runs in its own thread in the OS
int main()
{
    ComplexNumber c1(2.0,3.0);
    ComplexNumber c2(1.0,-1.0);
    ComplexNumber c1_copy = c1;
    c1.add(c2);   //c1 = c1 + c2
    c1.display();
    c1_copy.display();
    
    ComplexNumber c3 = c1.addedTo(c2);
    c3.conjugate();
    c3.display();

    //Create new scope
    {
        ComplexNumber test(1.0);
        test.display();
    }
    //test is now out of scope and should be destroyed

        // ======== ADDITIONAL TESTS ========
    std::cout << "\n--- negate / negated ---\n";
    ComplexNumber n = c1.negated();          // copy; c1 unchanged
    std::cout << "c1.negated(): "; n.display();
    c1.negate();                              // in-place
    std::cout << "c1 after negate(): "; c1.display();
    

    // Reset c1 to known value (3,2) to keep tests predictable
    //c1 = ComplexNumber(3.0, 2.0);

    std::cout << "\n--- subtract / subtractFrom ---\n";
    ComplexNumber subCopy = c1.subtractFrom(c2); // (3,2) - (1,-1) = (2,3)
    std::cout << "c1.subtractFrom(c2): "; subCopy.display();
    c1.subtract(c2);                              // in-place: (3,2) - (1,-1) = (2,3)
    std::cout << "c1 after subtract(c2): "; c1.display();

    // Reset
    //c1 = ComplexNumber(3.0, 2.0);

    std::cout << "\n--- multiply / multiplyWith ---\n";
    ComplexNumber mulCopy = c1.multiplyWith(c2); // (3+2j)*(1-1j) = (5 - j)
    std::cout << "c1.multiplyWith(c2): "; mulCopy.display();
    c1.multiply(c2);                            // in-place
    std::cout << "c1 after multiply(c2): "; c1.display();

    // Reset
    //c1 = ComplexNumber(3.0, 2.0);

    std::cout << "\n--- divide / divideWith ---\n";
    ComplexNumber q;
    if (c1.divideWith(c2, q)) {                // q = (3+2j)/(1-1j) = (0.5 + 2.5j)
        std::cout << "c1.divideWith(c2): "; q.display();
    } else {
        std::cout << "c1.divideWith(c2) failed (divide by zero)\n";
    }

    if (c1.divide(c2)) {                       // in-place divide
        std::cout << "c1 after divide(c2): "; c1.display();
    } else {
        std::cout << "c1.divide(c2) failed (divide by zero)\n";
    }

    // Try a divide-by-zero case to exercise the failure path
    ComplexNumber zero(0.0, 0.0);
    if (!c2.divideWith(zero, q)) {
        std::cout << "c2.divideWith(zero) failed (divide by zero)\n";
    }
    if (!c2.divide(zero)) {
        std::cout << "c2.divide(zero) failed (divide by zero)\n";
    }

    while (true);
}

