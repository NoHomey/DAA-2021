#include <vector>
#include <limits>

#include "indexed_queue.hpp"

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

using IPQ = IndexedPriorityQueue<Weight, Vertex>;

Result prim(const Graph& graph) {
    std::size_t n = graph.size();
    Result result{
        true,
        std::vector<Edge>(n, {n, std::numeric_limits<int>::max()}),
        0
    };
    std::vector<bool> selected(n, false);
    result.min_edge[0] = {0, 0};
    IPQ pq(n); // Theata(n), Theata(n)
    pq.push({0, 0, 0});
    for(Vertex v = 0; v < n; v++) {
        if(pq.is_empty()) {
            result.is_valid = false;
            return result;
        }
        Vertex current = pq.pop().element; // Theta(n * lg n), Theta(1)
        selected[current] = true;
        result.total += result.min_edge[current].second;
        for(Edge edge: graph[current]) {
            Vertex neigh = edge.first;
            Weight weight = edge.second;
            if(!selected[neigh] && weight < result.min_edge[neigh].second) {
                IPQ::Entry entry = {weight, neigh, neigh};
                if(result.min_edge[neigh].first == n) {
                    pq.push(entry);
                } else {
                    pq.update(entry);
                } // Theta(lg n), Theta(1)
                result.min_edge[neigh] = {current, weight};
            }
        } // Theta(m * lg n), Theta(n)
    }
    return result;
} // Theta(m * lg n), Theta(n)

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