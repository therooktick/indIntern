#include <bits/stdc++.h>
using namespace std;
const int N = 510;
const int mod = 998244353;
const int P = 97;
const int lg = 30;
#define pb push_back
#define ll long long
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //  freopen("in", "r", stdin);
    int x;
    cin >> x;
    cout << "1\n";
    if(x < 25){
        cout << x + x + 1 << '\n';
        cout << x << ' ';
        for(int i = 1;i <= x;i++){
            cout << 1 << ' ' << 1 << ((i < x)?' ':'\n');
        }
    }else{
        cout << 50 << '\n';
        for(int i = 1;i <= 25;i++){
            cout << 5 << ' ' << 5 << ((i < 25)?' ':'\n');
        }
    }
    return 0;
 }
