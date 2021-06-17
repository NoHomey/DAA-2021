#include <vector>
#include <algorithm>
#include <iostream>

using Nat = unsigned int;

using List = const std::vector<Nat>&;

class Table {
private:
    std::vector<Nat> profit;

public:
    Table(std::size_t colors): profit(colors, 0) {}

    Nat& operator[](std::size_t i) {
        return profit[i];
    }

    Nat operator[](std::size_t i) const {
        return profit[i];
    }

    void swap(Table& other) {
        profit.swap(other.profit);
    }

    void reset() {
        std::size_t m = profit.size();
        for(std::size_t i = 0; i < m; i++) {
            profit[i] = 0;
        }
    }
};

Nat color(Nat n, List profit) {
    std::size_t m = profit.size();
    if(n > 1 && m == 1) {
        return 0;
    }
    // Theta(m), Theta(m)
    Table prev(m), curr(m);

    // Theta(n * m^2), Theta(1)
    for(std::size_t k = 0; k < n; k++) {
        for(std::size_t i = 0; i < m; i++) {
            for(std::size_t j = 0; j < m; j++) {
                if(j != i) {
                    curr[i] = std::max(curr[i], prev[j]);
                }
            }
            curr[i] += profit[i];
        }
        prev.swap(curr);
        curr.reset();
    }

    // Theta(m), Theta(1)
    Nat res = 0;
    for(std::size_t i = 0; i < m; i++) {
        res = std::max(res, prev[i]);
    }
    return res;
}

// Theta(n * m^2), Theta(m)

int main() {
    std::cout << color(4, {10, 20, 10}) << std::endl;
    std::cout << color(4, {100}) << std::endl;
    return 0;
}