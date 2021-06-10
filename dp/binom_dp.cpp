#include <vector>

#include <iostream>

using Nat = unsigned long long;

Nat binom(Nat n, Nat k) {
    k = std::min(k, n - k);
    auto table = std::vector<std::vector<Nat>>(
        n + 1,
        std::vector<Nat>(k + 1, 0)
    );
    for(Nat i = 0; i <= n; i++) {
        table[i][0] = 1;
    }
    for(Nat r = 0; r < n; r++) {
        Nat limit = std::min(r + 1, k);
        for(Nat c = 0; c < limit; c++) {
            table[r + 1][c + 1] = table[r][c] + table[r][c + 1];
        }
    }
    return table[n][k];
}

// O(n * k), Theta((n + 1) * (k + 1))

int main() {
    std::cout << binom(3, 3) << std::endl;
    std::cout << binom(4, 2) << std::endl;
    return 0;
}