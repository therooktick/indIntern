#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e6+100;
const int M = 2005;
const int mod = (int)1e9 + 7;
const int P = 97;
const int lg = 30;
#define pb push_back
#define ll long long
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
void add(int &x, int y){
    x += y;
    if(x >= mod)x -= mod;
}
int mul(int x, int y){
    return (x * 1ll * y) % mod;
}
int deg[N],dg2[N];
int cm[M][M];
int binv[M][M];
int sinv[M];
int fact[N];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("in", "r", stdin);

    int n,m,k;
    cin >> n >> m >> k;
    if((k * 2) < m){
        cout << 0;
        return 0;
    }
    fact[0]=1;
    for(int i=1;i<N;i++)fact[i]=mul(fact[i-1],i);
    deg[0]=1;
    for(int i=1;i<N;i++){
        deg[i]=mul(deg[i-1],k);
    }
    int i2=binpow(2,mod-2);
    dg2[0]=1;
    for(int i=1;i<N;i++)dg2[i]=mul(dg2[i-1],i2);

    for(int i=1;i<=m;i++){
        sinv[i]=binpow(i,mod-2);
    }
    for(int ot=0;ot<=min(m,k);ot++){
        binv[ot][0]=1;
        for(int j=1;j<=min(k-ot,m);j++){
            binv[ot][j]=binv[ot][j-1];
            binv[ot][j]=mul(binv[ot][j],k-ot-j+1);
            binv[ot][j]=mul(sinv[j],binv[ot][j]);

          //  assert(binv[ot][j]==C(k-ot,j));
        }
    }
    int res = 0;
    int kol = 0;
    int vse = 0;
    for(int od=0;od<=m;od++){
        int dv=m-od;
        if(dv &1)continue;
        dv /= 2;
        if(od+dv>k)continue;
        int ct = binv[0][dv];
        ct=mul(ct,binv[dv][od]);
        ct=mul(ct,fact[m]);
        ct=mul(ct,dg2[dv]);
        add(vse,ct);
    }
    for(int t = 1;(t + t <= m) && (t <= k);t++){
        int cur = 1;
        cur=mul(cur,(deg[m-t]+mod-1)%mod);
        int sm = 0;
        for(int f = 1;n - m - (f * (m - t)) >= 0;f+=2){
            int tt = mul((n - m - (f * (m - t)) + 1), deg[n-m-(f*(m-t))]);
            add(sm, tt);
        }
        cur = mul(cur, sm);
        for(int f = 0;n - m - ((m - t)*f)>=0;f += 2){
            int sp = min(m-t,n-(m+((m-t)*f))+1);
            sp=mul(sp,deg[n-(m+((m-t)*f))]);
            add(cur, sp);
            //cout << "!!! t:" << t << ' ' << f << ' ' << sp << ' ' << m-t << '\n';
        }
        int sh = mul(fact[t], binv[0][t]);
        if(m - t - t > (2*(k - t)))continue;
        int tmp=0;
        for(int od=0;od<=min(k-t,m-t-t);od++){
            int dv = m-t-t-od;
            if(dv & 1)continue;
            dv/=2;
            if(od+dv>k-t)continue;
            int ct = mul(dg2[dv], fact[m-t-t]);
            ct=mul(ct,binv[t][dv]);
            ct=mul(ct,binv[t+dv][od]);

            add(tmp,ct);
        }
        /*
        for(int raz=0;raz<=min(k-t,m-t-t);raz++){
            int ct=cm[m-t-t][raz];
            ct=mul(ct,binv[t][raz]);
            add(tmp,ct);
            //cout << raz << ' ' << ct << ' ' << cm[m-t-t][raz] << ' ' << binv[t][raz] << ' ' << m-t-t << ' ' << raz<<' '<<t<<' '<<m << '\n';
        }
        */
        sh = mul(sh, tmp);
        add(vse, (mod-sh)%mod);
        add(res, mul(cur, sh));
    }
    //cout << "! " << vse << '\n';
    add(res, mul(mul(n-m+1,deg[n-m]),vse));
    cout<<res;
    return 0;
 }
