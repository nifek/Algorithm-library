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
vector<int> g[MAX];
int up[MAX][LG];
int timer = 0;
int tin[MAX], tout[MAX];

void dfs(int v, int p = 0) {
    tin[v] = timer++;
    for(auto to : g[v]) {
        if(to == p) continue;
        up[to][0] = v;
        dfs(to, v);
    }
    tout[v] = timer;
}

bool anc(int u, int v) {
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int LCA(int u, int v) {
    if(anc(u, v)) return u;
    if(anc(v, u)) return v;
    for(int l = LG - 1; ~l; l--) {
        if(!anc(up[u][l], v)) u = up[u][l];
    }
    return up[u][0];
}

void solve() {
    tout[0] = 1e9; timer = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) g[i].clear();
    for(int i = 1; i <= n; i++) g[i].shrink_to_fit();
    for(int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v); g[v].pb(u);
    }
    dfs(1);
    for(int l = 1; l < LG; l++) {
        for(int v = 1; v <= n; v++) {
            up[v][l] = up[up[v][l - 1]][l - 1];
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
