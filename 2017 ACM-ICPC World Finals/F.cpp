
#include <bits/stdc++.h>
using namespace std;
const int N = 300;
const int M = 2005;
const int mod = (int)1e9 + 9;
const int P = 97;
const int lg = 30;
#define pb push_back
#define ll long long
int d[N];
ll dp[N][N];
ll suff[N][N],pref[N][N];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
     // freopen("in", "r", stdin);
    int n,k;
    cin >> n >> k;
    const int dd = 256;
    for(int i = 1;i <= n;i++){
        int r,p;
        cin>>r>>p;
        r++;
        d[r]=p;
    }
    for(int i = 0;i <= dd;i++){
        for(int j = 0;j <= k;j++){
            dp[i][j]=(ll)1e18;
        }
    }
    for(int i = 1;i <= dd;i++){
        dp[i][1]=0;
        for(int j = i;j >= 1;j--){
            dp[i][1]+=(d[j]*1ll*((i-j)*1ll*(i-j)));
        }
        //cout << i << ' ' << dp[i][1] << '\n';
    }
    for(int r = 1;r <= dd;r++){
        suff[r][r]=0;
        for(int i = r - 1;i >= 1;i--){
            suff[r][i]=suff[r][i+1];
            suff[r][i]+=(d[i]*1ll*((i-r)*1ll*(i-r)));
        }
    }
    for(int l=1;l<=dd;l++){
        pref[l][l]=0;
        for(int i = l + 1;i <= dd;i++){
            pref[l][i]=pref[l][i-1];
            pref[l][i]+=(d[i]*1ll*((i-l)*1ll*(i-l)));
        }
    }
    for(int i = 1;i <= dd;i++){
        for(int d = 2;d <= k;d++){
            ll s1 = 0;
            ll s2 = 0;
            int id = i;
            for(int j = i-1;j >= 1;j--){
                int mid = (i+j)/2;
                dp[i][d]=min(dp[i][d],dp[j][d-1]+(pref[j][mid]+suff[i][mid+1]));
            }
        }
    }
    ll res = (ll)1e18;
    for(int i = 1;i <= dd;i++){
        for(int j = 1;j <= k;j++){
            dp[i][j]+=pref[i][dd];

            res = min(res, dp[i][j]);

        }
    }
    cout << res;
    return 0;
 }
