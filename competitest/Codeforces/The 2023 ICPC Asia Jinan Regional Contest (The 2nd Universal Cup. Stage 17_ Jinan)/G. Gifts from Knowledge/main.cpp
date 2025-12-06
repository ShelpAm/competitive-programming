#pragma once

#ifndef __cpp_concepts
#error This lib requires at least cpp20 to work.
#endif

// Problem: G. Gifts from Knowledge
// Contest: The 2023 ICPC Asia Jinan Regional Contest (The 2nd Universal Cup.
// Stage 17: Jinan) Judge: Codeforces URL:
// https://codeforces.com/gym/104901/problem/G Start: Tue 14 Oct 2025 07:04:07
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
namespace shelpam {

class Disjoint_set_union {
  public:
    explicit Disjoint_set_union(int size) : _parent(size), _size(size, 1)
    {
        std::ranges::iota(_parent, 0);
    }

    // With path compression
    int find(int x)
    {
        return _parent[x] == x ? x : _parent[x] = find(_parent[x]);
    }

    /// @return:
    /// false if there has been pair x,y in the set.
    /// true successfully united
    bool unite(int x, int y)
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

    [[nodiscard]] bool united(int x, int y)
    {
        return find(x) == find(y);
    }

    [[nodiscard]] auto size(int x)
    {
        return _size[find(x)];
    }

  private:
    std::vector<int> _parent;
    std::vector<int> _size;
};

using Dsu = Disjoint_set_union;

} // namespace shelpam
void solve_case()
{
    using namespace ::shelpam;
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> a(n);
    std::cin >> a;

    Dsu dsu(2 * n);
    std::vector<int> roc(m, -1);
    for (int i{}; i != n; ++i) {
        for (int j{}; j != m; ++j) {
            if (a[i][j] == '1') {
                if (roc[j] == -1 && roc[m - j - 1] == -1) {
                    roc[j] = i;
                }
                else {                      // any of has one
                    if ((2 * j) + 1 == m) { // mid
                        std::cout << 0 << '\n';
                        return;
                    }
                    if (roc[m - j - 1] != -1) {
                        dsu.unite(i, roc[m - j - 1]);
                        dsu.unite(i + n, roc[m - j - 1] + n);
                    }
                    if (roc[j] != -1) {
                        dsu.unite(i, n + roc[j]);
                        dsu.unite(roc[j], n + i);
                    }
                }
            }
        }
    }

    i64 ans{};
    for (int i{}; i != 2 * n; ++i) {
        if (dsu.united(i, (i + n) % (2 * n))) {
            std::cout << 0 << '\n';
            return;
        }
        if (dsu.find(i) == i) {
            ++ans;
        }
    }
    std::cout << pow(2LL, ans / 2, mod1e9p7) << '\n';
}
