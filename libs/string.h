#pragma once
#include <bits/stdc++.h>

namespace str {
std::vector<int> prefix_function(std::string_view pat)
{
    auto n = static_cast<int>(pat.size());
    std::vector<int> pi(n);
    for (int i{1}; i != n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && pat[i] != pat[j]) {
            j = pi[j - 1];
        }
        if (pat[i] == pat[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

/// @brief Returns indices of all first letters in occurrences.
std::vector<int> find_occurrences(std::string const &text,
                                  std::string const &pat)
{
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pat.size());
    std::vector<int> res;
    std::vector<int> lps = prefix_function(pat + '#' + text);
    for (int i = m + 1; i <= n + m; i++) {
        if (lps[i] == m) {
            res.push_back(i - 2 * m);
        }
    }
    return res;
}
std::vector<int> z_function(std::string_view s)
{
    auto const n{static_cast<int>(s.size())};
    std::vector<int> z(n);
    for (int i{1}, l{}, r{}; i != n; ++i) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        }
        else {
            z[i] = std::max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                ++z[i];
            }
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

// Manacher
std::vector<int> manacher_odd(std::string s)
{
    int n = s.size();
    s = "$" + s + "^";
    std::vector<int> p(n + 2);
    int l = 0;
    int r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = std::min(r - i, p[l + (r - i)]);
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return std::vector<int>(begin(p) + 1, end(p) - 1);
}

std::vector<int> manacher(std::string const &s)
{
    std::string t;
    for (auto c : s) {
        t += std::string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return std::vector<int>(begin(res) + 1, end(res) - 1);
}
} // namespace str
