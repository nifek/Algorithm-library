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

class functional_graph {
    int n;
    vector<int> a;
    vector<vector<int>> g;
    vector<int> idx, siz, comp, root, d;
    vector<int> tin, tout;
    int timer;

public:
    functional_graph() {}

    functional_graph(const vector<int> &A) {
        n = sz(A);
        a = A; a.insert(a.begin(), 0);
        g = vector<vector<int>>(n + 1);
        idx = vector<int>(n + 1, -1);
        siz = vector<int>(n + 1);
        comp = vector<int>(n + 1);
        root = vector<int>(n + 1);
        d = vector<int>(n + 1);
        tin = vector<int>(n + 1);
        tout = vector<int>(n + 1);
        timer = 0;
        process();
    }

    void process() {
        vector<int> used(n + 1);
        int cnt_cycles = 0;
        for(int i = 1; i <= n; i++) {
            if(used[i]) continue;
            int j = i;
            vector<int> curr;
            while(!used[j]) {
                used[j] = 1;
                curr.pb(j);
                j = a[j];
            }
            int ind = 0;
            while(ind < curr.size() && curr[ind] != j) ind++;
            for(int k = ind; k < curr.size(); k++) idx[curr[k]] = k - ind;
            for(int k = ind; k < curr.size(); k++) comp[curr[k]] = cnt_cycles;
            siz[cnt_cycles++] = curr.size() - ind;
        }
        for(int i = 1; i <= n; i++) {
            if(!~idx[i]) g[a[i]].pb(i);
        }
        for(int v = 1; v <= n; v++) {
            if(~idx[v]) {
                root[v] = v;
                dfs(v);
            }
        }
    }

    void dfs(int v) {
        tin[v] = timer++;
        for(auto to : g[v]) {
            d[to] = d[v] + 1;
            root[to] = root[v];
            comp[to] = comp[v];
            dfs(to);
        }
        tout[v] = timer;
    }

    bool anc(int v, int u) {
        return (tin[v] <= tin[u] && tout[v] >= tout[u]);
    }

    int dist(int v, int u) {
        if(comp[v] != comp[u]) return inf;
        if(!~idx[v] && !~idx[u]) return (anc(u, v)? d[v] - d[u] : inf);
        if(!~idx[u]) return inf;
        int ans = 0;
        if(!~idx[v] && ~idx[u]) ans = d[v], v = root[v];
        ans += (idx[v] <= idx[u]? idx[u] - idx[v] : siz[comp[v]] - idx[v] + idx[u]);
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
