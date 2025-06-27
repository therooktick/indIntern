#include <bits/stdc++.h>
using namespace std;
const int N = (int)4e5 + 100;
const int mod = 998244353;
const int P = 97;
//const int lg = 15;
#define pb push_back
#define ll long long
vector<int> odd;
vector<int> res,tmp;
vector<pair<int, int> > g[N];
int liv[N + N],clr[N + N];
int used[N],was[N];
map<pair<int,int>, int> ind;
int sz;

int get(int u,int v){
    return ind[{min(u, v), max(u, v)}];
}
bool need;
int tot;
void dfs(int v){
    tmp.pb(v);
    used[v] = 1;
    while(!g[v].empty()){
        if(need){
            if(v != tot){
                break;
            }else{
                need = 0;
                tot = -1;
            }
        }
        auto[to, id] = g[v].back();

        g[v].pop_back();
        if(!liv[id]){
            continue;
        }

        if(used[to]){

            ++sz;
            clr[get(v, to)] = sz;

            liv[id] = 0;

            used[v] = 0;
            while(tmp.back() != to){
                used[tmp.back()] = 0;
                int tt = (int)tmp.size();
                int a = tmp[tt - 1];
                int b = tmp[tt - 2];

                clr[get(a, b)] = sz;
                tmp.pop_back();
            }
            need = 1;
            tot = to;
            break;
        }

        liv[id] = 0;
        dfs(to);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
     // freopen("in", "r", stdin);
    int qq;
    cin >> qq;
    while(qq--){
        sz = 0;
        int n,m;
        cin >> n >> m;
        ind.clear();
        for(int i = 1;i <= m;i++){
            int u,v;
            cin >> u >> v;
            if(u > v)swap(u, v);
            ind[{u, v}] = i;
            g[u].pb({v, i});
            g[v].pb({u, i});
        }

        odd.clear();
        for(int v = 1;v <= n;v++){
            if((int)g[v].size() & 1){
                odd.pb(v);
            }
        }
        int t = (int)odd.size();
                int mx = m + t + 1;
         for(int v = 1;v <= mx;v++){
            liv[v] = 1;
        }
        for(int i = 0;i < t;i += 2){
            int u = odd[i];
            int v = odd[i + 1];
            if(u > v)swap(u, v);
            if(ind[{u, v}] == 0)
            ind[{u, v}] = m + 1 + i;
            g[u].pb({v, m + 1 + i});
            g[v].pb({u, m + 1 + i});
        }
        //int sz = 0;
        for(int v = 1;v <= n;v++){
            tmp.clear();
            need = 0;
            tot = -1;
            dfs(v);
        }
        for(int i = 1;i <= m;i++)cout << clr[i] << ' ';
        cout << '\n';
        for(int v = 1;v <= mx;v++){
            liv[v] = 0;
        }
        for(int v = 1;v <= n;v++){
            g[v].clear();
            used[v] = 0;
        }
    }
    return 0;
}
