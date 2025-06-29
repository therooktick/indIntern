#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 100;
const int mod = 998244353;
const int P = 97;
//const int lg = 15;
#define pb push_back
#define ll long long
const int MAX = 2000;
vector<int> g[N + 100];
int dp[N / 2][MAX];
int id[N + 100];
int p[N + 100];
int B;
int tmp[MAX + 100];
pair<int, int> vec[MAX + MAX + 100];
int asz,n;
void dfs(int v,int pr){
   // if(v == 139263)cout << "! " << v << ' ' << (int)g[v].size() << ' ' << id[v] << endl;
    if(g[v].empty()){
        for(int w = 0;w <= B;w++){
            dp[id[v]][w] = 0;
        }
        return;
    }

    int l = -1,r = -1;
    id[g[v][0]] = ++asz;
    int tt = asz;
    dfs(g[v][0], v);
    asz = tt;
    id[g[v][1]] = ++asz;
    dfs(g[v][1], v);

    l = id[g[v][0]];
    r = id[g[v][1]];

    tmp[0] = (int)1e8;
    for(int w = 1;w <= B;w++){
        tmp[w] = min(dp[l][w - 1] + 1 + dp[r][w], dp[l][w] + 1 + dp[r][w - 1]);
    }
    int idd = B;
    int sz = 0;
    for(int w = B;w >= 1;w--){
        while((idd >= 1) && (make_pair(dp[l][w], -w) >= make_pair(dp[r][idd], -idd))){
            vec[++sz] = {dp[r][idd], idd};
            --idd;
        }
        vec[++sz] = {dp[l][w], -w};
    }
    while(idd >= 1){
        vec[++sz] = {dp[r][idd], idd};
        --idd;
    }

    int cur[2] = {-1, -1};
    int lst[2] = {-1, -1};
    for(int i = 1;i <= B + B;i++){
        if(vec[i].second < 0){
            if(cur[0] == -1){
                cur[0] = i;
            }else{
                if(vec[i].first != vec[cur[0]].first)lst[0] = cur[0];
                cur[0] = i;
            }
        }else{
            if(cur[1] == -1){
                cur[1] = i;
            }else{
                if(vec[i].first != vec[cur[1]].first)lst[1] = cur[1];
                cur[1] = i;
            }
        }
        if(min(cur[0], cur[1]) >= 0){
            int kto = 1;if(cur[0] == i)kto = 0;
            int v1 = i,v2;
            if(vec[cur[1 - kto]].first != vec[i].first)v2 = cur[1 - kto]; else v2 = lst[1 - kto];
            if(v2 != -1){
                int sum = abs(vec[v1].second) + abs(vec[v2].second) + 1;
                //if(v == 3)cout << vec[v1].first << ' ' << vec[v2].first << ' ' << vec[v1].second << ' ' << vec[v2].second << ' ' << sum << '\n';
                if(sum <= B){
                    tmp[sum] = min(tmp[sum], vec[v1].first);
                }
            }
            v2 = cur[1 - kto];
            int sum = abs(vec[v1].second) + abs(vec[v2].second) + 1;
            if(sum <= B){
                tmp[sum] = min(tmp[sum], vec[v1].first + 1);
            }
        }
    }
    for(int w = 2;w <= B;w++){
        tmp[w] = min(tmp[w], tmp[w - 1]);
    }
    for(int w = 1;w <= B;w++){
        if(tmp[w] <= B){
            int val = tmp[w];

            tmp[val] = min(tmp[val], w);
        }
    }
    for(int w = 2;w <= B;w++){
        tmp[w] = min(tmp[w], tmp[w - 1]);
    }
    for(int w = 1;w <= B;w++){
        tmp[w] = min(tmp[w], (int)1e8);
    }
    for(int w = 0;w <= B;w++){
        dp[id[v]][w] = tmp[w];
    }

    if(v == 0){
        for(int w = 0;w <= B;w++){
            cout << tmp[w] << ' ';
        }
        exit(0);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  //  freopen("in", "r", stdin);
   // decrease BA
    int qq;
    cin >> qq;
    while(qq--){
        asz = -1;
        cin >> n;
        for(int i = 2;i <= n;i++){
            cin >> p[i];
           //p[i] = (i / 2);
            g[p[i]].pb(i);
        }
        int lg = 0;
        while((1 << lg) <= n)lg++;++lg;
        B = 0;
        while((B * B) <= (n * lg))B++;
        B = min(B, MAX - 2);
        id[1] = ++asz;
        dfs(1, -1);
        int res = (int)1e8;
        for(int w = 1;w <= B;w++){
            ll s = (w * 1ll * dp[id[1]][w]);
            //cout << w << ' ' << dp[id[1]][w] << '\n';
            if(s >= res)continue;
            res = s;
        }
        cout << res << '\n';
        for(int v = 1;v <= n;v++){
            g[v].clear();
        }
    }
    return 0;
}
/*
2
11
1 1 2 3 3 6 6 8 8 2
3
1 1

*/
