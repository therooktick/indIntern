#include <bits/stdc++.h>
using namespace std;
const int N = 510;
const int mod = 998244353;
const int P = 97;
const int lg = 30;
#define pb push_back
#define ll long long
array<ll, 2> p[N];
char c[N];
int cnt[1000];
ll cross(array<ll, 2> a, array<ll, 2> b, array<ll, 2> c){
    array<ll, 2> x = {b[0] - a[0], b[1] - a[1]};
    array<ll, 2> y = {c[0] - b[0], c[1] - b[1]};
    return (x[0] * 1ll * y[1]) - (x[1] * 1ll * y[0]);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //  freopen("in", "r", stdin);
    int n;
    cin >> n;
    int res = 0;
    for(int i = 1;i <= n;i++){
        cin >> p[i][0] >> p[i][1];
        cin >> c[i];
        cnt[c[i] - 'a']++;
        res = max(res, cnt[c[i] - 'a']);
    }
    res = min(res, 2);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(i ==j)continue;
            for(int k = 1;k <= n;k++){
                if(c[k] != c[i])continue;
                if((k == i) || (k == j))continue;
                if(cross(p[i], p[j], p[k]) > 0){
                    cout << "Infinity";
                    return 0;
                }
            }
        }
    }
    cout << res;
    return 0;
 }
