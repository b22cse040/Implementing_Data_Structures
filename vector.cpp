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

    void push_back(const T& ele) {
        if (size == capacity) reallocate(2 * capacity); // Double the capacity
        data[size++] = ele;
    }

    void pop_back() {
        if (size == 0) throw out_of_range("Array is empty, cannot pop!");
        size--;
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
};

// Main function for testing the Vector class
int main() {
    Vector<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    cout << "Vector elements: ";
    for (size_t i = 0; i < vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    string isEmpty = (vec.Empty()) ? "True" : "False";
    cout << "Is the array Empty? " << isEmpty << "\n";
    vec.pop_back();

    cout << "After pop_back: ";
    for (size_t i = 0; i < vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    cout << "Size: " << vec.Size() << ", Capacity: " << vec.maxSize() << endl;

    vec.resize(5, 100); // Resize and fill with 100

    cout << "After resize: ";
    for (size_t i = 0; i < vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    cout << "Size: " << vec.Size() << ", Capacity: " << vec.maxSize() << endl;

    return 0;
}
