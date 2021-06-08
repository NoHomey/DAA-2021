#pragma once

#include "./container/heap.hpp"
#include "./storage/indexed_pq.hpp"

template<typename Priority, typename Element>
class IndexedPriorityQueue {
private:
    using Container = IndexedPriorityQueueContainer<Priority, Element>;

public:
    using Entry = typename Container::Entry;

private:
    using Impl = Heap<Entry, Container>;
    
private:
    Impl impl;

public:
    IndexedPriorityQueue(std::size_t cap): impl(Container(cap)) {}

    bool is_empty() const {
        return impl.is_empty();
    }

    void push(Entry entry) {
        impl.push(entry);
    }

    Entry pop() {
        return impl.pop();
    }

    void update(Entry entry) {
        impl.update(entry);
    }
};