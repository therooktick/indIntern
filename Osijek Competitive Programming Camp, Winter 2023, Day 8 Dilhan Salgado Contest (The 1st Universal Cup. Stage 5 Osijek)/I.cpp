#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 100;
const int mod = 998244353;
#define pb push_back
#define ll long long
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
   // freopen("in", "r", stdin);
    ll n;
    cin >> n;
    if(n <= 2)cout << 1,exit(0);
    n %= mod;
    cout << (((n*2ll)) % mod);
    return 0;
}
