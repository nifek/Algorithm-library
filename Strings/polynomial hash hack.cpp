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
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;

ll mod = 998244353;
ll base = 1e6 + 9;
const ll inf = 1e18;
const int MAX = 2e5 + 42;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ll> dis(1, inf);

ull next(ull &seed) {
    ull z = (seed += ull(0x9E3779B97F4A7C15));
    z = (z ^ (z >> 30)) * ull(0xBF58476D1CE4E5B9);
    z = (z ^ (z >> 27)) * ull(0x94D049BB133111EB);
    return z ^ (z >> 31);
}

ull next(ull &seed, int n) {
    return next(seed) % n;
}

ull next(ull &seed, int l, int r) {
    return l + next(seed, r - l);
}

/*
fast multiplication of a and b (longs) under modulo mod (global variable above!)
uses https://github.com/kth-competitive-programming/kactl/blob/main/doc/modmul-proof.md
works when 0 <= a b mod < 2 ^ 63
*/
///!!!a and be have to be < mod!!!
int mult_long(int a, int b) {
    ll ans = a * b - mod * ll(ld(a) * b / mod);
    if(ans < 0) ans += mod;
    if(ans >= mod) ans -= mod;
    return ans;
}

//computes all the basic operations modulo mod (global!)
int mult(int a, int b) {
    return (ll) a * b % mod;
}

void adds(int &a, int b) {
    a += b;
    if(a >= mod) a -= mod;
}

ll add(int a, int b) {
    a += b;
    if(a >= mod) a -= mod;
    return a;
}

void subs(int &a, int b) {
    a -= b;
    if(a < 0) a += mod;
}

ll sub(int a, int b) {
    a -= b;
    if(a < 0) a += mod;
    return a;
}

//mod - int
///!p < m!
int compute_small_hash(const vector<int> &a) {
    int ans = 0;
    int power = 1;
    for(int i = 0; i < (int) a.size(); i++) {
        adds(ans, mult(power, a[i]));
        power = mult(power, base);
    }
    return ans;
}

//mod - long
///!p < m!
ll compute_big_hash(const vector<int> &a) {
    int ans = 0;
    int power = 1;
    for(int i = 0; i < (int) a.size(); i++) {
        adds(ans, mult_long(power, a[i]));
        power = mult_long(power, base);
    }
    return ans;
}

ll compute_overflow_hash(const vector<int> &a) {
    ll ans = 0;
    ll power = 1;
    for(int i = 0; i < (int) a.size(); i++) {
        ans += power * a[i];
        power *= base;
    }
    return ans;
}

ll compute_hash(const vector<ll> &a) {
    if(mod == 0) return compute_overflow_hash(a);
    return (mod < (1ll << 31)? compute_small_hash(a) : compute_big_hash(a));
}

pair<vector<int>, vector<int>> Thue_Morse() {
    int n = 1 << 10;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        a[i] = __builtin_popcount(i) & 1;
        b[i] = 1 - a[i];
    }
    return {a, b};
}

pair<vector<int>, vector<int>> tree_attack(const vector<int> &alp, int p, int m) {
    int A = alp.size();
    base = p; mod = m;
    for(int k = 2;; k++) {
        int n = 1 << k;
        cout << "TRYING LEN " << n << endl;
        vector<int> F(n), S(n);
        for(int i = 0; i < n; i++) {
            F[i] = dis(gen) % A;
            S[i] = dis(gen) % A;
            if(F[i] == S[i]) S[i]++;
            if(S[i] == A) S[i] = 0;
        }
        vector<pii> a(n);
        int pw = 1;
        for(int i = 0; i < n; i++) {
            int val = alp[F[i]] - alp[S[i]];
            if(val < 0) val += mod;
            a[i] = {mult_long(pw, val), i};
            pw = mult_long(pw, base);
        }
        vector<int> c(n, 1);
        vector<vector<int>> vert(n);
        for(int i = 0; i < n; i++) vert[i] = {i};
        while(1) {
            sort(all(a));
            if(a[0].first == 0) {
                int idx = a[0].second;
                vector<int> ans(n);
                for(auto i : vert[idx]) {
                    ans[i] = c[i];
                }
                vector<int> s(n), t(n);
                for(int i = 0; i < n; i++) {
                    if(ans[i] == 1) s[i] = alp[F[i]], t[i] = alp[S[i]];
                    else if(ans[i] == -1) s[i] = alp[S[i]], t[i] = alp[F[i]];
                    else s[i] = t[i] = alp[F[i]];
                }
                return {s, t};
            }
            if((int) a.size() == 1) break;
            vector<pii> na;
            int N = (int) a.size();
            for(int i = 0; i < N; i += 2) {
                int x = a[i].second;
                int y = a[i + 1].second;
                for(auto j : vert[x]) c[j] *= -1;
                for(auto j : vert[x]) vert[y].push_back(j);
                na.push_back({a[i + 1].first - a[i].first, y});
            }
            a = na;
        }
    }
}

/*
26 2
27 1000000007
27 1000000000000000003
*/

