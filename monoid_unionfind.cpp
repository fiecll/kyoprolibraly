// 可換モノイドを乗せたUnion-Find構造体
// 各連結成分のモノイド値を管理する
template<typename T, typename MonoidOp>
class MonoidUnionFind {
private:
    std::vector<int> parent; // 親ノード
    std::vector<int> size;   // 各木のサイズ
    std::vector<T> data;     // 各連結成分のモノイド値
    int num_groups;          // グループの数
    MonoidOp op;             // モノイド演算

public:
    // コンストラクタ
    MonoidUnionFind(const std::vector<T>& initial_data, MonoidOp op)
        : parent(initial_data.size()), size(initial_data.size(), 1), data(initial_data), num_groups(initial_data.size()), op(op) {
        for (int i = 0; i < parent.size(); ++i)
            parent[i] = i;
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
    // 既に同じグループの場合はfalseを返す
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y)
            return false;

        // サイズによる合併
        if (size[x] < size[y])
            std::swap(x, y);

        parent[y] = x;
        size[x] += size[y];
        data[x] = op(data[x], data[y]); // モノイド値を更新
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
    int num_groups() const {
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
};