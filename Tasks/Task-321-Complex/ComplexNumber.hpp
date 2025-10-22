//
//  ComplexNumber.hpp
//  Complex
//
//  Created by Nicholas Outram on 21/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef ComplexNumber_hpp
#define ComplexNumber_hpp

#include <stdio.h>
#include <iostream>
#include <stdexcept>
using namespace std;


class ComplexNumber {
private:
    double real;
    double imag;
    
public:
    //Default constructor
    ComplexNumber() {
        this->real = 0.0;
        this->imag = 0.0;
    }
    
    //Constructor 2 - default of second parameter is 1 if not specified
    ComplexNumber(const double r, const double i=0.0) {
        this->real = r;
        this->imag = i;
    }
    
    //Copy constructors
    ComplexNumber(const ComplexNumber& c) {
        this->imag = c.imag;
        this->real = c.real;
    }

    //Destructor
    ~ComplexNumber() {
        cout << "Lachoo" << endl;
    }
    
    //Read-only accessors
    double getReal() {
        return this->real;
    }

    double getImag() {
        return this->imag;
    }

    //Conjugate - verb, so perform in place
    void conjugate() {
        this->imag *= -1.0;
    }
    
    //Conjugated - adjective, so return new copy
    ComplexNumber conjugated() {
        return ComplexNumber(this->real, -1.0*this->imag);
    }

    //Add in place
    void add(const ComplexNumber& c) {
        this->real += c.real;
        this->imag += c.imag;
    }
    
    //Add
    ComplexNumber addedTo(const ComplexNumber& c) {
        return ComplexNumber(this->real+c.real, this->imag+c.imag);
    }

    // --- Negate / Negated ---
    void negate() { real = -real; imag = -imag; }                 // in-place
    ComplexNumber negated() const { return { -real, -imag }; }    // returns copy




    // --- Subtract / SubtractFrom ---
    // "subtract" mirrors add: this -= c
    void subtract(const ComplexNumber& c) { real -= c.real; imag -= c.imag; }            // in-place
    // "subtractFrom" mirrors addedTo: returns this - c
    ComplexNumber subtractFrom(const ComplexNumber& c) const { return { real - c.real, imag - c.imag }; }
    



    // --- Multiply / MultiplyWith ---
    // (a+bi)(c+di) = (ac - bd) + (ad + bc)i
    void multiply(const ComplexNumber& c) {                                              // in-place
        double r = real * c.real - imag * c.imag;
        double i = real * c.imag + imag * c.real;
        real = r; imag = i;
    }
    ComplexNumber multiplyWith(const ComplexNumber& c) const {                            // returns copy
        return { real * c.real - imag * c.imag, real * c.imag + imag * c.real };
    }


bool divide(const ComplexNumber& c) {
    const double denom = c.real * c.real + c.imag * c.imag; //  allowed inside class
    if (denom == 0.0) return false;
    const double r = (real * c.real + imag * c.imag) / denom;
    const double i = (imag * c.real - real * c.imag) / denom;
    real = r; imag = i;
    return true;
}

bool divideWith(const ComplexNumber& c, ComplexNumber& out) const {
    const double denom = c.real * c.real + c.imag * c.imag; // 
    if (denom == 0.0) return false;
    out = ComplexNumber(
        (real * c.real + imag * c.imag) / denom,
        (imag * c.real - real * c.imag) / denom
    );
    return true;
}


    //Display
    void display() {
        cout << this->real << " + " << this->imag << "j" << endl;
    }
    
};


#endif /* ComplexNumber_hpp */
