#pragma once

#include <utility>

template<typename Key, typename Value>
class Cache {
public:
    virtual std::pair<bool, const Value*> get(const Key& key) = 0;
};