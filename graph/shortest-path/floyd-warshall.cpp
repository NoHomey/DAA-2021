#include <stack>
#include <vector>
#include <iostream>

using Vertex = unsigned int;

using Edge = std::pair<Vertex, int>;

using Graph = std::vector<std::vector<Edge>>;

class Cost {
private:
    int cost;
    bool inf;

public:
    Cost(): cost(0), inf(true) {  }

    Cost(int c): cost(c), inf(false) { }

    bool isInf() const {
        return inf;
    }

    bool isFin() const {
        return !isInf();
    }

    int getCost() const {
        return cost;
    }

    void setCost(int c) {
        cost = c;
        inf = false;
    }

    bool isLess(Cost c) {
        return isFin() && (c.isInf() || cost < c.cost);
    }
};

Cost sum(Cost left, Cost right) {
    if(left.isInf() || right.isInf()) {
        return Cost{};
    }
    return Cost{left.getCost() + right.getCost()};
}

struct VertexResult {
    Cost cost;
    Vertex parent;
};

class Result {
private:
    std::vector<std::vector<VertexResult>> res;
    Vertex invalid;
    bool negativeCycle;

    void buildPath(Vertex i, Vertex j, std::stack<Vertex>& p) {
        Vertex parent = res[i][j].parent;
        if(parent == invalid && i != j) {
            p = {};
            return;
        }
        p.push(j);
        if(i == j) {
            return;
        }
        buildPath(i, parent, p);
    } 

public:
    Result(const Graph& graph) {
        negativeCycle = false;
        std::size_t n = graph.size();
        invalid = n;
        res = std::vector<std::vector<VertexResult>>(n);
        for(std::size_t row = 0; row < n; row++) {
            res[row] = std::vector<VertexResult>(n, VertexResult{Cost{}, static_cast<Vertex>(n)});
        } // Theta(n), Theta(n^2)
        for(Vertex v = 0; v < n; v++) {
            res[v][v].cost.setCost(0);
        } // Theta(n), Theta(1)
        for(Vertex i = 0; i < n; i++) {
            for(Edge edge: graph[i]) {
                Vertex j = edge.first;
                int weight = edge.second;
                if(i != j) {
                    res[i][j].cost.setCost(weight);
                    res[i][j].parent = i;
                }
            }
        } // Theta(m), Theta(1)
    } // Theta(n + m), Theta(n^2)

    Cost cost(Vertex i, Vertex j) const {
        return res[i][j].cost;
    }

    bool canBeRelaxed(Vertex i, Vertex j, Vertex k) {
        Cost alternative = sum(cost(i, k), cost(k, j));
        Cost current = cost(i, j);
        return alternative.isLess(current);
    }

    void relax(Vertex i, Vertex j, Vertex k) {
        res[i][j].cost = sum(cost(i, k), cost(k, j));
        res[i][j].parent = res[k][j].parent;
    }

    bool hasNegativeCycle() const {
        return negativeCycle;
    }

    void foundNegativeCycle() {
        negativeCycle = true;
    }

    std::stack<Vertex> path(Vertex i, Vertex j) {
        std::stack<Vertex> p;
        buildPath(i, j, p);
        return p;
    } // Theta(n), Theta(n)
};

Result shortestPath(const Graph& graph) {
    Result res = Result(graph); // Theta(n + m), Theta(n^2)
    std::size_t n = graph.size();
    for(std::size_t k = 0; k < n; k++) {
        for(Vertex i = 0; i < n; i++) {
            for(Vertex j = 0; j < n; j++) {
                if(res.canBeRelaxed(i, j, k)) {
                    res.relax(i, j, k);
                }
            }
        }
    } // Theta(n^3), Theta(1)
    for(Vertex i = 0; i < n; i++) {
        Cost cost = res.cost(i, i);
        if(cost.isFin() && cost.getCost() < 0) {
            res.foundNegativeCycle();
            break;
        }
    } // Theta(n), Theta(1)
    return res;
} // Theta(n^3), Theta(n^2)

int main() {
    Graph g = {
        {{1,1}, {2, -3}},
        {{3, -3}},
        {{3, 10}},
        {}
    };

    Result res = shortestPath(g);

    if(res.hasNegativeCycle()) {
        std::cout << "found negative cycle" << std::endl;
        return 0;
    }

    std::cout << res.cost(0, 3).getCost() << std::endl;

    std::cout << "path from 0 to 3" << std::endl;

    auto p = res.path(0, 3);

    while(!p.empty()) {
        std::cout << p.top() << std::endl;
        p.pop();
    }

    return 0;
} 