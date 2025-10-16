#pragma once

#include <cstddef>
#include <cstdint>
#include <numeric>
#include <vector>

namespace shelpam {

// NOLINTBEGIN(readability-math-missing-parentheses)
class Segment_tree {
    // 不包含u节点，只代表u的儿子的懒标记
    struct Lazy_tag {
        auto operator+=(Lazy_tag const &rhs) -> Lazy_tag &
        {
            addition += rhs.addition;
            return *this;
        }

        std::int_fast64_t addition{};
    };

    struct Node {
        struct Info {
            std::int_fast64_t sum{};
            std::int_fast64_t max{
                std::numeric_limits<std::int_fast64_t>::min()};
            std::int_fast64_t min{
                std::numeric_limits<std::int_fast64_t>::max()};
        };

        Node &operator+=(Node const &rhs)
        {
            info.sum += rhs.info.sum;
            info.max = std::max(info.max, rhs.info.max);
            info.min = std::min(info.min, rhs.info.min);
            return *this;
        }

        Node &operator+=(Lazy_tag const &tag)
        {
            info.sum += tag.addition * (right - left + 1);
            info.max += tag.addition;
            info.min += tag.addition;
            return *this;
        }

        int left{-1};
        int right{-1};
        Info info;
    };

  public:
    explicit Segment_tree(int l, int r)
        : node_(4 * (r - l + 1) + 1), lazy_tags_(4 * (r - l + 1) + 1)
    {
        build_tree(l, r, 1);
    }

    void apply(int l, int r, Lazy_tag const &tag)
    {
        apply_impl(l, r, 1, tag);
    }

    Node query(int l, int r)
    {
        return query_impl(l, r, 1);
    }

  private:
    // Sets up segments that nodes manage.
    void build_tree(int l, int r, int u)
    {
        node_[u].left = l;
        node_[u].right = r;

        if (l != r) {
            auto const m = (l + r) / 2;
            build_tree(l, m, u * 2);
            build_tree(m + 1, r, (u * 2) + 1);
        }
    }

    void do_lazy_propagation(std::size_t u)
    {
        if (is_leaf(u)) {
            return;
        }

        lazy_tags_[u * 2] += lazy_tags_[u];
        lazy_tags_[u * 2 + 1] += lazy_tags_[u];
        node_[u * 2] += lazy_tags_[u];
        node_[u * 2 + 1] += lazy_tags_[u];
        lazy_tags_[u] = {};
    }

    void apply_impl(int l, int r, std::size_t u, Lazy_tag const &tag)
    {
        if (l <= node_[u].left && node_[u].right <= r) {
            node_[u] += tag;
            lazy_tags_[u] += tag;
            return;
        }

        do_lazy_propagation(u);
        if (node_[u * 2].right >= l) {
            apply_impl(l, r, u * 2, tag);
        }
        if (node_[u * 2 + 1].left <= r) {
            apply_impl(l, r, u * 2 + 1, tag);
        }
        node_[u].info = {};
        node_[u] += node_[u * 2];
        node_[u] += node_[u * 2 + 1];
    }

    // We assume that [l, r] contains [_nodes[u].left_end, _nodes[u].right_end].
    Node query_impl(int l, int r, std::size_t u)
    {
        // If [l, r] nests node u, the segment node doesn't have to be divided
        // anymore. So we direct return the info of this node.
        if (l <= node_[u].left && node_[u].right <= r) {
            return node_[u];
        }

        do_lazy_propagation(u);

        Node res;
        if (node_[u * 2].right >= l) {
            res += query_impl(l, r, u * 2);
        }
        if (node_[u * 2 + 1].left <= r) {
            res += query_impl(l, r, u * 2 + 1);
        }
        return res;
    }

    [[nodiscard]] auto is_leaf(std::size_t u) const -> bool
    {
        return node_[u].left == node_[u].right;
    }

    std::vector<Node> node_;
    std::vector<Lazy_tag> lazy_tags_;
};
// NOLINTEND(readability-math-missing-parentheses)

} // namespace shelpam
