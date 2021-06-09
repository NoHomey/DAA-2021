#include <vector>
#include <algorithm>
#include <list>
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

bool lessWeight(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

void sortEdgesByWeight(Graph& graph) {
    // If needed we use Heap Sort !!!
    std::sort(graph.edges.begin(), graph.edges.end(), lessWeight); // Theta(n * lg n), Theta(1)
}

struct MST {
    Graph tree;
    Weight total;
};

struct State {
    std::size_t limit;
    UnionFind   forest;
    MST         mst;
};

std::vector<MST> networks(Graph& graph) {
    std::size_t n = graph.vertecies;
    std::vector<MST> res;
    std::list<State> state;

    sortEdgesByWeight(graph); // Theta(m * lg m), Theta(1)
    for(const Edge& e: graph.edges) {
        auto stateEnd = state.end();
        auto stateIter = stateEnd;
        for(auto iter = state.begin(); iter != stateEnd; ++iter) {
            UnionFind& forest = iter->forest;
            if(forest.Find(e.from) != forest.Find(e.to)) {
                stateIter = iter;
                break;
            }
        }
        if(stateIter == stateEnd) {
            state.push_back({1, UnionFind(n), {{{}, n}, 0}});
            stateIter = stateEnd;
            --stateIter;
        }
        State& current = *stateIter;
        current.forest.Union(e.from, e.to);
        current.mst.tree.edges.push_back(e);
        current.mst.total += e.weight;
        current.limit++;
        if(current.limit == n) {
            res.push_back(current.mst);
            state.erase(stateIter);
        }
    }
    return res;
} // Theta(m * lg m + m^2 / (n - 1)), Theta(n * m / (n - 1))

//  0 --2---3
//  | \   / |
//  10 \ /  5
//  |   3   |  
//  | /   \ |
//  1 --10--2

int main() {
    Graph g = {{{0, 1, 10}, {0, 2, 3}, {1, 2, 10}, {0, 3, 2}, {3, 2, 5}, {1, 3, 3}}, 4};
    std::vector<MST> res = networks(g);
    std::cout << res.size() << std::endl;
    std::cout << res[0].total << std::endl;
    std::cout << res[1].total << std::endl;
    return 0;
}