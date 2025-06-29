#include <bits/stdc++.h>
using namespace std;
const int N = 3050;
const int mod = 998244353;
const int P = 97;
#define pb push_back
#define ll long long
int a[N][N];
ll dp[N][N][2];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("in", "r", stdin);
    int qq;
    cin >> qq;
    while(qq--){
        int n,m;
        cin >> n >> m;
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                cin >> a[i][j];
            }
        }

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                dp[i][j][0] = dp[i][j][1] = 0;
            }
        }
        dp[1][1][0] = a[1][1];
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                if(i < n){
                    for(int id = 0;id < 2;id++)dp[i + 1][j][id] = max(dp[i + 1][j][id], dp[i][j][id] + a[i + 1][j]);
                    if(j > 1){
                            dp[i + 1][j][1] = max(dp[i + 1][j][1], dp[i][j][0] + a[i + 1][j] + a[i + 1][j - 1]);
                            if(i + 1 < n){
                                dp[i + 2][j - 1][1] = max(dp[i + 2][j - 1][1], dp[i][j][0] + a[i + 1][j] + a[i + 1][j - 1] + a[i + 2][j - 1]);
                            }
                    }
                }
                if(j < m){
                    for(int id = 0;id < 2;id++)dp[i][j + 1][id] = max(dp[i][j + 1][id], dp[i][j][id] + a[i][j + 1]);
                }
            }
        }
        cout << max(dp[n][m][0], dp[n][m][1]) << '\n';
    }
    return 0;
}
