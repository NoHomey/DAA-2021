#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

using Nat = unsigned int;

using List = const std::vector<Nat>&;

struct Entry {
    Nat profit;
    std::size_t prev_color;
};

struct Result {
    Nat profit;
    std::stack<std::size_t> solution;
};

struct TraceData {
    const std::vector<std::vector<Entry>>& table;
    Nat count;
    std::size_t last_color;
    std::stack<std::size_t>& solution;

    TraceData derive() {
        return {
            table,
            count - 1,
            table[count][last_color].prev_color,
            solution
        };
    }
};

void trace_solution(TraceData data) {
    if(data.count == 0) {
        return;
    }
    data.solution.push(data.last_color);
    trace_solution(data.derive());
}

Result color(Nat n, List profit) {
    std::size_t m = profit.size();
    if(n > 1 && m == 1) {
        return {0, {}};
    }
    // Theta(n * m), Theta(n * m)
    auto table = std::vector<std::vector<Entry>>(n + 1, std::vector<Entry>(m, {0, m}));

    // Theta(n * m^2), Theta(1)
    for(std::size_t k = 0; k < n; k++) {
        for(std::size_t i = 0; i < m; i++) {
            for(std::size_t j = 0; j < m; j++) {
                if(j != i) {
                    if(table[k + 1][i].profit < table[k][j].profit) {
                        table[k + 1][i] = {table[k][j].profit, j};
                    }
                }
            }
            table[k + 1][i].profit += profit[i];
        }
    }

    // Theta(m), Theta(1)
    std::stack<std::size_t> color;
    Entry last = {0, m};
    for(std::size_t i = 0; i < m; i++) {
        if(last.profit < table[n][i].profit) {
            last = {table[n][i].profit, i};
        }
    }
    std::size_t last_color = last.prev_color;
    // Theta(n), Theta(n)
    trace_solution({table, n, last_color, color});
    return {last.profit, color};
}

// Theta(n * m^2), Theta(n * m)

int main() {
    Result res = color(4, {10, 20, 10});
    std::cout << res.profit << std::endl;
    std::cout << "solution:" << std::endl;
    while(!res.solution.empty()) {
        std::cout << res.solution.top() << std::endl;
        res.solution.pop();
    }
    return 0;
}