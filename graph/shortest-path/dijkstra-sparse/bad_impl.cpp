#include <vector>
#include <stack>
#include <limits>

#include "priority_queue.hpp"

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
        if(canBeRelaxed(edge)) {
            int alternative = vertexRes[edge.from].cost + edge.weight;
            vertexRes[edge.to] = {edge.from, alternative};
        }
    }

    bool canBeRelaxed(WeightedEdge edge) const {
        int alternative = vertexRes[edge.from].cost + edge.weight;
        int current = vertexRes[edge.to].cost;
        return alternative < current;
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

using PQ = PriorityQueue<int, Vertex>;

Result dijkstra(const Graph& graph, Vertex start) {
    std::size_t n = graph.size();
    Result result = Result(n, start);
    PQ pq(16);
    pq.push({0, start}); // Theta(1)
    while(!pq.is_empty()) {
        PQ::Entry entry = pq.pop(); // Theta(lg m), Theta(1)
        // Theta((n + m) * lg m), Theta(1)
        Vertex current = entry.element;
        if(result.cost(current) != entry.priority) {
            continue;
        }
        for(Edge edge: graph[current]) {
            Vertex neigh = edge.first;
            int edgeWeight = edge.second;
            WeightedEdge weighted = {current, neigh, edgeWeight};
            if(result.canBeRelaxed(weighted)) {
                result.relax(weighted);
                pq.push({result.cost(neigh), neigh}); // Theta(lg m)
            }
        } // Theta((n + m) * lg m), Theta(m)
    }
    return result;
} // Theta((n + m) * lg m), Theta(n + m)

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
    std::stack<Vertex> p = res.path(5);
    std::cout << "path:" << std::endl;
    while(!p.empty()) {
        std::cout << p.top() << std::endl;
        p.pop();
    }
    return 0;
}