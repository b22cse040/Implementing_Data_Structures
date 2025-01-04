#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* arr;
    size_t capacity;
    size_t length;

    void resize(size_t newCapacity) {
        T* newArr = new T[newCapacity];
        for (size_t i = 0; i < length; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }
public:
    Vector() : arr(nullptr), capacity(0), length(0) {}

    ~Vector() {
        delete[] arr;
    }

    void push_back(const T& ele) {
        if (length == capacity) {
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
            resize(newCapacity);
        }
        arr[length++] = ele;
    }

    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        return arr[index];
    }

    size_t size() const { return length; }
    size_t maxSize() const {return capacity; }

    void pop_back() {
        if (length == 0) throw std::out_of_range("Vector underflow");
        --length;
    }

    void clear() { length = 0; }
};

template <typename T> class Stack{
    private:
    Vector<T> arr;

    public:
    void push(const T& ele){
        if(arr.size() == arr.maxSize()) std::out_of_range("Stack Overflow!");
        arr.push_back(ele);
    }

    void pop(){
        if(arr.size() == 0) std::out_of_range("Stack Underflow!");
        arr.pop_back();
    }

    T& top(){ return arr[arr.size() - 1]; }

    bool empty(){ return arr.size() == 0; }

    size_t stackSize() {return arr.size() - 1; }
};

/* =========================================================================================================== */
void testIntStack() {
    Stack<int> intStack;

    try {
        // Pushing integers onto the stack
        intStack.push(1);
        intStack.push(2);
        intStack.push(3);

        std::cout << "Top element in int stack: " << intStack.top() << std::endl;

        // Popping an element from the stack
        intStack.pop();
        std::cout << "Top element after pop: " << intStack.top() << std::endl;

        std::cout << "Stack size after pop: " << intStack.stackSize() << std::endl;

        // Popping all elements to check for underflow
        intStack.pop();
        intStack.pop();
        
        std::cout << "Stack size after all pops: " << intStack.stackSize() << std::endl;
    } 
    catch (const std::out_of_range& e) {
        std::cout << "Exception in int stack: " << e.what() << std::endl;
    }
}


/* ==================================================================================================================== */
void testStringStack() {
    Stack<std::string> stringStack;

    try {
        // Pushing strings onto the stack
        stringStack.push("Hello");
        stringStack.push("World");
        stringStack.push("Stack");

        std::cout << "Top element in string stack: " << stringStack.top() << std::endl;

        // Popping an element from the stack
        stringStack.pop();
        std::cout << "Top element after pop: " << stringStack.top() << std::endl;

        std::cout << "Stack size after pop: " << stringStack.stackSize() << std::endl;

        // Popping all elements to check for underflow
        stringStack.pop();
        stringStack.pop();
        
        std::cout << "Stack size after all pops: " << stringStack.stackSize() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Exception in string stack: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Testing int stack:" << std::endl;
    testIntStack();

    std::cout << "\nTesting string stack:" << std::endl;
    testStringStack();

    return 0;
}
