#include <algorithm>

struct uftree {
    int n, *par, *rank, *size;
    uftree(int N) : n(N) {
        par = new int[(size_t)N];
        rank = new int[(size_t)N];
        size = new int[(size_t)N];
        for (int i = 0; i < N; i++) {
            par[i]  = i;
            rank[i] = 0;
            size[i] = 1;
        }
    }
    int root(int x) {
        if (par[x] == x)
            return x;
        else {
            int r         = root(par[x]);
            size[x]       = size[par[x]];
            return par[x] = r;
        }
    }
    void unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return;
        if (rank[x] > rank[y])
            par[y] = x;
        else {
            par[x] = y;
            if (rank[x] == rank[y]) rank[y]++;
        }
        size[x] += size[y];
        size[y] = size[x];
    }
    int get_size(int x) {
        root(x);
        return size[x];
    }
    bool same(int x, int y) { return root(x) == root(y); }

    // 集合の数をカウントする関数
    // 1..nのつもりでやってる場合も0をカウントしちゃうので注意
    int count_sets() {
        int cnt = 0;
        bool used[n];
        fill(used, used+n, false);
        for (int i=0; i<n; i++) {
            if (used[root(i)]) continue;
            cnt++;
            used[root(i)] = true;
        }
        return cnt;
    }
};

// 重み付きver
struct uftree_w {
    int *par, *rank, *w_dif;  // w_difは親との重みの差
    uftree_w(int N) {
        par = new int[(size_t)N];
        rank = new int[(size_t)N];
        w_dif = new int[(size_t)N];
        for (int i = 0; i < N; i++) {
            par[i] = i;
            rank[i] = 0;
            w_dif[i] = 0;
        }
    }
    int root(int x) {
        if (par[x] == x)
            return x;
        else {
            int r = root(par[x]);
            w_dif[x] += w_dif[par[x]];
            return par[x] = r;
        }
    }
    int weight(int x) {
        root(x);  //経路圧縮
        return w_dif[x];
    }
    bool unite(int x, int y, int d) {
        d += weight(x) - weight(y);  //根っこ同士をつなぐので
        x = root(x);
        y = root(y);
        if (x == y) return d == 0;
        if (rank[x] > rank[y]) {
            par[y] = x;
            w_dif[y] = d;
        } else {
            par[x] = y;
            w_dif[x] = -d;
            if (rank[x] == rank[y]) rank[y]++;
        }
        return true;
    }
    bool same(int x, int y) { return root(x) == root(y); }
};