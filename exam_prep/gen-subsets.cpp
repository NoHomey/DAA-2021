#include <queue>

#include <iostream>

using SubSet = uint64_t;

using Element = uint8_t;

const SubSet EMPTY_SET = 0;

SubSet set_singleton(Element x) {
    return 1 << x;
}

SubSet set_union(SubSet a, SubSet b) {
    return a | b;
}

SubSet set_intersect(SubSet a, SubSet b) {
    return a & b;
}

SubSet set_complement(SubSet s) {
    return ~s;
}

SubSet set_diff(SubSet a, SubSet b) {
    return set_intersect(a, set_complement(b));
}

SubSet set_add(SubSet set, Element x) {
    return set_union(set, set_singleton(x));
}

SubSet set_remove(SubSet set, Element x) {
    return set_diff(set, set_singleton(x));
}

bool is_in_set(Element x, SubSet set) {
    return set_intersect(set_singleton(x), set) != EMPTY_SET;
}

uint64_t powerset_size(uint8_t n) {
    return 1 << n; // 2^n
}

struct State {
    SubSet set;
    Element next;
};

int main() {
    std::queue<State> q;
    Element n = 8;
    q.push({EMPTY_SET, 0});
    std::size_t counter = 0;
    while(!q.empty()) {
        State last = q.front();
        q.pop();
        counter++;
        for(Element x = last.next; x < n; x++) {
            q.push({set_add(last.set, x), static_cast<Element>(x + 1)});
        }
    }

    std::cout << (counter == powerset_size(n)) << std::endl;
    
    return 0;
} // Theta(2^n), O(2^n)