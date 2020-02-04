/*
verified on 2020/2/4
http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4155170
*/
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

/* snippet starts */

#include <cassert>
#include <initializer_list>

template <typename T>
class matrix {
    int h, w;
    vector<vector<T>> body;

    // 長方形の配列になっているかcheck
    bool check() {
        for (auto &b:body)
            if ((int)b.size() != w)
                return false;
        return true;
    }

public:
    matrix() = default;

    // 初期化子リスト matrix<T> mat{{0}, {1}, {2}}; みたいにかける
    matrix(initializer_list<initializer_list<T>> _body) {
        for (auto &bi:_body) body.emplace_back(vector<T>(bi.begin(), bi.end()));
        h = (int)body.size();
        w = (int)body[0].size();
        assert(check());
    }

    matrix(int _h, int _w, T init=0)
        : h(_h)
        , w(_w)
        , body((size_t)_h, vector<T>((size_t)_w, init)) {
    }
    // n x nの単位行列 matrix::I(n)でよべる
    static matrix I(int _n) {
        matrix m(_n, _n);
        for (size_t i=0; i<(size_t)_n; i++) m[i][i] = 1;
        return m;
    }

    pair<int, int> &shape() { return {h, w}; };
    
    template <typename ID> vector<T> &operator[](ID i) { return body[(size_t)i]; }
    template <typename ID> vector<T> operator[](ID i) const { return body[(size_t)i]; }

    auto begin() { return body.begin(); }
    auto end() { return body.end(); }
    auto begin() const { return body.begin(); }
    auto end() const { return body.end(); }

    matrix operator+(const matrix &r) {
        assert(h == r.h && w == r.w);
        matrix res(h, w);
        for (size_t i=0; i<(size_t)h; i++)
            for (size_t j=0; j<(size_t)w; j++)
                res[i][j] = body[i][j] + r[i][j];
        return res;
    }
    matrix operator-(const matrix &r) {
        assert(h == r.h && w == r.w);
        matrix res(h, w);
        for (size_t i=0; i<(size_t)h; i++)
            for (size_t j=0; j<(size_t)w; j++)
                res[i][j] = body[i][j] - r[i][j];
        return res;
    }
    matrix operator*(const matrix &r) {
        assert(w == r.h);
        matrix res(h, r.w);
        for (size_t i=0; i<(size_t)h; i++) {
            for (size_t j=0; j<(size_t)r.w; j++) {
                for (size_t k=0; k<(size_t)w; k++) {
                    res[i][j] += body[i][k] * r[k][j];
                }
            }
        }
        return res;
    }

    // TODO
    // T det() {
    //     assert(w == h);
        
    // }
    // matrix &inv() {
    //     matrix(h, w)
    // }

    // O(N^3 logk)
    matrix pow(const ll k) {
        assert(h == w);
        // if (k < 0) return matrix.inv().pow(-k);
        if (k <= 0) return matrix::I(h);
        else {
            matrix x = pow(k/2);
            if (k%2 == 0) return x * x;
            else return *this * x * x;
        }
    }
};

template <typename T>
ostream &operator<<(ostream &os, const matrix<T> &out) {
    for (auto &oi:out) {
        if (&oi != &*out.begin()) os << '\n';
        for (auto &oij:oi)
            if (&oij == &*oi.begin()) os << oij;
            else os << ' ' << oij;
    }
    return os;
}

template <typename T>
istream &operator>>(istream &is, matrix<T> &in) {
    for (auto &ini:in) {
        for (auto &inij:ini)
            is >> inij;
    }
    return is;
}

/* snippet ends */


int main() {
    int n, m, l;
    cin >> n >> m >> l;
    matrix<ll> a(n, m), b(m, l);
    cin >> a >> b;
    cout << a * b << '\n';
}