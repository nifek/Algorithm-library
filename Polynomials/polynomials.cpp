#ifdef LOCAL
    #include <bits/include_all.h>
#else
    #include <bits/stdc++.h>
    #include <ext/pb_ds/assoc_container.hpp>
    #include <ext/pb_ds/tree_policy.hpp>
#endif

#pragma GCC target ("avx2")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define int long long

using namespace std;
using namespace __gnu_pbds;

template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> inline bool umin(T &a, const T &b) { if(a > b) { a = b; return 1; } return 0; }
template <typename T> inline bool umax(T &a, const T &b) { if(a < b) { a = b; return 1; } return 0; }

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

const ll mod = 998244353;
const ll inf = 1e18;
const int MAX = 2e5 + 42;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ll> dis(1, inf);

constexpr int calculate_phi(int n) {
    if(n == 998244353 || n == 1000000007) return n - 1;
    int ans = n;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            ans /= i; ans *= i - 1; while(n % i == 0) n /= i;
        }
    }
    if(n > 1) ans /= n, ans *= n - 1;
    return ans;
}

// 7340033 = 1 (mod 2^20), 3
// 998244353 = 1 (mod 2^23), 3
// 167772161 = 1 (mod 2^25), 3
// 469762049 = 1 (mod 2^26), 3
// 2013265921 = 1 (mod 2^27), 31
class Mint {
public:
    // All modulo 998244353
    static constexpr int phi_minus_one = calculate_phi(mod) - 1;
    static const int square_root = sqrt(mod);
    static const int primitive_root = 3;
    int x;

public:
    void norm() {
        x %= mod;
        if(x < 0) x += mod;
    }
    Mint(int a, bool small) {
        x = a;
        if(x >= mod) x -= mod;
        if(x < 0) x += mod;
    }
    Mint() { x = 0; }
    Mint(long long a) {
        if(a >= mod || a <= -mod) a %= mod;
        x = a;
        if(x < 0) x += mod;
    }
    Mint(const Mint &b) { x = b.x; }
    friend ostream &operator <<(ostream &out, const Mint &a) { out << a.x; return out; }
    friend istream &operator >>(istream &in, Mint &a) { in >> a.x; return in; }
    Mint operator +(const Mint &b) const & {
        return Mint(x + b.x, 1);
    }
    Mint operator +(int a) const & {
        return Mint(x + a, 1);
    }
    Mint operator -(const Mint &b) const & {
        return Mint(x - b.x, 1);
    }
    Mint operator -(int a) const & {
        return Mint(x - a, 1);
    }
    friend Mint operator -(const Mint &a) {
        return Mint(mod - a);
    }
    Mint operator *(const Mint &b) const & {
         return Mint(1LL * x * b.x);
    }
    Mint operator *(int a) const & {
        return Mint(1LL * x * a);
    }
    Mint &operator +=(const Mint &b) {
        x += b.x;
        if(x >= mod) x -= mod;
        return *this;
    }
    Mint &operator +=(int a) {
        x += a;
        if(x >= mod) x -= mod;
        return *this;
    }
    Mint &operator -=(const Mint &b) {
        x += mod - b.x;
        if(x >= mod) x -= mod;
        return *this;
    }
    Mint &operator -=(int a) {
        x += mod - a;
        if(x >= mod) x -= mod;
        return *this;
    }
    Mint &operator *=(const Mint &b) {
        x = (long long) x * b.x % mod;
        return *this;
    }
    Mint &operator *=(int a) {
        x = (long long) x * a % mod;
        return *this;
    }
    Mint &operator /=(const Mint &b) {
        x = (long long) x * b.inv().x % mod;
        return *this;
    }
    Mint &operator /=(int a) {
        x = (long long) x * Mint(a, 1).inv().x % mod;
        return *this;
    }
    Mint &operator ++() {
        if(++x == mod) x = 0;
        return *this;
    }
    Mint operator ++(int32_t) {
        Mint ans(*this);
        if(++x == mod) x = 0;
        return ans;
    }
    Mint &operator --() {
        if(--x == -1) x = mod - 1;
        return *this;
    }
    Mint operator --(int32_t) {
        Mint ans(*this);
        if(--x == -1) x = mod - 1;
        return ans;
    }
    Mint bpow(long long n) const & {
        Mint a(x);
        Mint ans(1);
        while(n) {
            if(n & 1) ans *= a;
            n >>= 1;
            a *= a;
        }
        return ans;
    }
    Mint inv() const & {
        return bpow(phi_minus_one);
    }
    Mint operator /(const Mint &b) const & {
        return b.inv() * x;
    }
    Mint operator /(int a) const & {
        return Mint(a, 1).inv() * x;
    }
    friend Mint operator -(int a, const Mint &b) {
        Mint res(b - a);
        res.x = mod - res.x;
        if(res.x == mod) res.x = 0;
        return res;
    }
    friend Mint operator +(int a, const Mint &b) {
        return Mint(b + a);
    }
    friend Mint operator *(int a, const Mint &b) {
        return Mint(b * a);
    }
    friend Mint operator /(int a, const Mint &b) {
        return Mint(a, 1) * b.inv();
    }
    Mint &operator=(const Mint &b) {
        x = b.x;
        return *this;
    }
    bool operator==(int a) const & {
        return (x == a);
    }
    bool operator!=(int a) const & {
        return (x != a);
    }
    bool operator==(const Mint &b) const & {
        return (x == b.x);
    }
    bool operator!=(const Mint &b) const & {
        return (x != b.x);
    }
    friend bool operator==(int a, const Mint &b) {
        return (b.x == a);
    }
    friend bool operator!=(int a, const Mint &b) {
        return (b.x != a);
    }

