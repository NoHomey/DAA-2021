#include <cstddef>
#include <iostream>

int mod(int x, int k) {
    return ((x % k) + k) % k;
}

std::size_t longestSubArrayMod(const int* array, std::size_t len, int k) {
    bool* found = new bool[k];
    std::size_t res = 0;
    std::size_t beg = 0;
    for(int i = 0; i < k; i++) {
        found[i] = false;
    }
    for(std::size_t end = 0; end < len; end++) {
        int rem = mod(array[end], k);
        if(found[rem]) {
            while(true) {
                int begRem = mod(array[beg], k);
                if(begRem == rem) {
                    break;
                }
                found[begRem] = false;
                beg++;
            }
            beg++;
        } else {
            found[rem] = true;
            std::size_t curr = end - beg + 1;
            if(curr > res) {
                res = curr;
            }
        }
    }
    delete[] found;
    return res;
}

int main() {
    int arr[] = {1, 3, 2,4 , 3, 2, 1, 0, 4, 3};
    std::size_t len = sizeof(arr) / sizeof(arr[0]);
    std::cout << longestSubArrayMod(arr, len, 5) << std::endl;
    return 0;
}