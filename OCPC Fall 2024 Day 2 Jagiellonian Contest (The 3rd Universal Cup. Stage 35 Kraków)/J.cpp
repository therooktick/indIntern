#include <bits/stdc++.h>
using namespace std;
const int N = (int)3e5 + 100;
const int mod = 998244353;
const int P = 97;
const int lg = 20;
#define pb push_back
#define ll long long
int bg,sm;
ll d[N],a[N];
int n;
struct node{
    ll sum;
    pair<ll, int> mn;
    ll add;
    int cnt;
};
node t[4 * N];
node combine(node a, node b){
    node c;
    c.mn = min(a.mn, b.mn);
    c.sum = a.sum + b.sum;
    c.add = 0;
    c.cnt = a.cnt + b.cnt;
    return c;
}
void build(int v,int tl,int tr){
    t[v].mn.first = (ll)1e18;if(d[tl] > 0)t[v].mn.first = d[tl];
    t[v].mn.second = tl;
    t[v].sum = 0;if(d[tl] > 0)t[v].sum = d[tl];
    t[v].add = d[tl];
    t[v].cnt = (d[tl] > 0);
    if(tl == tr)return;
    int tm = (tl + tr) / 2;
    build(v << 1, tl, tm);
    build(v << 1 | 1, tm + 1, tr);
    t[v] = combine(t[v << 1], t[v << 1 | 1]);
}
void push(int v,int tl,int tr){
    if((tl == tr) || (t[v].add == 0))return;
    t[v << 1].sum += (t[v].add * 1ll * t[v << 1].cnt);
    t[v << 1].mn.first += t[v].add;
    t[v << 1].add += t[v].add;

    t[v << 1 | 1].sum += (t[v].add * 1ll * t[v << 1 | 1].cnt);
    t[v << 1 | 1].mn.first += t[v].add;
    t[v << 1 | 1].add += t[v].add;

    t[v].add = 0;
}
void update(int pos, ll val, bool did, int v,int tl,int tr){
    push(v, tl, tr);

    if(tl == tr){
        ll tt = t[v].add + val;
        t[v].mn.first = (ll)1e18;if(tt > 0)t[v].mn.first = tt;
        t[v].sum = 0;if(tt > 0)t[v].sum = tt;
        t[v].cnt = (tt > 0);
       // cout << "AAA " << t[v].sum << ' ' << val << ' ' << t[v].add << endl;
        if(did)t[v].add = tt;
        return;
    }
    int tm = (tl + tr) / 2;
    if(pos <= tm){
        update(pos, val, did, v << 1, tl, tm);
    }else{
        update(pos, val, did, v << 1 | 1, tm + 1, tr);
    }
    t[v] = combine(t[v << 1], t[v << 1 | 1]);
}
const ll MAX = (ll)1e16;
pair<ll, int> get(int l, int r,int v, int tl,int tr){
    push(v, tl, tr);
    if((tl > r) || (tr < l))return {MAX, 0};
    if((tl >= l) && (tr <= r)){
        return t[v].mn;
    }
    int tm = (tl + tr) / 2;
    return min(get(l, r, v << 1, tl, tm), get(l, r, v << 1 | 1, tm + 1, tr));
}
void add(int l, int r, ll val,int v,int tl,int tr){
    push(v, tl, tr);
    if((tl > r) || (tr < l))return;
    if((tl >= l) && (tr <= r)){
        if(t[v].mn.first + val <= 0){
            cout << "!! " << t[v].mn.first << ' ' << val << '\n';
            exit(0);
        }
        assert(t[v].mn.first + val > 0);
        t[v].mn.first += val;
        t[v].sum += (val * 1ll * t[v].cnt);
        t[v].add += val;
        return;
    }
    int tm = (tl + tr) / 2;
    add(l, r, val, v << 1, tl, tm);
    add(l, r, val, v << 1 | 1, tm + 1, tr);
    t[v] = combine(t[v << 1], t[v << 1 | 1]);
}
ll sum;
bool fit(){
    return (a[1] >= t[1].sum);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
   // freopen("in", "r", stdin);
    int qq;
    cin >> qq;
    while(qq--){
        int q;
        cin >> n >> q;
       // n = (abs(rand()) % 10) + 1;
        //q = (abs(rand()) % 10) + 1;
        for(int i = 1;i <= n;i++){
            cin >> a[i];
            //a[i] = (abs(rand()) % (int)1e9) + 10;
        }
        for(int i = 1;i < n;i++){
            d[i] = a[i] - a[i + 1];
        }
        build(1, 1, n - 1);
        if(fit())cout << "YES\n"; else cout << "NO\n";
        while(q--){
            int l,r;
            ll s,d;
            cin >> l >> r >> s >> d;
            //l = (abs(rand()) % n) + 1;
            //r = (abs(rand()) % n) + 1;
           // if(l > r)swap(l, r);
            //s = (abs(rand()) % (int)1e4) + 1;
           // d = (abs(rand()) % (int)1e4) + 1;

            if(l == 1){
                a[1] += s;
            }
            if(l > 1){
                update(l - 1, -s, 1, 1, 1, n - 1);
            }
            while(l < r){
                auto[mn, id] = get(l, r - 1, 1, 1, n - 1);

                //cout << "!!!!! " << mn << ' ' << d << ' ' << id << '\n';
                if(mn >= MAX)break;
                if(mn <= d){
                    update(id, -d, 0, 1, 1, n - 1);
                }else{
                    break;
                }
            }

           // cout << "AAsadsa " << '\n';
            if(l < r){
                add(l, r - 1, -d, 1, 1, n - 1);
            }
          //  cout << "AAsadsa " << '\n';
            if(r < n){
                update(r, ((r - l) * 1ll * d) + s, 1, 1, 1, n - 1);
            }

           // cout << "AAsadsa " << '\n';
            if(fit())cout << "YES\n"; else cout << "NO\n";
           // cout << "sum: " << t[1].sum << endl;
        }
    }
    return 0;
}
/*
1
4 3
10 12 20 14
2 3 1 10
1 2 6 6
3 4 5 5
YNNY

*/