    // Uses unordered map (!!!)
    int log(const Mint &b) const & {
        Mint a_pow = bpow(square_root);
        Mint pw = a_pow;
        std::unordered_map<int, int> used;
        for(int p = 1; p <= square_root + 1; p++) used[a_pow.x] = p, a_pow *= pw;
        a_pow = b;
        for(int q = 0; q <= square_root; q++) {
            if(used[a_pow.x]) {
                int ans = used[a_pow.x] * square_root - q;
                if(ans < mod) return ans;
            }
            a_pow *= x;
        }
        return -1;
    }

    int root(long long k) const & {
        Mint p = Mint(primitive_root).bpow(k);
        int logarithm = p.log(x);
        if(!~logarithm) return -1;
        return Mint(primitive_root).bpow(logarithm).x;
    }
};

namespace polynomials {
    const Mint primitive_root = Mint::primitive_root;
    const int max_len = 1 << 23;

    /// Computes a(x) + b(x), O(n)
    vector<Mint> add(const vector<Mint> &a, const vector<Mint> &b) {
        int n = a.size(), m = b.size();
        int siz = max(n, m);
        vector<Mint> c(siz);
        for(int i = 0; i < siz; i++) {
            if(i < n) c[i] += a[i];
            if(i < m) c[i] += b[i];
        }
        return c;
    }

    /// Computes a(x) - b(x), O(n)
    vector<Mint> sub(const vector<Mint> &a, const vector<Mint> &b) {
        int n = a.size(), m = b.size();
        int siz = max(n, m);
        vector<Mint> c(siz);
        for(int i = 0; i < siz; i++) {
            if(i < n) c[i] += a[i];
            if(i < m) c[i] -= b[i];
        }
        return c;
    }

    /// Computes x^i * k, O(n)
    vector<Mint> multiply(const vector<Mint> &a, Mint k) {
        vector<Mint> c = a;
        for(auto &i : c) i *= k;
        return c;
    }

    /// Computes the derivative of a(x) with [x^(n - 1)] a(x) = 0, O(n)
    vector<Mint> derivative(const vector<Mint> &a, int m = -1) {
        int n = a.size();
        if(~m) n = m;
        vector<Mint> c = a; c.resize(n);
        for(int i = 0; i < n; i++) c[i] *= i;
        c.erase(c.begin(), c.begin() + 1); c.push_back(0);
        return c;
    }

