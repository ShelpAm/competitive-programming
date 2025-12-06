#include <bits/stdc++.h>
void solve();
int main()
{
    int t = 1;
    std::cin >> t;
    for (int i{}; i != t; ++i) {
        // std::cerr << "Test " << i << '\n';
        solve();
    }
}
#define int long long
using namespace std;
void solve()
{
    int n, m, k;
    std::cin >> n >> m >> k;
    std::string s;
    std::cin >> s;

    bool leftis0{};
    int U{}, D{n - 1}, L{}, R{m - 1};
    for (char e : s) {
        if (e == 'U') {
            U = std::max(U - 1, 0LL);
            D = D - 1;
        }
        else if (e == 'D') {
            U = U + 1;
            D = std::min(D + 1, n - 1);
        }
        else if (e == 'L') {
            L = std::max(0LL, L - 1);
            R = R - 1;
        }
        else if (e == 'R') {
            L = L + 1;
            R = std::min(m - 1, R + 1);
        }
        // std::cerr << L << ' ' << R << ' ' << U << ' ' << D << "\n";
        if (L > R || U > D) {
            leftis0 = true;
        }
    }

    auto left = leftis0 ? 0 : std::max(0LL, (D - U + 1) * (R - L + 1));
    // std::cerr << "Left " << left << '\n';
    if (left < k) {
        std::cout << 0 << '\n';
        return;
    }
    if (left == 0) {
        std::cout << n * m << '\n';
        return;
    }

    int x = U;
    int y = L;
    for (char e : s)
        if (e == 'U')
            ++x;
        else if (e == 'D')
            --x;
        else if (e == 'L')
            ++y;
        else if (e == 'R')
            --y;

    auto p = n - 1 - x;
    auto q = m - 1 - y;
    assert(x >= 0 && x < n && y >= 0 && y < m);
    std::vector a((2 * n) + 10, std::vector<int>((2 * m) + 10));
    ++a[p + 1][q + 1];
    // std::cerr << p << ' ' << q << '\n';
    for (char e : s) {
        if (e == 'U')
            ++p;
        else if (e == 'D')
            --p;
        else if (e == 'L')
            ++q;
        else if (e == 'R')
            --q;
        // std::cerr << p << ' ' << q << '\n';
        if (0 <= p && p < 2 * n && 0 <= q && q < 2 * m) {
            a[p + 1][q + 1] = 1;
        }
    }

    // for (auto const &e : a) {
    //     for (auto e : e)
    //         std::cout << e << ' ';
    //     std::cout << "\n";
    // }

    for (int i{1}; i != a.size(); ++i) {
        for (int j{1}; j != a[0].size(); ++j) {
            // std::cerr << i << ' ' << j << ' ' << a.size() << ' ' <<
            // a[i].size()
            //           << '\n';
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }
    auto query = [&](int i, int j, int w, int h) {
        return a[i + w - 1][j + h - 1] - a[i - 1][j + h - 1] -
               a[i + w - 1][j - 1] + a[i - 1][j - 1];
    };

    // std::cout << "Width: " << R - L + 1 << '\n';
    int ans{};
    for (int i{1}; i != n + 1; ++i) {
        for (int j{1}; j != m + 1; ++j) {
            // std::cout << i << ' ' << j << ' '
            //           << query(i, j, R - L + 1, D - U + 1) << '\n';
            if (query(i, j, D - U + 1, R - L + 1) == left - k) {
                ++ans;
            }
        }
    }
    std::cout << ans << '\n';
}
