/*
verified on 2019/12/18
http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4056258#2
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using ll = long long;

using namespace std;


// Ford-Fulkerson法用名前空間(使いたかっただけ)
/*
 * 最大流量をF, 辺の数をMとして O(FM)
 * だが、蟻本曰くこんなにかかることはまずなく、一見危なそうでも意外と大丈夫らしい
 */

namespace FordFulkerson {
    const int MAX_N = 1000010;
    const ll INF = 10000000000000;

    struct edge {
        int to;
        ll cap;
        int rev; // 行先, 容量, 逆辺
    };
    int timestamp = 0;

    int used[MAX_N];
    vector<edge> G[MAX_N];

    // 辺の追加、ちょいめんどいので関数
    // f -> tに向かう流量がcr以上、c以下となるエッジを追加
    // 無向グラフの場合は directed = falseとする
    void add_edge(int f, int t, int c=0, bool directed=true) {
        G[f].push_back({t, c, (int)G[t].size()});
        G[t].push_back({f, (directed ? 0 : c), (int)G[f].size() - 1});
    }
    
    // 今の頂点v, ゴールt, vに流せる最大流量flow
    // 返り値dは最終的に流した流量
    ll dfs(int v, int t, ll flow) {
        used[v] = timestamp;
        if (v == t) return flow;
        for (auto &g:G[v]) {
            if (used[g.to] != timestamp && g.cap > 0) {
                ll d = dfs(g.to, t, min(flow, g.cap));
                if (d > 0) {
                    // 容量の更新
                    g.cap -= d;
                    G[g.to][(size_t)g.rev].cap += d;
                    return d;
                }
            }
        }
        return 0; // どこにも流せなければ0
    }

    ll max_flow(int s, int t) {
        ll flow = 0;
        fill(begin(used), end(used), -1);
        for (ll f; (f = dfs(s, t, INF)) > 0; timestamp++) {
            flow += f;
        }
        return flow;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i=0, u, v, c; i<m; i++) {
        cin >> u >> v >> c;
        FordFulkerson::add_edge(u, v, c);
    }
    cout << FordFulkerson::max_flow(0, n-1) << '\n';
    return 0;
}