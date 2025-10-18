#include "mbed.h"
#include "Complex_C.hpp"
#include <math.h>


// TASK - write and test complexConjugate, complexNegate, complexSubtract, complexMagnitude, complexMultiply and complexDivide

int main() {
    printf("\n\nTASK312\n");

    //Create instance of a complex number
    ComplexNumber_C p = {2.0, 3.0};
    ComplexNumber_C q = {1.0, 1.0};
    complexDisplay("p", p);
    complexDisplay("q", q);

    // Add
    ComplexNumber_C sum = complexAdd(p, q);
    complexDisplay("p+q", sum);

    // Subtract
    ComplexNumber_C diff = complexSubtract(p, q);
    complexDisplay("p-q", diff);

    // Conjugates
    ComplexNumber_C p_conj = complexConjugate(p);
    complexDisplay("conj(p)", p_conj);

    // Negate
    ComplexNumber_C neg_p = complexNegate(p);
    complexDisplay("-p", neg_p);

    // Magnitude
    double mag_p = complexMagnitude(p);
    printf("|p| = %f\n", mag_p);

    // Multiply
    ComplexNumber_C prod = complexMultiply(p, q);
    complexDisplay("p*q", prod);

    // Divide
    ComplexNumber_C quot = complexDivide(p, q);
    complexDisplay("p/q", quot);


     // --- In-place tests ---
    printf("\n-- In-place Conjugate Test --\n");
    complexConjugateInplace(&p);     // modifies p directly
    complexDisplay("p after conjugate", p);  // expect 2.0 - j3.0

    printf("\n-- In-place Negate Test --\n");
    complexNegateInplace(&p);        // modifies p again
    complexDisplay("p after negate", p);     // expect -2.0 + j3.0

    
    while (true) {
    }
}
