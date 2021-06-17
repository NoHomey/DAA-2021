#include <vector>
#include <algorithm>
#include <iostream>

using Nat = unsigned int;

using List = const std::vector<Nat>&;

Nat color(Nat n, List profit) {
    std::size_t m = profit.size();
    if(n > 1 && m == 1) {
        return 0;
    }
    // Theta(n * m), Theta(n * m)
    auto table = std::vector<std::vector<Nat>>(n + 1, std::vector<Nat>(m, 0));

    // Theta(n * m^2), Theta(1)
    for(std::size_t k = 0; k < n; k++) {
        for(std::size_t i = 0; i < m; i++) {
            for(std::size_t j = 0; j < m; j++) {
                if(j != i) {
                    table[k + 1][i] = std::max(table[k + 1][i], table[k][j]);
                }
            }
            table[k + 1][i] += profit[i];
        }
    }

    // Theta(m), Theta(1)
    Nat res = 0;
    for(std::size_t i = 0; i < m; i++) {
        res = std::max(res, table[n][i]);
    }
    return res;
}

// Theta(n * m^2), Theta(n * m)

int main() {
    std::cout << color(4, {10, 20, 10}) << std::endl;
    std::cout << color(4, {100}) << std::endl;
    return 0;
}