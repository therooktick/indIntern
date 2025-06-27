#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;

const int MAXN = (int)1e6 + 5;

struct Cycler {
  ll per, x, y;

  ll f(ll i) {
    return per * i + x;
  }

  ll g(ll i) {
    return per * i + y;
  }

  pair<ll, ll> lower_bound(ll T) {
    ll l = 0, r = (ll)1e12, res = -1;
    while (l <= r) {
      ll m = (l + r) / 2;
      if (g(m) >= T) {
        res = m;
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
    if (f(res) >= T)
      return {res, 0};
    else
      return {res, 1};
  }
};

array<ll, 4> cnt[MAXN];
ll ans[3 * MAXN];
ll A[MAXN];
int n;
ll m;

void add(ll st, ll per) {
  if (st <= m) {
    ans[st]++;
  }

  if (per > m) return;
  if (st == 0)
    cnt[per][0]++;
  else if (st == per - 1)
    cnt[per][1]++;
  else {
    assert(per % 2 == 1);
    if (st == (per - 1) / 2)
      cnt[per][2]++;
    else if (st == (per + 1) / 2)
      cnt[per][3]++;
    else
      assert(false);
  }
}

void solve() {
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }

  vector<array<ll, 3>> steps;
  fill(ans, ans + m, 0ll);

  for (int i = 1; i <= m; i++) {
    cnt[i].fill(0);
  }

  for (int i = 0; i < n; i++) {
    ll period = 2 * n - 1;
    ll x = i, y = period - i - 1;

    Cycler C;
    C.per = period;
    C.x = x;
    C.y = y;

    auto [nx, nxf] = C.lower_bound(x + A[i] + 1);
    auto [ny, nyf] = C.lower_bound(y + A[i] + 1);

    if (nxf == 0 || nx == ny) {
      // (i,0) -> (i+nx,0)
      add(0, nx);
      // steps.push_back({0, nx, nx});
      continue;
    }

    assert(nx == ny - 1);

    if (nyf == 1) {
      // (i,0) -> (i+nx,1)
      // (i,1) -> (i+ny,1)
      ans[0]++;
      add(nx, ny);
      // steps.push_back({nx, ny, ny});
      continue;
    }

    add(nx, nx + ny);
    add(0, nx + ny);
    // steps.push_back({0, nx, ny});
  }

  // for (auto &[st, j1, j2] : steps) {
  //   st = min(st, m);
  //   j1 = min(j1, m);
  //   j2 = min(j2, m);
  // }

  // for (auto [st, j1, j2] : steps) {
  //   while (st < m) {
  //     ans[st]++;
  //     st += j1;
  //     ans[st]++;
  //     st += j2;
  //   }
  // }

  for (int i = 1; i <= m; i++) {
    const auto coef = cnt[i];
    array<int, 4> offset{0, i - 1, (i - 1) / 2, (i + 1) / 2};

    for (int j = i; j <= m; j += i) {
      for (int k = 0; k < 4; k++) {
        ans[j + offset[k]] += coef[k];
      }
    }
  }

  for (int i = 0; i < m; i++) {
    cout << ans[i] << " \n"[i == m - 1];
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
