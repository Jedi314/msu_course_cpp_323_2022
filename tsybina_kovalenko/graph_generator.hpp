#pragma once

#include <queue>
#include <random>

#include "graph.hpp"

namespace uni_course_cpp {

class GraphGenerator {
 public:
  struct Params {
   public:
    Params(Graph::Depth depth, int new_vertices_count)
        : depth_(depth), new_vertices_count_(new_vertices_count) {}

    Graph::Depth depth() const { return depth_; }
    int new_vertices_count() const { return new_vertices_count_; }

   private:
    Graph::Depth depth_ = 0;
    int new_vertices_count_ = 0;
  };

  explicit GraphGenerator(Params&& params) : params_(std::move(params)) {}

  Graph generate() const;

 private:
  Params params_ = Params(0, 0);

  mutable std::mt19937 generator_{std::random_device()()};

  bool check_probability(float chance) const {
    std::bernoulli_distribution distribution(chance);
    return distribution(generator_);
  }

  void generate_grey_edges(Graph& graph) const;

  void generate_green_edges(Graph& graph) const;

  Graph::VertexId select_random_vertex(
      const std::vector<Graph::VertexId>& probable_vertices) const;

  std::vector<Graph::VertexId> get_unconnected_vertex_ids(
      const Graph& graph,
      Graph::Depth depth,
      Graph::VertexId from_vertex_id) const;

  void generate_yellow_edges(Graph& graph) const;

  void generate_red_edges(Graph& graph) const;
};
}  // namespace uni_course_cpp
