#pragma once

template<typename Key>
class HashFunc {
public:
    virtual uint64_t hash(const Key& key) const = 0; 
};