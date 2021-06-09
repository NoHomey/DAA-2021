#include <vector>
#include <algorithm>
#include "./union-find/union-find.h"

#include <iostream>

using Weight = int;

using Vertex = unsigned int;

struct Edge {
    Vertex from;
    Vertex to;
    Weight weight;
};

struct Graph {
    std::vector<Edge> edges;
    std::size_t       vertecies;
};

struct Result {
    bool valid;
    Graph tree;
    Weight total;
};

bool lessWeight(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

void sortEdgesByWeight(Graph& graph) {
    // If needed we use Heap Sort !!!
    std::sort(graph.edges.begin(), graph.edges.end(), lessWeight); // Theta(n * lg n), Theta(1)
}

Result kruskal(Graph& graph) {
    std::size_t n = graph.vertecies;
    Graph tree = {{}, n};
    tree.edges.reserve(n - 1);
    Result res = {true, std::move(tree), 0};
    std::size_t limit = 1;
    UnionFind forest(n); // Theta(n), Theta(n)

    sortEdgesByWeight(graph); // Theta(m * lg m), Theta(1)
    for(const Edge& e: graph.edges) { // Theta(m), Theta(1)
        if(limit == n) {
            break;
        }
        if(forest.Find(e.from) != forest.Find(e.to)) {
            forest.Union(e.from, e.to);
            res.tree.edges.push_back(e);
            res.total += e.weight;
            limit++;
        }
    }

    if(res.tree.edges.size() != n - 1) {
        res.valid = false;
    }
    return res;
} // Theta(m * lg m), Theta(n)

//  0    
//  | \
//  10 \
//  |   3    
//  |     \ 
//  1 --10--2

int main() {
    Graph g = {{{0, 1, 10}, {0, 2, 3}, {1, 2, 10}}, 3};
    Result res = kruskal(g);
    std::cout << res.valid << ":" << res.total << std::endl;
    return 0;
}