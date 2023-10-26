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
//#define int long long

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
const ll inf = 1e9;
const int MAX = 2e5 + 15;
const int LG = 30;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ll> dis(1, inf);

const int phi_minus_one = mod - 2;

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
             return Mint(1LL * x * b.x);
        }
        Mint operator *(int a) {
            return Mint(1LL * x * a);
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
            x = (ll) x * b.x % mod;
            return *this;
        }
        Mint& operator *=(int a) {
            x = (ll) x * a % mod;
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

const int N = 2;

vector<array<Mint, N>> mult(const vector<array<Mint, N>> &a, const vector<array<Mint, N>> &b) {
    int n = sz(a);
    vector<array<Mint, N>> ans(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < N; j++) {
            ans[i][j] = 0;
            for(int k = 0; k < N; k++) {
                ans[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return ans;
}

vector<array<Mint, N>> binpow(vector<array<Mint, N>> a, ll n) {
    auto ans = a; n--;
    while(n) {
        if(n & 1) ans = mult(ans, a);
        n >>= 1; a = mult(a, a);
    }
    return ans;
}

void solve() {

}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ttt = 1;
//    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
