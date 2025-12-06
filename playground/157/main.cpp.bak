#include <bits/stdc++.h>
void solve();
int main()
{
    int t = 1;
    // std::cin >> t;
    for (int i{}; i != t; ++i)
        solve();
}
// #define int long long
void solve()
{
    constexpr int n = 4;
    using State = std::array<int, n * n>;

    std::vector const dirs{std::pair{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    auto ok = [&dirs](State const &s) {
        std::unordered_set<int> set(std::from_range, s);
        State vis{};
        int cnt{};
        for (int i{}; i != n; ++i) {
            for (int j{}; j != n; ++j) {
                auto dfs = [&](this auto self, int x, int y) {
                    if (s[x * n + y] != s[i * n + j]) {
                        return;
                    }
                    vis[x * n + y] = 1;
                    for (auto [dx, dy] : dirs) {
                        dx += x;
                        dy += y;
                        if (dx >= 0 && dx < n && dy >= 0 && dy < n &&
                            !vis[dx * n + dy]) {
                            self(dx, dy);
                        }
                    }
                };
                if (!vis[i * n + j]) {
                    dfs(i, j);
                    ++cnt;
                }
            }
        }
        return cnt == set.size();
    };

    State a;
    for (auto &e : a)
        std::cin >> e;

    std::map<State, int> f;
    auto best = std::numeric_limits<int>::max();
    State best_state;
    std::queue<std::pair<State, int>> q;
    q.push({a, 0});
    while (!q.empty()) {
        auto [s, d] = q.front();
        q.pop();

        if (d > best || f.contains(s)) {
            continue;
        }

        f.insert({s, d});
        if (ok(s)) {
            best = d;
            best_state = s;
            continue;
        }

        for (int i{}; i != n * n; ++i) {
            auto x = i / n;
            auto y = i % n;
            for (auto [dx, dy] : dirs) {
                dx += x;
                dy += y;
                auto j = dx * n + dy;
                if (dx >= 0 && dx < n && dy >= 0 && dy < n) {
                    if (s[i] == s[j]) {
                        continue;
                    }
                    std::swap(s[i], s[j]);
                    q.push({s, d + 1});
                    std::swap(s[i], s[j]);
                }
            }
        }
    }

    std::println("Minimum number of steps is {}", best);
    for (auto row : best_state | std::views::chunk(n)) {
        std::println("{}", row);
    }
}
