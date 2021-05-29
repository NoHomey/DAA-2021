#include <vector>
#include <stack>
#include <limits>
#include <iostream>

using Vertex = unsigned int;

using Edge = std::pair<Vertex, int>;

using Graph = std::vector<std::vector<Edge>>;

struct Data {
    const Graph& graph  ;
    Vertex       current;

    Data derive(Vertex neigh) {
        return {graph, neigh};
    }
};

struct State {
    std::vector<bool>& visited;
    std::stack<Vertex>& order ;
};

void orderVertex(Data data, State state);

std::stack<Vertex> topoOrder(const Graph& graph) {
    std::stack<Vertex> order;
    std::size_t n = graph.size();
    std::vector<bool> visited = std::vector<bool>(n, false); // Theta(n), Theta(n)
    State state = {visited, order};
    for(Vertex v = 0; v < n; v++) {
        if(!visited[v]) {
            orderVertex({graph, v}, state);
        }
    }
    return order;
}

void orderVertex(Data data, State state) {
    state.visited[data.current] = true;
    for(Edge edge: data.graph[data.current]) {
        Vertex neigh = edge.first;
        if(!state.visited[neigh]) {
            orderVertex(data.derive(neigh), state);
        }
    }
    state.order.push(data.current);
}

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

    void buildPath(Vertex current, std::stack<Vertex>& p) {
        p.push(current);
        if(start == current) {
            return;
        }
        buildPath(parent(current), p);
    }

    bool hasPath(Vertex target) {
        return target == start || parent(target) != target;
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
        if(alternative < vertexRes[edge.to].cost) {
            vertexRes[edge.to] = {edge.from, alternative};
        }
    }

    std::stack<Vertex> path(Vertex target) {
        std::stack<Vertex> p;
        if(hasPath(target)) {
            buildPath(target, p);
        }
        return p;
    }

    int cost(Vertex v) {
        return vertexRes[v].cost;
    }

    Vertex parent(Vertex v) {
        return vertexRes[v].parent;
    }
};

Result singleSourceShortestPath(const Graph& graph, Vertex start) {
    std::stack<Vertex> order = topoOrder(graph); // Theta(n + m), Theta(n)
    std::size_t n = graph.size();
    Result result = Result(n, start);
    while(order.top() != start) {
        order.pop();
    }
    while(!order.empty()) {
        Vertex current = order.top();
        for(Edge edge: graph[current]) {
            result.relax({current, edge.first, edge.second});
        }
        order.pop();
    } // Theta(n + m), Theta(1)
    return result;
}

// T(n, m) = Theta(n + m)
// M(n, m) = Theta(n)


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