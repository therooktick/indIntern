#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 100;
#define pb push_back
#define ll long long
char a[1005][1005];
void rec(int p, int n){
    if(n <= 0)return;
    if(n == 1){
        a[p][p+1]='D';
        a[p+2][p+1]='U';
        return;
    }
    if(n == 2){
        a[p+1][p+1]='L';
        a[p+1][p+2]='U';
        a[p+2][p+1]='D';
        a[p+2][p+2]='R';
        return;
    }
    if(n == 3){
        vector<vector<char> > temp = {{'L', 'U', 'R'}, {'R', '.', 'L'}, {'L', 'D', 'R'}};
        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                a[p+1+i][p+1+j] = temp[i][j];
            }
        }
        return;
    }
    char x='U';
    for(int j = 1;j < n + (n % 2);j++){
        a[p+1][p+j]=x;
        x=char('U'+'D'-x);
    }
    x='R';
    for(int j = 1 + (n % 2);j < n;j++){
        a[p+j][p+n]=x;

        x=char('R'+'L'-x);
    }
    x='D';
    for(int j = n;j >= 1 + (1 - (n % 2));j--){
        a[p+n][p+j]=x;
        x=char('U'+'D'-x);
    }
    x='L';
    for(int j = n - (n % 2);j >= 2;j--){
        a[p+j][p+1]=x;
        x = char('L' + 'R' - x);
    }
    rec(p + 2, n - 4);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // freopen("in", "r", stdin);
    int n;
    cin >> n;
    if(n == 1)cout << 'U',exit(0);
    for(int i = 1;i <= n;i++)for(int j = 1;j <= n;j++)a[i][j]='.';
    rec(0, n);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cout << a[i][j];
        }
        cout << '\n';
    }
    return 0;
}
