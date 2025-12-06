#pragma once

/*Problem: B. Athlete Welcome Ceremony*/
/*Contest: 2024 ICPC Asia Chengdu Regional Contest (The 3rd Universal Cup. Stage
 * 15: Chengdu)*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/gym/105486/problem/B*/
/*Start: Wed 13 Nov 2024 08:50:42 PM CST*/
/*Author: ShelpAm*/

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

using i64 = std::int_fast64_t;
using u64 = std::uint_fast64_t;
/**   取模类（MLong & MInt 新版）
 *    2023-08-14:
 *https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63433564
 *
 *    根据输入内容动态修改 MOD 的方法：Z::setMod(p) 。
 **/
template <class T> constexpr T power(T a, i64 b)
{
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p)
{
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template <i64 P> struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}

    static i64 Mod;
    constexpr static i64 getMod()
    {
        if (P > 0) {
            return P;
        }
        else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_)
    {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const
    {
        return x;
    }
    explicit constexpr operator i64() const
    {
        return x;
    }
    constexpr MLong operator-() const
    {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) &
    {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) &
    {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a)
    {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, MLong const &a)
    {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs)
    {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs)
    {
        return lhs.val() != rhs.val();
    }
};

template <> i64 MLong<0LL>::Mod = i64(1E18) + 9;

template <int P> struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod()
    {
        if (P > 0) {
            return P;
        }
        else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_)
    {
        Mod = Mod_;
    }
    constexpr int norm(int x) const
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const
    {
        return x;
    }
    explicit constexpr operator int() const
    {
        return x;
    }
    constexpr MInt operator-() const
    {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) &
    {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) &
    {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a)
    {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, MInt const &a)
    {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs)
    {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs)
    {
        return lhs.val() != rhs.val();
    }
};

template <> int MInt<0>::Mod = 998244353;

template <int V, int P> constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 1000000007;
using Z = MInt<P>;

namespace {
[[maybe_unused]] constexpr std::uint_fast64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_fast64_t mod1e9p7{1'000'000'007ULL};
[[maybe_unused]] constexpr double eps{1e-8};
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
} // namespace shelpam::concepts

auto operator>>(auto &istream, auto &&t) -> decltype(istream)
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
auto chmax(auto &value, auto const &other) noexcept -> bool
{
    if (value < other) {
        value = other;
        return true;
    }
    return false;
}
auto chmin(auto &value, auto const &other) noexcept -> bool
{
    if (value > other) {
        value = other;
        return true;
    }
    return false;
}
constexpr auto sum_of(std::ranges::range auto const &coll) noexcept
{
    return std::accumulate(coll.begin(), coll.end(), Z{});
}
constexpr auto pow(auto a, std::int_fast64_t b, std::uint_fast64_t p)
{
    static_assert(sizeof(a) > sizeof(int), "Use of int is bug-prone.");
    if (b < 0) {
        throw std::invalid_argument{"Invalid exponent. It should be positive."};
    }
    decltype(a) res{1};
    while (b != 0) {
        if ((b & 1) == 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
auto binary_search(std::invocable<std::int_fast64_t> auto check,
                   std::int_fast64_t ok, std::int_fast64_t ng,
                   bool check_ok = true) -> std::int_fast64_t
{
    if (check_ok && !check(ok)) {
        throw std::invalid_argument{"check isn't true on 'ok'."};
    }
    while (std::abs(ok - ng) > 1) {
        auto const x{(ok + ng) / 2};
        (check(x) ? ok : ng) = x;
    }
    return ok;
}
constexpr auto lsb(std::signed_integral auto i) noexcept -> decltype(i)
{
    return i & -i;
}
// i mustn't be 0
constexpr auto msb(std::unsigned_integral auto i) -> int
{
    if (i == 0) {
        throw std::invalid_argument{"i must be positive."};
    }
    return sizeof(i) * CHAR_BIT - 1 - std::countl_zero(i);
}
/*[[maybe_unused]] auto gen_rand() noexcept*/
/*{*/
/*  static std::mt19937_64 rng(*/
/*      std::chrono::steady_clock::now().time_since_epoch().count());*/
/*  return rng();*/
/*}*/
void solve_case();
} // namespace
auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    constexpr auto my_precision{10};
    std::cout << std::fixed << std::setprecision(my_precision);
    int t{1};
    // std::cin >> t;
    for (int i{}; i != t; ++i) {
        try {
            std::cerr << "Test case " << i << '\n';
            solve_case();
        }
        catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << '\n';
        }
    }
    return 0;
}
namespace {
#define int i64
void solve_case()
{
    int n, q;
    std::cin >> n >> q;
    std::string s;
    std::cin >> s;
    s.insert(s.begin(), 0);

    using v1 = std::vector<Z>;
    using v2 = std::vector<v1>;
    using v3 = std::vector<v2>;
    using v4 = std::vector<v3>;
    int fl{};
    v4 f(2, v3(n + 1, v2(n + 1, v1(3))));
    // f[i][j][k]: in first i rounds, selecting j x, k y, and (n-j-k) z.
    f[fl][0][0].assign(3, 1);

    auto const questions{std::ranges::count(s, '?')};

    for (int i{1}; i != n + 1; ++i) {
        fl ^= 1;
        f[fl].assign(n + 1, v2(n + 1, v1(3)));
        for (int j{}; j != n + 1; ++j) {
            for (int k{}; k + j != n + 1; ++k) {
                if (s[i] != '?') {
                    auto const to{s[i] - 'a'};
                    for (int from{}; from != 3; ++from) {
                        if (to != from) {
                            f[fl][j][k][to] += f[fl ^ 1][j][k][from];
                        }
                    }
                }
                else {
                    auto const l{questions - j - k};
                    for (int from{}; from != 3; ++from) {
                        for (int to{}; to != 3; ++to) {
                            if (from == to) {
                                continue;
                            }
                            std::array<int, 3> d{};
                            d[to] = 1;
                            if (j >= d[0] && k >= d[1] && l >= d[2]) {
                                f[fl][j][k][to] +=
                                    f[fl ^ 1][j - d[0]][k - d[1]][from];
                            }
                        }
                    }
                }
            }
        }
    }

    v3 a(n + 1, v2(n + 1, v1(n + 1)));
    for (int i{}; i != questions + 1; ++i) {
        for (int j{}; i + j != questions + 1; ++j) {
            a[i][j][questions - i - j] = sum_of(f[fl][i][j]);
        }
    }

    using ll = i64;
    v3 p(n + 2, v2(n + 2, v1(n + 2)));

    for (ll i = 0; i <= n; i++) {
        for (ll j = 0; j <= n; j++) {
            for (ll k = 0; k <= n; k++) {
                p[i + 1][j + 1][k + 1] = a[i][j][k];
            }
        }
    }
    for (ll i = 1; i <= n + 1; i++) {
        for (ll j = 1; j <= n + 1; j++) {
            for (ll k = 1; k <= n + 1; k++) {
                p[i][j][k] +=
                    (p[i - 1][j][k] + p[i][j - 1][k] + p[i][j][k - 1]) -
                    (p[i][j - 1][k - 1] + p[i - 1][j][k - 1] +
                     p[i - 1][j - 1][k]) +
                    p[i - 1][j - 1][k - 1];
            }
        }
    }

    auto const div2{pow(2LL, mod1e9p7 - 2, mod1e9p7)};
    for (int i{}; i != q; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        chmin(x, n);
        chmin(y, n);
        chmin(z, n);
        std::cout << p[x + 1][y + 1][z + 1] * div2 << '\n';
    }
}
} // namespace
