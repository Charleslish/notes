#include "converter.hpp"

std::vector<std::tuple<std::string, std::string, int>>
ToEdgeList(const GraphAdjList<std::string, int>& g) {
  std::vector<std::tuple<std::string, std::string, int>> edges;
  for (const auto& from : g.GetVertices())
    for (const auto& to : g.GetNeighbors(from))
      edges.emplace_back(from, to, g.GetEdge(from, to));
  return edges;
}

GraphAdjMatrix<std::string, int>
ListToMatrix(const GraphAdjList<std::string, int>& g) {
  GraphAdjMatrix<std::string, int> matrix(g.IsDirected());
  const auto vertices = g.GetVertices();
  for (const auto& vertex : vertices)
    matrix.AddVertex(vertex);
  for (const auto& from : vertices)
    for (const auto& to : g.GetNeighbors(from))
      matrix.AddEdge(from, to, g.GetEdge(from, to));
  return matrix;
}

GraphAdjList<std::string, int>
MatrixToList(const GraphAdjMatrix<std::string, int>& g) {
  GraphAdjList<std::string, int> list(g.IsDirected());
  const auto vertices = g.GetVertices();
  for (const auto& vertex : vertices)
    list.AddVertex(vertex);
  for (const auto& from : vertices)
    for (const auto& to : g.GetNeighbors(from))
      list.AddEdge(from, to, g.GetEdge(from, to));
  return list;
}
