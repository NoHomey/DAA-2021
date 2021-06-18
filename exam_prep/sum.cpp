#include <vector>
#include <iostream>

using Nat = unsigned int;

using Int = int;

using Ints = std::vector<Int>;

struct Entry {
    Nat begin;
    Nat end;
    Nat prime;
};

using Data = std::vector<Entry>;

Nat mod(Int x, Nat s) {
    return (s + (x % s)) % s;
}

Nat compute(const Ints& a, Nat p, const Data& b) {
    Nat n = a.size();
    auto sum = std::vector<Int>(n + 1, 0);
    sum[0] = 0;
    for(Nat i = 0; i < n; i++) {
        sum[i + 1] = mod(sum[i] + mod(a[i], p), p);
    }
    // Theta(n), Theta(n)

    Nat res = 0;
    for(Entry entry: b) {
        Nat s = mod(sum[entry.end] - sum[entry.begin - 1], p);
        Nat r = mod(s, entry.prime);
        res = mod(res + r, p);
    }
    // Theta(m), Theta(1)
    return res;
} // Theta(n + m), Theta(n)

int main() {
    Ints a = {1, 2, 3, 3, 2, 1, 1, 2, 1};
    Nat p = 19;
    Data b = {{1, 3, 5}, {4, 6, 7}, {7, 9, 11}};
    std::cout << compute(a, p, b) << std::endl;
    return 0;
}