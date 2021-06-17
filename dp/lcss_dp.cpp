#include <vector>
#include <algorithm>
#include <iostream>

using Array = std::vector<int>;

std::size_t lcss(const Array& l, const Array& r) {
    std::size_t n = l.size();
    std::size_t m = r.size();
    // Theta((n + 1) * (m + 1)), Theta((n + 1) * (m + 1))
    auto table = std::vector<std::vector<std::size_t>>(n + 1, std::vector<std::size_t>(m + 1, 0));
    for(std::size_t i = 0; i < n; i++) {
        for(std::size_t j = 0; j < m; j++) {
            //table[i + 1][j + 1] = ...
            if(l[i] == r[j]) {
                table[i + 1][j + 1] = table[i][j] + 1;
            } else {
                table[i + 1][j + 1] = std::max(table[i][j + 1], table[i + 1][j]);
            }
        }
    }
    // Theta(n * m), Theta(1)
    return table[n][m];
}

// Theta((n + 1) * (m + 1)), Theta((n + 1) * (m + 1))

int main() {
    std::cout << lcss({1, 2, 5, 4, 3}, {2, 2, 4, 4}) << std::endl;
    return 0;
}