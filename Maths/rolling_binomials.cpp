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

#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int) (x).size())
#define pb push_back
#define mp make_pair
#define int long long

using namespace std;
using namespace __gnu_pbds;

template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> inline bool umin(T &a, const T &b) { if(a > b) { a = b; return 1; } return 0; }
template <typename T> inline bool umax(T &a, const T &b) { if(a < b) { a = b; return 1; } return 0; }

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll mod = 998244353;
const ll base = 1e6 + 9;
const ll inf = 1e18;
const int MAX = 2e5 + 42;
const int LG = 20;

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

constexpr int phi_minus_one = calculate_phi(mod) - 1;

class Mint {
public:
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
};

Mint fact[MAX], inv[MAX];

Mint C(int n, int k) {
    if(k == 0) return 1;
    if(n < k || k < 0) return 0;
    return fact[n] * inv[k] * inv[n - k];
}

const Mint inv_2 = mod + 1 >> 1;

class rolling_binomial {

private:
    int l, r, n;
    Mint ans = 0;

public:
    rolling_binomial(int N, int L, int R) {
        l = L;
        r = R;
        n = N;
        for(int i = l; i <= r; i++) ans += C(n, i);
    };

    void decrease_l() {
        l--;
        ans += C(n, l);
    }

    void increase_l() {
        ans -= C(n, l);
        l++;
    }

    void decrease_r() {
        ans -= C(n, r);
        r--;
    }

    void increase_r() {
        r++;
        ans += C(n, r);
    }

    void increase_n() {
        //2B(l, r, n) = C(n, l) + C(n, r) - C(n + 1, l) + B(l, r, n + 1)
        //B(l, r, n + 1) = 2B(l, r, n) - C(n, l) - C(n, r) + C(n + 1, l)
        ans = ans + ans - C(n, l) - C(n, r) + C(n + 1, l);
        n++;
    }

    void decrease_n() {
        //B(l, r, n) = (C(n, l) + C(n, r) - C(n + 1, l) + B(l, r, n + 1)) / 2
        n--;
        ans = (C(n, l) + C(n, r) - C(n + 1, l) + ans) * inv_2;
    }

    Mint set(int N, int L, int R) {
        while(n < N) increase_n();
        while(r < R) increase_r();
        while(l > L) decrease_l();
        while(l < L) increase_l();
        while(r > R) decrease_r();
        while(n > N) decrease_n();
        return ans;
    }

    Mint get() {
        return ans;
    }
};

void solve() {

}

signed main() {
    fact[0] = 1; for(int i = 1; i < MAX; i++) fact[i] = fact[i - 1] * i;
    inv[MAX - 1] = 1 / fact[MAX - 1];
    for(int i = MAX - 1; i; i--) inv[i - 1] = inv[i] * i; assert(inv[0] == 1);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ttt = 1;
    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
