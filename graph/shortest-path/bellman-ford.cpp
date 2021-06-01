#include <vector>
#include <stack>
#include <limits>
#include <iostream>

using Vertex = unsigned int;

using Edge = std::pair<Vertex, int>;

using Graph = std::vector<std::vector<Edge>>;

struct VertexResult {
    Vertex parent;
    int    cost;
};

struct WeightedEdge {
    Vertex from;
    Vertex to;
    int weight;
};

class Result {
private:
    std::vector<VertexResult> vertexRes;
    Vertex start;
    bool negativeCycle;

    void buildPath(Vertex current, std::stack<Vertex>& p) const {
        p.push(current);
        if(start == current) {
            return;
        }
        buildPath(parent(current), p);
    }

public:
    Result(std::size_t n, Vertex s)
    : vertexRes(n), start(s), negativeCycle(false) {
        for(Vertex v = 0; v < n; v++) {
            vertexRes[v] = {v, std::numeric_limits<int>::max()};
        }
        vertexRes[s].cost = 0;
    }

    void relax(WeightedEdge edge) {
        if(canBeRelaxed(edge)) {
            vertexRes[edge.to] = {edge.from, cost(edge.from) + edge.weight};
        }
    }

    std::stack<Vertex> path(Vertex target) const {
        std::stack<Vertex> p;
        if(hasPath(target)) {
            buildPath(target, p);
        }
        return p;
    }

    int cost(Vertex v) const {
        return vertexRes[v].cost;
    }

    Vertex parent(Vertex v) const {
        return vertexRes[v].parent;
    }

    bool hasPath(Vertex target) const {
        return target == start || parent(target) != target;
    }

    // new

    bool hasNegativeCycle() const {
        return negativeCycle;
    }

    void foundNegativeCycle() {
        negativeCycle = true;
    }

    bool canBeRelaxed(WeightedEdge edge) {
        int current = cost(edge.to);
        int alternative = cost(edge.from) + edge.weight;
        return hasPath(edge.from) && alternative < current;
    }
};

Result singleSourceShortestPath(const Graph& graph, Vertex start) {
    std::size_t n = graph.size();
    Result result = Result(n, start);
    for(std::size_t i = 1; i < n; i++) {
        for(Vertex from = 0; from < n; from++) {
            for(Edge e: graph[from]) {
                Vertex to = e.first;
                int weight = e.second;
                result.relax({from, to, weight});
            }
        }
    }
    for(Vertex from = 0; from < n; from++) {
        for(Edge e: graph[from]) {
            Vertex to = e.first;
            int weight = e.second;
            result.relax({from, to, weight});
        }
    }
    return result;
}


int main() {
    Graph g = {
        {{1,1}},
        {{2, -1}, {3, 2}},
        {{4, 10}},
        {{4, 3}},
        {{5, 2}},
        {}
    };
    auto res = singleSourceShortestPath(g, 1);
    std::cout << res.cost(5) << std::endl;
    std::cout << res.cost(0) << std::endl;
    std::stack<Vertex> p = res.path(5);
    while(!p.empty()) {
        std::cout << p.top() << std::endl;
        p.pop();
    }
    return 0;
}