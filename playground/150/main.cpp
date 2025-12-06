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
    int n, d;
    std::cin >> n >> d;
    std::vector<int> a(n);
    for (auto &e : a)
        std::cin >> e;

    int ans{};
    for (auto k : std::set(a.begin(), a.end())) {
        {
            auto l = k;
            auto r = k + d;
            auto b = a;
            int s{};
            for (auto &e : b)
                e = std::clamp(e, l, r);
            for (int i{1}; i != b.size(); ++i)
                s += std::abs(b[i] - b[i - 1]);
            ans = std::max(ans, s);
        }
        {
            auto l = k - d;
            auto r = k;
            auto b = a;
            int s{};
            for (auto &e : b)
                e = std::clamp(e, l, r);
            for (int i{1}; i != b.size(); ++i)
                s += std::abs(b[i] - b[i - 1]);
            ans = std::max(ans, s);
        }
    }
    std::cout << ans << '\n';
}
