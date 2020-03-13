/*
convex_hull verified on 2020/3/13
https://atcoder.jp/contests/agc021/submissions/10802949

cross_point verified on 2020/3/14
http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4260596
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/* snippet starts */

#include <complex>
#include <numeric>
#include <iomanip>

#define X real()
#define Y imag()

// operator overload for complex<value_t>
namespace std {
    using value_t = double;

    inline bool operator<(const complex<value_t> l, const complex<value_t> r) {
        return (l.X != r.X ? l.X < r.X : l.Y < r.Y);
    }
    inline bool operator>(const complex<value_t> l, const complex<value_t> r) {
        return (l.X != r.X ? l.X > r.X : l.Y > r.Y);
    }
    inline bool operator<=(const complex<value_t> l, const complex<value_t> r) { return !(l > r); }
    inline bool operator>=(const complex<value_t> l, const complex<value_t> r) { return !(l < r); }
    istream &operator>>(istream &is, complex<value_t> &p) {
        value_t a, b;
        is >> a >> b;
        p = complex<value_t>(a, b);
        return is;
    }
    ostream &operator<<(ostream &os, const complex<value_t> &p) {
        return os << fixed << setprecision(10) << p.X << ' ' << p.Y;
    }
}

namespace geometry2d {
    using value_t = std::value_t;
    using point_t = complex<value_t>;

    // 内積, 外積, 単位ベクトル, なす角のcos
    inline value_t dot(point_t a, point_t b)   { return a.X * b.X + a.Y * b.Y; }
    inline value_t cross(point_t a, point_t b) { return a.X * b.Y - a.Y * b.X; }
    inline point_t unit(point_t p) { return p / abs(p); }
    inline value_t cos_between(point_t a, point_t b) { return dot(unit(a), unit(b)); }


    // 点集合pointsに対して凸包を作る
    // ansに凸包の各点(pointsでのインデックス)が入る
    // 戻り値はansのサイズ
    int convex_hull(vector<point_t> &points, vector<int> &ans) {
        int n = (int)points.size();
        size_t k = 0;
        vector<size_t> lid((size_t)n), _ans((size_t)n * 2);

        // pointsを辞書順ソートしたときのインデックスの順列を作る
        iota(lid.begin(), lid.end(), 0);
        sort(lid.begin(), lid.end(), [&points](size_t l, size_t r) {
            return points[l] < points[r];
        });

        // 下側
        for (int i=0; i<n; i++) {
            while (k > 1 && cross(points[_ans[k-1]] - points[_ans[k-2]], points[lid[(size_t)i]] - points[_ans[k-1]]) <= 0)
                k--;
            _ans[k] = lid[(size_t)i];
            k++;
        }

        // 上側
        for (int i=n-2, s=(int)k; i>=0; i--) {
            while ((int)k > s && cross(points[_ans[k-1]] - points[_ans[k-2]], points[lid[(size_t)i]] - points[_ans[k-1]]) <= 0)
                k--;
            _ans[k] = lid[(size_t)i];
            k++;
        }

        for (size_t i=0; i<k-1; i++) ans.push_back((int)_ans[i]);

        return (int)k-1;
    }

    // 円を表す構造体
    struct circle {
        point_t c; // center
        value_t r; // radius
    };

    pair<point_t, point_t> cross_point(circle a, circle b) {
        point_t vec_ab = b.c - a.c;
        value_t d = abs(vec_ab);
        value_t theta = arg(vec_ab);
        value_t alpha = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));
        point_t p1 = a.c + polar(a.r, theta + alpha);
        point_t p2 = a.c + polar(a.r, theta - alpha);
        return {p1, p2};
    }

} // namespace geometry2d

/* snippet ends */

/* switch define flag for each verification */
// #define CONVEX_HULL // https://atcoder.jp/contests/agc021/tasks/agc021_b
#define CROSS_POINT // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E&lang=ja

int main(){
#ifdef CONVEX_HULL
    int n;
    cin >> n;
    vector<geometry2d::point_t> points(n);
    for (auto &pi:points) cin >> pi;
    vector<int> ch;
    int m = geometry2d::convex_hull(points, ch);
    double ans[n];
    fill(ans, ans+n, 0);
    geometry2d::point_t prev = points[ch[m-1]];
    for (int i=0; i<m; i++) {
        geometry2d::point_t cur  = points[ch[i]];
        geometry2d::point_t next = points[ch[(i+1)%m]];
        ans[ch[i]] = acos(geometry2d::cos_between(cur - prev, next - cur)) / (2 * M_PI);
        prev = cur;
    }
    for (auto &ai:ans) cout << fixed << setprecision(15) << ai << '\n';
#endif

#ifdef CROSS_POINT
    geometry2d::circle a, b;
    cin >> a.c >> a.r >> b.c >> b.r;
    auto p = geometry2d::cross_point(a, b);
    if (p.first > p.second) swap(p.first, p.second);
    cout << p.first << ' ' << p.second << '\n';
#endif

    return 0;
}