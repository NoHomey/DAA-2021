#include <queue>
#include <vector>
#include <set>
#include <iostream>

using Vertex = unsigned int;

using Graph = std::vector<std::vector<Vertex>>;

using VertexSet = std::set<Vertex>;

struct State {
    Vertex vertex;
    VertexSet onPath;
};

// Input: Digraph <graph>, vertex <start> and a positive natural number <k>.
// Output: Total count of simple paths with <k> vertecies starting from <start>.

std::size_t totalPaths(Graph& graph, Vertex start, unsigned int k) {
    std::size_t count = 0;
    std::queue<State> q;
    q.push({start, {start}});
    while(!q.empty()) {
        State current = q.front(); // Theta(1)
        q.pop();
        std::size_t s = current.onPath.size(); // Theta(1)
        if(s > k) {
            break;
        }
        if(s == k) {
            count++;
        }
        auto invalid = current.onPath.end();
        for(Vertex v: graph[current.vertex]) {
            if(current.onPath.find(v) == invalid) { // O(lg K)
                VertexSet extended = current.onPath; // O(K), Total Theta(K^2)
                extended.insert(v); // O(lg K)
                q.push({v, extended}); // Amort. Theta(1)
            }
        }
    }
    return count;
}

// Let P be the total count of simple paths with K vertecies.
// T(N, P, K) = Theta(P * (K - 1) * N * lg K + P * K^2) = Theta(P * N * (K - 1) * lg K)
// M(N, P, K) = Theta(P * K + P) = Theta(P * K)

int main() {
    Graph g = {
        {1, 3}, //0
        {2, 4}, //1
        {4},    //2
        {4},    //3
        {5, 6}, //4
        {6},    //5
        {}      //6
    };

    std::size_t count = totalPaths(g, 0, 4);

    std::cout << count << std::endl;

    return 0;
}