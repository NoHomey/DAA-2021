#include <vector>

#include <iostream>

using Nat = uint64_t;

Nat ways(Nat n, const std::vector<Nat>& coins) {
    Nat k = coins.size();
    auto t = std::vector<std::vector<Nat>>(n + 1, std::vector<Nat>(k, 0));
    for(Nat i = 0; i < k; i++) {
        t[0][i] =  1;
    }
    for(Nat s = 1; s <= n; s++) {
        for(Nat i = 0; i < k; i++) {
            for(Nat j = 0; j <= i; j++) {
                Nat c = coins[j];
                if(s >= c) {
                    t[s][i] += t[s - c][j];
                }
            }
        } // Theta(k^2)
    }
    return t[n][k - 1];
} // Theta(n * k^2), Theta(n * k)

int main() {
    std::cout << ways(7, {2, 3, 5}) << std::endl;
    return 0;
}