#include <iostream>     // IO library

class Stack {
public:
    Stack(int StackSize);
    ~Stack();
    void Push(int Value);
    int Pop();
    int Top();

private:
    int *Array;                     // Array to hold stack elements
    int MaxCapacity;                // Maximum capacity of the stack
    int CurrentPosition;            // Current position in the stack
};

// Stack constructor
Stack::Stack(int StackSize) {
    Array = new int[StackSize];
    MaxCapacity = StackSize;
    CurrentPosition = -1;
}

// Stack destructor
Stack::~Stack() {
    delete[] Array;
}

// Push an element onto the stack
void Stack::Push(int Value) {
    if (CurrentPosition < MaxCapacity - 1) {
        Array[++CurrentPosition] = Value;
    } else {
        std::cout << "Stack Overflow" << std::endl;
    }
}

// Pop an element from the stack
int Stack::Pop() {
    if (CurrentPosition >= 0) {
        return Array[CurrentPosition--];
    }
    std::cout << "Stack underflow" << std::endl;
    return -1;
}

// Get the top element of the stack
int Stack::Top() {
    if (CurrentPosition >= 0) {
        return Array[CurrentPosition];
    }
    std::cout << "Stack underflow" << std::endl;
    return -1;
}