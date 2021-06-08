#include <vector>
#include <limits>

#include <iostream>

using Weight = int;

using Vertex = unsigned int;

using Edge = std::pair<Vertex, Weight>;

using Graph = std::vector<std::vector<Edge>>;

struct Result {
    bool is_valid;
    std::vector<Edge> min_edge;
    Weight total;
};

Result prim(const Graph& graph) {
    std::size_t n = graph.size();
    Result result{
        true,
        std::vector<Edge>(n, {n, std::numeric_limits<int>::max()}),
        0
    };
    std::vector<bool> selected(n, false);
    result.min_edge[0] = {0, 0};
    for(Vertex v = 0; v < n; v++) {
        Vertex current = n;
        for(Vertex u = 0; u < n; u++) {
            if(!selected[u] && (current == n || result.min_edge[u].second < result.min_edge[current].second)) {
                current = u;
            }
        } // Theta(n^2), Theta(n)
        if(current == n) {
            result.is_valid = false;
            return result;
        }
        selected[current] = true;
        result.total += result.min_edge[current].second;
        for(Edge edge: graph[current]) {
            Vertex neigh = edge.first;
            Weight weight = edge.second;
            if(!selected[neigh] && weight < result.min_edge[neigh].second) {
                result.min_edge[neigh] = {current, weight};
            } // Theta(1), Theta(1)
        } // Theta(m), Theta(1)
    }
    return result;
} // Theta(n^2), Theta(n)


//  0    
//  | \
//  10 \
//  |   3    
//  |     \ 
//  1 --10--2


int main() {
    Graph g = {
        {{1, 10}, {2, 3}},
        {{0, 10}, {2, 10}},
        {{1, 10}, {0, 3}}
    };
    Result res = prim(g);
    std::cout << res.is_valid << ":" << res.total << std::endl;
    return 0;
}