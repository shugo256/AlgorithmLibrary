/*
最短距離のアルゴリズムたち
- ベルマンフォード
- ダイクストラ
- ワーシャル-フロイド
*/


#include <algorithm>
#include <queue>

#define MAX_N 100000
#define INF 100000000000000

using P = pair<int, int>;
#define fi first
#define se second

using namespace std;

/*
verified on 2019/8/12
https://atcoder.jp/contests/abc137/submissions/6863681
*/

int n, m;
long d[MAX_N];
bool negative[MAX_N];
struct edge {
    long from, to, cost;
};
vector<edge> edges;  // 長さM
// ベルマンフォード法でstartから各点までの最短距離を計算する O(MN)
// checkLoop=trueかつ負のループがある場合は負のループにより最短距離が
// -INFになってしまう点を検出し、negativeに格納
// 要するにnegativeは負のループと繋がってる部分がtrueになる
void bellmanFord(int start, bool checkLoop = false) {
    fill(d, d + n, INF);
    fill(negative, negative + n, false);
    d[start] = 0;
    bool negloop = false;
    for (int i = 1; i < n; i++) {
        for (auto e : edges) {
            if (d[e.from] == INF) continue;
            if (d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                if (i == n - 1) negloop = true;
            }
        }
    }
    if (!checkLoop || !negloop) return;
    for (int i = 0; i < n; i++) {
        for (auto e : edges) {
            if (d[e.from] == INF) continue;
            if (d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                negative[e.to] = true;
            } else if (negative[e.from])
                negative[e.to] = true;
        }
    }
}


// 各点への最短経路 dijkstra
long d[MAX_N];  //頂点kから各点への距離
vector<P> G[MAX_N]; //隣接行列
int n; 
void dijkstra(int k) { //Gは隣接行列 G[i][j].firstが距離, secondが向かう頂点名, kはスタートする頂点
    fill(d, d+n, INF); d[k] = 0;
    priority_queue< P, vector<P>, greater<P> > que;
    que.push(P(0, k));
    while (!que.empty()) {
        P p = que.top(); que.pop();
        int now = p.second;
        if (d[now] < p.first) continue;
        for (auto g:G[now]) {
            int to = g.second;
            long newd = g.first + d[now];
            if (d[to] > newd) {
                d[to] = newd;
                que.push(P(d[to], to));
            }
        }
    }
}


/*
verified on 2019/8/21
https://codeforces.com/contest/1204/submission/59164946
*/

// 全対全の距離を求める N^3
int n;
long d[MAX_N][MAX_N]; // i->jのコスト あらかじめINF初期化してから入力を反映させる
void warshall_floyd() { 
    for (int k=0; k<n; k++)
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}