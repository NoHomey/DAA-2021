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

    void buildPath(Vertex current, std::stack<Vertex>& p) const {
        p.push(current);
        if(start == current) {
            return;
        }
        buildPath(parent(current), p);
    }

public:
    Result(std::size_t n, Vertex s)
    : vertexRes(n), start(s) {
        for(Vertex v = 0; v < n; v++) {
            vertexRes[v] = {v, std::numeric_limits<int>::max()};
        }
        vertexRes[s].cost = 0;
    }

    void relax(WeightedEdge edge) {
        int alternative = vertexRes[edge.from].cost + edge.weight;
        int current = vertexRes[edge.to].cost;
        if(alternative < current) {
            vertexRes[edge.to] = {edge.from, alternative};
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
};

Result dijkstra(const Graph& graph, Vertex start) {
    std::size_t n = graph.size();
    Result result = Result(n, start);
    std::vector<bool> visited = std::vector<bool>(n, false);
    for(std::size_t i = 0; i < n; i++) {
        Vertex current = n;
        for(Vertex v = 0; v < n; v++) {
            if(!visited[v] && (current == n || result.cost(v) < result.cost(current))) {
                current = v;
            }
        } // Theta(n), Theta(1) => Theta(n^2), Theta(n)
        if(current == n) {
             break;
        }
        visited[current] = true;
        for(Edge edge: graph[current]) {
            Vertex neigh = edge.first;
            int weight = edge.second;
            result.relax({current, neigh, weight});
        } // Theta(m), Theta(1)
    }
    return result;
} // Theta(n^2 + m), Theta(n)

int main() {
    Graph g = {
        {{1,1}},
        {{2, -1}, {3, 2}},
        {{4, 10}},
        {{4, 3}},
        {{5, 2}},
        {}
    };
    auto res = dijkstra(g, 1);
    std::cout << res.cost(5) << std::endl;
    std::cout << res.hasPath(0) << ":" << res.cost(0) << std::endl;
    std::stack<Vertex> p = res.path(5);
    while(!p.empty()) {
        std::cout << p.top() << std::endl;
        p.pop();
    }
    return 0;
}