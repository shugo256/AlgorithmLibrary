#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

/* snippet starts */

namespace graph {

    // dijkstra法
    template<typename dist_t>
    class Dijkstra {
        using elem_t = pair<int, dist_t>;

        int n, // 頂点数
            m; // 辺の数

        bool directed,           // 有向グラフかどうか
             edge_length_input,  // 入力で辺の長さが与えられるかどうか(ない場合全て1に)
             zero_indexed_input; // 入力で与えられる頂点が0-indexedかどうか
        vector<elem_t> *G;
    
    public:

        Dijkstra(int _n, int _m, bool _directed=false, bool _edge_length_input=false, bool _zero_indexed_input=false) 
            : n(_n)
            , m(_m)
            , directed(_directed)
            , edge_length_input(_edge_length_input)
            , zero_indexed_input(_zero_indexed_input)
            , G(new vector<elem_t>[n]) {}

        Dijkstra(int _n, bool _directed, vector<elem_t> *_G)
            : n(_n)
            , directed(_directed)
            , G(_G) {}

        inline void add_edge(int from, int to, dist_t dist) {
            G[from].push_back(elem_t{to, dist});
            if (!directed) G[to].push_back(elem_t{to, dist});
        }

        friend istream &operator>>(istream &is, modlong &in) {
            dist_t d = 1;
            for (int i=0, u, v; i<m; i++) {
                is >> u >> v;
                if (edge_length_input) is >> d;
                if (!zero_indexed_input) { u--; v--; }
            }
        }

        inline dist_t *operator()(int start) {
            dist_t *d = new dist_t[n];
            fill(d, d+n, INF); 
            d[start] = 0;
            priority_queue< elem_t, vector<elem_t>, greater<elem_t> > que;
            que.push(elem_t{0, k});
            while (!que.empty()) {
                elem_t p = que.top(); que.pop();
                int now = p.first;
                if (d[now] < p.second) continue;
                for (auto g:G[now]) {
                    int to = g.first;
                    dist_t newd = g.second + d[now];
                    if (d[to] > newd) {
                        d[to] = newd;
                        que.push(elem_t(d[to], to));
                    }
                }
            }
            return d;
        }

        auto &operator[](int i) { return G[i]; } 
        auto begin() { return G; }
        auto end()   { return G + n; }
    };

    // 隣接行列クラス
    // - 
    class AdjacencyMatrix {
        
    };
}

/* snippet ends */

int main() {
    int n;
    cin >> n;
    cout << n << '\n';
    return 0;
}