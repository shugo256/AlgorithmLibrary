/*
verified on 2019/12/13
vec2d<double> -> https://atcoder.jp/contests/agc021/submissions/8932641
vec2d<long>   -> https://atcoder.jp/contests/abc022/submissions/8932886
*/

#include <iostream>

using namespace std;


/* ここからスニペット */
#include <cmath>
#include <numeric>
#include <iomanip>

// abs, cos_between関数の戻り値の精度
using AbsType = double; // 基本doubleで大丈夫

template <typename T>
struct vec2d {
    T x, y;
    vec2d() = default;
    vec2d(T _x, T _y)
        : x(_x)
        , y(_y) {}
    
    vec2d operator+=(const vec2d &v) { 
        x += v.x; 
        y += v.y;
        return *this; 
    }
    vec2d operator-=(const vec2d &v) { 
        x -= v.x; 
        y -= v.y;
        return *this; 
    }
    vec2d operator*=(const T &a) { 
        x *= a; 
        y *= a;
        return *this; 
    }
    vec2d operator/=(const T &a) { 
        x /= a; 
        y /= a;
        return *this; 
    }
    vec2d operator+(const vec2d &v) { return vec2d(*this) += v; }
    vec2d operator-(const vec2d &v) { return vec2d(*this) -= v; }
    vec2d operator*(const T &a) { return vec2d(*this) *= a; }
    vec2d operator/(const T &a) { return vec2d(*this) /= a; }
    vec2d operator-() { return vec2d(0, 0) - *this; }

    bool operator<(const vec2d &v)  { return (x != v.x ? x < v.x : y < v.y); }
    bool operator>(const vec2d &v)  { return (x != v.x ? x > v.x : y > v.y); }
    bool operator==(const vec2d &v) { return x == v.x && y == v.y; }
    bool operator<=(const vec2d &v) { return !(*this > v); }
    bool operator>=(const vec2d &v) { return !(*this < v); }
    bool operator!=(const vec2d &v) { return !(*this == v); }

    // 内積, 外積
    T dot(vec2d v)   { return x * v.x + y * v.y; }
    T cross(vec2d v) { return x * v.y - y * v.x; }

    // 絶対値、単位ベクトル
    AbsType abs() { return hypot((AbsType)x, (AbsType)y); }
    vec2d unit() { return *this / abs(); }

    // なす角のcos
    AbsType cos_between(vec2d v) { return unit().dot(v.unit()); }
};


template <typename T> T dot(vec2d<T> a, vec2d<T> b)   { return a.dot(b); }
template <typename T> T cross(vec2d<T> a, vec2d<T> b) { return a.cross(b); }
template <typename T> AbsType cos_between(vec2d<T> a, vec2d<T> b) { return a.cos_between(b); }

template <typename T>
istream &operator>>(istream &is, vec2d<T> &v) {
    is >> v.x >> v.y;
    return is;
}
template <typename T>
ostream &operator<<(ostream &os, const vec2d<T> &v) {
    os << setprecision(15) << fixed << v.x << ' ' << v.y;
    return os;
}

template <typename T>
// 点集合vvに対して凸包を作る
// ansに凸包の各点(vvでのインデックス)が入る
// 戻り値はansのサイズ
int convex_hull(vector<vec2d<T>> &vv, vector<int> &ans) {
    int n = (int)vv.size();
    size_t k = 0;
    vector<size_t> lid((size_t)n), _ans((size_t)n * 2);

    // vvを辞書順ソートしたときのインデックスの順列を作る
    iota(lid.begin(), lid.end(), 0);
    sort(lid.begin(), lid.end(), [&vv](size_t l, size_t r) {
        return vv[l] < vv[r];
    });

    // 下側
    for (int i=0; i<n; i++) {
        while (k > 1 && cross(vv[_ans[k-1]] - vv[_ans[k-2]], vv[lid[(size_t)i]] - vv[_ans[k-1]]) <= 0)
            k--;
        _ans[k] = lid[(size_t)i];
        k++;
    }

    // 上側
    for (int i=n-2, s=(int)k; i>=0; i--) {
        while ((int)k > s && cross(vv[_ans[k-1]] - vv[_ans[k-2]], vv[lid[(size_t)i]] - vv[_ans[k-1]]) <= 0)
            k--;
        _ans[k] = lid[(size_t)i];
        k++;
    }

    for (size_t i=0; i<k-1; i++) ans.push_back((int)_ans[i]);

    return (int)k-1;
}

using V = vec2d<double>;