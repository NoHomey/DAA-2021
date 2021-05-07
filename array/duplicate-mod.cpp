#include <iostream>

int mod(int x, int k) {
    return ((x % k) + k) % k;
}

bool duplicate(int arr[], size_t n, int k) {
    if(n > k) {
        return true;
    }
    bool found[k] = {};
    for(size_t i = 0; i < n; i++) {
        int r = mod(arr[i], k);
        if(found[r]) {
            return true;
        }
        found[r] = true;
    }
    return false;
}

// a[i] = r, 0 <= r < k
// a[i] = r + k

bool origin(unsigned int arr[], unsigned int len, unsigned int k) {
    if(len > k) {
        return true;
    }
    for(size_t i = 0; i < len; i++) {
        int r = mod(arr[i], k);
        if(arr[r] >= k) {
            return true;
        }
        arr[r] += k;
    }
    return false;
}

// a, b
// c = merge(a, b)
// median(c)

// n = len(a), k = len(b)
// T(n, k) = Theta(n + k)
// M(n, k) = Theta(1)
// T_opt(n, k) = Theta(lg n + lg k)

// Ans: a[i]

// a[1], a[2], ..., a[i - 1], a[i], a[i+1], ..., a[n]

// j = (n + k) / 2 - i -> b[j] vs a[i] + <b[j + 1] vs a[i]>

// x, y