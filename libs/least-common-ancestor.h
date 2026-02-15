#pragma once

#include "../templates/main.cpp"
#include "graph.h"

namespace shelpam::graph {

class Least_common_ancestor {
  public:
    Least_common_ancestor(Graph const &g, int root)
        : dfn_(g.size()),
          depth_(g.size(),
                 -1) // -1 to make `depth[parent-of-root] + 1` equal to 0.
    {
        std::function<void(int u, int p)> dfs{[this, &g, &dfs](int u, int p) {
            depth_[u] = depth_[p] + 1;
            dfn_[u] = seq_.size();
            seq_.push_back(u);
            for (auto const &[_, v] : g.edges_of(u)) {
                if (v != p) {
                    dfs(v, u);
                    seq_.push_back(u);
                }
            }
        }};

        dfs(root, root);

        f_.assign(1 + msb(seq_.size()),
                  std::vector<int>(seq_.size(), inf<int>));
        for (std::size_t i{}; i != seq_.size(); ++i) {
            f_[0][i] = depth_[seq_[i]];
        }
        h_.assign(1 + msb(seq_.size()), std::vector<int>(seq_.size()));
        h_[0] = seq_;

        for (std::size_t i{1}; i != f_.size(); ++i) {
            for (std::size_t j{}; j + (1 << i) - 1 != f_[i].size(); ++j) {
                if (chmin(f_[i][j], f_[i - 1][j])) {
                    h_[i][j] = h_[i - 1][j];
                }
                if (chmin(f_[i][j], f_[i - 1][j + (1 << (i - 1))])) {
                    h_[i][j] = h_[i - 1][j + (1 << (i - 1))];
                }
            }
        }
    }

    [[nodiscard]] auto query(Node_type u, Node_type v) const -> Node_type
    {
        auto const [l, r]{std::minmax(dfn_[u], dfn_[v])};
        auto const k{msb(r - l + 1)};
        Node_type result;
        int depth{inf<int>};
        if (chmin(depth, f_[k][l])) {
            result = h_[k][l];
        }
        if (chmin(depth, f_[k][r - (1 << k) + 1])) {
            result = h_[k][r - (1 << k) + 1];
        }
        return result;
    }

  private:
    // Of node
    std::vector<std::size_t> dfn_; // first time to be visited
    std::vector<Node_type> seq_;
    std::vector<int> depth_;

    std::vector<std::vector<int>> f_;       // Min sparse table for depth
    std::vector<std::vector<Node_type>> h_; // Sparse table for min depth node
};

using LCA = Least_common_ancestor;

/// @brief LogN version of LCA algorithm.
class LeastCommonAncestor {
  public:
    LeastCommonAncestor(Graph const &tree, Node_type root)
        : k_{std::__lg(tree.size())}, d_(tree.size()),
          f_(k_ + 1, std::vector<Node_type>(tree.size()))
    {
        assert(tree.size() != 0);
        auto init = [&](auto self, Node_type u, Node_type p) -> void {
            d_[u] = d_[p] + 1;
            f_[0][u] = p;
            for (auto i = 1; i != f_.size(); ++i) {
                f_[i][u] = f_[i - 1][f_[i - 1][u]];
            }
            for (auto [_, v] : tree.edges_of(u))
                if (v != p)
                    self(self, v, u);
        };
        init(init, root, root);
    }

    Node_type lca(Node_type u, Node_type v)
    {
        if (d_[u] < d_[v]) // Ensures d[u] >= d[v]
            std::swap(u, v);

        for (auto i = k_; i != -1; --i) // u goes up until d[u] == d[v].
            if (d_[f_[i][u]] >= d_[v])
                u = f_[i][u];

        if (u == v) // u is son of v, lca == u && lca == v
            return u;

        for (auto i = k_; i != -1; --i) {
            if (f_[i][u] != f_[i][v]) {
                u = f_[i][u];
                v = f_[i][v];
            }
        }

        return f_[0][v];
    }

  private:
    unsigned long k_;
    std::vector<int> d_; // d[i]: depth of node i. (root's depth starts from 1)
    // f[i][j] stands for the node which j go up for 2^i
    std::vector<std::vector<Node_type>> f_;
};

} // namespace shelpam::graph
