#include <bits/stdc++.h>
#define pb push_back
#define all(v) v.begin(), v.end()
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

const int N = 1005;
const ld eps = 1e-9;

ll n, t;
ll d[N], s[N];

bool check(ld c)
{
    ld sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        ld orig = s[i];
        orig += c;

        if (orig <= eps)
            return false;

        sum += ld(d[i]) / orig;
    }

    return (sum <= t + eps);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t;
    ll mn = 1001;
    for (int i = 1; i <= n; ++i)
    {
        cin >> d[i] >> s[i];
        mn = min(mn, s[i]);
    }

    ld l = -mn, r = 1e9;
    for (int step = 1; step <= 100; ++step)
    {
        ld m = (l + r) * 0.5;
        if (check(m))
            r = m;
        else
            l = m;
    }

    cout << fixed << setprecision(9) << r << "\n";

    return 0;
}
