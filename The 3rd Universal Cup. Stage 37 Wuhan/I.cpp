#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;

int A[55][55];

void solve() {
  int n, k;
  cin >> n >> k;

  if (k < n) {
    cout << "No\n";
    return;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      A[i][j] = 0;
    }
  }

  A[1][1] = k;

  for (int i = 2; i <= n; i++) {
    A[1][i] = i - 1;
  }

  int l = n, r = n * n;

  for (int i = 2; i <= n; i++) {
    A[i][i] = r--;
  }

  if (k < l || k > r) {
    cout << "No\n";
    return;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (!A[i][j]) {
        if (l == k) l++;
        A[i][j] = l++;
      }
    }
  }

  cout << "Yes\n";
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << A[i][j] << " \n"[j == n];
    }
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
