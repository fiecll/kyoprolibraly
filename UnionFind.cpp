struct UnionFind {
    vector<int> par;
    vector<int> rank;  // 追加：木の高さを管理
    vector<int> size;  // 追加：各木のサイズを管理
    int group_count;   // 追加：グループ数を管理

    UnionFind(int N) : par(N), rank(N, 0), size(N, 1) {
        for(int i = 0; i < N; i++) par[i] = i;
        group_count = N;  // 初期状態ではN個のグループ
    }

    int root(int x) {
        if (par[x] == x) return x;
        return par[x] = root(par[x]);  // 経路圧縮
    }

    void unite(int x, int y) {
        int rx = root(x);
        int ry = root(y);
        if (rx == ry) return;
        
        // ランクが小さい方を大きい方に繋ぐ
        if (rank[rx] < rank[ry]) {
            par[rx] = ry;
            size[ry] += size[rx];
        } else {
            par[ry] = rx;
            size[rx] += size[ry];
            if (rank[rx] == rank[ry]) rank[rx]++;
        }
        group_count--;  // グループ数を減らす
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    // サイズ取得
    int get_size(int x) {
        return size[root(x)];
    }

    // グループ数取得
    int get_group_count() {
        return group_count;
    }
};