    /// Computes the integral of a(x) with a(0) = 0, O(n)
    vector<Mint> integral(const vector<Mint> &a, int m = -1) {
        int n = a.size();
        if(~m) n = m;
        if(n == 1) return {0};
        vector<Mint> c = a; c.resize(n);
        c.insert(c.begin(), 0); c.pop_back();
        vector<Mint> inv(n);
        inv[1] = 1; for(int i = 2; i < n; i++) inv[i] = -(mod / i) * inv[mod % i];
        for(int i = 1; i < n; i++) c[i] *= inv[i];
        return c;
    }

    /// Computes x^k / k!, O(n)
    vector<Mint> egf(const vector<Mint> &a) {
        int n = a.size();
        vector<Mint> inv_fact(n);
        inv_fact[0] = inv_fact[1] = 1; for(int i = 2; i < n; i++) inv_fact[i] = -(mod / i) * inv_fact[mod % i]; for(int i = 1; i < n; i++) inv_fact[i] *= inv_fact[i - 1];
        vector<Mint> c = a;
        for(int i = 0; i < n; i++) c[i] *= inv_fact[i];
        return c;
    }

    /// Computes x^k * k!, O(n)
    vector<Mint> ogf(const vector<Mint> &a) {
        int n = a.size();
        Mint fact = 1;
        vector<Mint> c = a;
        for(int i = 0; i < n; i++) c[i] *= fact, fact *= i + 1;
        return c;
    }

    ///FFT source - https://codeforces.com/blog/entry/117947
    const long long mod2 = (long long) mod * mod;
    const int32_t proot = Mint::primitive_root;
    const int32_t alim = 64; // Bound for using O(n^2) polynomial mult

    int32_t modpow(int32_t b, ll e) {
        int32_t ans = 1;
        for (; e; b = (long long) b * b % mod, e /= 2)
            if (e & 1) ans = (long long) ans * b % mod;
        return ans;
    }

    const int32_t modinv = 2 - mod; // pow(-mod, -1, 2**32)
    inline int32_t m_reduce(long long x) {
        int32_t m = x * modinv;
        return (x>>32) - (((long long) m * mod) >> 32);
    }

    const int32_t r2 = modpow(2, 64);
    inline int32_t m_transform(int32_t x) {
        return m_reduce((long long)x * r2);
    }

    inline int32_t m_add(int32_t x, int32_t y) {
        int32_t z = x + y;
        if(z >= mod) z -= mod;
        else if(z < 0) z += mod;
        return z;
    }

    inline int32_t m_sub(int32_t x, int32_t y) {
        int32_t z = x - y;
        if(z >= mod) z -= mod;
        else if(z < 0) z += mod;
        return z;
    }

    inline int32_t m_mult(int32_t x, int32_t y) {
        return m_reduce((long long) x * y);
    }

    vector<int32_t> rt = {1};
    vector<int32_t> transformed_rt;
    vector<int32_t> transformed_rt2;

