#pragma once

#ifndef __cpp_concepts
#error This lib requires at least cpp20 to work.
#endif

// Problem: 跑酷大湿
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/121107/J
// Start: Sat 08 Nov 2025 02:31:03 PM CST
// Author: ShelpAm

// #include <bits/stdc++.h>
#include <algorithm>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numbers>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
[[maybe_unused]] constexpr std::int_least64_t mod998244353{998'244'353LL};
[[maybe_unused]] constexpr std::int_least64_t mod1e9p7{1'000'000'007LL};
[[maybe_unused]] constexpr double eps{1e-10};
template <typename T> constexpr T inf{std::numeric_limits<T>::max() / 4};
template <typename T> constexpr T max{std::numeric_limits<T>::max()};

// Concepts.
namespace shelpam::concepts {
template <typename> struct is_pair_t : std::false_type {};
template <typename T, typename U>
struct is_pair_t<std::pair<T, U>> : std::true_type {};
template <typename T>
concept pair = is_pair_t<T>::value;
template <typename> struct is_tuple_t : std::false_type {};
template <typename... Ts>
struct is_tuple_t<std::tuple<Ts...>> : std::true_type {};
template <typename... Ts>
concept tuple = is_tuple_t<Ts...>::value;
template <typename T, typename U = std::remove_cvref_t<T>>
concept non_string_range =
    !std::same_as<U, std::string> && (std::ranges::range<U> || pair<U>);
} // namespace shelpam::concepts

std::istream &operator>>(std::istream &istream,
                         shelpam::concepts::non_string_range auto &&t)
{
    using T = std::remove_cvref_t<decltype(t)>;
    static_assert(!shelpam::concepts::tuple<T>,
                  "tuple: not implemented yet.\n");
    if constexpr (std::ranges::range<T>)
        for (auto &ele : t)
            istream >> ele;
    else if constexpr (shelpam::concepts::pair<T>)
        istream >> t.first >> t.second;
    else
        istream >> t;
    return istream;
}
#ifndef ONLINE_JUDGE
#include "/home/shelpam/Documents/projects/competitive-programming/libs/debug.h"
#else
#define debug(...)
#endif
void YesNo(bool yes)
{
    std::cout << (yes ? "Yes\n" : "No\n");
}
bool chmax(auto &value, auto const &other) noexcept
{
    if (value < other) {
        value = other;
        return true;
    }
    return false;
}
bool chmin(auto &value, auto const &other) noexcept
{
    if (value > other) {
        value = other;
        return true;
    }
    return false;
}
template <typename T> constexpr T pow(T base, auto exp, std::integral auto p)
{
    static_assert(sizeof(base) > sizeof(int), "Use of `int`s is bug-prone.");
    if (exp < 0) {
        base = pow(base, p - 2, p);
        exp = -exp;
    }
    decltype(base) res{1};
    while (exp != 0) {
        if ((exp & 1) == 1)
            res = res * base % p;
        base = base * base % p;
        exp >>= 1;
    }
    return res;
}
std::int_least64_t binary_search(std::invocable<std::int_least64_t> auto check,
                                 std::int_least64_t ok, std::int_least64_t ng,
                                 bool check_ok = true)
{
    if (check_ok && !check(ok))
        throw std::invalid_argument{"check isn't true on 'ok'."};
    while (std::abs(ok - ng) > 1) {
        auto const x = (ok + ng) / 2;
        (check(x) ? ok : ng) = x;
    }
    return ok;
}
template <std::unsigned_integral T> constexpr T lsb(T i) noexcept
{
    return i & -i;
}
// i mustn't be 0
constexpr int msb(std::unsigned_integral auto i)
{
    if (i == 0)
        throw std::invalid_argument{"i must be positive."};
    return (sizeof(i) * CHAR_BIT) - 1 - std::countl_zero(i);
}
// [[maybe_unused]] auto gen_rand() noexcept
// {
//     static std::mt19937_64 rng(
//         std::chrono::steady_clock::now().time_since_epoch().count());
//     return rng();
// }
} // namespace
void solve_case();
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    constexpr auto my_precision = 10;
    std::cout << std::fixed << std::setprecision(my_precision);
    int t{1};
    // std::cin >> t;
    for (int i{}; i != t; ++i) {
#ifndef ONLINE_JUDGE
        std::cerr << "Test case " << i << '\n';
#endif
        solve_case();
    }
    return 0;
}
namespace shelpam::graph {

using Node_type = int;

constexpr auto infinity{std::numeric_limits<std::int_fast64_t>::max() / 4};
class Graph {
  public:
    static auto read(int num_of_vertices, int num_of_edges, bool directed,
                     bool contains_w, bool read_from_1 = true) -> Graph
    {
        Graph g(num_of_vertices);
        for (int i = 0; i != num_of_edges; ++i) {
            int u;
            int v;
            std::int_fast64_t w;
            std::cin >> u >> v;
            if (contains_w) {
                std::cin >> w;
            }
            else {
                w = 1;
            }
            if (read_from_1) {
                --u, --v;
            }
            g.add_edge(u, v, w);
            if (!directed) {
                g.add_edge(v, u, w);
            }
        }
        return g;
    }

