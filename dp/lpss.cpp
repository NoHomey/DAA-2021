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

std::size_t lpss(const Array& arr) {
    return lcss(arr, Array(arr.crbegin(), arr.crend()));
}

// Theta(n^2), Theta(n^2)

int main() {
    std::cout << lpss({11, 7, 7, 5, 13, 11, 13, 7}) << std::endl;
    return 0;
}