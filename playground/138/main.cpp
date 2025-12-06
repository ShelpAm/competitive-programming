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

struct Segment_Tree2 { // 区间修改成一个值, 区间求最大
    Segment_Tree2(vector<int> tt) : a(tt), n(tt.size() - 1), t(4 * tt.size())
    {
        build(1, 1, n);
    }
    struct tree {
        int l, r;
        int pre, add = 0;
    };
    int n;
    vector<int> a;
    vector<tree> t;
    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if (l == r) {
            t[p].pre = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(2 * p, l, mid);
        build(2 * p + 1, mid + 1, r);
        t[p].pre = gcd(t[2 * p].pre, t[2 * p + 1].pre);
    }
    void spread(int p)
    {
        if (t[p].add) {
            t[p * 2].pre = t[p].add;
            t[p * 2 + 1].pre = t[p].add;
            t[p * 2].add = t[p].add;
            t[p * 2 + 1].add = t[p].add;
            t[p].add = 0;
        }
    }
    void modify(int p, int x, int y, int value)
    {
        if (x <= t[p].l && y >= t[p].r) {
            t[p].add = value;
            t[p].pre = value;
            return;
        }
        spread(p);
        int mid = (t[p].l + t[p].r) >> 1;
        if (x <= mid)
            modify(2 * p, x, y, value);
        if (y > mid)
            modify(2 * p + 1, x, y, value);
        t[p].pre = gcd(t[p * 2].pre, t[p * 2 + 1].pre);
    }
    int get_max(int p, int x, int y)
    {
        if (x <= t[p].l && y >= t[p].r)
            return t[p].pre;
        spread(p);
        int mid = (t[p].l + t[p].r) >> 1;
        int max_of_seg = 0;
        if (x <= mid)
            max_of_seg = gcd(max_of_seg, get_max(p * 2, x, y));
        if (y > mid)
            max_of_seg = gcd(max_of_seg, get_max(p * 2 + 1, x, y));
        return max_of_seg;
    }
};
void solve()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a)
        std::cin >> e;
    a.insert(a.begin(), 0);

    std::vector<int> b(n + 1);
    for (int i{1}; i != n; ++i) {
        b[i] = a[i + 1] >= a[i] ? 0 : i;
    }

    Segment_Tree2 st(b);
    auto d = st.get_max(1, 1, n);
    std::cout << (d == 0 ? n : d) << '\n';
    for (int i{}; i != q; ++i) {
        int p, v;
        std::cin >> p >> v;
        a[p] = v;
        if (a[p - 1] > a[p]) {
            st.modify(1, p - 1, p - 1, p - 1);
        }
        else {
            st.modify(1, p - 1, p - 1, 0);
        }
        if (a[p] > a[p + 1]) {
            st.modify(1, p, p, p);
        }
        else {
            st.modify(1, p, p, 0);
        }
        auto d = st.get_max(1, 1, n);
        std::cout << (d == 0 ? n : d) << '\n';
    }
}
