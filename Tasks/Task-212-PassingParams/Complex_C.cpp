#include "Complex_C.hpp"
#include "stdio.h"
#include <math.h>

ComplexNumber_C complexAdd(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y = a;
    y.real += b.real;
    y.imag += b.imag;
    return y;

}

void complexDisplay(const char *strName, const ComplexNumber_C u) {
    printf("%s = %f + j%f\n", strName, u.real, u.imag);
}


// Subtract: a - b
ComplexNumber_C complexSubtract(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C r = { a.real - b.real, a.imag - b.imag };
    return r;
}


// Conjugate: conj(a+jb) = a - jb
ComplexNumber_C complexConjugate(const ComplexNumber_C u) {
    ComplexNumber_C r = { u.real, -u.imag };
    return r;
}

// Negate: -(a+jb) = -a - jb
ComplexNumber_C complexNegate(const ComplexNumber_C u) {
    ComplexNumber_C r = { -u.real, -u.imag };
    return r;
}




// Magnitude: |a+jb| = sqrt(a^2 + b^2)
double complexMagnitude(const ComplexNumber_C u) {
    // hypot is numerically stable vs direct sqrt(a*a + b*b)
    return hypot(u.real, u.imag);
}

// Multiply: (a+jb)(c+jd) = (ac - bd) + j(ad + bc)
ComplexNumber_C complexMultiply(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C r = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
    return r;
}


// Divide: (a+jb)/(c+jd) = [(a+jb)(c-jd)] / (c^2 + d^2)
ComplexNumber_C complexDivide(const ComplexNumber_C a, const ComplexNumber_C b) {
    double denom = b.real * b.real + b.imag * b.imag;
    ComplexNumber_C r = {0.0, 0.0};
    if (denom == 0.0) {
        // Handle divide-by-zero: leave as 0 and report
        printf("Warning: complexDivide by zero! Returning 0 + j0.\n");
        return r;
    }
    r.real = (a.real * b.real + a.imag * b.imag) / denom;
    r.imag = (a.imag * b.real - a.real * b.imag) / denom;
    return r;
}

// ---- NEW In-place Functions (pass by reference) ----

// Conjugate in-place: a + jb → a - jb
void complexConjugateInplace(ComplexNumber_C *u) {
    u->imag = -u->imag;
}

// Negate in-place: a + jb → -a - jb
void complexNegateInplace(ComplexNumber_C *u) {
    u->real = -u->real;
    u->imag = -u->imag;
}