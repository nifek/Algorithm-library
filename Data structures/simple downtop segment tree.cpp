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

struct segtree {
    int n;
    vector<int> t;

    segtree(int N) {
        n = N;
        t = vector<int>(2 * N + 5, -inf);
    };

    void build(vector<int> &a) {
        for(int i = 0; i < n; i++) {
            t[i + n] = a[i];
        }
        for(int i = n - 1; ~i; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
    }

    void build() {
        for(int i = 0; i < n; i++) {
            t[i + n] = -inf;
        }
        for(int i = n - 1; ~i; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
    }

    void update(int i, int x) {
        i += n;
        t[i] = x;
        i >>= 1;
        while(i) {
            t[i] = max(t[i << 1], t[i << 1 | 1]);
            i >>= 1;
        }
    }

    int get(int l, int r) {
        int ans = -inf;
        l += n, r += n;
        while(l < r) {
            if(l & 1) ans = max(ans, t[l++]);
            if(r & 1) ans = max(t[--r], ans);
            l >>= 1; r >>= 1;
        }
        return ans;
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
