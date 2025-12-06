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

    int ans{};
    for (int i{}; i != a.size(); ++i) {
        auto j = (i - 1 + a.size()) % a.size();
        auto k = (i + 1) % a.size();
        auto goleft = [&](int k) {
            std::pair<int, int> u{a[i].first - a[j].first,
                                  a[i].second - a[j].second};
            std::pair<int, int> v{a[k].first - a[i].first,
                                  a[k].second - a[i].second};
            auto t = u.first * v.second - u.second * v.first;
            return t > 0;
        };
        while (a[k].second == a[i].second && k != j) {
            ++k %= a.size();
        }
        if ((goleft((i + 1) % a.size()) && a[i].second < a[j].second &&
             a[i].second < a[k].second)) {
            ++ans;
        }
        if (k < i) {
            break;
        }
        i = k - 1;
    }
    assert(ans != 0);
    std::cout << ans << '\n';
}
