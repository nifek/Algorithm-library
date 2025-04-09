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
