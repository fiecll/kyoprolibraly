#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
using ll = long long;
using Graph = vector<vector<int>>;
using P = pair<int,int>;

//二部グラフならYes 違うならNoを返す
int main() {
    // 入力を受け取る
    int N, M; cin >> N >> M;
    vector<vector<int>> G(N);   // グラフを表現する隣接リスト
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        a--,b--
        // 頂点 a から頂点 b への辺を張る
        G[a].push_back(b);
        // 無向グラフのため、頂点 b から頂点 a への辺も張る
        G[b].push_back(a);
    }

    vector<int> color(N, -1);   // color[v]：頂点 v の色が黒なら 1, 白なら 0, 未探索なら -1
    string ans = "Yes";
    // 全ての頂点について
    for(int v = 0; v < N; ++v) {
        // 頂点 v がすでに訪問済みであれば、スキップ
        if(color[v] != -1) {continue;}
        // そうでなければ、頂点 v を含む連結成分は未探索
        // 頂点 v の色を白で決め打ちしたうえで、幅優先探索を行う
        queue<int> que; // 探索候補の頂点番号を入れるキュー
        color[v] = 0;
        que.push(v);
        // キューに要素が残っている限り
        while(que.size() > 0) {
            int qv = que.front();
            que.pop();
            // 頂点 qv に隣接している頂点 nv について、
            for(auto nv : G[qv]) {
                // nv がすでに探索済みならば、スキップする
                if(color[nv] != -1) {
                    // 隣り合う頂点どうしが同じ色なら、答えは No
                    if(color[nv] == color[qv]) {ans = "No";}
                    continue;
                }
                // そうでなければ、頂点 nv の色を color[qv] と逆にしたうえで、nv も探索候補に入れる
                color[nv] = 1 - color[qv];
                que.push(nv);
            }
        }
    }
    // 答えを出力する
    cout << ans << endl;

	return 0;
}