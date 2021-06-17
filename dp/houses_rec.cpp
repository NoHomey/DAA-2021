#include <vector>
#include <algorithm>
#include <iostream>

using Nat = unsigned int;

using List = const std::vector<Nat>&;

Nat color_rec_helper(Nat n, List profit, std::size_t color) {
    if(n == 0) {
        return 0;
    }
    Nat res = 0;
    std::size_t m = profit.size();
    for(std::size_t i = 0; i < m; i++) {
        if(i != color) {
            res = std::max(res, color_rec_helper(n - 1, profit, i) + profit[color]);
        }
    }
    return res;
}

Nat color_rec(Nat n, List profit) {
    Nat res = 0;
    std::size_t m = profit.size();
    for(std::size_t i = 0; i < m; i++) {
        res = std::max(res, color_rec_helper(n, profit, i));
    }
    return res;
}

int main() {
    std::cout << color_rec(4, {10, 20, 10}) << std::endl;
    return 0;
}