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
using Mat = std::vector<std::vector<int>>;
Mat mult(Mat l, Mat r)
{
    Mat t(l.size(), std::vector<int>(r[0].size(), -1e18));
    for (int i{}; i != t.size(); ++i)
        for (int j{}; j != t[0].size(); ++j)
            for (int k{}; k != l[0].size(); ++k)
                t[i][j] = std::max(t[i][j], l[i][k] + r[k][j]);
    return t;
}
void solve()
{
    int n, m, K, R;
    std::cin >> n >> m >> K >> R;
    std::vector<std::pair<int, int>> a(n);
    for (auto &[x, y] : a)
        std::cin >> x >> y;

    std::vector w(1 << n, std::vector<int>(1 << n, -2));
    for (int j{}; j != 1 << n; ++j) {
        for (int k{}; k != 1 << n; ++k) {
            int cost{};
            int weight{};
            for (int l{}; l != n; ++l) {
                if (!(k >> l & 1)) {
                    continue;
                }
                cost += ((j >> l & 1) ? K : 0) + a[l].second;
                weight += a[l].first;
            }
            w[j][k] = cost <= m ? weight : -1e17;
        }
    }

    Mat res(1 << n, std::vector<int>(1 << n));
    res[0] = w[0];
    R -= 1;
    while (R) {
        if (R % 2 == 1)
            res = mult(res, w);
        w = mult(w, w);
        R >>= 1;
    }
    auto ans = std::ranges::max(res[0]);
    std::cout << ans << '\n';
}
