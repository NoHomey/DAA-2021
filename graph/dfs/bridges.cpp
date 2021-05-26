#include <vector>
#include <algorithm>

using Vertex = unsigned int;

using Graph = std::vector<std::vector<Vertex>>;

struct State {
    bool visited;
    std::size_t level;
    std::size_t low;
};

std::size_t bridges(const Graph& graph) {
    std::size_t n = graph.size();
    std::vector<State> state = std::vector<State>(n, {false, 0, 0});
    std::size_t count = 0;
    for(Vertex vertex = 0; vertex < n; vertex++) {
        if(!state[vertex].visited) {
            count += findBridges({graph, vertex, vertex, 0}, state);
        }
    }
    return count;
}

struct Data {
    const Graph& graph;
    Vertex current;
    Vertex parent;
    std::size_t level;

    Data derive(Vertex neigh) {
        return {graph, neigh, current, level + 1};
    }
};

void traceLow(std::vector<State>& state, Vertex current, Vertex neigh) {
    state[current].low = std::min(state[current].low, state[neigh].low);
}

std::size_t findBridges(Data data, std::vector<State>& state) {
    std::size_t count = 0;
    state[data.current] = {true, data.level, data.level};
    for(Vertex neigh: data.graph[data.current]) {
        if(!state[neigh].visited) {
            count += findBridges(data.derive(neigh), state);
            traceLow(state, data.current, neigh);
            if(state[data.current].level < state[neigh].low) { // neigh is not in (simple)-cycle 
                count++; // <data.current, neigh> is bridge
            }
        } else if(neigh != data.parent) {
            traceLow(state, data.current, neigh);
        }
    }
    return count;
}

// T(n, m) = Theta(n + m)
// M(n, p) = Theta(n + p)