#pragma once

#include <vector>

class UnionFind {
private:
    struct Set {
        std::size_t size;
        std::size_t parent;
    };
    
private:
    std::vector<Set> set;

private:
    bool isLeader(std::size_t x) const;

    std::size_t parent(std::size_t x) const;

public:
    UnionFind(std::size_t count);

    std::size_t Find(std::size_t x);
    
    void Union(std::size_t x, std::size_t y);

    std::size_t Size(std::size_t x);

    std::size_t Count() const;
};