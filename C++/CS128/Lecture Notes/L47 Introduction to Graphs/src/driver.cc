#include <iostream>

#include "graph_builder.hpp"

int main() {
  GraphAdjList<std::string> g1 = BuildUndirected();
  std::cout << "=== Undirected ===" << std::endl;
  std::cout << g1 << std::endl;

  GraphAdjList<std::string> g2 = BuildDirected();
  std::cout << "=== Directed ===" << std::endl;
  std::cout << g2 << std::endl;

  GraphAdjList<std::string> g3 = BuildTwoComponents();
  std::cout << "=== Two Components ===" << std::endl;
  std::cout << g3 << std::endl;

  GraphAdjList<std::string> g4 = BuildWithCycle();
  std::cout << "=== With Cycle ===" << std::endl;
  std::cout << g4 << std::endl;

  GraphAdjList<std::string> g5 = BuildConnectedNoCycle();
  std::cout << "=== Connected No Cycle ===" << std::endl;
  std::cout << g5 << std::endl;

  return 0;
}
