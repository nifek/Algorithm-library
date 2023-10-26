#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll mod = 998244353;
const ll base = 1e6 + 9;
const ll inf = 1e18;
const int MAX = 1e7 + 5;
const int LG = 20;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ll> dis(1, inf);

int phi_minus_one = mod - 2;

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
        Mint(ll a) {
            x = a % mod;
            if(x < 0) x += mod;
        }
        friend ostream &operator <<(ostream &out, const Mint &a) { out << a.x; return out; }
        friend istream &operator >>(istream &in, Mint &a) { in >> a.x; return in; }
        Mint operator +(const Mint &b) const {
            return Mint(x + b.x, 1);
        }
        Mint operator +(int a) {
            return Mint(x + a, 1);
        }
        Mint operator -(const Mint &b) const {
            return Mint(x - b.x, 1);
        }
        Mint operator -(int a) {
            return Mint(x - a, 1);
        }
        friend Mint operator -(Mint a) {
            return Mint(mod - a);
        }
        Mint operator *(const Mint &b) const {
             return (__int128) x * b.x % mod;
        }
        Mint operator *(int a) {
            return (__int128) x * a % mod;
        }
        Mint& operator +=(const Mint &b) {
            x += b.x;
            if(x >= mod) x -= mod;
            return *this;
        }
        Mint& operator +=(int a) {
            x += a;
            if(x >= mod) x -= mod;
            return *this;
        }
        Mint& operator -=(Mint b) {
            x += mod - b.x;
            if(x >= mod) x -= mod;
            return *this;
        }
        Mint& operator -=(int a) {
            x += mod - a;
            if(x >= mod) x -= mod;
            return *this;
        }
        Mint& operator *=(Mint b) {
            x = (__int128) x * b.x % mod;
            return *this;
        }
        Mint& operator *=(int a) {
            x = (__int128) x * a % mod;
            return *this;
        }
        Mint& operator ++() {
            if(++x == mod) x = 0;
            return *this;
        }
        Mint bpow(ll n) {
            Mint a(x);
            Mint ans(1);
            while(n) {
                if(n & 1) ans *= a;
                n >>= 1;
                a *= a;
            }
            return ans;
        }
        Mint inv() {
            return bpow(phi_minus_one);
        }
        Mint operator /(Mint b) {
            return b.inv() * x;
        }
        Mint operator /(int a) {
            return Mint(a, 1).inv() * x;
        }
        friend Mint operator -(int a, Mint b) {
            Mint res(b - a);
            res.x = mod - res.x;
            if(res.x == mod) res.x = 0;
            return res;
        }
        friend Mint operator +(int a, Mint b) {
            return Mint(b + a);
        }
        friend Mint operator *(int a, Mint b) {
            return Mint(b * a);
        }
        friend Mint operator /(int a, Mint b) {
            return Mint(a, 1) * b.inv();
        }
        Mint operator =(Mint b) {
            x = b.x;
            return b;
        }
        bool operator ==(int a) {
            return (x == a);
        }
        bool operator !=(int a) {
            return !(x == a);
        }
        friend bool operator ==(int a, Mint b) {
            return (b.x == a);
        }
        friend bool operator !=(int a, Mint b) {
            return b.x != a;
        }
};

//vector<Mint> TESTERS = {2}; ///n <= 2e3
//vector<Mint> TESTERS = {2, 3}; ///n <= 1e6
//vector<Mint> TESTERS = {31, 73}; ///n <= 9e6
//vector<Mint> TESTERS = {2, 3, 5}; ///n <= 2e7
//vector<Mint> TESTERS = {2, 3, 5, 7}; ///n <= 3e9
//vector<Mint> TESTERS = {2, 7, 61}; ///n <= 4e9
//vector<Mint> TESTERS = {2, 13, 23, 1662803}; ///n <= 1e12
//vector<Mint> TESTERS = {2, 3, 5, 7, 11}; ///n <= 2e12
//vector<Mint> TESTERS = {2, 3, 5, 7, 11, 13}; ///n <= 3e12
//vector<Mint> TESTERS = {2, 3, 5, 7, 11, 13, 17}; ///n <= 3e14
vector<Mint> TESTERS = {2, 3, 5, 7, 11, 13, 17, 19, 23}; ///n <= 3e18
//vector<Mint> TESTERS = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; ///n <= 3e23
//vector<Mint> TESTERS = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41}; ///n <= 3e24
///https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test

bool prime(ll n) {
    if(n < 2) return 0;
    if(n == 2) return 1;
    if(n & 1 ^ 1) return 0;
    int s = __builtin_ctzll(n - 1);
    ll d = n - 1 >> s; mod = n;
    for(Mint a : TESTERS) {
        if(a == n) continue;
        Mint x = a.bpow(d);
        for(int it = 0; it < s; it++) {
            Mint y = x * x;
            if(y == 1 && x != 1 && x != n - 1) return 0;
            x = y;
        }
        if(x != 1) return 0;
    }
    return 1;
}

ll g(ll x, ll c) {
    return ((__int128) x * x + c) % mod;
}

ll run_Pollard_Rho(ll n) {
    if(n == 1) return 1;
    if(n & 1 ^ 1) return 2;
    ll x = dis(gen) % (n - 2) + 2;
    ll y = x;
    ll c = dis(gen) % (n - 1) + 1;
    ll d = 1;
    while(d == 1) {
        x = g(x, c);
        y = g(g(y, c), c);
        d = __gcd(abs(x - y), n);
    }
    return d;
}

ll get_factor(ll n) {
    if(prime(n)) return n;
    while(1) {
        ll c = run_Pollard_Rho(n);
        if(c != n) return c;
    }
}

vector<ll> factor(ll n) {
    if(prime(n)) return {n};
    mod = n;
    vector<ll> ans;
    while(n > 1) {
        ll f = get_factor(n); vector<ll> factorization = factor(f);
        ans.insert(ans.end(), all(factorization)); n /= f;
    }
    sort(all(ans));
    return ans;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> f = factor(n);
    cout << sz(f) << " "; for(auto i : f) cout << i << " "; cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ttt = 1;
    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
