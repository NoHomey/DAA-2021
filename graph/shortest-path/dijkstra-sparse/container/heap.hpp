#pragma once

#include <utility>

// Container should implement:
// $ bool        less(std::size_t i, std::size_t j)
// $ void        swap(std::size_t i, std::size_t j)
// $ std::size_t size()
// $ void        push(const Element& e)
// $ Element     pop()

template<typename Element, class Container>
class Heap {
private:
    Container container;

    void up(std::size_t idx) {
        while(true) {
            std::size_t parentIdx = (idx - 1) / 2;
            if(parentIdx >= idx || !container.less(idx, parentIdx)) {
                break;
            }
            container.swap(idx, parentIdx);
            idx = parentIdx;
        }
    }

    bool down(std::size_t idx, std::size_t size) {
        while(true) {
            std::size_t leftIdx = 2 * idx + 1;
            std::size_t rightIdx = leftIdx + 1;
            if(leftIdx >= size || leftIdx < idx) {
                break;
            }
            std::size_t swapIdx = leftIdx;
            if(rightIdx < size && container.less(rightIdx, leftIdx)) {
                swapIdx = rightIdx;
            }
            if(!container.less(swapIdx, idx)) {
                break;
            }
            container.swap(swapIdx, idx);
            idx = swapIdx;
        };
    }

public:
    Heap(Container&& c)
    : container(std::move(c)) {}

    ~Heap() = default;

    void push(const Element& element) {
        container.push(element);
        up(container.size() - 1);
    }

    Element pop() {
        std::size_t last = container.size() - 1;
        container.swap(0, last);
        down(0, last);
        return container.pop();
    }

    bool is_empty() const {
        return container.size() == 0;
    }
};