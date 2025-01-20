#include <iostream>
#include <string>
using namespace std;

template <typename K, typename V> class unordered_map{
    private:
    static const int COUNT_BUCKET = 1;
    struct Node {
        K key;
        V val;
        Node* next;
        Node(K k, V v) : key(k), value(v), next(NULL) {}
    }
    Node* buckets[COUNT_BUCKET];

    int hashFunction(const K& key) {
        return std::hash<K>{}(key) % BUCKET_COUNT;
    }

    public:
    
};