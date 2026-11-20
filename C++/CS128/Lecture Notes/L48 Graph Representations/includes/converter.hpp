#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "GraphAdjList.hpp"
#include "GraphAdjMatrix.hpp"

std::vector<std::tuple<std::string, std::string, int>>
    ToEdgeList(const GraphAdjList<std::string, int>& g);

GraphAdjMatrix<std::string, int>
    ListToMatrix(const GraphAdjList<std::string, int>& g);

GraphAdjList<std::string, int>
    MatrixToList(const GraphAdjMatrix<std::string, int>& g);

#endif
