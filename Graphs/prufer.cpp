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

vector<int> get_p(vector<int> prufer) {
    int n = prufer.size() + 2;
    vector<int> deg(n + 1, 1);
    for(auto v : prufer) deg[v]++;
    vector<int> p(n + 1);
    int ptr = 1;
    int leaf = -1;
    for(int v : prufer) {
        if(leaf == -1) {
            while(ptr <= n && deg[ptr] != 1) ptr++;
            assert(ptr <= n);
            leaf = ptr;
        }
        p[leaf] = v;
        deg[leaf]--;
        deg[p[leaf]]--;
        if(p[leaf] < ptr && deg[p[leaf]] == 1) leaf = p[leaf];
        else leaf = -1;
    }
    for(int v = 1; v < n; v++) {
        if(p[v] == 0) p[v] = n;
    }
    return p;
}

vector<int> get_prufer(vector<int> p) {
    int n = sz(p) - 1;
    int ptr = 1;
    vector<int> deg(n + 1, 1);
    for(int v = 1; v < n; v++) deg[p[v]]++;
    vector<int> prufer;
    int leaf = -1;
    for(int i = 0; i < n - 2; i++) {
        if(leaf == -1) {
            while(ptr <= n && deg[ptr] != 1) ptr++;
            assert(ptr <= n);
            leaf = ptr;
        }
        prufer.pb(p[leaf]);
        deg[leaf]--;
        deg[p[leaf]]--;
        if(p[leaf] < ptr && deg[p[leaf]] == 1) leaf = p[leaf];
        else leaf = -1;
    }
    return prufer;
}

void solve() {
    int n;
    cin >> n;
    vector<int> prufer(n - 2);
    for(int &v : prufer) {
        cin >> v;
    }
    vector<int> p = get_p(prufer);
    for(int v = 1; v < n; v++) cout << v << " " << p[v] << endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ttt = 1;
    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
