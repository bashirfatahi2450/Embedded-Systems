#include <iostream>
#include <cstdio>
using namespace std;

class Rectangle {
private:
    float length;
    float width;

public:
    // Constructor to initialize length and width
    Rectangle(float l, float w) {
        length = l;
        width = w;
    }

    // Function to calculate area
    float area() {
        return length * width;
    }

    // Function to calculate perimeter
    float perimeter() {
        return 2 * (length + width);
    }
};

int main()
{
    // Start program
    printf("Program Starting...\n");

    // Create a Rectangle object
    Rectangle rect(10.5, 5.2);

    // Output the area and perimeter of the rectangle
    printf("Rectangle Area: %.2f\n", rect.area());
    printf("Rectangle Perimeter: %.2f\n", rect.perimeter());

    return 0;
    while (true) {

    }
}


