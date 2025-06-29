#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e6 + 100;
const int mod = 998244353;
const int P = 97;
#define pb push_back
#define ll long long
int t[N];
int binpow(int a, int n){
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
int dv(int a,int b){
    int rt = a;
    rt = (rt * 1ll * binpow(b, mod - 2)) % mod;
    return rt;
}
int mul(int a, int b){
    return (a * 1ll * b) % mod;
}
int add(int a,int b){
    int rt = a + b;
    if(rt >= mod)rt -= mod;
    return rt;
}

int dp[N],inv[N],sum[N],sumq[N];
int C(int n, int k){
    int rt = t[n];
    rt = (rt * 1ll * inv[k]) % mod;
    rt = (rt * 1ll * inv[n - k]) % mod;
    return rt;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
   // freopen("in", "r", stdin);
    t[0] = 1;
    for(int i = 1;i < N;i++){
        t[i] = (t[i - 1] * 1ll * i) % mod;
    }
    inv[N - 1] = binpow(t[N - 1], mod - 2);
    for(int i = N - 2;i >= 0;i--){
        inv[i] = (inv[i + 1] * 1ll * (i + 1)) % mod;
    }
    /*
    for(int n = 1;n <= 20;n++){
        for(int k = 1;k <= n;k++){
            int v = C(n + 1, k);
            int v2 = 0;
            for(int y = 0;y <= k;y++){
                v2 = add(v2, C(n - y, k - y));
            }
           // cout << n << ' ' << k << ' ' << v << ' ' << v2 << endl;
            assert(v== v2);
        }
    }
    */
    dp[0] = 0;
    for(int i = 1;i < N;i++){
        dp[i] = dp[i - 1];
        dp[i] = add(dp[i], mul(mul(inv[i + 1], t[i]), i));
    }
    int qq;
    cin >> qq;
    while(qq--){
        int n;
        cin >> n;
        int res = dp[n];
        res = mul(res, n + 1);
        res = mul(res, mul(inv[n], t[n - 1]));
        cout << res << '\n';
    }
    return 0;
}
