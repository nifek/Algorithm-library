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

int n, k;
vector<int> g[MAX], rev[MAX];
vector<int> adj[MAX];
int used[MAX];
vector<int> topological_sort;
int comp[MAX];
int siz[MAX];

void find_topsort(int v) {
    used[v] = 1;
    for(auto to : g[v]) {
        if(!used[to]) find_topsort(to);
    }
    topological_sort.push_back(v);
}

void find_SCC(int v) {
    comp[v] = k;
    siz[k]++;
    used[v] = 1;
    for(auto to : rev[v]) {
        if(!used[to]) find_SCC(to);
    }
}

void run_SCC() {
    for(int v = 0; v <= n; v++) rev[v].clear();
    for(int v = 0; v <= n; v++) adj[v].clear();
    for(int v = 1; v <= n; v++) {
        for(auto to : g[v]) {
            rev[to].push_back(v);
        }
    }
    fill(used, used + n + 1, 0);
    for(int v = 1; v <= n; v++) {
        if(!used[v]) find_topsort(v);
    }
    k = 0;
    fill(used, used + n + 1, 0);
    reverse(all(topological_sort));
    for(auto v : topological_sort) {
        if(!used[v]) {
            ++k;
            siz[k] = 0;
            find_SCC(v);
        }
    }
    topological_sort.clear();
    fill(used, used + n + 1, 0);
    map<pair<int, int>, bool> was;
    for(int v = 1; v <= n; v++) {
        for(auto to : g[v]) {
            if(comp[v] != comp[to] && !was[{comp[v], comp[to]}]) {
                was[{comp[v], comp[to]}] = 1;
                adj[comp[v]].push_back(comp[to]);
            }
        }
    }
    for(int v = 0; v <= n; v++) g[v] = adj[v];
}

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
