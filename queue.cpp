#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T> class Vector {
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

template <typename T> class Queue{
    private:
    Vector<T> arr;

    public:
    void push(const T& ele){
        if(arr.size() == arr.maxSize()) std::out_of_range("Queue Overflow!");
        arr.push_back(ele);
    }

    void pop(){
        if(arr.size() == 0) std::out_of_range("Queue Underflow!");

        // Note that queue pops from the front
        for(size_t i = 1; i < arr.size(); i++) arr[i - 1] = arr[i];
        return;
    }

    T& front(){ 
        if(arr.size() == 0) std::out_of_range("Queue is Empty!");
        return arr[0]; 
    }

    T& back(){ return arr[arr.size() - 1]; }

    bool empty(){ return arr.size() == 0; }
};

int main() {
    Queue<int> intQueue;
    intQueue.push(1);
    intQueue.push(2);
    intQueue.push(3);

    std::cout << "Front: " << intQueue.front() << "\n"; // Output: Front: 1
    std::cout << "Back: " << intQueue.back() << "\n";   // Output: Back: 3

    intQueue.pop(); // Removes 1
    std::cout << "Front after pop: " << intQueue.front() << "\n"; // Output: Front: 2

    Queue<std::string> stringQueue;
    stringQueue.push("Hello");
    stringQueue.push("World");

    std::cout << "Front: " << stringQueue.front() << "\n"; // Output: Front: Hello
    std::cout << "Back: " << stringQueue.back() << "\n";   // Output: Back: World

    return 0;
}