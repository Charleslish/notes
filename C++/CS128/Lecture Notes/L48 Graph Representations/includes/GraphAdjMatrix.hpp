#ifndef GRAPHADJMATRIX_HPP
#define GRAPHADJMATRIX_HPP

#include <map>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename VertexType, typename EdgeType>
class GraphAdjMatrix {
 public:
  GraphAdjMatrix() = default;
  GraphAdjMatrix(bool directed);
  GraphAdjMatrix(const GraphAdjMatrix& other) = delete;
  GraphAdjMatrix& operator=(const GraphAdjMatrix& other) = delete;
  GraphAdjMatrix(GraphAdjMatrix&& other) = default;
  GraphAdjMatrix& operator=(GraphAdjMatrix&& other) = default;
  ~GraphAdjMatrix() = default;

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
  std::vector<std::vector<std::optional<EdgeType>>> adj_;
  std::map<VertexType, unsigned int> vertex_mapping_;
  std::vector<VertexType> index_to_vertex_;
  std::vector<bool> active_;
  bool directed_ = false;
};

template <typename VertexType, typename EdgeType>
GraphAdjMatrix<VertexType, EdgeType>::GraphAdjMatrix(bool directed)
    : directed_(directed) {}

template <typename VertexType, typename EdgeType>
bool GraphAdjMatrix<VertexType, EdgeType>::VertexExists(VertexType label) const {
  return vertex_mapping_.contains(label);
}

template <typename VertexType, typename EdgeType>
bool GraphAdjMatrix<VertexType, EdgeType>::EdgeExists(VertexType from,
                                                      VertexType to) const {
  if (!VertexExists(from) || !VertexExists(to)) {
    throw std::invalid_argument("One or both of the vertices do not exist.");
  }
  unsigned int from_ind = vertex_mapping_.at(from);
  unsigned int to_ind = vertex_mapping_.at(to);
  return adj_[from_ind][to_ind] != std::nullopt;
}

template <typename VertexType, typename EdgeType>
EdgeType GraphAdjMatrix<VertexType, EdgeType>::GetEdge(VertexType from,
                                                       VertexType to) const {
  if (!EdgeExists(from, to)) {
    throw std::invalid_argument("Edge does not exist.");
  }
  unsigned int from_ind = vertex_mapping_.at(from);
  unsigned int to_ind = vertex_mapping_.at(to);
  return adj_[from_ind][to_ind].value();
}

template <typename VertexType, typename EdgeType>
void GraphAdjMatrix<VertexType, EdgeType>::AddVertex(VertexType label) {
  if (VertexExists(label)) {
    throw std::invalid_argument("Vertex already exists.");
  }
  for (auto& row : adj_) {
    row.push_back(std::nullopt);
  }
  adj_.push_back(
      std::vector<std::optional<EdgeType>>(adj_.size() + 1, std::nullopt));
  index_to_vertex_.push_back(label);
  active_.push_back(true);
  vertex_mapping_[label] = index_to_vertex_.size() - 1;
}

template <typename VertexType, typename EdgeType>
void GraphAdjMatrix<VertexType, EdgeType>::RemoveVertex(VertexType label) {
  if (!VertexExists(label)) {
    throw std::invalid_argument("Vertex does not exist.");
  }
  active_[vertex_mapping_[label]] = false;
  vertex_mapping_.erase(label);
}

template <typename VertexType, typename EdgeType>
void GraphAdjMatrix<VertexType, EdgeType>::AddEdge(VertexType from,
                                                   VertexType to,
                                                   EdgeType label) {
  if (EdgeExists(from, to)) return;
  unsigned int from_ind = vertex_mapping_[from];
  unsigned int to_ind = vertex_mapping_[to];
  adj_[from_ind][to_ind] = label;
  if (!directed_) {
    adj_[to_ind][from_ind] = label;
  }
}

template <typename VertexType, typename EdgeType>
void GraphAdjMatrix<VertexType, EdgeType>::RemoveEdge(VertexType from,
                                                      VertexType to) {
  if (!EdgeExists(from, to)) {
    throw std::invalid_argument("The edge does not exist.");
  }
  unsigned int from_ind = vertex_mapping_[from];
  unsigned int to_ind = vertex_mapping_[to];
  adj_[from_ind][to_ind] = std::nullopt;
  if (!directed_) {
    adj_[to_ind][from_ind] = std::nullopt;
  }
}

template <typename VertexType, typename EdgeType>
std::vector<VertexType> GraphAdjMatrix<VertexType, EdgeType>::GetNeighbors(
    VertexType label) const {
  if (!VertexExists(label)) {
    throw std::invalid_argument("The vertex does not exist.");
  }
  std::vector<VertexType> neighbors;
  for (const auto& [vertex, ind] : vertex_mapping_) {
    if (EdgeExists(label, vertex)) {
      neighbors.push_back(vertex);
    }
  }
  return neighbors;
}

template <typename VertexType, typename EdgeType>
std::vector<VertexType> GraphAdjMatrix<VertexType, EdgeType>::GetVertices() const {
  std::vector<VertexType> vertices;
  for (const auto& [label, ind] : vertex_mapping_) {
    vertices.push_back(label);
  }
  return vertices;
}

template <typename VertexType, typename EdgeType>
bool GraphAdjMatrix<VertexType, EdgeType>::IsDirected() const {
  return directed_;
}

#endif
