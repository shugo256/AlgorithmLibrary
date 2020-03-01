/*
verified on 2020/3/1
http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4221790
*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

using ll = long long;


/* snippet starts */

#include <limits>

// 各点への最短経路 dijkstra
template<typename dist_t>
class Dijkstra {
    using elem_t = pair<dist_t, int>;

    int n, // 頂点数
        input_edge_num; // 辺の数

    bool directed,           // 有向グラフかどうか
         edge_length_input,  // 入力で辺の長さが与えられるかどうか(ない場合全て1に)
         zero_indexed_input; // 入力で与えられる頂点が0-indexedかどうか
    vector<elem_t> *G;

public:

    static const dist_t INF;

    Dijkstra(int _n, int _m, bool _directed=false, bool _edge_length_input=false, bool _zero_indexed_input=false) 
        : n(_n)
        , input_edge_num(_m)
        , directed(_directed)
        , edge_length_input(_edge_length_input)
        , zero_indexed_input(_zero_indexed_input)
        , G(new vector<elem_t>[(size_t)n]) {}

    Dijkstra(int _n, vector<elem_t> *_G, bool _directed=false)
        : n(_n)
        , directed(_directed)
        , G(_G) {}

    inline void add_edge(int from, int to, dist_t dist) {
        G[from].push_back(elem_t{dist, to});
        if (!directed) G[to].push_back(elem_t{dist, from});
    }

    friend istream &operator>>(istream &is, Dijkstra &in) {
        dist_t d = 1;
        for (int i=0, u, v; i<in.input_edge_num; i++) {
            is >> u >> v;
            if (in.edge_length_input) is >> d;
            if (!in.zero_indexed_input) { u--; v--; }
            in.add_edge(u, v, d);
        }
        return is;
    }

    struct result {
        result(int _n, int k) : n(_n), d(new dist_t[(size_t)_n]) {
            fill(d, d+n, INF); 
            d[k] = 0;
        }
        auto &operator[](int i) { return d[i]; } 
        auto begin() { return d; }
        auto end()   { return d + n; }
        operator dist_t*() { return d; } // dist_t* へのキャスト

        bool unreachable(int i) { return d[i] == INF; }  // 視点から到達不可能かどうか
    private:
        const int n;
        dist_t *d;
    };

    inline result operator()(int start) {
        result d(n, start);

        priority_queue< elem_t, vector<elem_t>, greater<elem_t> > que;
        que.push(elem_t{0, start});

        while (!que.empty()) {
            elem_t p = que.top(); que.pop();
            int now = p.second;
            if (d[now] < p.first) continue;

            for (auto &g:G[now]) {
                int to = g.second;
                dist_t newd = g.first + d[now];

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

template<typename dist_t>
const dist_t Dijkstra<dist_t>::INF = numeric_limits<dist_t>::max();

/* Constructers
 *
 * Dijkstra(int _n, int _m, bool _directed=false, bool _edge_length_input=false, bool _zero_indexed_input=false) 
 * Dijkstra(int _n, vector<elem_t> *_G, bool _directed=false)
 */

/* snippet ends */

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    Dijkstra<ll> dijk(n, m, true, true, true);
    cin >> dijk;
    ll *dist_raw = dijk(s);
    for (auto &di:dijk(s)) cout << (di < Dijkstra<ll>::INF ? to_string(di) : "INF") << '\n';
    // for (int i=0; i<n; i++) cerr << dist_raw[i] << '\n';
    return 0;
}