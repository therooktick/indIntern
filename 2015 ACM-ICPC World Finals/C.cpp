#include <bits/stdc++.h>
#define pb push_back
#define all(v) v.begin(), v.end()
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

const ll inf = 2e9;

int n, k;
ll e[402][402];

ll hungarian(const vector<vector<ll>> &a)
{
    if (a.empty())
        return 0;
    int n = sz(a) + 1, m = sz(a[0]) + 1;
    vector<ll> u(n), v(m), p(m);
    for (int i = 1; i < n; ++i)
    {
        p[0] = i;
        int j0 = 0;
        vector<ll> dist(m, inf), pre(m, -1);
        vector<bool> done(m + 1);
        do
        {
            done[j0] = true;
            int i0 = p[j0], j1;
            ll delta = inf;
            for (int j = 1; j < m; ++j)
            {
                if (!done[j])
                {
                    auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < dist[j])
                        dist[j] = cur, pre[j] = j0;
                    if (dist[j] < delta)
                        delta = dist[j], j1 = j;
                }
            }
            for (int j = 0; j < m; ++j)
            {
                if (done[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);

        while (j0)
        {
            ll j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    return -v[0];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j <= n - i; ++j)
        {
            cin >> e[i][i + j];
        }
    }

    int m = n + 1;
    vector<vector<ll>> cost(m - 1, vector<ll>(m + k - 1, inf));
    for (int i = 0; i < m; ++i)
    {
        for (int j = i + 1; j < m; ++j)
        {
            cost[j - 1][i] = e[i][j];
        }
    }
    for (int i = m; i < m + k - 1; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            cost[j - 1][i] = e[0][j];
        }
    }

    ll ans = hungarian(cost);
    cout << ans << "\n";

    return 0;
}
