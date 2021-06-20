#include <queue>
#include <vector>
#include <stack>
#include <limits>
#include <iostream>

using SubSet = uint64_t;

using Element = uint8_t;

const SubSet EMPTY_SET = 0;

SubSet set_singleton(Element x) {
    return 1 << x;
}

SubSet set_union(SubSet a, SubSet b) {
    return a | b;
}

SubSet set_intersect(SubSet a, SubSet b) {
    return a & b;
}

SubSet set_complement(SubSet s) {
    return ~s;
}

SubSet set_diff(SubSet a, SubSet b) {
    return set_intersect(a, set_complement(b));
}

SubSet set_add(SubSet set, Element x) {
    return set_union(set, set_singleton(x));
}

SubSet set_remove(SubSet set, Element x) {
    return set_diff(set, set_singleton(x));
}

bool is_in_set(Element x, SubSet set) {
    return set_intersect(set_singleton(x), set) != EMPTY_SET;
}

uint64_t powerset_size(uint8_t n) {
    return 1 << n; // 2^n
}

SubSet set_all(uint8_t n) {
    return powerset_size(n) - 1;
}

struct State {
    SubSet set;
    Element next;
};

class Weight {
private:
    uint64_t weight;
    bool is_inft;

private:
    Weight()
    : weight(std::numeric_limits<uint64_t>::max()), is_inft(true) { }

public:
    static Weight infinity() {
        return {};
    }

public:
    Weight(uint64_t w)
    : weight(w), is_inft(false) {}

    Weight(const Weight&) = default;

    Weight& operator=(const Weight&) = default;

    bool operator==(const Weight other) const {
        return is_inft == other.is_inft && weight == other.weight;
    }

    bool is_inifinity() const {
        return is_inft;
    }

    Weight operator+(const Weight other) const {
        if(is_inifinity()) {
            return *this;
        }
        if(other.is_inifinity()) {
            return other;
        }
        return Weight(weight + other.weight);
    }

    bool operator<(const Weight other) const {
        if(is_inifinity()) {
            return false;
        }
        if(other.is_inifinity()) {
            true;
        }
        return weight < other.weight;
    }

    uint64_t getWeight() const {
        return weight;
    }
};

using Vertex = Element;

using Graph = std::vector<std::vector<Weight>>;

struct Entry {
    Weight cost;
    Vertex parent;
};

using Path = std::stack<Vertex>;

class PathBuilder {
private:
    const std::vector<std::vector<Entry>>& table;
    Path& path;

public:
    PathBuilder(const std::vector<std::vector<Entry>>& t, Path& p)
    : table(t), path(p) { }

    void build(SubSet s, Vertex v) {
        path.push(v);
        Vertex parent = table[v][s].parent;
        if(parent == v) {
            return;
        }
        build(set_remove(s, v), parent);
    }
};

std::pair<Weight, Path> tsp(const Graph& g) {
    Vertex n = g.size();
    const Weight infinity = Weight::infinity();
    // Theta(n * 2^n), Theta(n * 2^n)
    auto t = std::vector<std::vector<Entry>>(n, std::vector<Entry>(powerset_size(n), {infinity, n}));
    std::queue<State> q;

    t[0][set_singleton(0)] = {0, 0};

    q.push({set_singleton(0), 1});
    while(!q.empty()) {
        State current = q.front();
        q.pop();

        for(Element x = current.next; x < n; x++) {
            if(is_in_set(x, current.set)) {
                continue;
            }
            Entry best = {infinity, n};
            for(Element y = 0; y < x; y++) {
                Entry prev = t[y][current.set];
                if(!is_in_set(y, current.set) || prev.cost.is_inifinity()) {
                    continue;
                }
                Weight target = prev.cost + g[y][x];
                if(target < best.cost) {
                    best = {target, y};
                }
            }
            t[x][set_add(current.set, x)] = best;

            q.push({set_add(current.set, x), static_cast<Element>(x + 1)});
        }
    } // Theta(n^2 * 2^n), O(2^n)

    Vertex last = n;
    Weight best = infinity;
    SubSet full = set_all(n);
    for(Vertex x = 1; x < n; x++) {
        Weight check = t[x][full].cost + g[x][0];
        if(check < best) {
            best = check;
            last = x;
        }
    } // Theta(n), Theta(1)

    Path p;    
    if(!best.is_inifinity()) {
        p.push(0);
        PathBuilder builder(t, p);
        builder.build(full, last);
        // Theta(n), Theta(n)
    }
    return std::make_pair(best, p);
} // Theta(n^2 * 2^n), Theta(n * 2^n)

int main() {
    Graph g = {
        {0, 10, 15, 20},
        {10, 0, 25, 25},
        {15, 25, 0, 30},
        {20, 25, 30, 0}
    };

    auto best = tsp(g);

    if(!best.first.is_inifinity()) {
        std::cout << best.first.getWeight() << std::endl;
        std::cout << "cycle" << std::endl;
        while(!best.second.empty()) {
            std::cout << static_cast<unsigned int>(best.second.top()) << std::endl;
            best.second.pop();
        }
    }

    return 0;
}