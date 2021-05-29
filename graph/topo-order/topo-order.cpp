#include <vector>
#include <stack>

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
    for(Vertex neigh: data.graph[data.current]) {
        if(!state.visited[neigh]) {
            orderVertex(data.derive(neigh), state);
        }
    }
    state.order.push(data.current);
}

int main() {
    Graph g = {{1, 2}, {3}, {3}, {}};
    std::stack<Vertex> order = topoOrder(g);
    while(!order.empty()) {
        std::cout << order.top() << std::endl;
        order.pop();
    }
    return 0;
}