#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "GraphAdjList.hpp"
#include "GraphAdjMatrix.hpp"
#include "converter.hpp"

int main() {
  GraphAdjList<std::string, int> g(true);
  g.AddVertex("A");
  g.AddVertex("B");
  g.AddVertex("C");
  g.AddEdge("A", "B", 10);
  g.AddEdge("B", "C", 20);
  g.AddEdge("A", "C", 30);

  std::cout << "=== ToEdgeList ===" << std::endl;
  std::vector<std::tuple<std::string, std::string, int>> edges = ToEdgeList(g);
  std::cout << "Edge count: " << edges.size() << std::endl;
  for (const std::tuple<std::string, std::string, int>& e : edges) {
    std::cout << "  " << std::get<0>(e) << " -> " << std::get<1>(e)
              << " : " << std::get<2>(e) << std::endl;
  }

  std::cout << std::endl << "=== ListToMatrix ===" << std::endl;
  GraphAdjMatrix<std::string, int> m = ListToMatrix(g);
  std::vector<std::string> mv = m.GetVertices();
  std::cout << "Vertex count: " << mv.size() << std::endl;

  std::cout << std::endl << "=== MatrixToList ===" << std::endl;
  GraphAdjList<std::string, int> l = MatrixToList(m);
  std::vector<std::string> lv = l.GetVertices();
  std::cout << "Vertex count: " << lv.size() << std::endl;

  return 0;
}
