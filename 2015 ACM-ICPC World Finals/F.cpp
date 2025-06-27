#include <bits/stdc++.h>
#define pb push_back
#define all(v) v.begin(), v.end()
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

const int inf = 2e9;

int n, m;
char c[51][51];
// int up[51][51], down[51][51], left[51][51], right[51][51];
int ID[51][51];
pair<int, int> cell[50 * 50 + 2];
string s;

int getId(int x, int y)
{
    return ID[x][y];
}

pair<int, int> getCell(int x)
{
    return cell[x];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> c[i][j];

            ID[i][j] = i * m + j;
            cell[ID[i][j]] = {i, j};
        }
    }

    vector<int> up(n * m + 2, inf);
    vector<int> down(n * m + 2, inf);
    vector<int> left(n * m + 2, inf);
    vector<int> right(n * m + 2, inf);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int x = getId(i, j);
            up[x] = left[x] = inf;
            if (i > 0)
                up[x] = (c[i][j] == c[i - 1][j] ? up[getId(i - 1, j)] + 1 : 1);
            if (j > 0)
                left[x] = (c[i][j] == c[i][j - 1] ? left[getId(i, j - 1)] + 1 : 1);
        }
    }

    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = m - 1; j >= 0; --j)
        {
            int x = getId(i, j);
            down[x] = right[x] = inf;
            if (i < n - 1)
                down[x] = (c[i][j] == c[i + 1][j] ? down[getId(i + 1, j)] + 1 : 1);
            if (j < m - 1)
                right[x] = (c[i][j] == c[i][j + 1] ? right[getId(i, j + 1)] + 1 : 1);
        }
    }

    cin >> s;
    s += "*";

    vector<int> dp(n * m + 2, inf);

    dp[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (auto x : s)
    {
        // prf = dp;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int x = getId(i, j);
                if (dp[x] != inf)
                    pq.push({dp[x], x});
            }
        }

        while (!pq.empty())
        {
            auto [dis, id] = pq.top();
            pq.pop();

            if (dis != dp[id])
                continue;

            auto [a, b] = getCell(id);

            int id2;
            if (up[id] < inf && dp[id2 = getId(a - up[id], b)] > dp[id] + 1)
            {
                dp[id2] = dp[id] + 1;
                pq.push({dp[id2], id2});
            }

            if (down[id] < inf && dp[id2 = getId(a + down[id], b)] > dp[id] + 1)
            {
                dp[id2] = dp[id] + 1;
                pq.push({dp[id2], id2});
            }

            if (left[id] < inf && dp[id2 = getId(a, b - left[id])] > dp[id] + 1)
            {
                dp[id2] = dp[id] + 1;
                pq.push({dp[id2], id2});
            }

            if (right[id] < inf && dp[id2 = getId(a, b + right[id])] > dp[id] + 1)
            {
                dp[id2] = dp[id] + 1;
                pq.push({dp[id2], id2});
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (c[i][j] != x)
                    dp[getId(i, j)] = inf;
            }
        }
    }

    int ans = inf;
    for (int i = 0; i < n * m; ++i)
    {
        ans = min(ans, dp[i]);
    }

    cout << ans + sz(s) << "\n";

    return 0;
}
