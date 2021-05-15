#include <cstddef>
#include <stack>
#include <iostream>

struct Array {
    unsigned int* data;
    std::size_t len;
};

struct Config {
    size_t (*index)(size_t len, size_t iter);
    size_t (*notFound)(size_t);
};

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

int main() {
    unsigned int array[] = {2, 1, 3, 2, 1, 2};
    size_t len = sizeof(array) / sizeof(array[0]);
    size_t* res = nextMin(array, len);
    for(size_t i = 0; i < len; i++) {
        std::cout << res[i] << std::endl;
    }
    return 0;
}