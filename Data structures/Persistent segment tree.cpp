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

int n;
int sz = 0;
ll t[2 * LG * MAX + 5];
int lf[2 * LG * MAX + 5], rt[2 * LG * MAX + 5];

int build(int l = 0, int r = n) {
    if(r - l == 1) return sz;
    int m = l + r >> 1;
    int v = ++sz;
    lf[v] = build(l, m); rt[v] = build(m, r);
    t[v] = 0;
    return v;
}

int update(int i, int x, int v, int l = 0, int r = n) {
    if(r - l == 1) {
        t[++sz] = t[v] + x;
        return sz;
    }
    int m = l + r >> 1;
    int ans = ++sz;
    lf[ans] = lf[v]; rt[ans] = rt[v];
    if(i < m) lf[ans] = update(i, x, lf[ans], l, m);
    else rt[ans] = update(i, x, rt[ans], m, r);
    t[ans] = t[lf[ans]] + t[rt[ans]];
    return ans;
}

ll get(int l, int r, int v, int tl = 0, int tr = n) {
    if(r <= tl || tr <= l) return 0;
    if(l <= tl && tr <= r) return t[v];
    int tm = tl + tr >> 1;
    return get(l, r, lf[v], tl, tm) + get(l, r, rt[v], tm, tr);
}

void solve() {
    int q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &i : a) {
        cin >> i;
    }
    int root = 0;
    for(int i = 0; i < n; i++) {
        root = update(i, a[i], root);
    }
    while(q--) {
        int t;
        cin >> t;
        if(t == 0) {
            int i, x;
            cin >> i >> x;
            root = update(i, x, root);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << get(l, r, root) << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ttt = 1;
    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
