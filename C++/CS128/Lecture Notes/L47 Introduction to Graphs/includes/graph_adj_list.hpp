#ifndef GRAPH_ADJ_LIST_HPP
#define GRAPH_ADJ_LIST_HPP

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

template <typename VertexType>
class GraphAdjList {
 public:
  GraphAdjList() = default;
  GraphAdjList(bool directed);
  GraphAdjList(const GraphAdjList& other) = delete;
  GraphAdjList& operator=(const GraphAdjList& other) = delete;
  GraphAdjList(GraphAdjList&& other) = default;
  GraphAdjList& operator=(GraphAdjList&& other) = default;
  ~GraphAdjList() = default;

  void AddVertex(VertexType label);
  void AddEdge(VertexType from, VertexType to);
  bool VertexExists(VertexType label) const;
  bool IsDirected() const;
  std::vector<VertexType> GetVertices() const;
  std::vector<VertexType> GetNeighbors(VertexType label) const;

  template <typename V>
  friend std::ostream& operator<<(std::ostream& os, const GraphAdjList<V>& g);

 private:
  std::map<VertexType, std::list<VertexType>> adj_;
  bool directed_ = false;
};

#include "graph_adj_list_impl.hpp"

#endif
