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

struct DSU {
    int n;
    vector<int> p, siz;
    int comp;

    DSU(int N) {
        n = N - 1;
        comp = 0;
        p = vector<int>(n + 1);
        siz = vector<int>(n + 1);
    };

    void create(int x) {
        p[x] = x;
        siz[x] = 1;
        comp++;
    }

    void init() {
        comp = 0;
        for(int v = 1; v <= n; v++) create(v);
    }

    int get(int x) {
        return p[x] = (p[x] == x? x : get(p[x]));
    }

    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if(x == y) return 0;
        if(siz[x] < siz[y]) swap(x, y);
        comp--;
        siz[x] += siz[y];
        p[y] = x;
        return 1;
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
