#include <vector>

using Vertex = unsigned int;

using Graph = std::vector<std::vector<Vertex>>;

bool isDigraphCyclic(const Graph& graph) {
    std::size_t n = graph.size();
    std::vector<bool> visited = std::vector<bool>(n, false);
    for(Vertex v = 0; v < n; v++) {
        if(!visited[v]) {
            if(dfsCheckCycleUtil(graph, visited, v, v)) {
                return true;
            }
        }
    }
    return false;
}

bool dfsCheckCycleUtil(const Graph& graph, std::vector<bool>& visited, Vertex parent, Vertex current) {
    visited[current] = true;
    for(Vertex neigh: graph[current]) {
        if(!visited[neigh] && dfsCheckCycleUtil(graph, visited, current, neigh)) {
            return true;
        }
        if(visited[neigh] && neigh != parent) {
            return true;
        }
    }
    return false;
}

// Time(N, M) = O(N + M)
// Mem(N, P) = O(N + P) where P is length of longest path.