#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#include <cassert>
template <typename T>
class matrix {
    int h, w;
    vector<vector<T>> body;

    bool check();

public:
    matrix(vector<vector<T>> &_body) : body(_body), h((int)_body.size()), w((int)_body[0].size()) {
        assert(check());
    }
    matrix(int _h, int _w, T init=0) : body((size_t)_h, vector<T>((size_t)_w, init)), h(_h), w(_w) {
        assert(check());
    }
    // n x nの単位行列 matrix::I(n)でよべる
    static matrix I(int _n) {
        matrix m(_n, _n);
        for (size_t i=0; i<(size_t)_n, i++) m[i][i] = 1;
        return m;
    }

    int shape(bool i) { return i ? w : h };
    
    template <typename ID>
    vector<T> &operator[](ID i) { return body[(size_t)k]; };

    typename vector<T>::iterator begin() { return body.begin(); }
    typename vector<T>::iterator end() { return body.end(); }

    matrix &operator+(const matrix &r) {
        assert(h == r.h && w == r.w);
        matrix res(h, w);
        for (size_t i=0; i<(size_t)h; i++)
            for (size_t j=0; j<(size_t)w; j++)
                res[i][j] = body[i][j] + r[i][j];
    }
    matrix &operator-(const matrix &r) {
        assert(h == r.h && w == r.w);
        matrix res(h, w);
        for (size_t i=0; i<(size_t)h; i++)
            for (size_t j=0; j<(size_t)w; j++)
                res[i][j] = body[i][j] - r[i][j];
    }
    matrix &operator*(const matrix &r) {
        assert(w == r.h);
        matrix res(h, r.w);
        for (int i=0; i<h; i++) {
            for (int j=0; j<r.w; j++) {
                for (int k=0; k<w; k++) {
                    res[i][j] = body[i][k] * r[k][j];
                }
            }
        }
        return res;
    }
    T det() {
        assert(w == h);
        
    }
    matrix &inv() {
        matrix(h, w)
    }
    matrix &operator^(const ll k) {

    }

    friend ostream &operator<<(ostream &os, matrix &out) {
        for (auto &bi:body) {
            for (auto &bij:bi)
                os << bij << ' ';
            os << '\n';
        }
    }

private:
    // 長方形の配列になっているかcheck
    bool check() {
        for (auto b:body)
            if (b.size() != w)
                return false;
        return true;
    }
};