    template<int32_t a>
    void transform(vector<int32_t> &P) {
        int32_t m = P.size();
        int32_t n = m / a;
        int32_t size = rt.size();
        while(2 * size < n) {
            rt.resize(n / 2);
            int32_t r = modpow(proot, mod / (4 * size));
            for(int32_t i = 0; i < size; ++i) rt[i + size] = (long long) r * rt[i] % mod;
            size *= 2;
        }
        // For montgomery
        for(int32_t i = transformed_rt.size(); i < rt.size(); ++i) {
            transformed_rt.resize(rt.size());
            transformed_rt[i] = m_transform(rt[i]);
            transformed_rt2.resize(rt.size());
            transformed_rt2[i] = (unsigned int32_t) modinv * transformed_rt[i];
        }
        // Radix 4 recursive NTT
        auto dfs = [&](auto &&self, int32_t i, int32_t k) -> void {
            if(k == 1) return;
            int32_t step = k * a;
            int32_t quarter_step = step / 4;
            int32_t R20 = transformed_rt2[2 * i];
            int32_t RR0 = transformed_rt[2 * i];
            int32_t R21 = transformed_rt2[2 * i + 1];
            int32_t RR1 = transformed_rt[2 * i + 1];
            int32_t R2 = transformed_rt2[i];
            int32_t RR = transformed_rt[i];
            int32_t *P1 = &P[i * step];
            int32_t *P2 = P1 + quarter_step;
            int32_t *P3 = P2 + quarter_step;
            int32_t *P4 = P3 + quarter_step;
            for(int32_t j = 0; j < quarter_step; ++j) {
                int32_t z0;
                {
                    int32_t z = P3[j];
                    int32_t m = (unsigned int) R2 * z;
                    z0 = ((long long) z * RR - (long long) m * mod) >> 32;
                }
                int32_t z1;
                {
                    int32_t z = P4[j];
                    int32_t m = (unsigned int) R2 * z;
                    z1 = ((long long) z * RR - (long long) m * mod) >> 32;
                }
                int32_t sum0 = m_add(P1[j], z0);
                int32_t diff0 = m_sub(P1[j], z0);
                int32_t sum1 = P2[j] + z1;
                int32_t diff1 = P2[j] - z1;
                // [sum0, sum1, diff0, diff1]
                int32_t zz0;
                {
                    int32_t z = sum1;
                    int32_t m = (unsigned int) R20 * z;
                    zz0 = ((long long) z * RR0 - (long long) m * mod) >> 32;
                }
                int32_t zz1;
                {
                    int32_t z = diff1;
                    int32_t m = (unsigned int) R21 * z;
                    zz1 = ((long long) z * RR1 - (long long) m * mod) >> 32;
                }
                P1[j]  = m_add(sum0, zz0);
                P2[j]  = m_sub(sum0, zz0);
                P3[j]  = m_add(diff0, zz1);
                P4[j]  = m_sub(diff0, zz1);
            }
            self(self, 4*i, k/4);
            self(self, 4*i+1, k/4);
            self(self, 4*i+2, k/4);
            self(self, 4*i+3, k/4);
        };
        int32_t k = n;
        while (k >= 4) k /= 4;
        if(k == 2) {
            int32_t step = n * a;
            int32_t half_step = step / 2;
            for(int32_t j1 = 0; j1 < half_step; ++j1) {
                int32_t j2 = j1 + half_step;
                int32_t diff = m_sub(P[j1], P[j2]);
                P[j1] = m_add(P[j1], P[j2]);
                P[j2] = diff;
            }
            k = n/2;
            dfs(dfs, 0, k);
            dfs(dfs, 1, k);
        } else {
            k = n;
            dfs(dfs, 0, k);
        }
        for(int32_t i = 0; i < m; ++i) if(P[i] < 0) P[i] += mod;
    }

    template<int32_t a>
    void inverse_transform(vector<int32_t> &P) {
        int32_t m = P.size();
        int32_t n = m / a;
        int32_t n_inv = m_transform(modpow(n, mod - 2));
        vector<int32_t> rev(n);
        for(int32_t i = 1; i < n; ++i) {
            rev[i] = rev[i / 2] / 2 + (i & 1) * n / 2;
        }
        // P = [p * n_inv for p in P]
        for(int32_t i = 0; i < m; ++i) P[i] = m_mult(n_inv, P[i]);
        // P = [P[a * rev[i // a] + (i % a)] for i in range(m)]
        for(int32_t i = 1; i < n; ++i) {
            if(i < rev[i]) {
                swap_ranges(P.begin() + a * i, P.begin() + a * i + a, P.begin() + a * rev[i]);
            }
        }
        // P = [P[-a * (i // a) + (i % a)] for i in range(m)]
        for(int32_t i = 1; i < n/2; ++i) swap_ranges(P.begin() + a * i, P.begin() + a * i + a, P.begin() + a * (n - i));
        transform<a>(P);
        // P = [P[a * rev[i // a] + (i % a)] for i in range(m)]
        for(int32_t i = 1; i < n; ++i) {
            if(i < rev[i]) {
                swap_ranges(P.begin() + a * i, P.begin() + a * i + a, P.begin() + a * rev[i]);
            }
        }
    }

