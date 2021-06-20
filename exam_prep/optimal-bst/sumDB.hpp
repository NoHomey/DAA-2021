#pragma once
#include <vector>

template<typename Number>
class SumDB {
public:
    using Array = std::vector<Number>;

private:
    Array prefixSum;

public:
    SumDB(const Array& value)
    : prefixSum(value.size() + 1, 0) {
        std::size_t n = value.size();
        for(std::size_t i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + value[i];
        }
    }

    Number query(std::size_t i, std::size_t j) {
        return prefixSum[j] - prefixSum[i - 1];
    }
};