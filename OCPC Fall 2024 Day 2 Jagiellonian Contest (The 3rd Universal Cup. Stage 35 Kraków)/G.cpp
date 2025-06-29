#include <bits/stdc++.h>
using namespace std;
const int N = (int)3e5 + 100;
const int mod = 998244353;
const int P = 97;
const int lg = 20;
#define pb push_back
#define ll long long
int c,tin[N],tout[N],timer;
int up[N][lg],go[N][lg];
ll d[N];
vector<pair<int, int> > g[N];
void dfs(int v, int pr){
    tin[v] = ++timer;
    if(pr == -1){
       go[v][0] = v;
    }else{
        go[v][0] = pr;
    }
    for(int j = 1;j < lg;j++){
        go[v][j] = go[go[v][j - 1]][j - 1];
    }
    if(pr == -1){
        up[v][0] = v;
    }else{
        int cur = v;
        for(int j = lg - 1;j >= 0;j--){

            if(d[v] - d[go[cur][j]] <= c){
                cur = go[cur][j];
            }
        }
        up[v][0] = cur;
    }
    for(int j = 1;j < lg;j++){
        up[v][j] = up[up[v][j - 1]][j - 1];
    }
    for(auto[to, w]: g[v]){
        if(to == pr)continue;
        d[to] = d[v] + w;
        dfs(to, v);
    }
    tout[v] = timer;
}
bool upper(int a,int b){
    return (tin[a] <= tin[b]) && (tout[a] >= tout[b]);
}
int lca(int a,int b){
    if(upper(a, b))return a;
    if(upper(b, a))return b;
    int v = a;
    for(int j = lg - 1;j >= 0;j--){
        if(!upper(go[v][j], b)){
            v = go[v][j];
        }
    }
    return go[v][0];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("in", "r", stdin);
    int qq;
    cin >> qq;
    while(qq--){
        timer = 0;
        int n,q;
        cin >> n >> q;
        cin >> c;
        for(int i = 1;i < n;i++){
            int u,v,w;
            cin >> u >> v >> w;
            g[u].pb({v, w});
            g[v].pb({u, w});
        }
        dfs(1, -1);
        while(q--){
            int u,v;
            cin >> u >> v;
            if(upper(u, v)){
                swap(u, v);
            }
            int lc = lca(u, v);
            int res = 0;
            int cur = u;
            for(int j = lg - 1;j >= 0;j--){
                if(!upper(up[cur][j], lc)){
                    res += (1 << j);
                    cur = up[cur][j];
                }
            }
            if(upper(v, u)){
                cout << res << '\n';
                continue;
            }
            ll cost = d[cur] - d[lc];
            if(cost + (d[v] - d[lc]) <= c){
                cout << res << '\n';
                continue;
            }
            assert(cost <= c);
            int mx = v;
            for(int j = lg - 1;j >= 0;j--){
                if(d[go[mx][j]] - d[lc] + cost > c){
                    mx = go[mx][j];
                }
            }
           // cout << "!!! " << cur << ' ' << lc << ' ' << d[mx] - d[lc] << ' ' << mx << endl;

            assert(mx != lc);
            mx = go[mx][0];
            cur = v;
            ++res;
            //cout << "!! " << mx << ' ' << cost << endl;
            for(int j = lg - 1;j >= 0;j--){
                if(!upper(up[cur][j], mx)){
                   // cout << "!! ! " << j << ' ' << ' ' << up[cur][j] << endl;
                    res += (1 << j);
                    cur = up[cur][j];
                }
            }
            cout << res << '\n';
        }
        for(int v = 1;v <= n;v++){
            g[v].clear();
        }
    }
    return 0;
}
