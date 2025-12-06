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
    std::string s;
    std::cin >> s;
    std::unordered_map<char, std::string> mp{{'T', "T1"}, {'D', "DRX"}};
    std::unordered_map<char, int> o;
    for (int i{}; i != 5; ++i) {
        if (++o[s[i]] == 3) {
            std::cout << mp[s[i]] << '\n';
            return;
        }
    }
}
