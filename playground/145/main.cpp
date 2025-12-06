#include <bits/stdc++.h>
void solve();
int main()
{
    int t = 1;
    std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
#define int long long
using namespace std;
void solve()
{
    int n, m, k;
    std::cin >> n >> k >> m;
    auto use = (n - k) / k;
    int ans{};
    ans += 1;
    auto rem = n - 1 - use;
    auto singles = std::min(rem, m);
    m -= singles;
    ans += singles;
    if (m > 0) {
        auto swap = std::min(m, use);
        use -= swap;
        ans += swap;
    }
    ans += use / 2;
    std::cout << ans << '\n';
}
