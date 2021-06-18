#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using Array = std::vector<int>;

std::tuple<bool, std::size_t, std::size_t> brute_force(const Array& a, int t) {
    std::size_t n = a.size();
    for(std::size_t i = 0; i < n; i++) {
        for(std::size_t j = i + 1; j < n; j++) {
            if((a[i] + a[j]) == t) {
                return std::make_tuple(true, i, j);
            }
        }
    }
    return std::make_tuple(false, n, n);
}

// Theta(n^2), Theta(1)

std::tuple<bool, std::size_t, std::size_t> hash_map(const Array& a, int t) {
    std::unordered_map<int, std::size_t> map;
    std::size_t n = a.size();
    for(std::size_t i = 0; i < n; i++) {
        auto res = map.find(t - a[i]);
        if(res != map.end()) {
            return std::make_tuple(true, res->second, i);
        }
        map[a[i]] = i;
    }
    return std::make_tuple(false, n, n);
}

// Theta(n), Theta(n)

std::tuple<bool, std::size_t, std::size_t> general(Array& a, int t) {
    std::sort(a.begin(), a.end()); // Theta(n * log n), Theta(1)
    std::size_t n = a.size();
    for(std::size_t i = 0; i < n; i++) {
        auto res = std::lower_bound(a.begin(), a.end(), t - a[i]); // Theta(lgn), Theta(1)
        if(res == a.end()) {
            continue;
        }
        std::size_t j = res - a.begin();
        if(*res == t - a[i] && (*res != a[i] || (j <= n && a[j + 1] == a[i]))) {
            return std::make_tuple(true, j, i);
        }
        // Theta(lgn), Theta(1)
    }
    // Theta(n * log n), Theta(1)
    return std::make_tuple(false, n, n);
}
// Theta(n * log n), Theta(1)

std::tuple<bool, std::size_t, std::size_t> sorted(const Array& a, int t) {
    std::size_t n = a.size();
    std::size_t begin = 0;
    std::size_t end = n - 1;
    while(begin < end) {
        int sum = a[begin] + a[end];
        if(sum == t) {
            return std::make_tuple(true, begin, end);
        }
        if(sum < t) {
            begin++;
        } else {
            end--;
        }
    }
    return std::make_tuple(false, n, n);
}

// Theta(n), Theta(1)

int main() {
    Array a = { 1, -2, 11, 3, 5, 7, 11};
    std::sort(a.begin(), a.end());
    auto res = sorted(a, 22);
    if(std::get<0>(res)) {
        std::cout << a[std::get<1>(res)] << ' ' << a[std::get<2>(res)] << std::endl;
    }
    return 0;
}