#include <vector>
#include <iostream>

using Seq = std::vector<int>;

Seq lcsa(const Seq& l, const Seq& r) {
    std::size_t n = l.size();
    std::size_t m = r.size();
    std::size_t max_len = 0;
    std::size_t max_end = 0;
    // Theta((n + 1) * (m + 1)), Theta((n + 1) * (m + 1))
    auto t = std::vector<std::vector<std::size_t>>(n + 1, std::vector<std::size_t>(m + 1, 0));
    
    // Theta(n * m), Theta(1)
    for(std::size_t i = 0; i < n; i++) {
        for(std::size_t j = 0; j < m; j++) {
            // t[i+1][j+1] = ...
            if(l[i] == r[j]) {
                std::size_t curr = 1 + t[i][j];
                if(curr > max_len) {
                    max_len = curr;
                    max_end = i + 1;
                }
                t[i+1][j+1] = curr;
            }
        }
    }

    std::size_t start_idx = max_end - max_len;
    auto offset = l.begin() + start_idx;
    return Seq(offset, offset + max_len);
}
// Theta((n + 1) * (m + 1)), Theta((n + 1) * (m + 1))

Seq lpsa(const Seq& seq) {
    return lcsa(seq, Seq(seq.crbegin(), seq.crend()));
}

// Theta(n^2), Theta(n^2)

int main() {
    Seq res = lpsa({11, 7, 7, 5, 13, 11, 13, 7});
    for(auto x: res) {
        std::cout << x << std::endl;
    }
    return 0;
}