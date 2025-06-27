#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;

const int MAXN = (int)2e5 + 5;
const int INF = (int)1e9;

string s;
int n, q;
int sa[MAXN], sp[MAXN], lcp[MAXN];
int low[MAXN], high[MAXN];

namespace SufArray {

int sym[MAXN];

void build() {
  for (int i = 0; i < n; i++) {
    sym[i] = s[i] - 'a';
  }
  vector<array<int, 3>> vec;
  vec.reserve(n);
  for (int jmp = 1; jmp <= n; jmp *= 2) {
    vec.clear();

    for (int i = 0; i < n; i++) {
      int a = sym[i];
      int b = (i + jmp < n ? sym[i + jmp] : -1);
      vec.push_back({a, b, i});
    }
    sort(all(vec));
    int val = 0;

    for (int i = 0; i < n; i++) {
      if (i > 0 && (vec[i][0] != vec[i - 1][0] || vec[i][1] != vec[i - 1][1])) {
        val++;
      }
      int idx = vec[i][2];
      sym[idx] = val;
    }
  }

  vector<int> ord(n);
  iota(all(ord), 0);
  sort(all(ord), [](int a, int b) {
    return sym[a] < sym[b];
  });

  for (int i = 0; i < n; i++) {
    sa[i] = ord[i];
    sp[ord[i]] = i;
  }
}

}  // namespace SufArray

namespace Hash {
const int MOD[] = {(int)1e9 + 7, (int)1e9 + 9};
const int P[] = {31, 59};
const int K = 2;

array<int, K> hsh[MAXN];
array<int, K> pw[MAXN];

void build() {
  pw[0].fill(1);

  for (int i = 1; i < MAXN; i++) {
    for (int j = 0; j < K; j++) {
      pw[i][j] = (pw[i - 1][j] * 1ll * P[j]) % MOD[j];
    }
  }

  for (int i = 0; i < n; i++) {
    int c = s[i] - 'a' + 1;
    for (int j = 0; j < K; j++) {
      hsh[i][j] = (pw[i][j] * 1ll * c + (i > 0 ? hsh[i - 1][j] : 0)) % MOD[j];
    }
  }
}

array<int, K> get_hsh(int l, int r) {
  array<int, K> res;
  for (int i = 0; i < K; i++) {
    res[i] = (hsh[r][i] - (l > 0 ? hsh[l - 1][i] : 0) + MOD[i]) % MOD[i];
    res[i] = (res[i] * 1ll * pw[n - l][i]) % MOD[i];
  }
  return res;
}

// check s[i,i+k-1] and s[j,j+k-1]
bool eq(int i, int j, int k) {
  if (i + k > n || j + k > n) return false;
  return get_hsh(i, i + k - 1) == get_hsh(j, j + k - 1);
}

}  // namespace Hash

pair<int, int> get_seg(int sl, int sr) {
  int pos = sp[sl];
  int len = sr - sl + 1;
  int l = pos, r = pos;

  assert(sa[pos] == sl);

  for (int k = 18; k >= 0; k--) {
    int jmp = (1 << k);
    if (l >= jmp && Hash::eq(sa[l - jmp], sl, len)) l -= jmp;
    if (r + jmp < n && Hash::eq(sa[r + jmp], sl, len)) r += jmp;
  }

  return {l, r};
}

