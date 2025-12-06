#pragma once

#ifndef __cpp_concepts
#error This lib requires at least cpp20 to work.
#endif

// Problem: E. I Just Want... One More...
// Contest: The 2023 ICPC Asia Jinan Regional Contest (The 2nd Universal Cup.
// Stage 17: Jinan) Judge: Codeforces URL:
// https://codeforces.com/gym/104901/problem/E Start: Tue 14 Oct 2025 03:20:34
// PM CST Author: ShelpAm

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
[[maybe_unused]] constexpr std::uint_least64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_least64_t mod1e9p7{1'000'000'007ULL};
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
    if constexpr (std::ranges::range<T>) {
        for (auto &ele : t) {
            istream >> ele;
        }
    }
    else if constexpr (shelpam::concepts::pair<T>) {
        istream >> t.first >> t.second;
    }
    else {
        istream >> t;
    }
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
constexpr auto sum_of(std::ranges::range auto const &coll) noexcept
{
    return std::accumulate(
        coll.begin(), coll.end(),
        typename std::remove_cvref_t<decltype(coll)>::value_type{});
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
        if ((exp & 1) == 1) {
            res = res * base % p;
        }
        base = base * base % p;
        exp >>= 1;
    }
    return res;
}
std::int_least64_t binary_search(std::invocable<std::int_least64_t> auto check,
                                 std::int_least64_t ok, std::int_least64_t ng,
                                 bool check_ok = true)
{
    if (check_ok && !check(ok)) {
        throw std::invalid_argument{"check isn't true on 'ok'."};
    }
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
    if (i == 0) {
        throw std::invalid_argument{"i must be positive."};
    }
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
    constexpr auto my_precision{10};
    std::cout << std::fixed << std::setprecision(my_precision);
    int t{1};
    std::cin >> t;
    for (int i{}; i != t; ++i) {
#ifndef ONLINE_JUDGE
        std::cerr << "Test case " << i << '\n';
#endif
        solve_case();
    }
    return 0;
}
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
using namespace std;
using ll = i64;
#define int ll
struct MaxFlow {
    struct Edge {
        int v;    // 目标顶点
        int cap;  // 容量
        int flow; // 当前流量 ----> 可以知道每条边流经的流量
        int rev;  // 反向边在邻接表中的索引
    };

    int n;                      // 顶点总数
    int S, T;                   // 源点和汇点
    int maxflow;                // 最大流结果
    vector<vector<Edge>> graph; // 图的邻接表
    vector<int> dep;            // 深度数组（BFS分层）
    vector<int> cur;            // 当前弧优化数组

    // 构造函数：初始化最大流算法
    MaxFlow(int num_nodes, int source, int sink)
        : n(num_nodes), S(source), T(sink), maxflow(0)
    {
        graph.resize(n + 1);
        dep.resize(n + 1);
        cur.resize(n + 1);
    }

    void addedge(int u, int v, ll w)
    {
        // 添加正向边：u->v，容量w
        graph[u].push_back({v, w, 0, (int)graph[v].size()});
        // 添加反向边：v->u，容量0
        graph[v].push_back({u, 0, 0, (int)graph[u].size() - 1});
    }

    bool bfs()
    {
        queue<int> q;
        fill(dep.begin(), dep.end(), 0);

        dep[S] = 1;
        q.push(S);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto e : graph[u]) {
                int v = e.v;
                // 未访问过且有余量
                if (!dep[v] && e.cap > e.flow) {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        return dep[T]; // 返回汇点是否可达
    }

    int dfs(int u, int flow)
    {
        if (u == T || flow == 0)
            return flow;

        int ret = 0;
        for (int &i = cur[u]; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            int v = e.v;
            // 按层次图移动且有余量
            if (dep[v] == dep[u] + 1 && e.cap > e.flow) {
                int d = dfs(v, min(flow - ret, e.cap - e.flow));
                if (d > 0) {
                    ret += d;
                    e.flow += d; // 更新正向边流量
                    // 更新反向边流量
                    graph[v][e.rev].flow -= d;
                    if (ret == flow)
                        break;
                }
            }
        }
        return ret;
    }

    void dinic()
    {
        maxflow = 0;
        while (bfs()) {
            fill(cur.begin(), cur.end(), 0); // 重置当前弧
            maxflow += dfs(S, inf<i64>);
        }
    }
};
void solve_case()
{
    using namespace ::shelpam;
    int n, m;
    std::cin >> n >> m;
    MaxFlow mf(2 * n + 2, 0, 2 * n + 1);
    for (int i{}; i != m; ++i) {
        int u, v;
        std::cin >> u >> v;
        mf.addedge(u, n + v, 1);
    }
    for (int i{}; i != n; ++i) {
        mf.addedge(0, i + 1, 1);
        mf.addedge(n + i + 1, 2 * n + 1, 1);
    }

    mf.dinic();

    auto bfs = [&](int s) {
        std::queue<int> q;
        q.push(s);
        std::vector<int> vis(2 * n + 2);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            if (vis[u]) {
                continue;
            }
            vis[u] = 1;

            for (auto e : mf.graph[u]) {
                if (e.cap - e.flow != 0) {
                    q.push(e.v);
                }
            }
        }
        return vis;
    };
    auto bfs1 = [&](int s) {
        std::queue<int> q;
        q.push(s);
        std::vector<int> vis(2 * n + 2);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            if (vis[u]) {
                continue;
            }
            vis[u] = 1;

            for (auto e : mf.graph[u]) {
                if (e.cap - e.flow == 0) {
                    q.push(e.v);
                }
            }
        }
        return vis;
    };

    auto v1 = bfs(0);
    debug("v1", v1);
    auto l = std::accumulate(v1.begin() + 1, v1.begin() + 1 + n, 0LL);
    auto v2 = bfs1(2 * n + 1);
    debug("v2", v2);
    auto r = std::accumulate(v2.begin() + 1 + n, v2.begin() + 1 + 2 * n, 0LL);
    std::cout << l * r << '\n';
}
