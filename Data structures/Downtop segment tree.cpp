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
node t[2 * MAX + 5];

void build(vector<int> &a) {
    for(int i = 0; i < n; i++) {
        t[i + n].len = 1;
        t[i + n].sum = a[i];
    }
    for(int i = n - 1; ~i; i--) t[i] = combine(t[i << 1], t[i << 1 | 1]);
}

void build() {
    for(int i = 0; i < n; i++) {
        t[i + n].len = 1;
    }
    for(int i = n - 1; ~i; i--) t[i] = combine(t[i << 1], t[i << 1 | 1]);
}

void update(int i, int x) {
    i += n;
    t[i].sum += x;
    i >>= 1;
    while(i) {
        t[i] = combine(t[i << 1], t[i << 1 | 1]);
        i >>= 1;
    }
}

node get(int l, int r) {
    node lans = ntrl, rans = ntrl;
    l += n, r += n;
    while(l < r) {
        if(l & 1) lans = combine(lans, t[l++]);
        if(r & 1) rans = combine(t[--r], rans);
        l >>= 1; r >>= 1;
    }
    return combine(lans, rans);
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
            update(i, x);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << get(l, r).sum << '\n';
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
