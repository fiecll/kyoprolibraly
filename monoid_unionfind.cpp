template<typename T, typename MonoidOp>
class MonoidUnionFind {
private:
    std::vector<int> parent; // 親ノード
    std::vector<int> size;   // 各木のサイズ
    std::vector<T> data;     // 各連結成分のモノイド値
    int num_groups;          // グループの数
    MonoidOp op;             // モノイド演算
    T identity;              // モノイドの単位元
    std::unordered_map<T, int> value_count;  // 各モノイド値の出現回数を管理

public:
    // コンストラクタ
    MonoidUnionFind(const std::vector<T>& initial_data, MonoidOp op, T identity)
        : parent(initial_data.size()), size(initial_data.size(), 1), data(initial_data),
          num_groups(initial_data.size()), op(op), identity(identity) {
        for (int i = 0; i < parent.size(); ++i) {
            parent[i] = i;
            value_count[data[i]]++;
        }
    }

    // xの根を見つける（経路圧縮あり）
    int root(int x) {
        if (parent[x] == x)
            return x;
        else {
            parent[x] = root(parent[x]); // 経路圧縮
            return parent[x];
        }
    }

    // xとyが同じグループに属するかを判定
    bool same(int x, int y) {
        return root(x) == root(y);
    }

    // xとyのグループを併合
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;

        if (size[x] < size[y]) std::swap(x, y);

        // 古い値を削除
        value_count[data[x]]--;
        value_count[data[y]]--;
        if (value_count[data[x]] == 0) value_count.erase(data[x]);
        if (value_count[data[y]] == 0) value_count.erase(data[y]);

        // グループを統合
        parent[y] = x;
        size[x] += size[y];
        data[x] = op(data[x], data[y]);

        // 新しい値を追加
        value_count[data[x]]++;
        --num_groups;

        return true;
    }

    // xが属するグループのサイズを取得
    int same_count(int x) {
        return size[root(x)];
    }

    // xが属するグループのモノイド値を取得
    T same_data(int x) {
        return data[root(x)];
    }

    // グループの数を取得
    int group_count() const {
        return num_groups;
    }

    // グループを取得
    std::vector<std::vector<int>> groups() {
        int n = parent.size();
        std::vector<int> root_ids(n);
        std::vector<int> group_size(n);
        for (int i = 0; i < n; ++i) {
            root_ids[i] = root(i);
            group_size[root_ids[i]]++;
        }
        std::vector<std::vector<int>> result(n);
        for (int i = 0; i < n; ++i) {
            result[root_ids[i]].push_back(i);
        }
        // 空でないグループのみを収集
        std::vector<std::vector<int>> groups;
        for (auto& group : result) {
            if (!group.empty())
                groups.push_back(group);
        }
        return groups;
    }

    // 指定した要素の値を更新
    void update(int x, const T& new_value) {
        int rx = root(x);

        // 古い値を削除
        value_count[data[rx]]--;
        if (value_count[data[rx]] == 0) value_count.erase(data[rx]);

        // 値を更新
        data[x] = new_value;

        // グループ全体の値を再計算
        data[rx] = recalculate(rx);

        // 新しい値を追加
        value_count[data[rx]]++;
    }

    // 指定したモノイド値を持つグループの数を返す
    int count_groups_with_value(const T& target_value) const {
        auto it = value_count.find(target_value);
        return (it != value_count.end()) ? it->second : 0;
    }

private:
    // 指定したルートノードの値を再計算
    T recalculate(int root_node) {
        T result = identity;
        for (int i = 0; i < parent.size(); ++i) {
            if (root(i) == root_node) {
                result = op(result, data[i]);
            }
        }
        return result;
    }
};
