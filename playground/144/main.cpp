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
    int n, m, k, b;
    std::cin >> n >> m >> k >> b;
    std::vector<std::pair<int, int>> a(n);
    int ans{};
    int upgradable{};
    for (auto &[origin, now] : a) {
        for (int i{}; i != m; ++i) {
            int x;
            std::cin >> x;
            origin += x;
            if (x <= 0) {
                ++x;
            }
            else {
                --x;
            }
            now += x;
        }
        if (origin >= k) {
            ++ans;
        }
        else if (now >= k) {
            ++upgradable;
        }
    }
    ans += std::min(upgradable, b);
    std::cout << ans << '\n';
}
