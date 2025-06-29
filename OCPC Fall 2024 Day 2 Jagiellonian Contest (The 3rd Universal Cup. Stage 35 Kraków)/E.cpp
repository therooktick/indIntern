#include <bits/stdc++.h>
using namespace std;
const int N = 3050;
const int mod = 998244353;
const int P = 97;
#define pb push_back
#define ll long long
map<pair<ll, ll>, int> mp;
int solve(ll b, ll a){
    if(b > a){
        swap(a, b);
    }
    if(b == 0)return 0;
    if(mp[make_pair(b, a)])return -(int)1e9;
    mp[make_pair(b, a)]=1;

    return solve(b + b, a - b) + 1;
}
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
        mp.clear();
        ll a,b;
        cin >> a >> b;
        int s = -1;
        ll g = __gcd(a, b);
        ll f = (a + b) / g;
       // cout << "!! " << f << endl;
        ll d = 1;
        int cnt = 0;
        while((d < f))d <<= 1,++cnt;
        if(d == f){
            s = cnt;
        }else{
            s = -1;
        }
        if(s < 0){
            cout << 2;
        }else{
            int res = 0;
            int p = 1;
            for(int v = 1;v <= s;v++){
                p = (p * 1ll * ((mod + 1) / 2)) % mod;
                add(res, (p * 1ll * v) % mod);
            }
            add(res, (p * 1ll * s) % mod);

            cout << res;
        }
        cout << '\n';
    }
    return 0;
}
