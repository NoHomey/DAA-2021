#include <iostream>

int mod(int x, int k) {
    return ((x % k) + k) % k;
}

// [1, 2, 3, 3, 2, 1]
bool isKPalindrome(int arr[], size_t n, int k) {
    size_t left = 0;
    size_t right = n - 1;
    while(left < right) {
        int leftElement = mod(arr[left], k);
        int rightElement = mod(arr[right], k);
        if(leftElement != rightElement) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// M(n) = Theta(1)
// T(n) = Theta(n/2) = Theta(n)
// Inv: arr[1...left - 1] ++ arr[right+1...n] is K-palindrome.

int main() {
    int arr[] = {-1, -2, -3, -3, 3, 4};
    size_t n = sizeof(arr)/ sizeof(arr[0]);
    int k = 5;
    std::cout << isKPalindrome(arr, n, k) << std::endl;
    return 0;
}