#ifndef GRAPH_BUILDER_HPP
#define GRAPH_BUILDER_HPP

#include "graph_adj_list.hpp"

GraphAdjList<std::string> BuildUndirected();
GraphAdjList<std::string> BuildDirected();
GraphAdjList<std::string> BuildTwoComponents();
GraphAdjList<std::string> BuildWithCycle();
GraphAdjList<std::string> BuildConnectedNoCycle();

#endif
