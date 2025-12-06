#include <bits/stdc++.h>
void solve();
int main()
{
    int t = 1;
    // std::cin >> t;
    for (int i{}; i != t; ++i)
        solve();
}
#define int long long
using namespace std;
void solve()
{
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a;
    for (int i{}; i != n; ++i) {
        int x, y;
        std::cin >> x >> y;
        a.push_back({x, y});
    }

    std::vector<int> pa(2 * n);
    std::iota(pa.begin(), pa.end(), 0);
    std::function<int(int)> find = [&](int x) {
        if (x != pa[x])
            return pa[x] = find(pa[x]);
        return x;
    };
    auto unite = [&](int u, int v) {
        u = find(u);
        v = find(v);
        pa[u] = v;
    };

    for (int i{}; i != a.size(); ++i) {
        auto j = (i - 1 + a.size()) % a.size();
        auto k = (i + 1) % a.size();
        auto goleft = [&]() {
            std::pair<int, int> u{a[i].first - a[j].first,
                                  a[i].second - a[j].second};
            std::pair<int, int> v{a[k].first - a[i].first,
                                  a[k].second - a[i].second};
            auto t = u.first * v.second - u.second * v.first;
            return t > 0;
        };
        if (goleft()) {
            unite(2 * i, (2 * i) + 1);
        }
        if (a[i].second >= a[j].second) {
            unite(2 * i, (2 * j) + 1);
        }
        if (a[i].second >= a[k].second) {
            unite(2 * k, (2 * i) + 1);
        }
    }
    int ans{};
    for (int i{}; i != 2 * n; ++i) {
        ans += pa[i] == i;
    }
    std::cout << ans << '\n';
}
