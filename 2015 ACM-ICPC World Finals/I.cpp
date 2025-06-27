#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;
using ld = long double;

const int MAXN = (int)1e5 + 5;

int n, w, u, v, t1, t2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> w >> u >> v >> t1 >> t2;
  vector<pair<ld, ld>> segments;

  for (int i = 1; i <= n; i++) {
    char dir;
    cin >> dir;

    int m;
    cin >> m;

    for (int j = 1; j <= m; j++) {
      int len, pos;
      cin >> len >> pos;

      if (dir == 'E') {
        // we will flip and assume it goes 'W'
        pos = -pos;
      }

      // it's already beyond the line
      if (pos + len < 0) {
        continue;
      }

      ld isect_l = 0;
      ld isect_r = 0;

      ld p = (i - 1) * 1.0L * w / v;
      ld q = i * 1.0L * w / v;

      isect_l = pos * 1.0L / u;
      isect_r = (pos + len) * 1.0L / u;
      isect_l -= (q - p);
      isect_l -= p;
      isect_r -= p;

      // cout << "isect " << isect_l << " " << isect_r << endl;
      segments.push_back({isect_l, isect_r});
    }
  }

  cout << setprecision(9) << fixed;

  // no ships cross at all
  if (segments.empty()) {
    ld l = t1, r = t2;
    cout << (r - l) << '\n';
    return 0;
  }

  ld ans = 0.0L;

  const auto cons = [&](ld L, ld R) -> void {
    // cout << "cons " << L << ' ' << R << endl;
    L = max(L, (ld)t1);
    R = min(R, (ld)t2);
    // R = min(R - w * 1.0L * n / v, (ld)t2);
    // cout << "con2s " << L << ' ' << R << endl;
    if (L <= R) ans = max(ans, R - L);
  };

  ld lst = 0;

  sort(all(segments));
  for (auto &[l, r] : segments) {
    if (lst <= l) {
      cons(lst, l);
    }
    lst = max(lst, r);
  }

  cons(lst, t2);
  cout << ans << '\n';
  return 0;
}
