#ifndef GRAPHADJLIST_HPP
#define GRAPHADJLIST_HPP

#include <list>
#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename VertexType, typename EdgeType>
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
  void AddEdge(VertexType from, VertexType to, EdgeType label);

  bool VertexExists(VertexType label) const;
  bool EdgeExists(VertexType from, VertexType to) const;
  EdgeType GetEdge(VertexType from, VertexType to) const;

  void RemoveVertex(VertexType label);
  void RemoveEdge(VertexType from, VertexType to);

  std::vector<VertexType> GetNeighbors(VertexType label) const;
  std::vector<VertexType> GetVertices() const;
  bool IsDirected() const;

 private:
  std::map<VertexType, std::list<std::pair<VertexType, EdgeType>>> adj_;
  bool directed_ = false;
};

template <typename VertexType, typename EdgeType>
GraphAdjList<VertexType, EdgeType>::GraphAdjList(bool directed)
    : directed_(directed) {}

template <typename VertexType, typename EdgeType>
bool GraphAdjList<VertexType, EdgeType>::VertexExists(VertexType label) const {
  return adj_.contains(label);
}

template <typename VertexType, typename EdgeType>
bool GraphAdjList<VertexType, EdgeType>::EdgeExists(VertexType from,
                                                    VertexType to) const {
  if (!VertexExists(from) || !VertexExists(to)) {
    throw std::invalid_argument("One or both of the vertices do not exist.");
  }
  for (const auto& [adj_vertex, edge_label] : adj_.at(from)) {
    if (adj_vertex == to) {
      return true;
    }
  }
  return false;
}

template <typename VertexType, typename EdgeType>
EdgeType GraphAdjList<VertexType, EdgeType>::GetEdge(VertexType from,
                                                     VertexType to) const {
  if (!VertexExists(from) || !VertexExists(to)) {
    throw std::invalid_argument("One or both of the vertices do not exist.");
  }
  for (const auto& [adj_vertex, edge_label] : adj_.at(from)) {
    if (adj_vertex == to) {
      return edge_label;
    }
  }
  throw std::invalid_argument("Edge does not exist.");
}

template <typename VertexType, typename EdgeType>
void GraphAdjList<VertexType, EdgeType>::AddVertex(VertexType label) {
  if (VertexExists(label)) {
    throw std::invalid_argument("Vertex already exists.");
  }
  adj_[label] = {};
}

template <typename VertexType, typename EdgeType>
void GraphAdjList<VertexType, EdgeType>::RemoveVertex(VertexType label) {
  if (!VertexExists(label)) {
    throw std::invalid_argument("Vertex does not exist.");
  }
  for (auto& [vertex, adj_list] : adj_) {
    if (EdgeExists(vertex, label)) {
      RemoveEdge(vertex, label);
    }
  }
  adj_.erase(label);
}

template <typename VertexType, typename EdgeType>
void GraphAdjList<VertexType, EdgeType>::AddEdge(VertexType from,
                                                 VertexType to,
                                                 EdgeType label) {
  if (EdgeExists(from, to)) return;
  adj_[from].push_back(std::make_pair(to, label));
  if (!directed_) {
    adj_[to].push_back(std::make_pair(from, label));
  }
}

template <typename VertexType, typename EdgeType>
void GraphAdjList<VertexType, EdgeType>::RemoveEdge(VertexType from,
                                                    VertexType to) {
  if (!EdgeExists(from, to)) {
    throw std::invalid_argument("The edge does not exist.");
  }
  adj_[from].remove(std::make_pair(to, GetEdge(from, to)));
  if (!directed_) {
    adj_[to].remove(std::make_pair(from, GetEdge(to, from)));
  }
}

template <typename VertexType, typename EdgeType>
std::vector<VertexType> GraphAdjList<VertexType, EdgeType>::GetNeighbors(
    VertexType label) const {
  if (!VertexExists(label)) {
    throw std::invalid_argument("The vertex does not exist.");
  }
  std::vector<VertexType> neighbors;
  for (const auto& [adj_vertex, edge_label] : adj_.at(label)) {
    neighbors.push_back(adj_vertex);
  }
  return neighbors;
}

template <typename VertexType, typename EdgeType>
std::vector<VertexType> GraphAdjList<VertexType, EdgeType>::GetVertices() const {
  std::vector<VertexType> vertices;
  for (const auto& [label, adj_list] : adj_) {
    vertices.push_back(label);
  }
  return vertices;
}

template <typename VertexType, typename EdgeType>
bool GraphAdjList<VertexType, EdgeType>::IsDirected() const {
  return directed_;
}

#endif
