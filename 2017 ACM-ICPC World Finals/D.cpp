#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;

const int MAXN = (int)5e5 + 5;

pair<ll, ll> A[MAXN], B[MAXN];
ll ans;
int n, m;

void calc(int l, int r, int optl, int optr) {
  if (l > r) return;
  int m = (l + r) / 2;
  int optm = optl;
  ll best = 0;
  for (int i = optl; i <= optr; i++) {
    if (B[i].first > A[m].first) {
      ll cur = (B[i].first - A[m].first) * (B[i].second - A[m].second);
      if (cur > best) {
        best = cur;
        optm = i;
      }
    }
  }
  ans = max(ans, best);
  calc(l, m - 1, optl, optm);
  calc(m + 1, r, optm, optr);
}

void dnc(int l, int r, int bl, int br) {
  if (l > r || bl > br) return;
  int m = (l + r) / 2;
  int bm = lower_bound(B + bl, B + br + 1, make_pair(A[m].first, 0)) - B;
  if (l <= m && bm <= br) {
    calc(l, m, bm, br);
  }
  dnc(l, m - 1, bl, bm - 1);
  dnc(m + 1, r, bm, br);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    // A[i] = {i, n - i};
    cin >> A[i].first >> A[i].second;
  }

  for (int i = 1; i <= m; i++) {
    // B[i] = {n + m - i, i};
    cin >> B[i].first >> B[i].second;
  }

  sort(A + 1, A + n + 1);
  sort(B + 1, B + m + 1, greater<>());

  int new_n = 0;
  ll mn = (ll)1e18;
  for (int i = 1; i <= n; i++) {
    if (mn <= A[i].second) {
      // skip
    } else {
      A[++new_n] = A[i];
      mn = A[i].second;
    }
  }
  n = new_n;

  int new_m = 0;
  ll mx = (ll)0;
  for (int i = 1; i <= m; i++) {
    if (mx >= B[i].second) {
      // skip
    } else {
      B[++new_m] = B[i];
      mx = B[i].second;
    }
  }
  m = new_m;

  reverse(B + 1, B + m + 1);
  dnc(1, n, 1, m);
  cout << ans << '\n';
  return 0;
}
