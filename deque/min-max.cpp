#include <iostream>
#include <deque>
#include <cstddef>
#include <algorithm>

void add(int* array, std::size_t index, std::deque<std::size_t>& deck) {
    int elem = array[index];
    while(!deck.empty() && elem >= array[deck.back()]) {
        deck.pop_back();
    }
    deck.push_back(index);
}

void ensureSize(std::size_t index, std::size_t k, std::deque<std::size_t>& deck) {
    while(!deck.empty() && deck.front() <= index - k) {
        deck.pop_front();
    }
}

int maxInSubArray(int* array, const std::deque<std::size_t>& deck) {
    return array[deck.front()];
}

void updateResult(int* array, const std::deque<std::size_t>& deck, int& result) {
    result = std::min(result, maxInSubArray(array, deck));
}

int minOfMaxes(int* array, std::size_t len, std::size_t k) {
    std::deque<std::size_t> deck;
    for(std::size_t i = 0; i < k; i++) {
        add(array, i, deck);
    }
    int res = maxInSubArray(array, deck);
    for(std::size_t i = k; i < len; i++) {
        ensureSize(i, k, deck);
        add(array, i, deck);
        updateResult(array, deck, res);
    }
    return res;
}

int main() {
    int data[] = {10, 5, 2, 7, 8, 7};
    std::size_t len = sizeof(data) / sizeof(data[0]);
    std::cout << minOfMaxes(data, len, 3) << std::endl;
    return 0;
}