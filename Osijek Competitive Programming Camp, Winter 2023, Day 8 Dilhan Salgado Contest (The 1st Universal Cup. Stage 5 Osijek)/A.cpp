#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 100;
const int mod = 998244353;
#define pb push_back
#define ll long long
const int lg = 25;
void add(int &x, int y){
    x += y;
    if(x >= mod)x -= mod;
}
int BIT(int a,int j){
    return (a >> j)&1;
}
int o[N][4],x[N][4],a[N][4];
vector<int> g[N];
int val[N];
int j,t;
int of,xf,af;
void dfs(int v, int pr){
    for(int tt = 0;tt < 4;tt++)o[v][tt]=x[v][tt]=a[v][tt]=0;
    int m = BIT(val[v], j) + (BIT(val[v], t) << 1);
    o[v][m] = x[v][m] = a[v][m] = 1;
    if((pr != -1) && ((int)g[v].size()==1)){
        return;
    }
    for(int to: g[v]){
        if(to == pr)continue;
        dfs(to, v);
    }
    for(int to: g[v]){
        if(to == pr)continue;
        for(int tt = 0;tt < 4;tt++){
            add(xf, (x[v][tt] * 1ll * x[to][3 ^ tt]) % mod);
            int sm = 0;
            for(int p = 1;p >= 1-BIT(tt,0);p--){
                for(int s=1;s>=1-BIT(tt,1);s--){
                    add(sm, o[to][p+(s<<1)]);
                }
            }
            add(of, (sm * 1ll * o[v][tt]) % mod);
        }
        add(af, (a[v][3] * 1ll * a[to][3]) % mod);

        for(int tt = 0;tt < 4;tt++){
            add(x[v][tt^m], x[to][tt]);
            add(o[v][tt|m], o[to][tt]);
            add(a[v][tt&m], a[to][tt]);
        }
    }
}
void calc(int v, int pr){
    for(int tt = 0;tt < 2;tt++)o[v][tt]=x[v][tt]=a[v][tt]=0;
    int m = BIT(val[v], j);
    o[v][m] = x[v][m] = a[v][m] = 1;
    if((pr != -1) && ((int)g[v].size()==1)){
        return;
    }
    for(int to: g[v]){
        if(to == pr)continue;
        calc(to, v);
    }
    for(int to: g[v]){
        if(to == pr)continue;
        for(int tt = 0;tt < 2;tt++){
            add(xf, (x[v][tt] * 1ll * x[to][1 ^ tt]) % mod);
            int sm = 0;
            for(int p = 1;p >= 1-BIT(tt,0);p--){
                add(sm, o[to][p]);
            }
            add(of, (sm * 1ll * o[v][tt]) % mod);
        }
        add(af, (a[v][1] * 1ll * a[to][1]) % mod);

        for(int tt = 0;tt < 2;tt++){
            add(x[v][tt^m], x[to][tt]);
            add(o[v][tt|m], o[to][tt]);
            add(a[v][tt&m], a[to][tt]);
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("in", "r", stdin);
    //freopen("out", "w", stdout);
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++)cin >> val[i];
    for(int i = 1;i < n;++i){
        int u,v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    int so = 0,sa = 0,sx = 0;
    int ro = 0,ra = 0,rx = 0;
    for(t = 0;t < lg;t++){
        for(j = 0;j < t;j++){
            of = 0;
            xf = 0;
            af = 0;
            dfs(1, -1);
            add(of, of);
            add(xf, xf);
            add(af, af);

            for(int v = 1;v <= n;v++){
                if(BIT(val[v], j) && BIT(val[v], t)){
                    add(of, 1);
                    add(xf, 1);
                    add(af, 1);
                }
            }

            int vt = (1ll << (t + j)) % mod;
            add(ro, (of * 1ll * vt) % mod);
            add(ra, (af * 1ll * vt) % mod);
            add(rx, (xf * 1ll * vt) % mod) ;
        }
    }
    add(ro, ro);
    add(ra, ra);
    add(rx, rx);
    for(j = 0;j < lg;j++){

        int vt = (1ll << (j + j)) % mod;
        of = xf = af = 0;
        calc(1, -1);
        add(of, of);
        add(xf, xf);
        add(af, af);
        for(int v = 1;v <= n;v++){
            if(BIT(val[v], j)){
                add(of, 1);
                add(xf, 1);
                add(af, 1);
            }
        }


        add(sa, (vt * 1ll * af) % mod);
        add(so, (vt * 1ll * of) % mod);
        add(sx, (vt * 1ll * xf) % mod);
    }
    add(ro, so);
    add(ra, sa);
    add(rx, sx);
    cout << ra << ' ' << ro << ' ' << rx;
    return 0;
}

