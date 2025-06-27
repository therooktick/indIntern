#include <bits/stdc++.h>

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())

using namespace std;
using ll = long long;

const int MAXN = 100 + 5;
const ll LINF = (ll)1e18;

namespace mcmf {
const int MAXV = 200 + 5;
const int INF = (int)1e9;

struct edge {
  int v, to, f, cap, cost;
};

vector<edge> E;
vector<int> G[MAXV];
int n;

void clear() {
  E.clear();
  for (int i = 0; i < n; i++) G[i].clear();
}

void add_edge(int u, int v, int cap, int cost) {
  E.push_back({u, v, 0, cap, cost});
  G[u].push_back(sz(E) - 1);
  E.push_back({v, u, 0, 0, cost});
  G[v].push_back(sz(E) - 1);
}

int d[MAXV], p[MAXV];
deque<int> D;

bool bfs(int src, int sink) {
  for (int i = 0; i < n; i++) {
    d[i] = INF;
  }
  D.clear();
  d[src] = 0;
  D.push_back(src);

  while (!D.empty()) {
    int v = D.front();
    D.pop_front();

    for (int id : G[v]) {
      const auto &edge = E[id];
      if (edge.f == edge.cap) continue;
      int to = edge.to;
      int w = edge.cost;
      if (d[v] + w < d[to]) {
        if (w == 0)
          D.push_front(to);
        else
          D.push_back(to);
        d[to] = d[v] + w;
        p[to] = id;
      }
    }
  }

  return d[sink] != INF;
}

int push(int src, int sink) {
  if (!bfs(src, sink)) {
    return -1;
  }
  for (int v = sink; v != src;) {
    int id = p[v];
    E[id].f++;
    E[id ^ 1].f--;
    v = E[id].v;
  }
  return d[sink];
}

};  // namespace mcmf

ll rmax[MAXN], cmax[MAXN];
ll A[MAXN][MAXN];
int n, m;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
      rmax[i] = max(rmax[i], A[i][j]);
      cmax[j] = max(cmax[j], A[i][j]);
    }
  }

  ll ans = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans += (A[i][j] > 0);
    }
  }

  for (int i = 0; i < n; i++) {
    rmax[i]--;
    if (rmax[i] > 0) ans += rmax[i];
  }
  for (int i = 0; i < m; i++) {
    cmax[i]--;
    if (cmax[i] > 0) ans += cmax[i];
  }

  set<ll> vals;
  for (int i = 0; i < n; i++) vals.insert(rmax[i]);
  for (int i = 0; i < m; i++) vals.insert(cmax[i]);

  for (ll val : vals) {
    if (val <= 0) continue;
    vector<pair<int, int>> R, C;
    for (int i = 0; i < n; i++) {
      if (rmax[i] == val) {
        int flag = 0;
        for (int j = 0; j < m; j++) {
          if (cmax[j] > val && A[i][j] > 0) {
            flag = 1;
          };
        }
        R.push_back({flag, i});
      }
    }
    for (int i = 0; i < m; i++) {
      if (cmax[i] == val) {
        int flag = 0;
        for (int j = 0; j < n; j++) {
          if (rmax[j] > val && A[j][i] > 0) {
            flag = 1;
          }
        }
        C.push_back({flag, i});
      }
    }

    int src = 0, sink = sz(R) + sz(C) + 2;
    mcmf::n = sink + 1;
    mcmf::clear();
    int cnt_important = 0;

    for (int i = 0; i < sz(R); i++) {
      cnt_important += (R[i].first == 0);
      mcmf::add_edge(src, i + 1, 1, R[i].first);
      for (int j = 0; j < sz(C); j++) {
        if (A[R[i].second][C[j].second] > 0) {
          mcmf::add_edge(i + 1, sz(R) + 1 + j, 1, 0);
        }
      }
    }
    for (int i = 0; i < sz(C); i++) {
      cnt_important += (C[i].first == 0);
      mcmf::add_edge(sz(R) + 1 + i, sink, 1, C[i].first);
    }
    int flow = 0, cost = 0;
    int best_flow = 0;
    while (true) {
      int tmp = mcmf::push(src, sink);
      if (tmp == -1) break;
      flow++;
      cost += tmp;
      int dif = 2 * flow - cost;
      best_flow = flow;
    }
    ans -= best_flow * val;
  }

  ll total_sum = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      total_sum += A[i][j];
    }
  }

  // cerr << total_sum << " " << ans << '\n';
  cout << total_sum - ans << '\n';
  return 0;
}
