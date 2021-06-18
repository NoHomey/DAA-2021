#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using Array = std::vector<int>;

std::tuple<bool, std::size_t, std::size_t> sorted_2sum(const Array& a, std::size_t start, int t) {
    std::size_t n = a.size();
    std::size_t begin = start;
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
} // Theta(n), Theta(1)

std::tuple<bool, std::size_t, std::size_t, std::size_t> sol_3sum(Array& a, int t) {
    std::sort(a.begin(), a.end()); // Theta(n * lgn), Theta(1)
    std::size_t n = a.size();
    for(std::size_t i = 0; i < n; i++) {
        auto res = sorted_2sum(a, i + 1, t - a[i]);
        if(std::get<0>(res)) {
            return std::make_tuple(true, i, std::get<1>(res), std::get<2>(res));
        }
    }
    return std::make_tuple(false, n, n, n);
} // Theta(n^2), Theta(1)

int main() {
    Array a = { 1, -2, 11, 3, 5, 7, 11};
    auto res = sol_3sum(a, 23);
    if(std::get<0>(res)) {
        std::cout << a[std::get<1>(res)] << ' ' << a[std::get<2>(res)] << ' ' << a[std::get<3>(res)]<< std::endl;
    }
    return 0;
}