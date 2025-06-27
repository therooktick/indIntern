#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;

const int MAXN = (int)3e3 + 5;

int A[MAXN];
int n;

void solve() {
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }

  sort(A + 1, A + n + 1);
  int ans = 1;

  for (int m = 1; m <= n; m++) {
    int tar = A[m] * 2;
    int ptr = n;

    for (int i = 1; i <= m; i++) {
      int ox = tar - A[i];

      while (ptr > m && A[ptr] > ox) {
        ptr--;
      }

      if (A[ptr] == ox) {
        int l = m - i, r = ptr - m;
        ans = max(ans, min(l, r) * 2 + 1);
        ans = max(ans, min(l + 1, r) * 2);
      }
    }
  }

  cout << ans << '\n';
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
