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
    for (int i{1}; i != n + 1; ++i) {
        std::cout << (i <= m ? "OK" : "Too Many Requests") << '\n';
    }
}