    template<int32_t a>
    void fast_polymult_mod(vector<int32_t> &P, vector<int32_t> &Q) {
        int32_t m = P.size();
        int32_t n = m / a;
        transform<a>(P);
        transform<a>(Q);
        vector<int32_t> &PQ = P;
        for(int32_t i = 0; i < n; ++i) {
            vector<unsigned long long> res(2 * a);
            for(int32_t j = 0; j < a; ++j) {
                if(j >= 9 && j % 8 == 7) {
                    for(int32_t k = j; k < j + a - 9; ++k) res[k] -= (res[k] >> 63) * 9 * mod2;
                }
                for(int32_t k = 0; k < a; ++k) res[j + k] += (long long) P[i * a + j] * Q[i * a + k];
            }
            int32_t c = rt[i/2];
            if(i & 1) c = mod - c;
            for(int32_t j = 0; j < a; ++j) PQ[i * a + j] = (res[j] + c * (res[j + a] % mod)) % mod;
        }
        inverse_transform<a>(PQ);
    }

    template <size_t... N>
    void work(std::index_sequence<N...>, int32_t x, std::vector<int32_t>& a, std::vector<int32_t>& b) {
        static void (*ptrs[])(std::vector<int32_t>&, std::vector<int32_t>&) = {&fast_polymult_mod<N+1>...};
        ptrs[x - 1](a, b);
    }

    /// Computes a(x) * b(x)
    /// O(n log n), 151 ms for n = 5e5
    vector<Mint> multiply(const vector<Mint> &A, const vector<Mint> &B, int32_t M = -1) {
        int32_t m1 = A.size();
        int32_t m2 = B.size();
        vector<int32_t> P(m1), Q(m2);
        for(int32_t i = 0; i < m1; i++) P[i] = A[i].x;
        for(int32_t i = 0; i < m2; i++) Q[i] = B[i].x;
        int32_t res_len = m1 + m2 - 1;
        int32_t b = 1;
        while ((alim << b) < res_len) ++b;
        int32_t a = ((res_len - 1) >> b) + 1;
        int32_t m = a << b;
        P.resize(m);
        Q.resize(m);
        // Call fast_polymult_mod<a>(P, Q);
        work(std::make_index_sequence<alim>{}, a, P, Q);
        if(~M) res_len = M;
        P.resize(res_len);
        vector<Mint> C(res_len);
        for(int32_t i = 0; i < res_len; i++) C[i] = P[i];
        return C;
    }

    /// Computes 1 / a(x) or returns an empty vector if it does not exist
    ///O(n log n), 183 ms for n = 5e5
    vector<Mint> inverse(const vector<Mint> &a, int m = -1) {
        if(a[0] == 0) return {};
        int n = a.size();
        if(~m) n = m;
        int siz = 1;
        while(siz < n) siz <<= 1;
        vector<Mint> c(1, 1 / a[0]);
        for(int len = 2; len <= siz; len <<= 1) {
            vector<Mint> c_squared = multiply(c, c); c.resize(len);
            vector<Mint> f(a.begin(), a.begin() + min(len, (int) a.size())); if(f.size() < len) f.resize(len);
            c_squared = multiply(c_squared, f); c_squared.resize(len);
            c = sub(multiply(c, 2), c_squared);
        }
        c.resize(n);
        return c;
    }

    /// Computes log(a(x)) or returns an empty vector if it does not exist
    /// O(n log n), 223 ms for n = 5e5
    vector<Mint> log(const vector<Mint> &a, int m = -1) {
        if(a[0] != 1) return {};
        int n = a.size();
        if(~m) n = m;
        vector<Mint> c = integral(multiply(derivative(a, n), inverse(a, n))); c.resize(n);
        return c;
    }

    /// Computes e^a(x) or returns an empty vector if it does not exist
    /// O(n log n), 416 ms for n = 5e5
    vector<Mint> exp(const vector<Mint> &a, int m = -1) {
        if(a[0] != 0) return {};
        int n = a.size();
        if(~m) n = m;
        int siz = 1;
        while(siz < n) siz <<= 1;
        vector<Mint> c(1, 1);
        for(int len = 2; len <= siz; len <<= 1) {
            vector<Mint> f(a.begin(), a.begin() + min(len, (int) a.size())); if(f.size() < len) f.resize(len); f[0] += 1;
            f = sub(f, log(c, len));
            c = multiply(c, f); c.resize(len);
        }
        c.resize(n);
        return c;
    }

