#include <vector>

using Vertex = unsigned int;

using Graph = std::vector<std::vector<Vertex>>;

struct Result {
    Vertex parent;

    std::size_t discoveryTime;

    std::size_t finishTime;
};

enum class VertexStatus {NotVisited, Discovered, Finished};

std::vector<Result> dfs(const Graph& graph) {
    std::size_t n = graph.size();
    std::vector<Result> result = std::vector<Result>(n);
    std::vector<VertexStatus> status = std::vector<VertexStatus>(n, VertexStatus::NotVisited);
    std::size_t time = 0;
    for(Vertex vertex = 0; vertex < n; vertex++) {
        if(status[vertex] != VertexStatus::NotVisited) {
            result[vertex].parent = vertex;
            dfsVisit({graph, vertex}, {result, status, time});
        }
    }
    return result;
}

struct State {
    std::vector<Result>& result;
    std::vector<VertexStatus>& status;
    std::size_t& time;
};

struct Data {
    const Graph& graph;
    Vertex current;
};

void dfsVisit(Data data, State state) {
    state.status[data.current] = VertexStatus::Discovered;
    state.result[data.current].discoveryTime = state.time;
    state.time++;
    for(Vertex neigh: data.graph[data.current]) {
        if(state.status[neigh] == VertexStatus::NotVisited) {
            state.result[neigh].parent = data.current;
            dfsVisit({data.graph, neigh}, state);
        }
    }
    state.status[data.current] = VertexStatus::Finished;
    state.result[data.current].finishTime = state.time;
    state.time++;
}