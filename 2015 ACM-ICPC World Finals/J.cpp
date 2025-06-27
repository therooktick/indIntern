#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;

const int MAXN = (int)5e5 + 5;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C> &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    for (int i = k; i < 2 * k; i++) {
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
  }
  vector<int> rev(n);
  for (int i = 0; i < n; i++) {
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  }
  for (int i = 0; i < n; i++) {
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int k = 1; k < n; k *= 2) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k];
        C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
    }
  }
}
vd conv(const vd &a, const vd &b) {
  if (a.empty() || b.empty()) return {};
  vd res(sz(a) + sz(b) - 1);
  int L = 32 - __builtin_clz(sz(res)), n = (1 << L);
  vector<C> in(n), out(n);
  copy(all(a), begin(in));
  for (int i = 0; i < sz(b); i++) in[i].imag(b[i]);
  fft(in);
  for (C &x : in) x *= x;
  for (int i = 0; i < n; i++) {
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  }
  fft(out);
  for (int i = 0; i < sz(res); i++) {
    res[i] = imag(out[i]) / (4 * n);
  }
  return res;
}
vector<ll> conv(vector<ll> A, vector<ll> B) {
  vd Ap(sz(A)), Bp(sz(B));
  copy(all(A), begin(Ap));
  copy(all(B), begin(Bp));
  vd resp = conv(Ap, Bp);
  vector<ll> res(sz(resp));
  for (int i = 0; i < sz(res); i++) {
    res[i] = (ll)(resp[i] + 0.5);
  }
  return res;
}

vector<ll> R;

void pre() {
  vector<ll> A(MAXN, 0);

  for (int i = 1; i < MAXN; i++) {
    for (int j = 1; i * j < MAXN; j++) {
      A[i * j]++;
    }
  }

  R = conv(A, A);
}

int main() {
  pre();

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    int l, r;
    cin >> l >> r;
    ll mx = max_element(R.begin() + l, R.begin() + r + 1) - R.begin();
    cout << mx << " " << R[mx] << '\n';
  }

  return 0;
}