    explicit Graph(std::size_t max_num_of_vertices)
        : adjacent_(max_num_of_vertices)
    {
    }

    void add_edge(std::size_t u, std::size_t v, std::int_fast64_t w)
    {
        adjacent_[u].emplace_back(w, v);
    }

    [[nodiscard]] auto edges_of(std::size_t u) const
        -> std::vector<std::pair<std::int_fast64_t, int>> const &
    {
        return adjacent_[u];
    }

    [[nodiscard]] auto size() const -> std::size_t
    {
        return adjacent_.size();
    }

  private:
    std::vector<std::vector<std::pair<std::int_fast64_t, int>>> adjacent_;
};

auto to_edges(Graph const &g)
    -> std::vector<std::tuple<std::int_fast64_t, int, int>>
{
    std::vector<std::tuple<std::int_fast64_t, int, int>> edges;
    for (std::size_t u{}; u != g.size(); ++u) {
        for (auto const &[w, v] : g.edges_of(u)) {
            edges.emplace_back(w, u, v);
        }
    }
    return edges;
}
// Tested in https://www.luogu.com.cn/problem/P3366
/// @return:
///   -1 to denote that the graph is not connected.
///   weight of minimum spanning tree.
auto kruskal(Graph const &g) -> std::int_fast64_t
{
    class Disjoint_set_union {
      public:
        explicit Disjoint_set_union(int size) : _parent(size), _size(size, 1)
        {
            std::iota(_parent.begin(), _parent.end(), 0);
        }
        // with path compression
        auto find(int x) -> int
        {
            return _parent[x] == x ? x : _parent[x] = find(_parent[x]);
        }
        /// @return:
        /// false if there has been pair x,y in the set.
        /// true successfully united
        auto unite(int x, int y) -> bool
        {
            x = find(x), y = find(y);
            if (x == y) {
                return false;
            }
            if (_size[x] < _size[y]) {
                std::swap(x, y);
            }
            _parent[y] = x;
            _size[x] += _size[y];
            return true;
        }
        [[nodiscard]] auto united(int x, int y) -> bool
        {
            return find(x) == find(y);
        }
        [[nodiscard]] auto size(int x) -> std::size_t
        {
            return _size[find(x)];
        }

      private:
        std::vector<int> _parent;
        std::vector<std::size_t> _size;
    };
    auto edges{to_edges(g)};
    std::sort(edges.begin(), edges.end());
    Disjoint_set_union dsu(static_cast<int>(g.size()));
    std::int_fast64_t sum_weights{};
    for (auto const &[w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            sum_weights += w;
        }
    }
    if (dsu.size(0) != g.size()) {
        return -1;
    }
    return sum_weights;
}
// Tested in https://www.luogu.com.cn/problem/P3366
auto prim(Graph const &g) -> std::int_fast64_t
{
    // `distance[i]` means the distance from connected block to unconnected
    // block (aka i), not from source to i.
    std::vector<std::int_fast64_t> distance(g.size(), infinity);

    constexpr auto defined_source{0};
    distance[defined_source] = 0;

    // `visited[u]` is true means u had been a start point, and it shouldn't be
    // start point once more.
    std::deque<bool> visited(g.size());
    std::size_t num_visited{};

    std::priority_queue<std::pair<std::int_fast64_t, int>,
                        std::vector<std::pair<std::int_fast64_t, int>>,
                        std::greater<>>
        q;
    q.emplace(distance[defined_source], defined_source);

    std::int_fast64_t sum_weights{};
    while (!q.empty()) {
        auto const [w,
                    u]{q.top()}; // Extract unvisited closest vertex to sources.
        q.pop();

        // If some vertex was set visited, then it has had been start point to
        // its neighbours, hence there is no need to begin edges with that.
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        sum_weights += w;
        if (++num_visited == g.size()) {
            return sum_weights;
        }

        for (auto const &[w, v] : g.edges_of(u)) {
            if (chmin(distance[v], w)) {
                q.emplace(w, v);
            }
        }
    }

    // If all vertices were travelled through, the algorithm would have returned
    // in the loop above.
    return -1;
}
struct Bellman_ford_result {
    bool contains_negative_circle;
    // When `no_negative_circle` is true, this is invalid.
    std::vector<std::int_fast64_t> distance;
};
auto bellman_ford(Graph const &g, int source, std::deque<bool> &visited)
    -> Bellman_ford_result
{
    std::vector<std::int_fast64_t> dist(g.size(), infinity);
    std::vector<std::size_t> num_intermediates(g.size());
    // std::vector<int> vis(g.size());

    dist[source] = 0;
    visited[source] = true;
    // Only those in `q` could lead to relaxation.
    std::deque<int> q{source};
    auto swap_smaller_to_front{[&](std::deque<int> &q) {
        if (dist[q.back()] < dist[q.front()]) {
            std::swap(q.back(), q.front());
        }
    }};
    while (!q.empty()) {
        auto const u{q.front()};
        q.pop_front();
        swap_smaller_to_front(q);
        visited[u] = false;

        for (auto const [w, v] : g.edges_of(u)) {
            if (auto const alt{dist[u] + w}; chmin(dist[v], alt)) {
                num_intermediates[v] = num_intermediates[u] + 1;
                if (num_intermediates[v] >= g.size()) {
                    return {.contains_negative_circle = true, .distance = {}};
                }
                if (!visited[v]) {
                    visited[v] = true;
                    q.push_back(v);
                    swap_smaller_to_front(q);
                }
            }
        }
    }
    return {.contains_negative_circle = false, .distance = dist};
}

struct Dijkstra_result {
    std::vector<std::int_fast64_t> distance;
    std::vector<int> previous;
};
auto dijkstra(Graph const &g, std::vector<int> const &sources)
    -> Dijkstra_result
{
    std::vector<std::int_fast64_t> dist(g.size(), infinity);
    std::vector<int> prev(g.size(), -1);

    // Nodes not in q had got the shortest distance from source(s)
    auto by_dist{[&](int l, int r) {
        return std::tie(dist[l], l) < std::tie(dist[r], r);
    }};
    std::set<int, decltype(by_dist)> q{by_dist};
    for (auto const source : sources) {
        dist[source] = 0;
        q.insert(source);
    }

    while (!q.empty()) { // The main loop
        // Extract and remove the closest vertex from queue.
        auto const u{*q.begin()};
        q.erase(u);

        for (auto const &[w, v] : g.edges_of(u)) {
            if (auto const alt{dist[u] + w}; dist[v] > alt) {
                q.erase(v);
                dist[v] = alt;
                prev[v] = u;
                q.insert(v);
            }
        }
    }

    return {.distance{dist}, .previous{prev}};
}
auto dijkstra(Graph const &graph, int source) -> Dijkstra_result
{
    return dijkstra(graph, std::vector<int>{source});
}

using adjacent_matrix_t = std::vector<std::vector<std::int_fast64_t>>;
auto floyd(Graph const &g) -> adjacent_matrix_t
{
    auto const n = static_cast<int>(g.size());

    adjacent_matrix_t f(n, std::vector<std::int_fast64_t>(n, infinity));

    // Initializes data
    for (int u = 0; u != n; ++u) {
        f[u][u] = 0;
        for (auto const &[w, v] : g.edges_of(u)) {
            chmin(f[u][v],
                  w); // Do not directly use `f[u][v] = w;` to fight against
                      // multiple edges connecting the same vertices.
        }
    }

    for (int k = 0; k != n; ++k) {
        // In k-th round (At the end of the round), f[i][j] denotes the minimum
        // distance between i, j, concerning first k vertices.
        for (int i = 0; i != n; ++i) {
            for (int j = 0; j != n; ++j) {
                chmin(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }

    return f;
}
struct Toposort_result {
    bool acyclic;
    std::vector<int> order;
};
auto toposort(Graph const &g, bool directed) -> Toposort_result
{
    assert(directed && "haven't implement undirected");
    int const n{static_cast<int>(g.size())};
    std::vector<int> in(n);
    for (std::size_t u{}; u != g.size(); ++u) {
        for (auto const [_, v] : g.edges_of(u)) {
            ++in[v];
        }
    }
    std::vector<int> order;
    std::queue<int> q;
    for (int i{}; i != n; ++i) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    if (directed) {
        while (!q.empty()) {
            auto const u{q.front()};
            q.pop();
            order.push_back(u);
            for (auto const [_, v] : g.edges_of(u)) {
                if (--in[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
    if (order.size() != g.size()) {
        return {.acyclic = false, .order = {}};
    }
    return {.acyclic = true, .order = order};
};
// The graph should only contains left-to-right edges, and should not
// convert/transform the vertices' ID. For example, if you want to make a edge
// from left vertex x to right vertex y, you should use
// `g.add_edge(x, y, 1);` rather than `g.add_edge(x, y + n, 1);`.
auto maximum_matching(Graph const &g, int left_size, int right_size) -> int
{
    assert(left_size >= 0 && right_size >= 0);
    assert(g.size() == static_cast<std::size_t>(left_size));
    int num_of_matches{};

    int idx{}; // dfs order, identifying if a vertex was visited in current
               // round
    std::vector<int> dfn(left_size);

    // Matches from a and matches from b
    std::vector<int> pa(left_size, -1);
    std::vector<int> pb(right_size, -1);

    // All `u` will represent left side vertices.
    std::function<bool(int)> dfs{[&](int u) {
        dfn[u] = idx;
        // direct match
        for (auto const [_, v] : g.edges_of(u)) {
            if (pb[v] == -1) {
                // make a match: u - v
                pa[u] = v;
                pb[v] = u;
                return true;
            }
        }
        // augmenting path
        for (auto const [_, v] : g.edges_of(u)) {
            if (dfn[pb[v]] != idx && dfs(pb[v])) {
                pa[u] = v;
                pb[v] = u;
                return true;
            }
        }
        return false;
    }};

    while (true) {
        ++idx;
        int cnt{};
        for (int i{}; i != left_size; ++i) {
            if (pa[i] == -1 && dfs(i)) {
                ++cnt;
            }
        }
        if (cnt == 0) {
            break;
        }
        num_of_matches += cnt;
    }
    return num_of_matches;
}
struct Tarjan_cuts {
    Tarjan_cuts(Graph const &g) : g(g), n(g.size()), low(n), dfn(n) {}
    Graph g;
    std::size_t n;
    int idx{};
    // You can check dfn[i] to identify if vertex i has been visited.
    std::vector<int> low, dfn;
    std::vector<int> cuts;
    void run(int u, bool isroot = true)
    {
        low[u] = dfn[u] = ++idx;
        int cnt{};
        for (auto const [_, v] : g.edges_of(u)) {
            if (!dfn[v]) {
                run(v, false);
                chmin(low[u], low[v]);
                cnt += dfn[u] <= low[v];
            }
            else {
                chmin(low[u], dfn[v]);
            }
        }
        if (cnt > isroot) {
            cuts.push_back(u);
        }
    }
};
struct Tarjan_bridges {
    Tarjan_bridges(Graph g) : g(std::move(g)), n(g.size()), low(n), dfn(n) {}
    Graph g;
    std::size_t n;
    int idx{};
    std::vector<int> low, dfn;
    std::vector<std::pair<int, int>> bridges;
    void run(int u, int p)
    {
        low[u] = dfn[u] = ++idx;
        for (auto const [_, v] : g.edges_of(u)) {
            if (!dfn[v]) {
                run(v, u);
                chmin(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    bridges.emplace_back(u, v);
                }
            }
            else if (v != p) {
                chmin(low[u], dfn[v]);
            }
        }
    }
};

// Time complexity: linear, O(|g.E| + |g.V|)
struct Tarjan_scc {
  public:
    Tarjan_scc(Graph g)
        : _g{std::move(g)}, _n(static_cast<int>(_g.size())), _index(_n),
          _lowlink(_n), _on_stack(_n)
    {
        for (int i{}; i != _n; ++i) {
            if (!_index[i]) {
                strong_connect(i);
            }
        }
    }

    std::vector<std::vector<int>> scc;

  private:
    void strong_connect(int u)
    {
        _lowlink[u] = _index[u] = ++_idx;
        _stack.push(u);
        _on_stack[u] = 1;

        // Consider successors of u
        for (auto const &[_, v] : _g.edges_of(u)) {
            if (!_index[v]) {
                // Successor w has not yet been visited; recurse on it
                strong_connect(v);
                chmin(_lowlink[u], _lowlink[v]);
            }
            else if (_on_stack[v]) {
                chmin(_lowlink[u], _index[v]);
            }
        }

        // If v is a root node, pop the stack and generate an SCC
        if (_lowlink[u] == _index[u]) {
            scc.emplace_back();
            int v;
            do {
                _on_stack[v = _stack.top()] = 0;
                _stack.pop();
                scc.back().push_back(v);
            } while (v != u);
        }
    }

    Graph _g;
    int _n;
    int _idx{};
    std::stack<int> _stack;
    std::vector<int> _index; // DFS order of each vertex
    std::vector<int> _lowlink;
    std::vector<int> _on_stack;
};
struct Contract_edges_result {
    Graph h;
    std::vector<std::size_t> scc_id;
};
auto contract_edges(Graph const &g) -> Contract_edges_result
{
    auto const scc{std::move(Tarjan_scc(g).scc)};

    std::vector<std::size_t> scc_id(g.size());
    Graph h(scc.size());
    for (std::size_t i{}; i != scc.size(); ++i) {
        for (auto const u : scc[i]) {
            scc_id[u] = i;
        }
    }
    for (std::size_t i{}; i != scc.size(); ++i) {
        for (auto const u : scc[i]) {
            for (auto const &[w, v] : g.edges_of(u)) {
                if (i != scc_id[v]) {
                    h.add_edge(i, scc_id[v], w);
                }
            }
        }
    }
    return Contract_edges_result{.h = h, .scc_id = scc_id};
}

struct Get_centroids_result {
    std::vector<Node_type> centroids;
    std::vector<int> weight; // Maximum size of all subtrees
};

/// @return At most two, at least 1 centroid(s) of the given tree.
Get_centroids_result get_centroids(Graph const &g,
                                   std::vector<int> const &ok) noexcept
{
    int sz{};
    int root;
    for (int i{}; i != g.size(); ++i) {
        if (ok[i] == 1) {
            ++sz;
            root = i;
        }
    }

    std::vector<int> size(g.size());
    std::vector<int> weight(g.size()); // Maximum size of all subtrees
    std::vector<int> centroids;
    auto dfs = [&](auto dfs, int u, int p) -> void {
        size[u] = 1;
        weight[u] = 0;
        for (auto [w, v] : g.edges_of(u)) {
            if (v != p && ok[v]) {
                dfs(dfs, v, u);
                size[u] += size[v];
                chmax(weight[u], size[v]);
            }
        }
        chmax(weight[u], sz - size[u]);
        if (weight[u] <= sz / 2) {
            centroids.push_back(u);
        }
    };
    dfs(dfs, root, root);
    return Get_centroids_result{.centroids = centroids, .weight = weight};
}

} // namespace shelpam::graph
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
void solve_case()
{
    using namespace ::shelpam;
    int n, m, s;
    std::cin >> n >> m >> s;
    --s;
    std::vector<int> src(m);
    std::cin >> src;
    for (auto &e : src)
        --e;
    auto g = graph::Graph::read(n, n - 1, false, false);

    auto dist = graph::dijkstra(g, src).distance;

    std::queue<std::pair<int, int>> q;
    q.push({0, s});
    int ans{inf<int>};
    std::vector<int> vis(n);
    while (!q.empty()) {
        auto [t, u] = q.front();
        q.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        if (t >= dist[u]) {
            continue;
        }
        if (g.edges_of(u).size() == 1) {
            debug("leaf node", u);
            chmin(ans, t);
        }
        else {
            for (auto [_, v] : g.edges_of(u)) {
                q.push({t + 1, v});
            }
        }
    }
    std::cout << (ans == inf<int> ? -1 : ans) << '\n';
}
