#include <bits/stdc++.h>
void solve();
int main()
{
    int t = 1;
    std::cin >> t;
    for (int i{}; i != t; ++i)
        solve();
}
namespace shelpam {

class Sieve {
  public:
    explicit Sieve(std::uint_least64_t upper_bound)
        : _upper_bound{upper_bound}, _min_factor(upper_bound + 1, 0)
    {
        _primes.reserve(_upper_bound / static_cast<std::uint_least64_t>(
                                           std::log(_upper_bound)));

        for (int i = 2; i != _upper_bound + 1; ++i) {
            if (_min_factor[i] == 0) {
                _primes.push_back(i);
                _min_factor[i] = i;
            }
            for (auto const p : _primes) {
                if (i * p > upper_bound || p > _min_factor[i]) {
                    break;
                }
                _min_factor[i * p] = p;
            }
        }
    }

    // Time complexity:
    //     if x <= upper_bound then O(log(x))
    //     else if x <= upper_bound ^ 2 then O(sqrt(x))
    //     else unsupported
    [[nodiscard]] std::map<std::uint_least64_t, std::uint_least64_t>
    factorize(std::uint_least64_t x) const
    {
        // O(log(x))
        if (x <= _upper_bound) {
            std::vector<std::pair<std::uint_least64_t, std::uint_least64_t>>
                res;
            while (x != 1) {
                auto fact = _min_factor[x];
                if (res.empty() || res.back().first != fact) {
                    assert(res.empty() || res.back().first < fact);
                    res.emplace_back(fact, 0);
                }
                ++res.back().second; // Count once
                x /= fact;
            }
            return {res.begin(), res.end()};
        }

        // O(sqrt(x) * log2(64) * log2(64)) = 36 * sqrt(x)
        if (x <= _upper_bound * _upper_bound) {
            std::map<std::uint_least64_t, std::uint_least64_t> res;
            for (auto const p : _primes) {
                if (p > x) {
                    break;
                }
                while (x % p == 0) {
                    x /= p;
                    ++res[p];
                }
            }
            if (x >= _min_factor.size()) {
                ++res[x];
            }
            return res;
        }

        assert(false && "x is too big, even greater than upper_bound ^ 2");
    }

    [[nodiscard]] bool is_prime(std::uint_least64_t x) const
    {
        return _min_factor[x] == x;
    }

    [[nodiscard]] std::vector<std::uint_least64_t> const &primes() const
    {
        return _primes;
    }

  private:
    std::uint_least64_t _upper_bound;
    std::vector<std::uint_least64_t> _primes;
    std::vector<std::uint_least64_t> _min_factor;
};

} // namespace shelpam
#define int long long
void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a)
        std::cin >> e;

    auto d = 0LL;
    for (auto e : a)
        d = std::gcd(d, e);
    shelpam::Sieve s(1e3);
    for (auto e : s.primes()) {
        if (std::gcd(e, d) == 1) {
            std::cout << e << '\n';
            break;
        }
    }
    assert(false);
}
