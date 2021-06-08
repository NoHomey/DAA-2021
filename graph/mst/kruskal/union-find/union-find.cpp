#include "union-find.h"

UnionFind::UnionFind(std::size_t count)
: set(count) {
    for(std::size_t i = 0; i < count; i++) {
        set[i] = {1, i};
    }
}

std::size_t UnionFind::Find(std::size_t x) {
    while(!isLeader(x)) {
        set[x].parent = parent(parent(x));
        x = parent(x);
    }
    return x;
}
    
void UnionFind::Union(std::size_t x, std::size_t y) {
    std::size_t leaderOfX = Find(x);
    std::size_t leaderOfY = Find(y);
    std::size_t leader = leaderOfX;
    std::size_t element = leaderOfY;
    if(Size(leaderOfX) < Size(leaderOfY)) {
        leader = leaderOfY;
        element = leaderOfX;
    }
    set[leader].size += set[element].size;
    set[element].parent = leader;
}

bool UnionFind::isLeader(std::size_t x) const {
    return parent(x) == x;
}

std::size_t UnionFind::parent(std::size_t x) const {
    return set[x].parent;
}

std::size_t UnionFind::Size(std::size_t x) {
    return set[Find(x)].size;
}

std::size_t UnionFind::Count() const {
    return set.size();
}