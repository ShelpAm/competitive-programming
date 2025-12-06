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
void solve()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> a(n), b(m);
    for (auto &[x, y] : a)
        std::cin >> x >> y;
    for (auto &[x, y] : b)
        std::cin >> x >> y;

    auto merge = [](auto a) {
        std::ranges::sort(a);
        std::vector<std::pair<int, int>> b{a[0]};
        for (int i{1}; i != a.size(); ++i) {
            if (b.back().second >= a[i].first) {
                b.back().second = std::max(b.back().second, a[i].second);
            }
            else {
                b.push_back(a[i]);
            }
        }
        return b;
    };
    a = merge(a);
    b = merge(b);
    std::cout << "after merge a\n";
    for (auto [l, r] : a)
        std::cout << l << ' ' << r << '\n';
    std::cout << "b\n";
    for (auto [l, r] : b)
        std::cout << l << ' ' << r << '\n';

    bool ap{std::ranges::all_of(a, [](auto p) { return p.first == p.second; })};
    bool bp{std::ranges::all_of(b, [](auto p) { return p.first == p.second; })};

    if (ap && bp) {
        //
        return;
    }

    std::set<int> set;
    for (auto [l, r] : a) {
        set.insert(l);
        set.insert(r);
    }
    for (auto [l, r] : b) {
        set.insert(l);
        set.insert(r);
    }
    set.insert(1e9 + 1);
    auto breakk = [&set](auto const &a) {
        std::vector<std::pair<int, int>> b;
        auto it = set.begin();
        for (auto [l, r] : a) {
            int last{l};
            while (it != set.end() && *it <= l) {
                ++it;
            }
            while (it != set.end() && *it <= r) {
                b.push_back({last, *it});
                last = *it;
                ++it;
            }
        }
        return b;
    };

    std::map<int, double> s;

    if (ap || bp) {
        if (bp) {
            std::swap(a, b);
        }
        assert(!ap);
        b = breakk(b);

        std::cout << "after breakk a\n";
        for (auto [l, r] : a)
            std::cout << l << ' ' << r << '\n';
        std::cout << "b\n";
        for (auto [l, r] : b)
            std::cout << l << ' ' << r << '\n';
        return;
    }

    a = breakk(b);
    b = breakk(b);

    std::cout << "after breakk a\n";
    for (auto [l, r] : a)
        std::cout << l << ' ' << r << '\n';
    std::cout << "b\n";
    for (auto [l, r] : b)
        std::cout << l << ' ' << r << '\n';
    return;
}
