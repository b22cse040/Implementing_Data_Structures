#include <iostream>
#include <string>
using namespace std;

template <typename K, typename V>
class unordered_map {
private:
    struct Node {
        K key;
        V val;
        Node* next;
        Node(K k, V v) : key(k), val(v), next(NULL) {}
    };

    Node** buckets;                                             // Array of pointers to linked lists (buckets)
    int countBuckets;                                           // Number of buckets
    const double LOAD_FACTOR = 0.75;                            // Threshold for resizing
    int size;                                                   // Number of key-value pairs in the map

    // Hash function to map keys to bucket indices
    int hashFunction(const K& key) const {
        return std::hash<K>()(key) % countBuckets;
    }

    // Resize the hash table when load factor exceeds threshold
    void resize() {
        int newCountBuckets = 2 * countBuckets; 
        Node** newBuckets = new Node*[newCountBuckets]();

        // Rehash all elements into the new bucket array
        for (int i = 0; i < countBuckets; ++i) {
            Node* current = buckets[i];
            while (current) {
                int newIndex = std::hash<K>()(current->key) % newCountBuckets;

                Node* nextNode = current->next;  
                current->next = newBuckets[newIndex];
                newBuckets[newIndex] = current;

                current = nextNode;           
            }
        }

        delete[] buckets;             
        buckets = newBuckets;          
        countBuckets = newCountBuckets; 
    }

public:
    // Constructor
    unordered_map() : countBuckets(2), size(0) {
        buckets = new Node*[countBuckets]();
    }

    // Destructor
    ~unordered_map() {
        for (int i = 0; i < countBuckets; ++i) {
            Node* current = buckets[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] buckets;
    }

    // Insert a key-value pair into the map
    void insert(const K& k, const V& v) {
        int idx = hashFunction(k);
        Node* curr = buckets[idx];

        // Check if the key already exists and update its value
        while (curr) {
            if (curr->key == k) {
                curr->val = v;  
                return;
            }
            curr = curr->next;
        }

        // If key does not exist, add a new node at the start of the list
        Node* newNode = new Node(k, v);
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
        size++;

        // Check load factor and resize if necessary
        if (static_cast<double>(size) / countBuckets > LOAD_FACTOR) resize();
    }
};
