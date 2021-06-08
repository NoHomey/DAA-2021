#pragma once

#include <vector>

template<typename Priority, typename Element>
class IndexedPriorityQueueContainer {
public:
    struct Entry {
        Priority priority;
        Element element;
        std::size_t id;
    };
    
private:
    std::vector<Entry> storage;
    std::vector<std::size_t> storageIndex;

public:
    IndexedPriorityQueueContainer(std::size_t count)
    : storage(), storageIndex(count, count) {
        storage.reserve(count);
    }

    IndexedPriorityQueueContainer(IndexedPriorityQueueContainer&&) = default;

    ~IndexedPriorityQueueContainer() = default;

    std::size_t size() const {
        return storage.size();
    }

    bool less(std::size_t i, std::size_t j) const {
        return storage[i].priority < storage[j].priority;
    }

    void swap(std::size_t i, std::size_t j) {
        std::size_t idOfI = storage[i].id;
        std::size_t idOfJ = storage[j].id;

        Entry tmp = storage[i];
        storage[i] = storage[j];
        storage[j] = tmp;

        storageIndex[idOfI] = j;
        storageIndex[idOfJ] = i;
    }

    void push(Entry entry) {
        storageIndex[entry.id] = storage.size();
        storage.push_back(entry);
    }

    Entry pop() {
        Entry last = storage.back();
        storage.pop_back();
        storageIndex[last.id] = storageIndex.size();
        return last;
    }

    void update(const Entry& entry) {
        storage[index(entry)] = entry;
    }

    std::size_t index(const Entry& entry) const {
        return storageIndex[entry.id];
    }
};