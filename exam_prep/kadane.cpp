#include <vector>

#include <iostream>

struct Result {
    std::size_t begin;
    std::size_t end;
    int         sum;
};

Result kadane(const std::vector<int>& array) {
    Result max = {0, 0, 0};
    Result curr = {0, 0, 0};
    for(int x: array) {
        if(curr.sum <= 0) {
            curr.begin = curr.end;
            curr.sum = 0;
        }
        curr.sum += x;
        if(curr.sum > max.sum) {
            max = {curr.begin, curr.end + 1, curr.sum};
        }
        curr.end++;
    }
    return max;
}

// Theta(n), Theta(1)

int main() {
    //std::vector<int> arr = {-1, -2, -3, -1, -2, -10, -3};
    std::vector<int> arr = {1, -2, 3, -1, 2, -10, 3};
    Result res = kadane(arr);
    std::cout << "max-sum: " << res.sum << std::endl;
    for(std::size_t i = res.begin; i < res.end; i++) {
        std::cout << arr[i] << ",";
    }
    std::cout << std::endl;

    return 0;
}