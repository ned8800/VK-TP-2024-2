#ifndef GRAPH_INCLUDE_GRAPHFUNCTIONS_H_
#define GRAPH_INCLUDE_GRAPHFUNCTIONS_H_

#include <iostream>
#include <queue>

#include "IGraph.hpp"


void BFS(const IGraph& graph, void (*callback)(int v));

void DFS(const IGraph& graph, void (*callback)(int v));

#endif  // GRAPH_INCLUDE_GRAPHFUNCTIONS_H_

