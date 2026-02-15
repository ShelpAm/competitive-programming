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
constexpr int mod = 998244353;
int qpow(int a, int n, int p)
{
    int res{1};
    while (n) {
        if (n & 1)
            res = res * a % p;
        a = a * a % p;
        res >>= 1;
    }
    return res;
}
int inv(int x)
{
    return qpow(x, mod - 2, mod);
}
void solve()
{
    int l, r;
    std::cin >> l >> r;

    auto rev = [](int r) {
        auto s = std::to_string(r);
        std::reverse(s.begin(), s.end());
        return std::stoll(s);
    };

    int ans{};
    ans = std::max(ans, rev(r));
    for (int i{1}; i <= r; i *= 10) {
        auto t = r;
        while (t / i % 10 != 9) {
            t -= i;
            if (t < l)
                goto stop;
        }
        r = t;
        ans = std::max(ans, rev(r));
    }
stop:
    std::cout << ans << '\n';
}
