#pragma once

#include <vector>

template<typename Priority, typename Element>
class PriorityQueueContainer {
public:
    struct Entry {
        Priority priority;
        Element element;
    };
    
private:
    std::vector<Entry> storage;

public:
    PriorityQueueContainer(std::size_t cap) {
        storage.reserve(cap);
    }

    PriorityQueueContainer(PriorityQueueContainer&&) = default;

    ~PriorityQueueContainer() = default;

    std::size_t size() const {
        return storage.size();
    }

    bool less(std::size_t i, std::size_t j) const {
        return storage[i].priority < storage[j].priority;
    }

    void swap(std::size_t i, std::size_t j) {
        Entry tmp = storage[i];
        storage[i] = storage[j];
        storage[j] = tmp;
    }

    void push(Entry entry) {
        storage.push_back(entry);
    }

    Entry pop() {
        Entry last = storage.back();
        storage.pop_back();
        return last;
    }
};