    vector<Mint> pow_no_leading_zeros(const vector<Mint> &a, long long k, int m = -1) {
        assert(a[0] != 0);
        int n = a.size();
        if(~m) n = m;
        Mint d = 1 / a[0];
        vector<Mint> b = a;
        for(auto &i : b) i *= d;
        vector<Mint> c = exp(multiply(log(b, n), k % mod), n);
        d = (1 / d).bpow(k);
        for(auto &i : c) i *= d;
        return c;
    }

    /// Computes a(x)^k
    /// O(n log n), 577 ms for n = 5e5
    vector<Mint> pow(const vector<Mint> &a, long long k, int m = -1) {
        int n = a.size();
        if(~m) n = m;
        if(k == 0) {
            vector<Mint> c(n); c[0] = 1;
            return c;
        }
        int cnt_leading_zeros = 0;
        while(cnt_leading_zeros < a.size() && a[cnt_leading_zeros] == 0) cnt_leading_zeros++;
        if(cnt_leading_zeros == a.size() || (__int128) k * cnt_leading_zeros > n) return vector<Mint>(n, 0);
        vector<Mint> b(a.size() - cnt_leading_zeros);
        for(int i = cnt_leading_zeros; i < a.size(); i++) b[i - cnt_leading_zeros] = a[i];
        vector<Mint> c = pow_no_leading_zeros(b, k, n - cnt_leading_zeros * k);
        cnt_leading_zeros *= k;
        reverse(c.begin(), c.end()); while(cnt_leading_zeros--) c.push_back(0); reverse(c.begin(), c.end()); c.resize(n);
        return c;
    }

    vector<Mint> root_no_leading_zeros(const vector<Mint> &a, long long k, int m = -1) {
        assert(a[0] != 0);
        int n = a.size();
        if(~m) n = m;
        Mint d = 1 / a[0];
        vector<Mint> b = a;
        for(auto &i : b) i *= d;
        vector<Mint> c = exp(multiply(log(b, n), Mint(k).inv()), n);
        d = d.inv();
        int new_root = d.root(k);
        if(!~new_root) return vector<Mint>(0);
        d = new_root;
        for(auto &i : c) i *= d;
        return c;
    }

    /// Computes b(x) s.t. b(x)^k = a(x) or returns an empty vector if it does not exist
    /// O(sqrt(mod) + n log n), 586 ms for n = 5e5
    vector<Mint> root(const vector<Mint> &a, long long k, int m = -1) {
        assert(k != 0);
        int n = a.size();
        if(~m) n = m;
        int cnt_leading_zeros = 0;
        while(cnt_leading_zeros < a.size() && a[cnt_leading_zeros] == 0) cnt_leading_zeros++;
        if(cnt_leading_zeros == a.size()) return vector<Mint>(n, 0);
        if(cnt_leading_zeros % k != 0) return vector<Mint>(0);
        vector<Mint> b(a.size() - cnt_leading_zeros);
        for(int i = cnt_leading_zeros; i < a.size(); i++) b[i - cnt_leading_zeros] = a[i];
        vector<Mint> c = root_no_leading_zeros(b, k, n - cnt_leading_zeros / k);
        if(c.empty()) return c;
        cnt_leading_zeros /= k;
        reverse(c.begin(), c.end()); while(cnt_leading_zeros--) c.push_back(0); reverse(c.begin(), c.end()); c.resize(n);
        return c;
    }

    /// Computes the coefficients of a(x + C)
    /// O(n log n), 120 ms for n = 5e5
    vector<Mint> taylor_shift(const vector<Mint> &a, Mint C) {
        int n = a.size();
        vector<Mint> c = a; c = ogf(c); reverse(c.begin(), c.end());
        vector<Mint> d(n);
        Mint pw = 1;
        for(int i = 0; i < n; i++) d[i] = pw, pw *= C;
        d = egf(d);
        c = multiply(c, d, n); reverse(c.begin(), c.end()); c = egf(c);
        return c;
    }
}

void solve() {

}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ttt = 1;
    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
