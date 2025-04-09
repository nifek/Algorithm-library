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

struct fast_bitset {
    int n, m;
    vector<ull> bits;

    fast_bitset(int N = 0) {
        n = N + 63 >> 6;
        m = N;
        bits.assign(n, 0);
    }

    void clear() {
        n = m = 0;
        bits.clear();
    }

    void reset() {
        fill(all(bits), 0);
    }

    void clean() {
        if(m != (n << 6)) bits.back() &= (1ull << (m - (n - 1 << 6))) - 1;
    }

    void set(const int &idx, const bool &val) {
        bits[idx >> 6] |= 1ull << (idx & 63);
        bits[idx >> 6] ^= ull(val ^ 1) << (idx & 63);
    }

    bool operator [](int idx) const {
        return bits[idx >> 6] >> (idx & 63) & 1;
    }

    void or_shift(int shift) {
        int div = shift >> 6, mod = shift & 63;
        if (!mod) {
            for (int i = n - 1; i >= div; i--) bits[i] |= bits[i - div];
            return;
        }
        for (int64_t i = n - 1; i >= div + 1; i--) bits[i] |= bits[i - (div + 1)] >> (64 - mod) | bits[i - div] << mod;
        if (div < n) bits[div] |= bits[0] << mod;
        clean();
    }

    friend ostream &operator << (ostream &out, const fast_bitset &bs) {
        for(int i = 0; i < bs.m; i++) out << bs[i];
        return out;
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
