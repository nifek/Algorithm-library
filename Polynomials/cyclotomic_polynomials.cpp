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

///calculates n-th cyclotomic polynomial
///fits into long long when n < 169828113
vector<ll> cyclotomic(int n) {
    bool even = n & 1 ^ 1;
    int N = 1;
    int was_n = n;
    vector<int> primes;
    for(int i = 2; i <= n; i++) {
        if(n % i) continue;
        N *= i;
        if(i > 2) primes.push_back(i);
        while(n % i == 0) n /= i;
    }
    int mult = was_n / N;
    if(N & 1 ^ 1) N >>= 1;
    n = N;
    int phi = n;
    N = n;
    for(int i = 2; i <= n; i++) {
        if(n % i) continue;
        phi /= i; phi *= i - 1;
        n /= i;
    }
    n = N;
    vector<ll> ans(phi + 1); ans[0] = 1;
    int k = primes.size();
    for(int mask = 0; mask < (1 << k); mask++) {
        int p = 1;
        for(int i = 0; i < k; i++) {
            if(mask >> i & 1) p *= primes[i];
        }
        if(__builtin_popcount(mask) % 2 == k % 2) {
            for(int i = phi; i >= p; i--) ans[i] -= ans[i - p];
        }
        else {
            for(int i = p; i <= phi; i++) ans[i] += ans[i - p];
        }
    }
    if(k == 0) {
        for(int i = 0; i <= phi; i++) ans[i] = -ans[i];
    }
    if(even) {
        if(n > 1) {
            for(int i = 0; i < (int) ans.size(); i++) {
                if(i & 1) ans[i] = -ans[i];
            }
        }
        else ans[0] = ans[1] = 1;
    }
    vector<ll> nans(phi * mult + 1);
    for(int i = 0; i <= phi; i++) nans[i * mult] = ans[i];
    ans = nans;
    return ans;
}

///returns irreducible factorization of x^n - 1 if flag = 0
///otherwise returns factorization of (x^n - 1) / (x - 1)
vector<vector<int>> factorization(int n, bool flag = 0) {
    vector<vector<int>> ans;
    for(int i = 1; i <= n; i++) {
        if(n % i == 0) {
            if(i != 1 || !flag) ans.push_back(cyclotomic(i));
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    auto ans = factorization(n);
    for(auto a : ans) {
        int m = a.size();
        cout << "(";
        for(int i = m - 1; ~i; i--) {
            if(a[i] == 0) continue;
            int x = a[i];
            if(x < 0) {
                cout << "-";
                if(x != -1 || i == 0) cout << abs(x);
            }
            else {
                if(i != m - 1) cout << "+";
                if(x != 1 || i == 0) cout << x;
            }
            if(i != 0) cout << "x^" << i;
        }
        cout << ")";
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ttt = 1;
    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
