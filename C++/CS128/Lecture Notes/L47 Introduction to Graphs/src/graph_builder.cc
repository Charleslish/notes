#include "graph_builder.hpp"
GraphAdjList<std::string> BuildUndirected() {
  GraphAdjList<std::string> graph(false);
  graph.AddVertex("A");
  graph.AddVertex("B");
  graph.AddVertex("C");
  graph.AddVertex("D");
  graph.AddVertex("E");
  graph.AddEdge("A", "B");
  graph.AddEdge("B", "C");
  graph.AddEdge("C", "D");
  graph.AddEdge("D", "E");
  graph.AddEdge("E", "A");
  graph.AddEdge("A", "C");
  return graph;
}

GraphAdjList<std::string> BuildDirected() {
  GraphAdjList<std::string> graph(true);
  graph.AddVertex("A");
  graph.AddVertex("B");
  graph.AddVertex("C");
  graph.AddVertex("D");
  graph.AddEdge("A", "B");
  graph.AddEdge("B", "C");
  graph.AddEdge("C", "D");
  graph.AddEdge("D", "A");
  graph.AddEdge("A", "C");
  return graph;
}

GraphAdjList<std::string> BuildTwoComponents() {
  GraphAdjList<std::string> graph(false);
  graph.AddVertex("A");
  graph.AddVertex("B");
  graph.AddVertex("C");
  graph.AddVertex("D");
  graph.AddEdge("A", "B");
  graph.AddEdge("C", "D");
  return graph;
}

GraphAdjList<std::string> BuildWithCycle() {
  GraphAdjList<std::string> graph(false);
  graph.AddVertex("A");
  graph.AddVertex("B");
  graph.AddVertex("C");
  graph.AddVertex("D");
  graph.AddEdge("A", "B");
  graph.AddEdge("B", "C");
  graph.AddEdge("C", "D");
  graph.AddEdge("D", "A");
  return graph;
}

GraphAdjList<std::string> BuildConnectedNoCycle() {
  GraphAdjList<std::string> graph(false);
  graph.AddVertex("A");
  graph.AddVertex("B");
  graph.AddVertex("C");
  graph.AddVertex("D");
  graph.AddEdge("A", "B");
  graph.AddEdge("B", "C");
  graph.AddEdge("C", "D");
  return graph;
}
