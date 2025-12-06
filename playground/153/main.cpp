#include <bits/stdc++.h>
void solve();
int main()
{
    int t = 1;
    std::cin >> t;
    for (int i{}; i != t; ++i)
        solve();
}
#define int long long
int bins(auto check, int ok, int ng)
{
    while (std::abs(ok - ng) > 1) {
        auto mi = ok + ng >> 1;
        (check(mi) ? ok : ng) = mi;
    }
    return ok;
}
void solve()
{
    int n, m;
    std::cin >> n >> m;

    if ((n + 1) * n * (m + 1) * m % 8 != 0) {
        std::cout << "No\n";
        return;
    }
    std::cout << "Yes\n";

    bool swapped{};
    if ((m + 1) * m % 4 != 0) {
        std::swap(n, m);
        swapped = true;
    }

    std::vector<int> l;
    auto t = (m + 1) * m / 4;
    int r{};
    while (r < m) {
        auto k =
            bins([&](auto k) { return t >= (k * (k + 1) / 2) + m - r - k; }, 1,
                 m + 1);
        r += k;
        t -= k * (k + 1) / 2;
        l.push_back(k);
    }

    std::vector ans(n, std::vector<int>());
    int use{};
    for (auto e : l) {
        for (int i{}; i != e; ++i) {
            ans[0].push_back(use);
        }
        use ^= 1;
    }
    for (int i{1}; i != n; ++i) {
        ans[i] = ans[0];
    }

    if (swapped) {
        for (int j{}; j != ans[0].size(); ++j) {
            for (int i{}; i != ans.size(); ++i) {
                std::cout << ans[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
    else {
        for (int i{}; i != ans.size(); ++i) {
            for (int j{}; j != ans[0].size(); ++j) {
                std::cout << ans[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
}
