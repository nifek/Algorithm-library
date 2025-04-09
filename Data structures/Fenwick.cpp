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

struct fenwick {
    int N;
    vector<ll> f;

    fenwick(int n): N(n + 42), f(n + 42) {}

    void update(int p, int x) {
        p += 5;
        for(; p < N; p += p & -p) f[p] += x;
    }

    ll get(int p) {
        p += 5;
        ll ans = 0;
        for(; p; p -= p & -p) ans += f[p];
        return ans;
    }

    ll get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &i : a) {
        cin >> i;
    }
    fenwick f(n);
    for(int i = 0; i < n; i++) f.update(i, a[i]);
    while(q--) {
        int t;
        cin >> t;
        if(t == 0) {
            int i, x;
            cin >> i >> x;
            f.update(i, x);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << f.get(l, r - 1) << '\n';
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
