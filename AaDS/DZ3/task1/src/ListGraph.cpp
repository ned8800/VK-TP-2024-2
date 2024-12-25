#include "ListGraph.hpp"


ListGraph::ListGraph(int _verticesCount) : listGraph(_verticesCount), verticesCount(_verticesCount) {}


ListGraph::ListGraph(const IGraph &graph) : listGraph(graph.VerticesCount()), verticesCount(graph.VerticesCount()) {
    for (int i = 0; i < verticesCount; ++i) {
        listGraph[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    if ((from >= 0) && (to >= 0) && (from < verticesCount) && (to < verticesCount)) {
        listGraph[from].push_back(to);
    }    
}

int ListGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    if ((vertex >= 0) && (vertex < verticesCount)) {
        return listGraph[vertex];
    }
    else {
        std::vector<int> emptyVertices{};
        return emptyVertices;
    }
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    if ((vertex >= 0) && (vertex < verticesCount)) {
        std::vector<int> prevVertices;
        for (int parent = 0; parent < verticesCount; ++parent) {
            for (const auto &vert: listGraph[parent]) {
                if (vert == vertex) {
                    prevVertices.push_back(parent);
                    break;
                }
            }
        }
        return prevVertices;
    }
    else {
        std::vector<int> emptyVertices{};
        return emptyVertices;
    }
}