namespace ST1 {
struct Node {
  ll mx, mx2, cnt_mx, sum;
  Node() = default;
  Node(ll x) {
    mx = x;
    cnt_mx = 1;
    sum = x;
    mx2 = -1;
  }
} t[MAXN * 2];
int e[MAXN * 2];

Node comb(Node a, Node b) {
  Node res;
  res.sum = a.sum + b.sum;

  if (a.mx == b.mx) {
    res.mx = a.mx;
    res.cnt_mx = a.cnt_mx + b.cnt_mx;
    res.mx2 = max(a.mx2, b.mx2);
  } else {
    if (a.mx < b.mx) swap(a, b);
    res.mx = a.mx;
    res.cnt_mx = a.cnt_mx;
    res.mx2 = max(b.mx, a.mx2);
  }

  return res;
}

void build(int v, int tl, int tr) {
  e[v] = INF;
  if (tl == tr) {
    t[v] = Node(high[tl]);
    return;
  }
  int mid = (tl + tr) / 2;
  int c1 = v + 1, c2 = v + (mid + 1 - tl) * 2;
  build(c1, tl, mid);
  build(c2, mid + 1, tr);
  t[v] = comb(t[c1], t[c2]);
}

void push(int v, int tl, int tr) {
  if (e[v] >= t[v].mx) return;
  t[v].sum -= (t[v].mx - e[v]) * t[v].cnt_mx;
  t[v].mx = e[v];

  if (tl != tr) {
    int mid = (tl + tr) / 2;
    int c1 = v + 1, c2 = v + (mid + 1 - tl) * 2;
    e[c1] = min(e[c1], e[v]);
    e[c2] = min(e[c2], e[v]);
  }

  e[v] = INF;
}

void update(int v, int tl, int tr, int l, int r, int x) {
  push(v, tl, tr);
  if (l > r || tl > r || tr < l) return;
  if (t[v].mx <= x) return;
  if (l <= tl && tr <= r && t[v].mx2 < x) {
    e[v] = x;
    push(v, tl, tr);
    return;
  }
  int mid = (tl + tr) / 2;
  int c1 = v + 1, c2 = v + (mid + 1 - tl) * 2;
  update(c1, tl, mid, l, r, x);
  update(c2, mid + 1, tr, l, r, x);
  t[v] = comb(t[c1], t[c2]);
}

void del(int v, int tl, int tr, int pos) {
  push(v, tl, tr);
  if (tl == tr) {
    t[v] = Node(0);
    return;
  }
  int mid = (tl + tr) / 2;
  int c1 = v + 1, c2 = v + (mid + 1 - tl) * 2;
  if (pos <= mid) {
    del(c1, tl, mid, pos);
    push(c2, mid + 1, tr);
  } else {
    del(c2, mid + 1, tr, pos);
    push(c1, tl, mid);
  }
  t[v] = comb(t[c1], t[c2]);
}

int get(int v, int tl, int tr, int pos) {
  push(v, tl, tr);
  if (tl == tr) {
    return t[v].sum;
  }
  int mid = (tl + tr) / 2;
  int c1 = v + 1, c2 = v + (mid + 1 - tl) * 2;
  if (pos <= mid) {
    return get(c1, tl, mid, pos);
  } else {
    return get(c2, mid + 1, tr, pos);
  }
}

};  // namespace ST1

namespace ST2 {
struct Node {
  pair<int, int> mx;
  Node() : mx{-1, -1} {}
} t[MAXN * 2];

Node comb(Node a, Node b) {
  Node res;
  res.mx = max(a.mx, b.mx);
  return res;
}

void build(int v, int tl, int tr) {
  if (tl == tr) {
    t[v].mx = {low[tl], tl};
    return;
  }
  int mid = (tl + tr) / 2;
  int c1 = v + 1, c2 = v + (mid + 1 - tl) * 2;
  build(c1, tl, mid);
  build(c2, mid + 1, tr);
  t[v] = comb(t[c1], t[c2]);
}

void del(int v, int tl, int tr, int pos) {
  if (tl == tr) {
    t[v].mx = {-1, -1};
    return;
  }
  int mid = (tl + tr) / 2;
  int c1 = v + 1, c2 = v + (mid + 1 - tl) * 2;
  if (pos <= mid) {
    del(c1, tl, mid, pos);
  } else {
    del(c2, mid + 1, tr, pos);
  }
  t[v] = comb(t[c1], t[c2]);
}

Node query(int v, int tl, int tr, int l, int r) {
  if (l > r || tl > r || tr < l) {
    return {};
  }
  if (l <= tl && tr <= r) return t[v];
  int mid = (tl + tr) / 2;
  int c1 = v + 1, c2 = v + (mid + 1 - tl) * 2;
  return comb(query(c1, tl, mid, l, r), query(c2, mid + 1, tr, l, r));
}

};  // namespace ST2

void solve() {
  cin >> s;
  n = sz(s);
  cin >> q;

  SufArray::build();
  Hash::build();

  for (int i = 0; i + 1 < n; i++) {
    int a = sa[i], b = sa[i + 1];
    int &x = lcp[i];
    x = 0;

    if (a > b) swap(a, b);

    for (int k = 18; k >= 0; k--) {
      int jmp = (1 << k);
      if (b + jmp <= n && Hash::eq(a, b, jmp)) {
        a += jmp;
        b += jmp;
        x += jmp;
      }
    }
  }

  ll tot = 0;

  for (int i = 0; i < n; i++) {
    low[i] = (i == 0 ? 0 : lcp[i - 1]);
    high[i] = n - sa[i];
    tot += high[i];
  }

  ST1::build(1, 0, n - 1);
  ST2::build(1, 0, n - 1);

  for (int i = 1; i <= q; i++) {
    int sl, sr;
    cin >> sl >> sr;
    sl--, sr--;

    auto [l, r] = get_seg(sl, sr);
    int len = sr - sl;
    ST1::update(1, 0, n - 1, l, r, len);

    do {
      auto tmp = ST2::query(1, 0, n - 1, l, r);
      if (tmp.mx.first <= len) break;
      int pos = tmp.mx.second;
      ST2::del(1, 0, n - 1, pos);
      ST1::del(1, 0, n - 1, pos);
      tot -= low[pos];
    } while (true);

    ST1::push(1, 0, n - 1);
    ll ans = ST1::t[1].sum;

    // for (int j = 0; j < n; j++) {
    //   ans += max(low[j], ST1::get(1, 0, n - 1, j));
    // }

    cout << tot - ans << " \n"[i == q];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    solve();
  }

  return 0;
}
