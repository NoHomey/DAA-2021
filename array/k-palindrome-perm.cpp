#include <iostream>

int mod(int x, int k) {
    return ((x % k) + k) % k;
}

// [1, 3, 1, 2, 2, 3] -> [2, 1, 3, 3, 1, 2]
bool isKPalindromePermutation(int arr[], size_t n, int k) {
    bool count[k] = {};
    size_t oddCounters = 0;
    for(size_t index = 0; index < n; index++) {
        int rem = mod(arr[index], k);
        count[rem] = !count[rem];
        if(count[rem]) {
            oddCounters++;
        } else {
            oddCounters--;
        }
    }
    return oddCounters <= 1;
}

// M(n, k) = Theta(k)
// T(n, k) = Theta(n)

int main() {
    int arr[] = {1, 3, 1, 2, 2, 3};
    size_t n = sizeof(arr)/ sizeof(arr[0]);
    int k = 5;
    std::cout << isKPalindromePermutation(arr, n, k) << std::endl;
    return 0;
}