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

struct line {
    int k, b, idx;
    line(): k(0), b(-inf), idx(0) {}
    line(int k, int b, int idx): k(k), b(b), idx(idx) {}
    int operator ()(int x) {
        return k * x + b;
    }
};

struct lichao {
    int n;
    vector<line> t;
    vector<int> x;

    lichao(const vector<int> &a) {
        n = sz(a);
        x = a; sort(all(x));
        t.resize(4 * n + 5);
    };

    void add(line seg, int v, int l, int r) {
        if(r - l == 1) {
            if(seg(x[l]) > t[v](x[l])) t[v] = seg;
            return;
        }
        int m = (l + r) / 2;
        if(seg.k < t[v].k) swap(seg, t[v]);
        if(seg(x[m]) > t[v](x[m])) {
            swap(seg, t[v]);
            add(seg, 2 * v + 1, l, m);
        }
        else {
            add(seg, 2 * v + 2, m, r);
        }
    }

    int get(int i, int v, int l, int r) {
        if(r - l == 1) return t[v](x[i]);
        int m = (l + r) / 2;
        if(i < m) {
            return max(t[v](x[i]), get(i, 2 * v + 1, l, m));
        }
        else {
            return max(t[v](x[i]), get(i, 2 * v + 2, m, r));
        }
    }

    void add(line seg) { add(seg, 0, 0, n);}

    int get(int X) { return get(lower_bound(all(x), X) - x.begin(), 0, 0, n); }
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
