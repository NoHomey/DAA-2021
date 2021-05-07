#include <iostream>

int mod(int x, int k) {
    return ((x % k) + k) % k;
}

size_t remove(int arr[], size_t n, size_t k, int x, int y, int z) {
    size_t writeIndex = 0;
    for(size_t readIndex = 0; readIndex < n; readIndex++) {
        int elem = arr[readIndex];
        int r = mod(elem, k);
        if(r == z) {
            continue;
        }
        if(r == y && writeIndex > 0) {
            int p = mod(arr[writeIndex - 1], k);
            if(p == x) {
                writeIndex--;
                continue;
            }
        }
        arr[writeIndex] = elem;
        writeIndex++;
    }
    return writeIndex;
}

// M(n) = Theta(1)
// T(n) = Theta(n)

int main() {
    int arr[] = {-1, -2, -3, -3, 3, 4};
    size_t n = sizeof(arr)/ sizeof(arr[0]);
    int k = 5;
    size_t res = remove(arr, n, k, 3, 4, 2);
    std::cout << res << std::endl;
    for(size_t i = 0; i < res; i++) {
        std::cout << mod(arr[i], k) << ", ";
    }
    std::cout << std::endl;
    return 0;
}