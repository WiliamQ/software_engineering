#include "graph/graph.h"
#include "util/param_mgr.h"

namespace fzur {

extern ParamMgr g_param_mgr;  // global varaible

void Graph::Init(size_t num_nodes, size_t num_edges, size_t num_nets,
                 size_t num_net_groups) {
  num_nodes_ = num_nodes;
  num_edges_ = num_edges;
  num_nets_ = num_nets;
  num_groups_ = num_net_groups;

  for (id_t i = 0; i < num_nets; ++i) {
    nets_.push_back(Net());
    nets_[i].SetId(i);
  }

  netgroups_.resize(num_net_groups);
  edge_nets_.resize(num_edges);

  routing_count_.assign(num_edges, 0);  // initialized to 0

  node_nets.resize(num_nodes);
}

void Graph::ShowRoutingFrequencyOfAllEdges() const {
  std::cout << "Routing frequency of all edges:\n";
  std::cout << "edge id| #nets| net ids\n";
  for (size_t i = 0; i < NumEdges(); ++i) {
    std::cout << " " << i << "\t" << routing_count_[i] << '\t';
    for (auto& net_id : edge_nets_[i]) {
      std::cout << net_id << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "\n";
}

void Graph::OutputResult(std::ostream& out) const {
  for (const auto& net : nets_) {
    net.ShowEdgeRatios(out);
  }
}

}  // namespace fzur
