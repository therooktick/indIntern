#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;
using ld = long double;

const int MAXN = (int)1e4 + 5;
const ld PI = acosl(-1.0L);

struct Sphere {
  int r{0}, x{0}, y{0}, z{0};

  ld area(ld s, ld t) {
    s = max(s, (ld)(z - r));
    t = min(t, (ld)(z + r));

    if (t <= s) {
      return 0.0L;
    }

    ld res = 0;

    res += (r * 1.0L * r - z * 1.0L * z) * (t - s);
    res -= (t * 1.0L * t * t / 3.0L) - (s * 1.0L * s * s / 3.0L);
    res += z * ((t * 1.0L * t) - (s * 1.0L * s));

    return PI * res;
  }

  ld area() {
    return area(0, 1e6);
  }
};

int n, s;
Sphere A[MAXN];

ld get_area(ld z_low, ld z_high) {
  assert(z_low <= z_high);
  ld res = (z_high - z_low) * 1e10;

  for (int i = 1; i <= n; i++) {
    res -= A[i].area(z_low, z_high);
  }

  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> s;
  cout << setprecision(9) << fixed;

  ld area = 1e15L;

  for (int i = 1; i <= n; i++) {
    cin >> A[i].r >> A[i].x >> A[i].y >> A[i].z;
    area -= A[i].area();
  }

  ld tar = area / s;
  ld z_low = 0.0;

  ld ML = 0.001L;

  for (int rep = 0; rep < s; rep++) {
    ld l = z_low, r = 1e5L;

    for (int step = 0; step < 50; step++) {
      ld m = (l + r) * 0.5L;
      if (get_area(z_low, m) >= tar) {
        r = m;
      } else {
        l = m;
      }
    }

    ld z_high = (l + r) * 0.5L;
    cout << (z_high - z_low) * ML << '\n';
    z_low = z_high;
  }

  return 0;
}
