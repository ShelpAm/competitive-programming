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
void solve()
{
    int n, m, c;
    std::cin >> n >> m >> c;
    std::vector<int> a(n);
    for (auto &e : a)
        std::cin >> e;

    std::map<int, int> o;
    o.insert({0, 0});
    o.insert({m, 0});
    for (auto e : a)
        ++o[e];
    std::vector<int> b{0};
    for (auto [k, v] : o)
        b.push_back(b.back() + v);
    for (auto [k, v] : o)
        b.push_back(b.back() + v);

    std::vector<int> w(b.size(), -1);
    for (int i{}; i != (b.size() / 2) + 1; ++i) {
        auto j = std::ranges::lower_bound(b, b[i] + c) - b.begin();
        w[i] = b[j] - b[i];
    }

    int ans{};
    int i{};
    for (auto it = o.begin(); std::next(it) != o.end(); ++it) {
        ans += (std::next(it)->first - it->first) * w[i + 1];
        // std::cerr << it->first << ' ' << (std::next(it)->first - it->first)
        //           << ' ' << w[i + 1] << '\n';
        ++i;
    }
    std::cout << ans << '\n';
}
