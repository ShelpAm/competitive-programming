#include <bits/stdc++.h>
void solve();
int main()
{
    int t = 1;
    // std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
#define int long long
using namespace std;
bool chmin(auto &x, auto y)
{
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}
struct Dist {
    int w = 1e9;
    int from = -1;
    friend Dist operator+(Dist d, int w)
    {
        return Dist{d.w + w, d.from};
    }
    friend bool operator<(Dist l, Dist r)
    {
        return l.w < r.w;
    }
};
void solve()
{
    int n, m;
    std::cin >> n >> m;
    std::vector g(n, std::vector<int>{});
    for (int i{}; i != m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    std::string s;
    std::cin >> s;

    std::queue<std::tuple<Dist, Dist, int>> q;
    std::vector dist(n, std::array<Dist, 2>{});
    for (int i{}; i != n; ++i) {
        if (s[i] == 'S') {
            dist[i][0].from = i;
            dist[i][0].w = 0;
            q.push({dist[i][0], dist[i][1], i});
        }
    }
    while (!q.empty()) {
        auto [_, _1, u] = q.front();
        q.pop();
        for (auto v : g[u]) {
            std::vector<Dist> t{dist[v][0], dist[v][1], dist[u][0] + 1,
                                dist[u][1] + 1};
            std::ranges::sort(t, std::less<>{});
            // std::cerr << "original:\n";
            // for (auto [w, from] : t) {
            //     std::cerr << "w,from: " << w << ' ' << from << '\n';
            // }
            if (t[1].from == t[0].from) {
                std::swap(t[1], t[2]);
            }
            // std::cerr << "after swap:\n";
            // for (auto [w, from] : t) {
            //     std::cerr << "w,from: " << w << ' ' << from << '\n';
            // }
            assert(t[0].from != t[1].from);
            if (chmin(dist[v], std::array{t[0], t[1]})) {
                q.push({dist[v][0], dist[v][1], v});
            }
        }
    }

    for (int i{}; i != n; ++i) {
        if (s[i] == 'D') {
            std::cout << dist[i][0].w + dist[i][1].w << '\n';
            assert(dist[i][0].from != dist[i][1].from);
        }
    }
}
