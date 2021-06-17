#include <vector>
#include <iostream>

using State = unsigned int;

using Symbol = char;

using Nat = std::size_t;

struct Transition {
    State state;
    Symbol symbol;
};

using FSM = std::vector<std::vector<Transition>>;

class Table {
private:
    std::vector<std::vector<Nat>> table;

public:
    Table(Nat n): table(n, std::vector<Nat>(n, 0)) { }

    void init() {
        Nat n = table.size();
        for(Nat i = 0; i < n; i++) {
            table[i][i] = 1;
        }
    }

    void reset() {
        Nat n = table.size();
        for(State i = 0; i < n; i++) {
            for(State j = 0; j < n; j++) {
                table[i][j] = 0;
            }
        }
    }

    void swap(Table& other) {
        table.swap(other.table);
    }

    Nat& operator()(Nat i, Nat j) {
        return table[i][j];
    }

    Nat operator()(Nat i, Nat j) const {
        return table[i][j];
    }
};

std::size_t words(Nat len, const FSM& fsm, const std::vector<State>& final) {
    Nat n = fsm.size();
    Nat k = fsm[0].size();
    // Theta(n^2), Theta(n^2)
    Table prev(n), curr(n);
    // Theta(n), Theta(1)
    prev.init();

    // Theta(len * n^2 * k), Theta(1)
    for(Nat l = 0; l < len; l++) {
        for(State i = 0; i < n; i++) {
            for(State u = 0; u < n; u++) {
                for(Transition trans: fsm[i]) {
                    curr(i, u) += prev(trans.state, u);
                }
            }
        }
        prev.swap(curr);
        curr.reset();
    }

    // O(n), Theta(1)
    Nat res = 0;
    for(State f: final) {
        res += prev(0, f);
    }
    return res;
}

// Theta(len * n^2 * k), Theta(n^2)

int main() {
    FSM fsm = {
        {{1, 'a'}, {2, 'b'}},
        {{1, 'a'}, {0, 'b'}},
        {{0, 'a'}, {2, 'b'}}
    };

    std::cout << words(3, fsm, {1}) << std::endl;

    return 0;
}