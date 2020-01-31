#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using ll = long long;

using namespace std;

/*
verified on 2019/10/16
https://atcoder.jp/contests/arc060/submissions/7988691
*/

#define LOG_MAX 30
// 1つ先が無い(木の根など)場合、値を負かn以上とする
template <typename T>
class Doubling {
    const size_t n;
    vector<vector<T>> next;
public:
    Doubling() {}
    Doubling(vector<T> first_row) 
    : n(first_row.size()), 
      next(LOG_MAX, vector<T>(n)) {
        copy(first_row.begin(), first_row.end(), next[0].begin());
        for (size_t i=1; i<LOG_MAX; i++) {
            for (size_t j=0; j<n; j++) {
                next[i][j] = (
                    (0 <= next[i-1][j] && (size_t)next[i-1][j] < n)
                    ? next[i-1][(size_t)next[i-1][j]]
                    : next[i-1][j]
                );
            }
        }
    }

    // iからstep回移動して到達できる場所をO(log(n))で返す
    T n_step(T i, int step=1) {
        for (int k=LOG_MAX-1; k>=0; k--) {
            if ((step >> k) & 1) i = next[(size_t)k][(size_t)i];
            if (i < 0 || n <= (size_t)i) break;
        }
        return i;
    }

    // 任意のi, sについて next[s][i] >= i or next[s][i] == -1
    // が成り立つ時のみ使用可能
    // iからj(jからi)に行くまでの距離をO(log(n))で計算
    T dist(T i, T j) {
        if (i > j) swap(i, j);
        int d = 0;
        for (int k=LOG_MAX-1; k>=0 && i < j; k--) {
            if (next[k][i] < j) {
                i = next[k][i];
                d += (1 << k);
            }
        }
        return d + 1;
    }
};