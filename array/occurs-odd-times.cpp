#include <iostream>

int oddTimes(int arr[], size_t n) {
    int sum = 0;
    for(size_t i = 0; i < n; i++) {
        sum ^= arr[i];
    }
    return sum;
}