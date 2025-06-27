#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;

int G[26][26];
int m, n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m >> n;

  for (int i = 0; i < m; i++) {
    char a, b;
    cin >> a >> b;
    G[a - 'a'][b - 'a'] = 1;
  }

  for (int i = 0; i < 26; i++) G[i][i] = 1;

  for (int k = 0; k < 26; k++) {
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
        if (G[i][k] && G[k][j]) {
          G[i][j] = 1;
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    string a, b;
    cin >> a >> b;
    if (sz(a) != sz(b)) {
      cout << "no\n";
      continue;
    }
    bool ans = true;
    for (int j = 0; j < sz(a); j++) {
      int x = a[j] - 'a', y = b[j] - 'a';
      if (!G[x][y]) ans = false;
    }
    cout << (ans ? "yes" : "no") << '\n';
  }

  return 0;
}
