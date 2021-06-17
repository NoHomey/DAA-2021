#include <iostream>
#include <vector>

using Nat = std::size_t;

Nat sums_rec(Nat n, const std::vector<Nat>& coins) {
    if(n == 0) {
        return 1;
    }
    Nat sum = 0;
    for(Nat coin: coins) {
        if(coin <= n) {
            sum += sums_rec(n - coin, coins);
        }
    }
    return sum;
}

Nat sums(Nat n, const std::vector<Nat>& coins) {
    auto table = std::vector<Nat>(n + 1, 0);
    table[0] = 1;
    for(Nat k = 1; k <= n; k++) {
        Nat sum = 0;
        for(Nat coin: coins) {
            if(coin <= k) {
                sum += table[k - coin];
            }
        }
        table[k] = sum;
    }
    return table[n];
}
// Theta(n, t) = n * t, Theta(n) where t = coins.size()

int main() {
    std::cout << sums(1, {2, 3, 5}) << std::endl;
    std::cout << sums(7, {2, 3, 5}) << std::endl;
    std::cout << sums(10, {4, 8}) << std::endl;
    std::cout << sums(15, {4, 8}) << std::endl;
    return 0;
}