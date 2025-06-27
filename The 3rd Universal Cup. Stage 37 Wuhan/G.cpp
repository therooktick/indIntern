#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 100;
const int mod = 998244353;
const int P = 97;
//const int lg = 15;
#define pb push_back
#define ll long long
const int MAX = 2000;
int d[N];
int t[N],inv[N];
void add(int &x, int y){
    x += y;
    if(x >= mod)x -= mod;
}
int C(int n, int k){
    int rt = t[n];
    rt = (rt * 1ll * inv[k]) % mod;
    rt = (rt * 1ll * inv[n - k]) % mod;
    return rt;
}
int binpow(int a,int n){
    int rt = 1;
    while(n){
        if(n & 1){
            rt = (rt * 1ll * a) % mod;
        }
        n >>= 1;
        a = (a * 1ll * a) % mod;
    }
    return rt;
}
vector<int> a[N],dp[N];
vector<pair<int, int> > val[N];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
      //freopen("in", "r", stdin);
    t[0] = 1;
    for(int i = 1;i < N;i++){
        t[i] = (t[i - 1] * 1ll * i) % mod;
    }
    inv[N - 1] = binpow(t[N - 1], mod - 2);
    for(int i = N - 2;i >= 0;i--){
        inv[i] = (inv[i + 1] * 1ll * (i + 1)) % mod;
    }
    int qq;
    cin >> qq;
    while(qq--){
        int n,m;
        cin >> n >> m;
        for(int i = 1;i <= n;i++){
            a[i].resize(m + 1);
            dp[i].resize(m + 1);
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                cin >> a[i][j];
                val[a[i][j]].pb({i,j});
            }
        }
        int B = 0;
        while((B * B) <= (n * m))B++;
        int res = 0;
        for(int v = 1;v <= (n * m);v++){
            int s = (int)val[v].size();
            if(s > B){
                if(a[1][1] == v){
                    add(res, C(n - 1 + m - 1, n - 1));
                    continue;
                }
                dp[1][1] = 1;
                for(int i = 1;i <= n;i++){
                    for(int j = 1;j <= m;j++){
                        if((i == 1) && (j == 1))continue;
                        dp[i][j] = 0;
                        if(a[i][j] == v){
                            int skok = 0;
                            if(j > 1)add(skok, dp[i][j - 1]);
                            if(i > 1)add(skok, dp[i - 1][j]);
                            add(res, (skok * 1ll * C(n - i + m - j, m - j)) % mod);
                            continue;
                        }
                        if((i == 1) && (j == 1))continue;
                        if((i > 1) && (a[i - 1][j] != v))add(dp[i][j], dp[i - 1][j]);
                        if((j > 1) && (a[i][j - 1] != v))add(dp[i][j], dp[i][j - 1]);
                    }
                }
            }else{
                for(int i = 0;i < s;i++){
                    auto[x, y] = val[v][i];
                    int skok = C(x - 1 + y - 1, x - 1);
                    int bad = 0;
                    for(int j = 0;j < i;j++){
                        auto[xx, yy] = val[v][j];
                        if((xx > x) || (yy > y))continue;
                        add(bad, (C((x - xx) + (y - yy), (x - xx)) * 1ll * d[j]) % mod);
                    }
                    add(skok, (mod - bad) % mod);
                    d[i] = skok;
                    add(res, (d[i] * 1ll * C(n - x + m - y, n - x)) % mod);
                }
            }
        }
        cout << res << '\n';


        for(int i = 1;i <= n;i++){
            a[i].clear();
            dp[i].clear();
        }
        for(int i = 1;i <= (n * m);i++){
            val[i].clear();
        }
    }
    return 0;
}
