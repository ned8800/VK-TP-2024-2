#include <iostream>

#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include "BFS_and_DFS.hpp"

int main() {
    ArcGraph arcGraph(7);
    arcGraph.AddEdge(0, 1);
    arcGraph.AddEdge(0, 2);
    arcGraph.AddEdge(1, 3);
    arcGraph.AddEdge(1, 4);
    arcGraph.AddEdge(2, 5);
    arcGraph.AddEdge(2, 6);

    std::cout << std::endl << " arcGraph " << std::endl <<
                 "Вершин: " << arcGraph.VerticesCount() << std::endl <<
                 "Обход в глубину: ";
    DFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << "|  Обход в ширину: ";
    BFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl;
    


    ListGraph listGraph(arcGraph);

    std::cout << std::endl << " listGraph " << std::endl <<
                 "Вершин: " << listGraph.VerticesCount() << std::endl <<
                 "Обход в глубину: ";
    DFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << "|  Обход в ширину: ";
    BFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl;




    MatrixGraph matrixGraph(listGraph);

    std::cout << std::endl << " matrixGraph " << std::endl <<
                 "Вершин: " << matrixGraph.VerticesCount() << std::endl <<
                 "Обход в глубину: ";
    DFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << "|  Обход в ширину: ";
    BFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl;




    SetGraph setGraph(matrixGraph);

    std::cout << std::endl << " setGraph " << std::endl <<
                 "Вершин: " << setGraph.VerticesCount() << std::endl <<
                 "Обход в глубину: ";
    DFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << "|  Обход в ширину: ";
    BFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl;

    SetGraph arcGraphAgain(setGraph);

    std::cout << std::endl << " Again ArcGraph " << std::endl <<
                 "Вершин: " << arcGraphAgain.VerticesCount() << std::endl <<
                 "Обход в глубину: ";
    DFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << "|  Обход в ширину: ";
    BFS(arcGraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl;
}

