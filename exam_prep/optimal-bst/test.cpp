#include <iostream>

#include "cache.hpp"
#include "hashFunc.hpp"
#include "optimalBSTCache.hpp"

class IdHashFunc: public HashFunc<uint64_t> {
public:
    uint64_t hash(const uint64_t& key) const override {
        return key;
    }
};

int main() {
    IdHashFunc idHash;
    HashFunc<uint64_t>& hashFunc = idHash;

    using BST = OptimalBSTCache<uint64_t, uint64_t, uint64_t>;
    BST::Data data = {{3, 9, 3}, {4, 16, 4}, {2, 4, 2}, {1, 1, 1}};
    auto bst = BST(data,hashFunc);

    Cache<uint64_t, uint64_t>& cache = bst;

    std::cout << *(cache.get(4).second) << std::endl;
    std::cout << cache.get(100).first << std::endl;

    bst.print(std::cout);
    std::cout << std::endl;

    std::cout << bst.score() << std::endl;

    return 0;
}