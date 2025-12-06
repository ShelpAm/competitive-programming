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
using namespace std;
void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a)
        std::cin >> e;

    for (int m{1}; m != 201; ++m) {
        std::vector<int> ls;
        std::vector<int> rs;
        int sl{};
        int sr{};
        for (auto e : a) {
            auto l = ((2 * e - 1) * m + 200 - 1) / 200;
            auto r = ((2 * e + 1) * m - 1) / 200;
            sl += l;
            sr += r;
            assert(l >= 0);
            assert(r <= m);
            ls.push_back(l);
            rs.push_back(r);
        }
        if (sl <= m && m <= sr) {
            std::cout << "Yes\n";
            int rem{m - sl};
            for (auto [l, r] : std::views::zip(ls, rs)) {
                auto d = std::min(rem, r - l);
                std::cout << l + d << ' ';
                rem -= d;
            }
            std::cout << '\n';
            return;
        }
    }
    std::cout << "No\n";
}
