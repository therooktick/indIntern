#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 100;
#define pb push_back
#define ll long long
vector<pair<int,int>> mv8={{1, 1}, {4, 2}, {7, 3}, {8, 6}, {5, 7}, {2, 8}, {3, 5}, {6, 4}};
vector<pair<int,int>> mv10={{1, 1}, {2, 4}, {5, 3}, {8, 2}, {9, 5}, {6, 6}, {3, 7}, {4, 10}, {7, 9}, {10, 8}};
vector<pair<int,int>> mv9={{1, 1}, {4, 2}, {7, 3}, {8, 6}, {5, 5}, {2, 4}, {3, 7}, {6, 8}, {9, 9}};
vector<pair<int,int>> mv11={{1, 1}, {4, 2}, {5, 5}, {2, 6}, {3, 9}, {6, 10}, {9, 11}, {10, 8}, {7, 7}, {8, 4}, {11, 3}};


vector<pair<int,int>> mv={{1, 1}, {2, 4}, {5, 5}, {6, 2}, {3, 3}, {4, 6}};
vector<pair<int, int> > d = {{-3, 1}, {-3, -1}, {3, 1}, {3, -1}, {1, -3}, {1, 3}, {-1, 3}, {-1, -3}};
int row[(int)1e5 + 100],col[(int)1e5 + 100];
int n=5;
vector<pair<int, int> > tmp;
void rec(int i, int j, int st){
    if(st == n){
        for(auto[x, y]: tmp){
            cout << '{' << x << ", " << y << "}, ";
        }
        exit(0);
        return;
    }
    for(auto[dx, dy]: d){
        int x = dx + i;
        int y = dy + j;
        if(min(x, y) < 1)continue;
        if(max(x, y) > n)continue;
        if(row[x] || col[y])continue;
        row[x]=1;
        col[y]=1;
        tmp.pb({x, y});
        rec(x, y, st + 1);
        tmp.pop_back();
        row[x]=0;
        col[y]=0;
    }
}
vector<pair<int, int> > res;
void solve(int p, int n){
    if(n <= 0)return;
    if(n == 1){

        assert(!col[1+p]);
        assert(!row[1+p]);
        row[1+p]=col[1+p]=1;
        res.pb({1 + p, 1 + p});
        return;
    }
    if(n == 6){
        for(auto[i, j]: mv){
            assert(!row[i+p]);
            assert(!col[j+p]);
            res.pb({i + p, j+p});
            col[j+p]=1;
            row[i+p]=1;
        }
        return;
    }
    if(n == 8){
        for(auto[i, j]: mv8){
            assert(!row[i+p]);
            assert(!col[j+p]);
            res.pb({i + p, j+p});
            col[j+p]=1;
            row[i+p]=1;
        }
        return;
    }
    if(n == 9){
        for(auto[i, j]: mv9){
            assert(!row[i+p]);
            assert(!col[j+p]);
            res.pb({i + p, j+p});
            col[j+p]=1;
            row[i+p]=1;
        }
        return;
    }
    if(n == 10){
        for(auto[i, j]: mv10){
            assert(!row[i+p]);
            assert(!col[j+p]);
            res.pb({i + p, j+p});
            col[j+p]=1;
            row[i+p]=1;
        }
        return;
    }
    if(n == 11){
        for(auto[i, j]: mv11){
            assert(!row[i+p]);
            assert(!col[j+p]);
            res.pb({i + p, j+p});
            col[j+p]=1;
            row[i+p]=1;
        }
        return;
    }
    for(auto[i, j]: mv){
        assert(!row[i+p]);
        assert(!col[j+p]);
        res.pb({i + p, j+p});
        col[j+p]=1;
        row[i+p]=1;
    }
    solve(p + 6, n - 6);
}
vector<pair<int, int>> mv5 = {{1, 3}, {4, 4}, {5, 1}, {2, 2}, {3, 5}};
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // freopen("in", "r", stdin);
    //freopen("out", "w", stdout);
    cin >> n;

    if(n < 6){
        if(n == 5){
           cout << "POSSIBLE\n";
             for(auto[i, j]: mv5){
                cout << i << ' ' << j << '\n';

            }
            return 0;
        }
        if(n == 1){
            cout << "POSSIBLE\n1 1";
            return 0;
        }
        cout << "IMPOSSIBLE";
        return 0;
    }
    cout << "POSSIBLE\n";
    solve(0, n);
    for(int i = 1;i < n;i++){
        bool f = 0;
        for(auto[dx, dy]: d){
           f |= (((res[i].first + dx) == res[i - 1].first) && ((res[i].second + dy) == res[i - 1].second));
        }
        assert(f);
    }
    for(int i = 0;i < n;i++)cout << res[i].first << ' ' << res[i].second << '\n';
    return 0;
}
