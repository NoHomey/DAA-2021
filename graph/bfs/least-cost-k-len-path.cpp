#include <queue>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

using Vertex = unsigned int;

using Weigth = float;

using Edge = std::pair<Vertex, Weigth>; 

using Graph = std::vector<std::vector<Edge>>;

struct State {
    Vertex vertex;
    float cost;
    unsigned int level;
};

// Input: Weigthed Digraph <graph> with positive edge weigths,
//        two vertecies <start> and <finish> and a natural number <k>.
// Output: Min Cost of path from <start> to <finish> with exactly <k> edges.

float leastCostKEdgePath(Graph& graph, Vertex start, Vertex finish, unsigned int k) {
    float cost = std::numeric_limits<float>::max(); // infinity
    std::queue<State> q;
    q.push({start, 0.0, 0});
    while(!q.empty()) {
        State current = q.front();
        q.pop();
        if(current.level > k) {
            break;
        }
        if(current.level == k && current.vertex == finish) {
            cost = std::min(cost, current.cost);
        }
        for(Edge e: graph[current.vertex]) {
            q.push({e.first, current.cost + e.second, current.level + 1});
        }
    }
    return cost;
}

// D is max deg- of a vertex.
// T(D, K) = O(D^K)
// M(D, K) = O(D^K) ( O(n) )

int main() {
    Graph g = {
        {{1, 0.1}, {3, 0.2}}, //0
        {{4, 0.6}, {2, 0.5}}, //1
        {{4, 0.7}},           //2
        {{4, 0.1}},           //3
        {{5, 0.2}, {6, 0.9}}, //4
        {{6, 0.1}},           //5
        {}                    //6
    };

    float cost = leastCostKEdgePath(g, 0, 6, 4);

    std::cout << cost << std::endl;

    return 0;
}