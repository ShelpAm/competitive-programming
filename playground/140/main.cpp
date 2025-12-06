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
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (auto &e : a)
        std::cin >> e;
    auto s = std::accumulate(a.begin(), a.end(), 0LL);
    if (std::ranges::find(a, s - m) != a.end()) {
        std::cout << "Yes\n";
    }
    else {
        std::cout << "No\n";
    }
}
