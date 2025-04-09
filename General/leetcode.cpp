#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int) (x).size())
#define pb push_back
#define mp make_pair

using namespace std;

template <typename T> inline bool umin(T &a, const T &b) { if(a > b) { a = b; return 1; } return 0; }
template <typename T> inline bool umax(T &a, const T &b) { if(a < b) { a = b; return 1; } return 0; }

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll mod = 1e9 + 7;
const ll base = 1e6 + 9;
const ll inf = 1e9;
const int MAX = 2e5 + 42;
const int LG = 20;
