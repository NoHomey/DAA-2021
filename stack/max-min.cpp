#include <cstddef>
#include <stack>
#include <algorithm>
#include <iostream>

// helpers
struct Array {
    unsigned int* data;
    std::size_t len;
};

struct Config {
    size_t (*index)(size_t len, size_t iter);
    size_t (*notFound)(size_t);
};

// M(N) = O(N)
// T(N) = Theta(N + N) = Theta(N)

size_t* neighboorMin(Array array, Config config) {
    size_t* res = new size_t[array.len];
    std::stack<size_t> s;
    for(size_t iter = 0; iter < array.len; iter++) {
        size_t index = config.index(array.len, iter);
        while(!s.empty() && array.data[s.top()] >= array.data[index]) {
            s.pop();
        }
        if(!s.empty()) {
            res[index] = s.top();
        } else {
            res[index] = config.notFound(array.len);
        }
        s.push(index);
    }
    return res;
}

size_t prevIndex(size_t len, size_t iter) {
    return iter;
}

size_t prevNotFound(size_t len) {
    return -1;
}

size_t* prevMin(unsigned int* array, std::size_t len) {
    Array input = {array, len};
    Config config = {prevIndex, prevNotFound};
    return neighboorMin(input, config);
}

size_t nextIndex(size_t len, size_t iter) {
    return len - 1 - iter;
}

size_t nextNotFound(size_t len) {
    return len;
}

size_t* nextMin(unsigned int* array, std::size_t len) {
    Array input = {array, len};
    Config config = {nextIndex, nextNotFound};
    return neighboorMin(input, config);
}

// solution
unsigned int* maxOfMins(unsigned int* array, std::size_t len) {
    std::size_t* prev = prevMin(array, len); // Time: Theta(N), Memory: O(N)
    std::size_t* next = nextMin(array, len); // Time: Theta(N), Memory: O(N)
    unsigned int* res = new unsigned int[len + 1];
    for(std::size_t i = 0; i <= len; i++) { // Time: Theta(N)
        res[i] = 0;
    }
    for(std::size_t i = 0; i < len; i++) {  // Time: Theta(N)
        std::size_t window = next[i] - prev[i] - 1;
        res[window] = std::max(res[window], array[i]);
    }
    for(std::size_t i = len; i > 0; i--) { // Time: Theta(N)
        res[i - 1] = std::max(res[i - 1], res[i]);
    }
    res[0] = 0;
    return res;
}

// Time: Theta(N)
// Space: O(N)

int main() {
    unsigned int array[] = {2, 1, 3, 2, 1, 2};
    size_t len = sizeof(array) / sizeof(array[0]);
    unsigned int* res = maxOfMins(array, len);
    for(size_t i = 1; i <= len; i++) {
        std::cout << res[i] << std::endl;
    }
    return 0;
}