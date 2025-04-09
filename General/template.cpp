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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &i : a) {
        cin >> i;
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
