#include <bits/stdc++.h>
void solve();
int main()
{
    std::cout << std::fixed << std::setprecision(10);
    int t = 1;
    // std::cin >> t;
    for (int i{}; i != t; ++i)
        solve();
}
#define int long long
using namespace std;
void solve()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    for (auto &e : a)
        std::cin >> e;
    for (auto &e : b)
        std::cin >> e;

    std::vector<std::vector<int>> O{a, b};

    std::vector<double> ans(3);
    auto dfs = [&](auto dfs, int turn, std::vector<std::vector<int>> &L,
                   std::array<int, 2> active, double prob) -> void {
        std::vector<int> die(2);
        for (int i{}; i != 2; ++i) {
            die[i] = std::ranges::all_of(L[i], [](auto e) { return e <= 0; });
        }
        if (die[0] && die[1]) {
            // std::cout << "tie " << prob << '\n';
            ans[2] += prob;
            return;
        }
        if (die[0]) {
            // std::cout << "1 win " << prob << '\n';
            ans[1] += prob;
            return;
        }
        if (die[1]) {
            // std::cout << "0 win " << prob << '\n';
            ans[0] += prob;
            return;
        }

        auto s1 = L[turn].size();
        auto s2 = L[turn ^ 1].size();

        std::vector<int> alive;
        for (int j{}; j != s2; ++j) {
            if (L[turn ^ 1][j] > 0) {
                alive.push_back(j);
            }
        }

        while (L[turn][active[turn]] <= 0) {
            ++active[turn];
            active[turn] %= L[turn].size();
        }
        auto i = active[turn]++;
        active[turn] %= L[turn].size();
        for (int j{}; j != s2; ++j) {
            if (L[turn ^ 1][j] > 0) {
                L[turn][i] -= O[turn ^ 1][j];
                L[turn ^ 1][j] -= O[turn][i];
                dfs(dfs, turn ^ 1, L, active, prob / alive.size());
                L[turn][i] += O[turn ^ 1][j];
                L[turn ^ 1][j] += O[turn][i];
            }
        }
    };

    std::vector<std::vector<int>> L{a, b};
    std::array<int, 2> active{0, 0};
    if (n < m) {
        dfs(dfs, 1, L, active, 1);
    }
    else if (n > m) {
        dfs(dfs, 0, L, active, 1);
    }
    else {
        dfs(dfs, 0, L, active, 0.5);
        dfs(dfs, 1, L, active, 0.5);
    }

    for (auto e : ans)
        std::cout << e << ' ';

    // if mask >> (i * m + j) & 1 is 1, then i has battled with j.
    // std::map<std::pair<int, int>, double> p;
    // // p[{0, 0}] = 1;
    // std::queue<std::pair<int, int>> q;
    // while (!q.empty()) {
    //     auto [mask, turn] = q.front();
    //     q.pop();
    //
    //     std::vector L{a, b};
    //     for (int i{}; i != n; ++i) {
    //         for (int j{}; j != m; ++j) {
    //             if (mask >> (i * m + j) & 1) {
    //                 L[0][i] -= b[j];
    //                 L[1][j] -= a[i];
    //                 L[0][i] = std::max(0LL, L[0][i]);
    //             }
    //         }
    //     }
    //     if (L[0]) {
    //     }
    //     for (int i{}; i != L[turn].size(); ++i) {
    //         if (L[turn][0] > 0) {
    //         }
    //     }
    // }
}
