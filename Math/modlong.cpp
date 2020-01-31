#include <cassert>
#define MOD (long)(1e9 + 7)
#define MAX 2000000  // 階乗をいくつまで計算するか

class modlong {
    long val;
    static const long mod = MOD;
    static long *invs, *facts, *finvs;

    // 階乗, 逆元, 階乗の逆元をMAXまで求める
    bool initModlong() {
        invs[1] = 
        facts[0] = facts[1] =
        finvs[0] = finvs[1] = 1;
        for (int i=2; i<=MAX; i++) {
            invs[i]  = -invs[MOD % i] * (MOD / i) % MOD;
            facts[i] = facts[i - 1] * i % MOD;
            finvs[i] = finvs[i - 1] * invs[i] % MOD;
        }
        return true;
    }

public:
    // 初期化 値を引数に与えなかった場合はval=0としておく
    modlong(long init = 0) : val(init) {
        static bool call_once = initModlong(); // static変数の性質により一度だけ呼ばれる
        assert(call_once); // unusedの回避
        if (val < 0 || val >= mod) val %= mod;
        if (val < 0) val += mod;   // 0以上であることを保証
    }

    // longへのキャスト operator long()で定義すると modlong +
    // longとかができなくなる
    inline long tol() { return this->val; }

    // 代入
    void operator=(const modlong &r) { this->val = r.val; }
    void operator=(const long &r) { *this = modlong(r); }

    // 足し算; 符号反転; 引き算
    modlong operator+(const modlong &r) {
        long ans = this->val + r.val;
        if (ans >= mod) ans -= mod;
        return modlong(ans);
    }
    modlong operator-() {
        long ans = mod - this->val;
        return modlong(ans);
    }
    modlong operator-(const modlong &r) {
        modlong rr = r;
        return *this + (-rr);
    }

    //かけ算; 逆元; わり算
    modlong operator*(const modlong &r) {
        long ans = this->val * r.val;
        return modlong(ans);
    }
    modlong inv() {
        assert(*this != 0);
        if (*this == 1) return modlong(1);

        modlong p, q = *this, m(0), n(1), r, c;
        p.val = mod;  // p=modとかくとp.val=mod%mod=0となってしまう
        while (q > MAX) {
            r = p.val % q.val;  // r.val=p.val % q.val
                                // とかくよりもこのほうが代入時に%modされるので安全
            c = m.val - n.val * (p.val / q.val);
            p = q, q = r, m = n, n = c;
        }
        return n * invs[q.val];
    }
    modlong operator/(const modlong &r) { return *this * modlong(r).inv(); }

    // ++ -- 前付きと後ろ付き
    void operator++() { ++this->val; }
    void operator++(int a) {
        a = 0;
        this->val++;
    }  // a使ってなくねっていうwarningをsilenceするためにaをいじってる
    void operator--() { --this->val; }
    void operator--(int a) {
        a = 0;
        this->val--;
    }

    // 四則演算&代入
    void operator+=(const modlong &r) { *this = *this + r; }
    void operator-=(const modlong &r) { *this = *this - r; }
    void operator*=(const modlong &r) { *this = *this * r; }
    void operator/=(const modlong &r) { *this = *this / r; }

    // べき乗
    modlong pow(long n) {
        if (n < 0)
            return inv().pow(-n);  // 逆元の-n乗
        else if (n == 0)
            return modlong(1);

        modlong half = pow(n / 2);
        if (n % 2)
            return *this * half * half;
        else
            return half * half;
    }
    modlong pow(modlong n) { return pow(n.val); }

    // コンビネーション
    modlong comb(modlong _k) {
        assert(this->val <= MAX);
        const long n = this->val, k = _k.val;
        if (k < 0 || k > n) return 0;
        if (k == 0 || k == n) return 1;
        return modlong(facts[n]) * finvs[k] * finvs[n - k];
    }

    // 階乗
    modlong fact() { 
        assert(this->val <= MAX);
        return modlong(facts[this->val]);
    }

    friend bool operator<(const modlong &l, const modlong &r);
    friend bool operator>(const modlong &l, const modlong &r);
    friend bool operator==(const modlong &l, const modlong &r);
    friend bool operator!=(const modlong &l, const modlong &r);
    friend bool operator<=(const modlong &l, const modlong &r);
    friend bool operator>=(const modlong &l, const modlong &r);
    friend ostream &operator<<(ostream &os, const modlong &out);
    friend istream &operator>>(istream &is, modlong &out);
};

//比較
bool operator<(const modlong &l, const modlong &r) { return l.val < r.val; }
bool operator>(const modlong &l, const modlong &r) { return l.val > r.val; }
bool operator==(const modlong &l, const modlong &r) { return l.val == r.val; }
bool operator!=(const modlong &l, const modlong &r) { return !(l == r); }
bool operator<=(const modlong &l, const modlong &r) { return !(l > r); }
bool operator>=(const modlong &l, const modlong &r) { return !(l < r); }

// cout、cerr、cin用の演算子たち
ostream &operator<<(ostream &os, const modlong &out) {
    os << out.val;
    return os;
}
istream &operator>>(istream &is, modlong &in) {
    long inl;
    is >> inl;
    in.val = inl % MOD;
    return is;
}

// コンビネーション
inline modlong modComb(long n, long k) { return modlong(n).comb(k); }
// 階乗
inline modlong modFact(long n) { return modlong(n).fact(); }

// static変数たち
long *modlong::invs  = new long[MAX+1],
     *modlong::facts = new long[MAX+1],
     *modlong::finvs = new long[MAX+1];