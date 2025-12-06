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
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a)
        std::cin >> e;

    std::map<int, int> o;
    for (auto e : a)
        ++o[e];

    int ans{};
    for (auto [k, v] : o)
        ans += (v - 1) * v / 2 * (n - v);
    std::cout << ans << '\n';
}
