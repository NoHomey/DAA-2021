#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using Nat = uint32_t;
using Int = int64_t;

struct Entry {
    Nat begin;
    Nat end;
    Nat value;
};

using Data = std::vector<Entry>;

Nat begin(const Data& data) {
    Nat res = data[0].begin;
    Nat l = data.size();
    for(Nat i = 1; i < l; i++) {
        auto entry = data[i];
        if(entry.begin < res) {
            res = entry.begin;
        }
    }
    return res;
}

Nat end(const Data& data) {
    Nat res = 0;
    for(Entry e: data) {
        if(e.end > res) {
            res = e.end;
        }
    }
    return res;
}

Nat max(const Data& data) {
    Entry res = {begin(data), end(data), 0};
    auto hist = std::vector<Nat>(res.end - res.begin + 1, 0);
    for(Entry e: data) {
        for(Nat i = e.begin; i <= e.end; i++) {
            hist[i - res.begin] += e.value;
        }
    } // O(n), Theta(n) where n = res.end - res.begin + 1
    for(Nat val: hist) {
        res.value = std::max(res.value, val);
    } // Theta(n), Theta(1)
    return res.value;
} // Theta(n), Theta(n)

Nat max_mem_opt(const Data& data) {
    Entry res = {begin(data), end(data), 0};
    std::map<Nat, Nat> hist;
    for(Entry e: data) {
        for(Nat i = e.begin; i <= e.end; i++) {
            hist[i - res.begin] += e.value;
        }
    } // O(n * lg k), Theta(2k) where n = res.end - res.begin + 1, k = data.size()
    for(auto pair: hist) {
        res.value = std::max(res.value, pair.second);
    } // Theta(k), Theta(1)
    return res.value;
} // O(n * lg k + k), Theta(k)

Nat max_opt(const Data& data) {
    Entry res = {begin(data), end(data), 0};
    std::map<Nat, Int> hist;
    for(Entry e: data) {
        hist[e.begin - res.begin] = e.value;
        hist[e.end - res.begin] = -static_cast<Int>(e.value);
    } // O(k * lg k), Theta(2k) where k = data.size()
    Nat max_so_far = 0;
    for(auto pair: hist) {
        res.value += pair.second;
        max_so_far = std::max(res.value, max_so_far);
    } // Theta(k), Theta(1)
    return max_so_far;
} // O(k * lg k), Theta(k)

int main() {
    Data data = {{1, 3, 5}, {2, 5, 3}, {4, 6, 4}};
    std::cout << max(data) << std::endl;
    return 0;
}