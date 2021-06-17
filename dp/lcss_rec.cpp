#include <vector>
#include <algorithm>
#include <iostream>

using Array = std::vector<int>;

class Solver {
private:
    const Array& left;
    const Array& right;

private:
    std::size_t solve(std::size_t n, std::size_t m) const {
        if(n == 0 || m == 0) {
            return 0;
        }
        if(left[n - 1] == right[m - 1]) {
            return solve(n - 1, m - 1) + 1;
        }
        return std::max(solve(n - 1, m), solve(n, m - 1));
    }

public:
    Solver(const Array& l, const Array& r)
    : left(l), right(r) {}

    std::size_t solve() const {
        return solve(left.size(), right.size());
    }
};

std::size_t lcss(const Array& l, const Array& r) {
    Solver s(l, r);
    return s.solve();
}

int main() {
    std::cout << lcss({1, 2, 5, 4, 3}, {2, 2, 4, 4}) << std::endl;
    return 0;
}