#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 100;
const int mod = 998244353;
const int P = 97;
//const int lg = 15;
#define pb push_back
#define ll long long
const int MAX = 2000;
int a[N],l[N],r[N];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
   //   freopen("in", "r", stdin);
    int qq;
    cin >> qq;
    while(qq--){
        int n,q;
        cin >> n >> q;
        for(int i = 1;i <= n;++i){
            cin >> a[i];
            l[i] = 1;
            r[i] = (int)1e9;
        }
        for(int i = 1;i <= q;i++){
            int p,a,b;
            cin >> p >> a >> b;
            l[p] = max(l[p], a);
            r[p] = min(r[p], b);
        }
        ll res = 0;
        bool can = 1;
        for(int i = 1;i <= n;i++){
            if(l[i] > r[i]){
                can = 0;
                break;
            }
            if((a[i] >= l[i]) && (a[i] <= r[i])){

            }else{
                res += min(abs(a[i] - l[i]), abs(a[i]- r[i]));
            }
        }
        if(!can)res = -1;
        cout << res << '\n';
    }
    return 0;
}
