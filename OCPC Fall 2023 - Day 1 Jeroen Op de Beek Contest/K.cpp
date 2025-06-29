#include <bits/stdc++.h>
using namespace std;
const int N = 510;
const int mod = 998244353;
const int P = 97;
const int lg = 30;
#define pb push_back
#define ll long long
char a[N][N];
vector<pair<int, int> > pos;
int dist(pair<int, int> a,pair<int,int>b){
    return abs(a.first-b.first)+abs(a.second-b.second);
}
bool check(pair<int, int> a,pair<int,int>b){
    return max(abs(a.first-b.first),abs(a.second-b.second)) > 1;
}
int tot = 0;
void rec(int p, int n){
    if(n <= 1)return;
    if((n % 3 == 2) && (n % 2 == 1)){
        for(int i = 1;i <= n;i += 2){
            for(int j = 1;j <= n;j += 3){
                a[i + p][j + p] = '#';
                ++tot;
                a[i + p][j + 1 + p] = '#';
            }
        }
        return;
    }
    if((n % 3 == 2) && (n % 2 == 0)){
        for(int i = 1;i <= n;i += 2){
            for(int j = 1;j <= n;j += 3){
                a[i + p][j + p] = '#';
                ++tot;
                a[i + p][j + 1 + p] = '#';
            }
        }
        for(int j = 1;j <= n;j++){
            a[n - 1 + p][j + p] = '.';
        }
        for(int j = 1;j <= n;j += 2){
            ++tot;
            a[n - 1 + p][j + p] = '#';
            a[n + p][j + p] = '#';
        }
        return;
    }
    if(n % 6 == 0){
        for(int i = 1;i + 1 < n;i += 2){
            a[1 + p][i + p] = '#';
            a[2 + p][i + p] = '#';
        }
        for(int i = 1;i + 1 < n;i += 2){
            a[i + p][n + p] = '#';
            a[i + p][n - 1 + p] = '#';
        }
        for(int i = n;i - 1 > 1;i -= 2){
            a[n + p][i + p] = '#';
            a[n + p - 1][i + p] = '#';
        }

        for(int i = n;i - 1 > 1;i -= 2){
            a[i + p][1 + p] = '#';
            a[i + p][2 + p] = '#';
        }
        rec(p + 3, n - 6);
        return;
    }
    pos.clear();
    for(int i = 1;i <= n;i++){
        pos.pb({1, i});
    }
    for(int j = 2;j <= n;j++){
        pos.pb({j, n});
    }
    for(int j = n - 1;j >= 1;j--){
        pos.pb({n, j});
    }
    for(int i = n - 1;i > 1;i--){
        pos.pb({i, 1});
    }
    for(int f = 0;f + 1 < (int)pos.size();f++){
        if(dist(pos[f], pos[f + 1]) != 1)continue;
        bool ok = 1;
        for(int j = 0;j < (int)pos.size();j++){
            if(a[pos[j].first + p][pos[j].second + p] == '.')continue;
            if(check(pos[j], pos[f]) && check(pos[j], pos[f + 1]))continue;
            ok = 0;
            break;
        }
        if(ok){
                ++tot;
            a[pos[f].first + p][pos[f].second + p] = '#';
            a[pos[f + 1].first + p][pos[f + 1].second + p] = '#';
        }
    }
    rec(p + 2, n - 4);
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
            for(int j = 1;j <= n;j++){
                a[i][j] = '.';
            }
        }
        rec(0, n);
        //cout << tot << '\n';
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                cout << a[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
 }
