#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 100;
#define pb push_back
#define ll long long
int m;
vector<int> pos[100];
int cur;
int cl[100][100],cr[100][100],cntl[100],cntr[100];
void add(int &x, int y){
    x += y;
    if(x >= m)x -= m;
}
void add1(int x){
    x-=33;
    for(int z = 0;z <= 93;z++){
        add(cr[x][z], cntr[z]);
    }
    add(cntr[x], 1);
}
void del(int x){
    x-=33;

    cntr[x]--;if(cntr[x]<0)cntr[x]+=m;
    for(int z = 0;z <= 93;z++){
        cr[x][z] -= cntr[z];
        if(cr[x][z]<0)cr[x][z]+=m;


        cur -= ((cl[z][x]*1ll*cntr[z])%m);
        if(cur<0)cur+=m;
    }
}
void add2(int x){
    x-=33;
    for(int z = 0;z <= 93;z++){
        add(cl[z][x], cntl[z]);
        add(cur, (cr[x][z]*1ll*cntl[z])%m);
    }
    add(cntl[x], 1);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // freopen("in", "r", stdin);
    string s;
    cin >> s;
    cin >> m;
    int n = s.size();
    for(int i = n-1;i>=0;i--){
        add1(s[i]);
    }
    int res=0;
    for(int i=0;i<n;i++){
        del(s[i]);

        assert(cur >= 0);
        cur %= m;
        add(res, cur);
        add2(s[i]);
    }
    res %= m;
    cout << res;
    return 0;
}
