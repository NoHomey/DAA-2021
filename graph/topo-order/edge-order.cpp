#include <vector>

#include <iostream>

using Vertex = std::size_t;

using Graph = std::vector<std::vector<bool>>;

struct Data {
    const Graph& graph  ;
    Vertex       current;

    Data derive(Vertex neigh) {
        return {graph, neigh};
    }
};

struct State {
    std::vector<bool>& visited;
    std::vector<Vertex>& order;
    std::size_t&         position;
};

void orderVertexOriented(Data data, State state);

std::vector<Vertex> topoOrientedOrder(const Graph& graph) {
    std::size_t n = graph.size();
    std::vector<Vertex> order = std::vector<Vertex>(n, n);
    std::vector<bool> visited = std::vector<bool>(n, false); // Theta(n), Theta(n)
    std::size_t position = n;
    State state = {visited, order, position};
    for(Vertex v = 0; v < n; v++) {
        if(!visited[v]) {
            orderVertexOriented({graph, v}, state);
        }
    }
    return order;
}

bool hasEdge(const Graph& g, Vertex u, Vertex v) {
    return g[u][v];
}

bool hasOrientedEdge(const Graph& g, Vertex u, Vertex v) {
    return hasEdge(g, u, v) && !hasEdge(g, v, u);
}

void orderVertexOriented(Data data, State state) {
    std::size_t n = data.graph.size();
    state.visited[data.current] = true;
    for(Vertex vertex = 0; vertex < n; vertex++) {
        if(!state.visited[vertex] && hasOrientedEdge(data.graph, data.current, vertex)) {
            orderVertexOriented(data.derive(vertex), state);
        }
    }
    state.order[state.position - 1] = data.current;
    state.position--;
}

bool hasUndirectedEdge(const Graph& g, Vertex u, Vertex v) {
    return hasEdge(g, u, v) && hasEdge(g, v, u);
}

void setOrientation(Graph& graph) {
    std::vector<Vertex> order = topoOrientedOrder(graph); // Theta(n + m), Theta(n)
    std::size_t n = graph.size();
    std::vector<Vertex> index = std::vector<Vertex>(n); // Theta(n), Theta(n)
    for(std::size_t i = 0; i < n; i++) {
        Vertex v = order[i];
        index[v] = i;
    } // Theta(n), Theta(1)
    for(Vertex v = 0; v < n; v++) {
        for(Vertex u = v + 1; u < n; u++) {
            if(hasUndirectedEdge(graph, u, v)) {
                if(index[u] < index[v]) {
                    graph[v][u] = false;
                } else {
                    graph[u][v] = false;
                }
            }
        }
    } // Theta(n^2), Theta(1)
}

// T(n, m) = Theta(n^2 + m) = Theta(n^2)
// M(n, m) = Theta(n)

int main() {
    Graph g = {
        {false, true, true, false},
        {false, false, false, true},
        {true, false, false, true},
        {false, true, false, false},
    };
    setOrientation(g);
    std::size_t n = g.size();
    for(Vertex v = 0; v < n; v++) {
        for(Vertex u = v + 1; u < n; u++) {
            if(hasUndirectedEdge(g, u, v)) {
                std::cout << '{' << u << ',' << v << '}' << std::endl;
            }
        }
    }
    return 0;
}