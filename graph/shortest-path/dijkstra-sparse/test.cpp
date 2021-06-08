#include <vector>
#include "container/heap.hpp"
#include <iostream>

class Container {
private:
    std::vector<int> storage;

public:
    Container(std::size_t cap) {
        storage.reserve(cap);
    };

    Container(Container&& c) = default;

    std::size_t size() const {
        return storage.size();
    }

    bool less(std::size_t i, std::size_t j) const {
        return storage[i] < storage[j];
    }

    void swap(std::size_t i, std::size_t j) {
        int tmp = storage[i];
        storage[i] = storage[j];
        storage[j] = tmp;
    }

    void push(const int& element) {
        storage.push_back(element);
    }

    int pop() {
        int last = storage.back();
        storage.pop_back();
        return last;
    }
};

using H = Heap<int, Container>;

int main() {
    H h(Container(10));
    h.push(10);
    h.push(-1);
    h.push(2);
    while(!h.is_empty()) {
        std::cout << h.pop() << std::endl;
    }
    return 0;
}