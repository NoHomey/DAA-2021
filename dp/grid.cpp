#include <vector>

#include <iostream>

using Nat = unsigned long long;

class Row {
private:
    std::vector<Nat> data;

public:
    Row(Nat k): data(k + 1, 0) {
        data[0] = 1;
    }

    void swap(Row& other) {
        data.swap(other.data);
    }

    Nat& operator[](std::size_t i) {
        return data[i];
    }

    Nat operator[](std::size_t i) const {
        return data[i];
    }
};

Nat binom(Nat n, Nat k) {
    k = std::min(k, n - k);
    Row curr(k);
    Row prev(k);
    for(Nat r = 0; r < n; r++) {
        Nat limit = std::min(r + 1, k);
        curr[0] = 1;
        for(Nat c = 0; c < limit; c++) {
            curr[c + 1] = prev[c] + prev[c + 1];
        }
        prev.swap(curr);
    }
    return prev[k];
}

// O(n * min(k, n - k)), Theta(min(k, n - k))

Nat grid(Nat n, Nat m) {
    return binom(n + m - 2, m - 1);
}

int main() {
    std::cout << binom(3, 3) << std::endl;
    std::cout << binom(4, 2) << std::endl;
    std::cout << grid(4, 6) << std::endl;
    return 0;
}