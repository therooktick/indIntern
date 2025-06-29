
#include <bits/stdc++.h>
using namespace std;
const int N = (int)5e5 + 100;
const int mod = 998244353;
const int P = 97;
const int lg = 30;
#define pb push_back
#define ll long long
int bal[N];
vector<int> g[N];
int ov;
int used[N],p[N];
vector<int> tmp,vec,el[N];
int res[N];
int A,B,d[N],sz;
void dfs(int v, int pr){
    used[v] = 1;
    d[v] = (pr != -1);
    ++ov;
    int kto = 0;
   // cout << "!!! " << v << '\n';
    for(int to: g[v]){
        if(used[to])continue;
        if(to == A || to == B)continue;
        dfs(to, v);
        if(d[to] + (pr != -1) > d[v]){
            kto = to;
            d[v] = d[to] + (pr != -1);
        }
    }
    for(int to: g[v]){
        if(to == A || to == B)continue;
        if(to == pr)continue;
        if(to == kto)continue;
        el[sz].pb(d[to]);
    }
}
set<pair<int,int> > st;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
     //freopen("in", "r", stdin);
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> p[i];
        g[i].pb(p[i]);
        g[p[i]].pb(i);
    }
    for(int i = 1;i <= n;i++){
        if(used[i])continue;
        int cur = i;
        tmp.clear();
        while(!used[cur]){
            tmp.pb(cur);
            used[cur] = 1;
            cur = p[cur];
        }
        for(int x: tmp){
            used[x] = 0;
        }
        tmp.clear();
        int mx = 0;
        int len = 0;
        int lst = cur;
        cur = p[cur];
        ++sz;
        while(!used[cur]){
            used[cur] = 1;

            A = lst;
            B = p[cur];
            dfs(cur, -1);
            tmp.pb(d[cur]);


            lst = cur;
            cur = p[cur];
            ++len;
        }
        sort(tmp.begin(), tmp.end());
        if(!tmp.empty()){
            bal[len] = max(bal[len], tmp.back() + 1);
            el[sz].pb(tmp.back() + len);tmp.pop_back();
            for(int x: tmp){
               // cout << "pop " << sz << ' ' << x << ' ' << bal[len] << '\n';
                el[sz].pb(x);
            }
            sort(el[sz].begin(), el[sz].end());
        }else{
            el[sz].pb(len);
        }
    }

    for(int i = 1;i <= sz;i++){
        st.insert({el[i].back(), i});
        el[i].pop_back();
    }

    for(int i = 1;i <= n;i++){
        res[i] = (int)1e9 + 100;
    }
    int sm = 0;
    int b = 0;
    for(int i = 1;i <= n;i++){
        b = max(b, bal[i]);
        if(b > 0){
            res[i] = 0;
        }
        --b;
    }
    int rt = -1;
    while(!st.empty()){
        ++rt;
        auto[val, i] = *(--st.end());
       // cout << "!! " << val << '\n';
        st.erase(--st.end());
        for(int j = sm + 1;j <= sm + val;j++){
            res[j] = min(res[j], rt + (sm == 0));
        }
        sm += val;
        if(!el[i].empty()){
            st.insert({el[i].back(), i});
            el[i].pop_back();
        }
    }
    for(int i = 1;i <= n;i++){
        cout << res[i] << ' ';
    }
    return 0;
 }
