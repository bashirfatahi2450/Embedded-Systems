#include "mbed.h"

DigitalOut led(LED1); // LED for visual feedback

#define STACK_SIZE 4              // Size of the stack (4 elements)
int stack[STACK_SIZE];            // Stack array
int top = 0;                      // Stack pointer

void push(int value) {
    if (top >= STACK_SIZE) {
        // Handle stack full case
        printf("[ERR] Stack full, cannot push %d\r\n", value);
        return;
    }
    // Push value onto stack and increment top
    stack[top++] = value;
    printf("[OK ] Pushed %d (top=%d)\r\n", value, top);
}

int pop() {
    if (top <= 0) {
        // Handle stack empty case
        printf("[ERR] Stack empty, cannot pop\r\n");
        return 0; // sentinel; adjust if you prefer another policy
    }
    // Decrement top and return the value
    int value = stack[--top];
    printf("[OK ] Popped %d (top=%d)\r\n", value, top);
    return value;
}

void display_top() {
    if (top <= 0) {
        // Handle stack empty case
        printf("[ERR] Stack empty, nothing to display\r\n");
        return;
    }
    // Display the top value
    int value = stack[top - 1];
    printf("[TOP] %d (top index=%d)\r\n", value, top - 1);
}

int main() {
    // Push first value
    push(10);
    // Push second value
    push(20);

    display_top();  // Display top value after pushing

    // Pop the top value
    (void)pop();
    display_top();  // Display new top value after popping

    while (1) {
        led = !led;          // Blink LED
        wait_us(500000);     // Wait half a second (500,000 µs)
    }
}


