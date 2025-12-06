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

class AC {
  private:
    struct Node {
        std::vector<int> s;
        int f, id, c;
        Node() : s(26, 0), f(0), id(0), c(0) {}
    };

    std::vector<Node> t;
    std::vector<int> in, mp;
    int cnt, n;

    void ins(std::string const &p, int id)
    {
        int u = 1;
        for (char c : p) {
            int i = c - 'a';
            if (!t[u].s[i]) {
                t[u].s[i] = cnt++;
                t.emplace_back();
            }
            u = t[u].s[i];
        }
        if (!t[u].id)
            t[u].id = id;
        mp[id] = t[u].id;
    }

    void bld()
    {
        std::queue<int> q;
        for (int i = 0; i < 26; i++)
            t[0].s[i] = 1;
        q.push(1);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int fl = t[u].f;
            for (int i = 0; i < 26; i++) {
                int &v = t[u].s[i];
                if (!v)
                    v = t[fl].s[i];
                else {
                    t[v].f = t[fl].s[i];
                    in[t[v].f]++;
                    q.push(v);
                }
            }
        }
    }

    void run(std::string const &s)
    {
        int u = 1;
        for (char c : s) {
            u = t[u].s[c - 'a'];
            t[u].c++;
        }
    }

    void topo()
    {
        std::queue<int> q;
        for (int i = 0; i < cnt; i++)
            if (!in[i])
                q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int v = t[u].f;
            if (v) {
                t[v].c += t[u].c;
                if (!--in[v])
                    q.push(v);
            }
        }
    }

  public:
    AC(int n) : n(n)
    {
        cnt = 2;
        t.resize(2);
        mp.resize(n + 1);
    }

    void build(std::vector<std::string> const &ps)
    {
        for (int i = 0; i < n; i++)
            ins(ps[i], i + 1);
        in.resize(cnt, 0);
        bld();
    }

    std::vector<int> match(std::string const &s)
    {
        run(s);
        topo();

        std::vector<int> res(n + 1);
        for (int i = 0; i < cnt; i++)
            if (t[i].id)
                res[t[i].id] = t[i].c;

        std::vector<int> ans;
        for (int i = 1; i <= n; i++)
            ans.push_back(res[mp[i]]);

        return ans;
    }
};
} // namespace str
