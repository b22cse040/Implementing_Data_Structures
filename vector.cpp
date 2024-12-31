#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Vector {
private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void reallocate(size_t newCapacity) {
        // Expand or shrink the vector
        if (newCapacity < size) {
            capacity = size;
            return;
        } 
        else if (newCapacity == size) return;
        else { // Expand
            T* newData = new T[newCapacity];
            for (size_t i = 0; i < size; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

public:
    Vector() { reallocate(1); } // Initial capacity of 1

    ~Vector() { delete[] data; }

    T* begin(){ return data; }
    T* end(){ return data + size; }

    void push_back(const T& ele) {
        if (size == capacity) reallocate(2 * capacity); // Double the capacity
        data[size++] = ele;
    }

    void pop_back() {
        if (size == 0) throw out_of_range("Array is empty, cannot pop!");
        size--;
    }

    T& front(){ return data[0]; }
    T& back(){ return data[size - 1]; }

    T& at(size_t idx) {
        if(idx >= size) throw out_of_range("Index is out of Bounds!");
        return data[idx];
    }

    T& operator[](size_t idx) {
        if (idx >= size) throw out_of_range("Index is out of bounds!");
        return data[idx];
    }

    const T& operator[](size_t idx) const {
        if (idx >= size) throw out_of_range("Index is out of bounds!");
        return data[idx];
    }

    size_t Size() const { return size; }
    size_t maxSize() const { return capacity; }
    bool Empty() const { return size == 0; }

    void resize(size_t newSize) {
        while (capacity <= newSize) reallocate(2 * capacity);
        size = newSize;
    }

    void resize(size_t newSize, const T& ele) {
        while (capacity <= newSize) reallocate(2 * capacity);
        for (size_t i = size; i < newSize; i++) data[i] = ele;
        size = newSize;
    }

    void swap(T* ele1, T* ele2){
        T temp = *ele1;
        *ele1 = *ele2;
        *ele2 = temp;
    }
};

// Main function for testing the Vector class
int main() {
    Vector<int> vec;

    // Test push_back
    cout << "Test: push_back\n";
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    cout << "Vector elements after push_back: ";
    for (size_t i = 0; i < vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << "\n";

    // Test Empty
    cout << "Test: Empty\n";
    string isEmpty = (vec.Empty()) ? "True" : "False";
    cout << "Is the vector Empty? " << isEmpty << "\n\n";
    
    // Test pop_back
    cout << "Test: pop_back\n";
    vec.pop_back();
    cout << "After pop_back: ";
    for (size_t i = 0; i < vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << "\n\n";

    // Test Size and Capacity
    cout << "Test: Size and Capacity\n";
    cout << "Size: " << vec.Size() << ", Capacity: " << vec.maxSize() << "\n\n";

    // Test swap
    cout << "Test: swap\n";
    cout << "Before swap: vec[0] = " << vec[0] << ", vec[1] = " << vec[1] << "\n\n";
    vec.swap(&vec[0], &vec[1]);
    cout << "After swap: vec[0] = " << vec[0] << ", vec[1] = " << vec[1] << "\n\n";

    // Test resize with a fill value
    cout << "Test: resize with a fill value\n";
    vec.resize(5, 100); // Resize and fill with 100
    cout << "After resize with fill value 100: ";
    for (size_t i = 0; i < vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << "\n";
    cout << "Size: " << vec.Size() << ", Capacity: " << vec.maxSize() << "\n\n";

    // Test front and back
    cout << "Test: front and back\n";
    cout << "The element at front is: " << vec.front() << "\n";
    cout << "The element at back is: " << vec.back() << "\n\n";

    // Test at() with exception handling
    cout << "Test: at() with exception handling\n";
    try {
        cout << "Element at index 2: " << vec.at(2) << "\n";
        cout << "Element at index 10: " << vec.at(10) << "\n"; // Should throw exception
    } 
    catch (const out_of_range& e) {
        cout << "Exception: " << e.what() << "\n\n";
    }

    // Test operator[] with exception handling
    cout << "Test: operator[] with exception handling\n";
    try {
        cout << "Element at index 1 using operator[]: " << vec[1] << "\n";
        cout << "Element at index 5 using operator[]: " << vec[5] << "\n"; // Should throw exception
    } 
    catch (const out_of_range& e) {
        cout << "Exception: " << e.what() << "\n\n";
    }

    return 0;
}
