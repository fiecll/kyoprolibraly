#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using ll = long long;
using Graph = vector<vector<int>>;
using P = pair<int,int>;

// a:対象の二次元配列
// [h1,h2)×[w1,w2) の範囲の区間和を返します

// 前処理を行う
// S:累積和を記録する配列
void pre_process(vector<vector<int>> const &a, vector<vector<int>> &S) {
    int H = (int)a.size();
    int W = (int)a[0].size();
    S.assign(H + 1, vector<int>(W + 1));
    for (int h = 1; h < H + 1; h++) {
        for (int w = 1; w < W + 1; w++) {
            S[h][w] = a[h - 1][w - 1] + S[h][w - 1] + S[h - 1][w] - S[h - 1][w - 1];
        }
    }
}
// [h1,h2)×[w1,w2) の区間和を求める
int query(int h1, int h2, int w1, int w2, vector<vector<int>> const &S) {
    return S[h2][w2] - S[h1][w2] - S[h2][w1] + S[h1][w1];
}
//以下　H*W
int main() {
    int h,w;
    cin >> h >> w;
    vector<vector<int>>a(h,vector<int>(w));
    vector<vector<int>>S(h,vector<int>(w));
    rep(i,hh)rep(j,w) cin >> a[i] >> a[j];
    pre_process(a, S);
    int p,q,r,s;
    cij >> p >> q >> r >> s;
    cout << query(p,r,q,s,S) << endl;  // [1,3)×[2,3) = 3+3 = 6
    return 0;
}