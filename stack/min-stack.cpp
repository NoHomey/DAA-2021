#include <stack>
#include <iostream>

class MinStack {
private:
    std::stack<int> dataStack;
    std::stack<int> minStack;

public:
    MinStack() = default;
    ~MinStack() = default;

    bool isEmpty() const {
        return dataStack.empty();
    }

    std::size_t size() const {
        return dataStack.size();
    }

    int top() const {
        return dataStack.top();
    }

    int min() const {
        return minStack.top();
    }

    void push(int val) {
        if(isEmpty() || (!isEmpty() && val <= min())) {
            minStack.push(val);
        }
        dataStack.push(val);
    }

    void pop() {
        if(top() == min()) {
            minStack.pop();
        }
        dataStack.pop();
    }
};

int main() {
    MinStack s;

    s.push(10);
    std::cout << s.min() << std::endl;

    s.push(-1);
    std::cout << s.min() << std::endl;

    s.push(-1);
    std::cout << s.min() << std::endl;

    s.push(2);
    std::cout << s.min() << std::endl;

    while(!s.isEmpty()) {
        std::cout << s.min() << std::endl;
        s.pop();
    }

    return 0;
}