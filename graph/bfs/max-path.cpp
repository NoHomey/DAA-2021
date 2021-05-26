 #include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
#include <iostream>

using Vertex = unsigned int;

using Weigth = int;

using Edge = std::pair<Vertex, Weigth>; 

using Graph = std::vector<std::vector<Edge>>;

using VertexSet = std::set<Vertex>;

struct State {
    Vertex vertex;
    int cost;
    VertexSet visited;
};

float maxPath(Graph& graph, Vertex start, Vertex end, int minCost) {
    int cost = std::numeric_limits<int>::min();
    std::queue<State> q;
    q.push({start, 0, {start}});
    while(!q.empty()) {
        State current = q.front();
        q.pop();
        if(current.vertex == end && current.cost >= minCost) {
            cost = std::max(cost, current.cost);
        }
        // Theta(1)
        VertexSet::iterator invalid = current.visited.end();
        for(Edge edge: graph[current.vertex]) {
            if(current.visited.find(edge.first) == invalid) { // O(lg N)
                VertexSet path = current.visited; // O(N)
                path.insert(edge.first); // O(lg N)
                q.push({edge.first, current.cost + edge.second, path});
            }
        }
    }
    return cost;
}

// P is the simple paths count.
// T(N, P) = O(P * N^2 * lg N + P * N^2) = O(P * N^2 * lg N)
// M(N, P) = O(P * N + P) = O(P * N)

int main() {
    Graph g = {
        {{1, 1}, {3, 2}}, //0
        {{4, 6}, {2, 5}}, //1
        {{4, 7}},         //2
        {{4, 1}},         //3
        {{5, 2}, {6, -9}},//4
        {{6, 1}},         //5
        {}                //6
    };

    int cost = maxPath(g, 0, 6, 4);

    std::cout << cost << std::endl;

    return 0;
}