#include "MatrixGraph.hpp"
#include <algorithm>
#include <stdexcept>

MatrixGraph::MatrixGraph(int _verticesCount) : matrixGraph(_verticesCount, std::vector<bool>(_verticesCount, false)), 
                                                verticesCount(_verticesCount) {}

MatrixGraph::MatrixGraph(const IGraph &graph) : matrixGraph(graph.VerticesCount(),
                                                std::vector<bool>(graph.VerticesCount(), false)), 
                                                verticesCount(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (const auto &vertex: nextVertices) {
            matrixGraph[i][vertex] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    if ((from >= 0) && (to >= 0) && (from < verticesCount) && (to < verticesCount)) {
        matrixGraph[from][to] = true;
    }    
}

int MatrixGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    if ((vertex >= 0) && (vertex < verticesCount)) {
        std::vector<int> nextVertices;
        for (int j = 0; j < matrixGraph.size(); ++j) {
            if (matrixGraph[vertex][j]) {
                nextVertices.push_back(j);
            }
        }
        return nextVertices;
    }
    else {
        std::vector<int> emptyVertices{};
        return emptyVertices;
    }
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    if ((vertex >= 0) && (vertex < verticesCount)) {
        std::vector<int> prevVertices;
        for (int parent = 0; parent < verticesCount; ++parent) {
            for (const auto &vert: matrixGraph[parent]) {
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

