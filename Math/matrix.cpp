/*
operator* verified on 2020/4/1
https://onlinejudge.u-aizu.ac.jp/status/users/shugo256/submissions/1/ITP1_7_D/judge/4312230/C++14
pow_self verified on 2020/4/1
https://atcoder.jp/contests/ddcc2020-final/submissions/11411714
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

    void swap(matrix& m) {
        this->body.swap(m.body);
        std::swap(this->h, m.h);
        std::swap(this->w, m.w);
    }

public:
    matrix() = default;

    // 初期化子リスト matrix<T> mat{{0}, {1}, {2}}; みたいにかける
    matrix(initializer_list<initializer_list<T>> _body) {
        for (auto &bi:_body) body.emplace_back(bi);
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
        for (int i=0; i<_n; i++) {
            m[i][i] = 1;
        }
        return m;
    }

    pair<int, int> &shape() { return {h, w}; };
    
    vector<T> &operator[](int i) { return body[(size_t)i]; }
    const vector<T> &operator[](int i) const { return body[(size_t)i]; }

    auto begin() { return body.begin(); }
    auto end() { return body.end(); }
    auto begin() const { return body.begin(); }
    auto end() const { return body.end(); }

    inline matrix &operator+=(const matrix &r) {
        assert(h == r.h && w == r.w);
        matrix res(h, w);
        for (size_t i=0; i<(size_t)h; i++)
            for (size_t j=0; j<(size_t)w; j++)
                res[i][j] = body[i][j] + r[i][j];
        this->swap(res);
        return *this;
    }
    inline matrix &operator-=(const matrix &r) {
        assert(h == r.h && w == r.w);
        matrix res(h, w);
        for (size_t i=0; i<(size_t)h; i++)
            for (size_t j=0; j<(size_t)w; j++)
                res[i][j] = body[i][j] - r[i][j];
        this->swap(res);
        return *this;
    }

    inline matrix &operator*=(const matrix &r) {
        assert(w == r.h);
        matrix res(h, r.w);
        for (size_t i=0; i<(size_t)h; i++) {
            for (size_t j=0; j<(size_t)r.w; j++) {
                for (size_t k=0; k<(size_t)w; k++) {
                    res[i][j] = body[i][k] * r[k][j] + res[i][j];
                }
            }
        }
        this->swap(res);
        return *this;
    }

    inline matrix operator+(const matrix &r) { return matrix(*this) += r; }
    inline matrix operator-(const matrix &r) { return matrix(*this) -= r; }
    inline matrix operator*(const matrix &r) { return matrix(*this) *= r; }

    // TODO
    // T det() {
    //     assert(w == h);
        
    // }
    // matrix &inv() {
    //     matrix(h, w)
    // }

    // O(N^3 logk)
    // 破壊的ver
    inline matrix &pow_self(ll k) {
        assert(h == w);
        // if (k < 0) return matrix.inv().pow(-k);
        matrix x = I(h);
        while(k > 0){
            if(k & 1){
                x *= *this;
            }
            *this *= *this;
            k >>= 1;
        }
        this->swap(x);
        return *this;
    }
    // 非破壊的ver
    inline matrix pow(ll k) { return matrix(*this).pow_self(k); }

    friend ostream &operator<<(ostream &os, const matrix<T> &out) {
        for (auto &oi:out) {
            if (&oi != &*out.begin()) os << '\n';
            for (auto &oij:oi)
                if (&oij == &*oi.begin()) os << oij;
                else os << ' ' << oij;
        }
        return os;
    }
    friend istream &operator>>(istream &is, matrix<T> &in) {
        for (auto &ini:in) {
            for (auto &inij:ini)
                is >> inij;
        }
        return is;
    }
};

/* snippet ends */


int main() {
    int n, m, l;
    cin >> n >> m >> l;
    matrix<ll> a(n, m), b(m, l);
    cin >> a >> b;
    cout << a * b << '\n';
}