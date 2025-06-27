#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const int N = (int)2e5 + 100;//(int)1e7 + 100
const int mod = (int)1e9 + 7;
//const int m = (int)1e9;
const int MAX = (int)1e5;
const int lg = 60;
const double EPS = 1e-7;
int p,a,b,c,d;
double price(int k){
    return p * 1.0 * (sin((a * k) + b) + cos((c * k) + d) + 2.0);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("in", "r", stdin);
    cin >> p >> a >> b >> c >> d;
    int n;
    cin >> n;
    double res = 0;

    double mx = price(1);
    for(int i = 2;i <= n;i++){
        double cur = price(i);
        res = max(res, mx - cur);
        mx = max(mx, cur);
    }
    cout << fixed << setprecision(8) << res;
    return 0;
}
