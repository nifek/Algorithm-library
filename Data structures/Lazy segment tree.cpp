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

const ll mod = 1e9 + 7;
const ll base = 1e6 + 9;
const ll inf = 1e18;
const int MAX = 3e5 + 42;
const int LG = 20;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ll> dis(1, inf);

struct node {
    ll sum = 0;
    int len = 0;
};

node combine(const node &a, const node &b) {
    if(a.len == 0) return b;
    if(b.len == 0) return a;
    node res;
    res.sum = a.sum + b.sum;
    res.len = a.len + b.len;
    return res;
}

int n;
node ntrl;
node t[4 * MAX + 5];
ll add[4 * MAX + 5];

void push(int v, int l, int r) {
    t[v].sum += add[v] * (r - l);
    if(r - l > 1) {
        add[v << 1 | 1] += add[v];
        add[(v << 1) + 2] += add[v];
    }
    add[v] = 0;
}

void build(vector<int> &a, int v = 0, int l = 0, int r = n) {
    if(r - l == 1) {
        t[v].len = 1;
        t[v].sum = a[l];
        return;
    }
    int m = l + r >> 1;
    build(a, v << 1 | 1, l, m); build(a, (v << 1) + 2, m, r);
    t[v] = combine(t[v << 1 | 1], t[(v << 1) + 2]);
}

void update(int l, int r, int x, int v = 0, int tl = 0, int tr = n) {
    push(v, tl, tr);
    if(r <= tl || tr <= l) return;
    if(l <= tl && tr <= r) {
        add[v] += x;
        push(v, tl, tr);
        return;
    }
    int tm = tl + tr >> 1;
    update(l, r, x, v << 1 | 1, tl, tm); update(l, r, x, (v << 1) + 2, tm, tr);
    t[v] = combine(t[v << 1 | 1], t[(v << 1) + 2]);
}

node get(int l, int r, int v = 0, int tl = 0, int tr = n) {
    push(v, tl, tr);
    if(r <= tl || tr <= l) return ntrl;
    if(l <= tl && tr <= r) return t[v];
    int tm = tl + tr >> 1;
    return combine(get(l, r, v << 1 | 1, tl, tm), get(l, r, (v << 1) + 2, tm, tr));
}

void solve() {
    int q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &i : a) {
        cin >> i;
    }
    build(a);
    while(q--) {
        int t;
        cin >> t;
        if(t == 0) {
            int i, x;
            cin >> i >> x;
            update(i, i + 1, x);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << get(l, r).sum << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ttt = 1;
//    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