vector<int> get_array(ull &seed, int n, const vector<int> &alp) {
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = alp[next(seed, alp.size())];
    }
    return a;
}

void get_next(ull &seed, int n, const vector<int> &alp) {
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = alp[next(seed, alp.size())];
    }
    seed = compute_hash(a);
}

//finds 2 arrays of the same size with the same hash using birthday paradox
pair<vector<int>, vector<int>> birthday_attack(const vector<int> &alp, int p, int m) {
    for(auto i : alp) assert(i < m || m == 0);
    int A = alp.size();
    base = p; mod = m;
    //computes sz such that we can safely guarantee a lot of collisions
    //if works too slowly you can adjust constant factor
    //also if sz is too small and you use bad randomization there is a good chance that you just find 2 same strings
    int sz = (m != 0? 1.2 * log(mod) / log(A) : 18); umax(sz, 5ll);
    cerr << "USING SIZE = " << sz << endl;
    int COUNT = 0;
    for(int it = 1;; it++) {
        ull x = it, y = it;
        while(1) {
            COUNT++;
            get_next(x, sz, alp); get_next(x, sz, alp);
            get_next(y, sz, alp);
            if(COUNT % 1000000 == 0) cout << "FINISHED " << COUNT << " ITERATIONS" << endl;
            if(x == y) break;
        }
        if(y == it) {
            cerr << "FAILED ITERATION " << it << endl;
            continue;
        }
        cerr << "FOUND AFTER " << COUNT << " ITERATIONS" << endl;
        x = it;
        ull p, q;
        while(x != y) {
            p = x, get_next(x, sz, alp);
            q = y, get_next(y, sz, alp);
        }
        assert(p != q);
        vector<int> a = get_array(p, sz, alp);
        vector<int> b = get_array(q, sz, alp);
        return {a, b};
    }
}

pair<vector<int>, vector<int>> birthday_attack(int A, int p, int m) {
    vector<int> a;
    for(int i = 0; i < A; i++) a.push_back(i);
    return birthday_attack(a, p, m);
}

pair<vector<int>, vector<int>> hack_single_hash(const vector<int> &a, int p, int m) {
    if(m == 0 && 0) return Thue_Morse();
    else if((ld) m <= 1e13) return birthday_attack(a, p, m);
    else return tree_attack(a, p, m);
}

pair<vector<int>, vector<int>> hack_single_hash(int A, int p, int m) {
    vector<int> a;
    for(int i = 0; i < A; i++) a.push_back(i);
    return hack_single_hash(a, p, m);
}

pair<vector<int>, vector<int>> hack_multiple_modulos(const vector<int> &a, const vector<int> &p, const vector<int> &modulos) {
    auto [s, t] = hack_single_hash(a, p[0], modulos[0]);
    int N = p.size();
    assert(N == modulos.size());
    for(int i = 1; i < N; i++) {
        base = p[i]; mod = modulos[i];
        int h1 = compute_hash(s);
        int h2 = compute_hash(t);
        if(h1 == h2) continue;
        base = 1; for(int j = 0; j < s.size(); j++) base = mult_long(base, p[i]);
        vector<int> b = {h1, h2};
        auto [x, y] = hack_single_hash(b, base, mod);
        vector<int> new_s, new_t;
        for(auto i : x) {
            if(i == h1) new_s.insert(new_s.end(), all(s));
            else new_s.insert(new_s.end(), all(t));
        }
        for(auto i : y) {
            if(i == h1) new_t.insert(new_t.end(), all(s));
            else new_t.insert(new_t.end(), all(t));
        }
        s = new_s; t = new_t;
    }
    return {s, t};
}

pair<vector<int>, vector<int>> hack_multiple_modulos(int A, int p, const vector<int> &modulos) {
    vector<int> a;
    for(int i = 0; i < A; i++) a.push_back(i);
    vector<int> b;
    for(int i = 0; i < modulos.size(); i++) b.push_back(p);
    return hack_multiple_modulos(a, b, modulos);
}

pair<vector<int>, vector<int>> hack_multiple_modulos(int A, const vector<int> &p, const vector<int> &modulos) {
    vector<int> a;
    for(int i = 0; i < A; i++) a.push_back(i);
    return hack_multiple_modulos(a, p, modulos);
}

string get_string(const vector<int> &a) {
    string ans;
    for(auto i : a) ans.push_back(char('a' + i));
    return ans;
}

void solve() {
    int A;
    cin >> A;
    int n;
    cin >> n;
    vector<int> p(n), modulos(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i] >> modulos[i];
    }
    auto [a, b] = hack_multiple_modulos(A, p, modulos);
    string s = get_string(a), t = get_string(b);
    assert(s != t);
//    reverse(all(s));
//    reverse(all(t));
    cout << s << '\n'; cout << t << '\n';
    for(int i = 0; i < n; i++) {
        base = p[i]; mod = modulos[i];
        assert(compute_hash(a) == compute_hash(b));
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ttt = 1;
//    cin >> ttt;
    while(ttt--) {
        solve();
    }
}
