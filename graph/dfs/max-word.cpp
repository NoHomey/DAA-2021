#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using Index = std::size_t;

using Graph = std::vector<std::vector<Index>>;

using Swap = std::pair<Index, Index>;

Graph buildGraph(const std::vector<Swap>& swaps, Index max) {
    Graph graph = Graph(max);
    for(Swap swap: swaps) {
        graph[swap.first].push_back(swap.second);
        graph[swap.second].push_back(swap.first);
    }
    return graph;
}

void discoverComponent(const Graph& graph, Index current, std::vector<Index>& component, std::vector<bool>& visited) {
    component.push_back(current);
    visited[current] = true;
    for(Index neigh: graph[current]) {
        if(!visited[neigh]) {
            discoverComponent(graph, neigh, component, visited);
        }
    }
}

std::vector<std::vector<Index>> connectedComponents(const Graph& graph) {
    std::size_t n = graph.size();
    std::vector<std::vector<Index>> componets;
    std::vector<bool> visited = std::vector<bool>(n, false);
    for(Index i = 0; i < n; i++) {
        if(!visited[i]) {
            std::vector<Index> component;
            discoverComponent(graph, i, component, visited);
            component.shrink_to_fit();
            componets.push_back(std::move(component));
        }
    }
    return componets;
}

void sortComponets(std::vector<std::vector<Index>>& components) {
    for(std::vector<Index>& component: components) {
        std::make_heap(component.begin(), component.end());
        std::sort_heap(component.begin(), component.end());
    }
}

void updateWord(std::string& word, const std::vector<Index>& indexes) {
    std::size_t count[26] = {};
    for(Index i: indexes) {
        count[word[i] - 'a']++;
    }
    std::size_t i = 0;
    for(char sym = 'z'; sym >= 'a'; sym--) {
        for(std::size_t c = 0; c < count[sym - 'a']; c++) {
            word[indexes[i]] = sym;
            i++;
        }
    }
}

void maxWord(std::string& word, const std::vector<Swap>& swaps) {
    Graph graph = buildGraph(swaps, word.length());
    std::vector<std::vector<Index>> components = connectedComponents(graph);
    sortComponets(components);
    for(const std::vector<Index>& component: components) {
        updateWord(word, component);
    }
}

int main() {
    std::string word = "accddf";
    maxWord(word, {{0, 4}, {5, 4}, {0, 5}, {1, 3}});

    std::cout << word << std::endl;
    return 0;
}