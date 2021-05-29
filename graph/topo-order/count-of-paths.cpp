#include <vector>
#include <deque>

#include <iostream>

using Vertex = unsigned int;

using Graph = std::vector<std::vector<Vertex>>;

struct Data {
    const Graph& graph  ;
    Vertex       current;

    Data derive(Vertex neigh) {
        return {graph, neigh};
    }
};

struct State {
    std::vector<bool>& visited;
    std::deque<Vertex>& order ;
};

void orderVertex(Data data, State state);

std::deque<Vertex> topoOrder(const Graph& graph) {
    std::deque<Vertex> order;
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
    for(Vertex neigh: data.graph[data.current]) {
        if(!state.visited[neigh]) {
            orderVertex(data.derive(neigh), state);
        }
    }
    state.order.push_back(data.current);
}

std::vector<std::size_t> countOfPaths(const Graph& graph, Vertex target) {
    std::size_t n = graph.size();
    std::vector<std::size_t> paths = std::vector<std::size_t>(n, 0); // Theta(n), Theta(1)
    std::deque<Vertex> order = topoOrder(graph); // Theta(n + m), Theta(n)
    while(order.front() != target) { // Theta(n), Theta(1)
        order.pop_front();
    }
    paths[target] = 1;
    order.pop_front();
    while(!order.empty()) {
        Vertex current = order.front();
        for(Vertex neigh: graph[current]) {
            paths[current] += paths[neigh];
        } // Theta(m), Theta(1)
        order.pop_front();
    }
    return paths;
}

// T(n, m) = Theta(n + m)
// M(n, m) = Theta(n)

int main() {
    Graph g = {{1, 2}, {3}, {3}, {}};
    std::vector<std::size_t> paths = countOfPaths(g, 2);
    std::size_t vertex = 0;
    for(std::size_t count: paths) {
        std::cout << vertex << ": " << count << std::endl;
        vertex++;
    }
    return 0;
}