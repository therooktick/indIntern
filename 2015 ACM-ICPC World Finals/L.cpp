#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define ld long double
const int N = 105;//(int)1e7 + 100
const int mod = (int)1e9 + 7;
//const int m = (int)1e9;
const int MAX = (int)1e5;
const int lg = 60;
const double EPS = 1e-13;
const int INF = (int)1e9 + 100;
multiset<pair<ld, ll> > A;

ll C[N][N];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    C[0][0] = 1;
    for(int i = 1;i < N;i++){
        C[i][i] = C[i][0] = 1;
        for(int j = 1;j < i;j++){
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    //freopen("in", "r", stdin);
    array<ld, 4> P;

    int n;
    cin >> n >> P[0] >> P[1] >> P[2] >> P[3];
    //P = {0.25, 0.25, 0.25, 0.25};
    array<int, 4> Q;
    ll s =0 ;
    ld ov = 0;
    for (Q[0] = 0; Q[0] <= n; Q[0]++) {
      for (Q[1] = 0; Q[0] + Q[1] <= n; Q[1]++) {
        for (Q[2] = 0; Q[0] + Q[1] + Q[2] <= n; Q[2]++) {
          Q[3] = n - Q[0] - Q[1] - Q[2];
          ld prob = 1.0;
          ll cnt = 1, cur = n;

          for (int i = 0; i < 4; i++) {
            cnt *= C[cur][Q[i]];
           cur -= Q[i];
            prob *= powl(P[i], Q[i]);
          }
         // cout << "! " << prob << ' ' << cnt << endl;
            ov += (prob * cnt);
            A.insert({prob, cnt});

        }
      }
    }
    ld res = 0;
    //cout << "! " << ov << endl;

    while((int)A.size() > 1){
        auto[pr, gr] = *(A.begin());
        A.erase(A.begin());
        //cout << "! " << pr << ' ' << gr << endl;
        if(gr == 0)continue;
        if(gr > 1){
            res += (((gr / 2ll) * 2ll) * 1.0 * pr);
            A.insert({pr * 2, (gr / 2)});
            if(gr & 1){
                A.insert({pr, 1});
            }
        }else{
            auto[pr2, gr2] = *(A.begin());
            A.erase(A.begin());
            res += (pr2 + pr);
            A.insert({pr2 + pr, 1});
            if(gr2 > 1){
                A.insert({pr2, gr2 - 1});
            }
        }
    }
    cout << fixed << setprecision(6);
   // cout << (*A.begin()).first << endl;
    cout << res;
    return 0;
}

