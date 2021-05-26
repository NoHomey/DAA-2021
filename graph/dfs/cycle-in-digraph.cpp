#include <vector>

using Vertex = unsigned int;

using Graph = std::vector<std::vector<Vertex>>;

bool isDigraphCyclic(const Graph& graph) {
    std::size_t n = graph.size();
    std::vector<bool> visited = std::vector<bool>(n, false);
    for(Vertex v = 0; v < n; v++) {
        if(!visited[v]) {
            if(dfsCheckCycleUtil(graph, v, visited)) {
                return true;
            }
        }
    }
    return false;
}

bool dfsCheckCycleUtil(const Graph& graph, Vertex vertex, std::vector<bool>& visited) {
    visited[vertex] = true;
    for(Vertex neigh: graph[vertex]) {
        if(visited[neigh]) {
            return true;
        }
        if(dfsCheckCycleUtil(graph, neigh, visited)) {
            return true;
        }
    }
    return false;
}

// Time(N, M) = O(N + M)
// Mem(N, P) = O(N + P) where P is length of longest path.