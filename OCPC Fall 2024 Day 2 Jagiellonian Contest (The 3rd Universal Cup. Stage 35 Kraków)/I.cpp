#include <bits/stdc++.h>
using namespace std;
const int N = (int)3e5 + 100;
const int mod = 998244353;
const int P = 97;
#define pb push_back
#define ll long long
int a[N];
int p[N],ps[N];
ll b[N];
void add(int &x, int y){
    x += y;
    if(x >= mod){
        x -= mod;
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("in", "r", stdin);
    int qq;
    cin >> qq;
    while(qq--){
        int n;
        cin >> n;
        for(int i = 1;i <= n;i++){
            cin >> b[i];
        }
        sort(b + 1,b + 1 + n);
        for(int i = 1;i <= n;i++){
            ll x = b[i];
            a[i] = (x % mod);
            p[i] = p[i - 1];
            ps[i] = ps[i - 1];

            add(p[i], (a[i] * 2ll) % mod);
            add(ps[i], (a[i] * 1ll * a[i]) % mod);
        }
        sort(a + 1,a + 1 + n);
        int res = 0;
        for(int i = n;i >= 1;i--){
            int cur = i + 1;
            ll val = 0;
            for(int k = 1;cur <= n;k++){
                val = ((b[cur] / b[i]) * 1ll * b[i]);
                int id = -1;
                if(val > b[n]){
                    id = n + 1;
                }else{
                    id = lower_bound(b + 1 + cur, b + 1 + n, val + b[i]) - b;
                }
                int len = id - cur;
                int valm = val % mod;
                int ost = (ps[id - 1] - ps[cur - 1] + mod) % mod;


                int ot = (valm * 1ll * ((p[id - 1] - p[cur - 1] + mod) % mod)) % mod;
                ot = (mod - ot) % mod;
                add(ost, ot);
               // cout << "!! " << i << ' ' << ost << ' ' << valm << ' ' << endl;
                valm = (valm * 1ll * valm) % mod;
                add(ost, (valm * 1ll * len) % mod);

                add(res, ost);
                cur = id;
            }
            add(res, ps[i - 1]);
        }
        cout << res << '\n';
    }
    return 0;
}
