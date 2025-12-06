#pragma once

#ifndef __cpp_concepts
#error This lib requires at least cpp20 to work.
#endif

// Problem: $(PROBLEM)
// Contest: $(CONTEST)
// Judge: $(JUDGE)
// URL: $(URL)
// Start: $(DATE)
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
std::pair<int, int> operator-(std::pair<int, int> l, std::pair<int, int> r)
{
    return {l.first - r.first, l.second - r.second};
}
std::pair<int, int> operator+(std::pair<int, int> l, std::pair<int, int> r)
{
    return {l.first + r.first, l.second + r.second};
}
void solve_case()
{
    using namespace ::shelpam;
    int m;
    std::cin >> m;
    using Submission = std::tuple<std::string, char, int, bool>;
    std::vector<Submission> a(m);
    for (auto &[c, p, t, s] : a) {
        std::string ac;
        std::cin >> c >> p >> t >> ac;
        s = ac == "accepted";
    }

    std::unordered_map<
        std::string,
        std::unordered_map<char, std::vector<std::tuple<int, int, bool>>>>
        sub;
    for (int i{}; auto const &[c, p, t, s] : a) {
        sub[c][p].push_back({t, i++, s});
    }

    auto calc_contrib = [](std::vector<std::tuple<int, int, bool>> const &v)
        -> std::pair<int, int> {
        bool ac{};
        int pen{};
        for (auto [t, _, s] : v) {
            if (!ac && s) { // first ac
                pen += t;
            }
            ac |= s;
            if (!ac) {
                pen += 20;
            }
        }
        return std::pair{ac, ac ? -pen : 0};
    };

    // num of ac, -penalty
    std::unordered_map<std::string, std::pair<int, int>> score;
    for (auto &[c, v] : sub) {
        for (auto &[p, v] : v) {
            std::ranges::sort(v);

            auto contrib = calc_contrib(v);
            score[c] = score[c] + contrib;
        }
    }

    std::vector<std::pair<std::string, std::pair<int, int>>> result(
        score.begin(), score.end());
    std::ranges::sort(result, std::ranges::greater{},
                      [](auto const &e) { return e.second; });

    auto n = static_cast<int>(std::ranges::count_if(
        score, [](auto const &pair) { return pair.second.first != 0; }));
    std::unordered_set<std::string> ans;

    if (n == 1) { // 一个人过，没有银首，特判
        for (int i{1}; i != score.size(); ++i) {
            auto const &c = result[i].first;
            std::pair<int, int> maxd{-2, 0};
            for (auto [p, v] : sub[c]) {
                auto prev = calc_contrib(v);
                auto it = std::ranges::find_if(
                    v, [](auto const &pair) { return !std::get<2>(pair); });
                if (it == v.end()) {
                    continue;
                }
                std::get<2>(*it) = true;
                auto cur = calc_contrib(v);
                auto delta = cur - prev;
                chmax(maxd, delta);
            }
            if (result[i].second + maxd >= result[0].second) {
                ans.insert(c);
            }
        }

        ans.insert(result[0].first);
        std::cout << ans.size() << '\n';
        for (auto const &e : ans) {
            std::cout << e << ' ';
        }
        std::cout << '\n';
        return;
    }

    if (n == 0) {
        std::cout << score.size() << '\n';
        for (auto const &[c, v] : score) {
            std::cout << c << ' ';
        }
        std::cout << '\n';
        return;
    }

    auto gold = std::min(static_cast<int>(std::ceil(0.1 * n)), 35);
    assert(gold > 0 && gold < score.size());
    auto last_gold = result[gold - 1];
    auto first_silver = result[gold];
    int num_last{};

    std::unordered_set<std::string> silver_heads;
    std::pair<int, int> worst{inf<int>, 0};
    for (int i{}; i != score.size(); ++i) {
        auto const &c = result[i].first;
        if (result[i].second >= last_gold.second) {
            if (result[i].second == last_gold.second) {
                ++num_last;
            }
            ans.insert(c);
            std::pair<int, int> mind{inf<int>, 0};
            for (auto [p, v] : sub[c]) {
                auto prev = calc_contrib(v);
                auto it = std::ranges::find_if(
                    v, [](auto const &pair) { return std::get<2>(pair); });
                if (it == v.end()) {
                    continue;
                }
                std::get<2>(*it) = false;
                auto cur = calc_contrib(v);
                auto delta = cur - prev;
                chmin(mind, delta);
            }
            if (mind != std::pair{inf<int>, 0}) {
                chmin(worst, result[i].second + mind);
            }
        }
        else {
            if (result[i].second == first_silver.second && num_last == 1) {
                // 银首,且金尾仅一队
                silver_heads.insert(c);
                if (worst <= first_silver.second) {
                    ans.insert(c);
                }
            }
            std::pair<int, int> maxd{-2, 0};
            for (auto [p, v] : sub[c]) {
                auto prev = calc_contrib(v);
                auto it = std::ranges::find_if(
                    v, [](auto const &pair) { return !std::get<2>(pair); });
                if (it == v.end()) {
                    continue;
                }
                std::get<2>(*it) = true;
                auto cur = calc_contrib(v);
                std::get<2>(*it) = false;
                auto delta = cur - prev;
                chmax(maxd, delta);
            }
            if (result[i].second + maxd >= last_gold.second) {
                ans.insert(c);
            }
        }
    }

    // 没过题的
    if (std::min(static_cast<int>(std::ceil(0.1 * (n + 1))), 35) > gold) {
        std::pair<int, int> worst{inf<int>, 0};
        for (int i{n}; i != score.size(); ++i) {
            auto const &c = result[i].first;

            std::pair<int, int> mind{inf<int>, 0};
            for (auto [p, v] : sub[c]) {
                auto prev = calc_contrib(v);
                auto it = std::ranges::find_if(
                    v.rbegin(), v.rend(),
                    [](auto const &pair) { return !std::get<2>(pair); });
                assert(it != v.rend());
                std::get<2>(*it) = true;
                auto cur = calc_contrib(v);
                std::get<2>(*it) = false;
                auto delta = cur - prev;
                chmin(mind, delta);
            }
            assert(mind != std::make_pair(inf<int>, 0));
            chmin(worst, result[i].second + mind);

            std::pair<int, int> maxd{-2, 0};
            for (auto [p, v] : sub[c]) {
                auto prev = calc_contrib(v);
                auto it = std::ranges::find_if(
                    v, [](auto const &pair) { return !std::get<2>(pair); });
                if (it == v.end()) {
                    continue;
                }
                std::get<2>(*it) = true;
                auto cur = calc_contrib(v);
                auto delta = cur - prev;
                chmax(maxd, delta);
            }
            assert(maxd != std::pair(-2, 0));
            if (result[i].second + maxd >= first_silver.second) {
                ans.insert(c);
            }
        }
        if (worst <= first_silver.second) {
            ans.insert(silver_heads.begin(), silver_heads.end());
        }
    }

    std::cout << ans.size() << '\n';
    for (auto const &e : ans) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}
