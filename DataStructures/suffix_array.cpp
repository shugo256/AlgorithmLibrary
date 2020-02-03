/*
verified on 2020/2/3
https://atcoder.jp/contests/ddcc2020-final/submissions/9880042
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* snippet starts */

#define isLMS(i) (isL[(i)-1] && !isL[i])
#define LIMIT 200000

template <typename T>
class SuffixArray {
    vector<T> s;
    const size_t len,
                 limit;  // lenは配列長 limitは配列に登場する文字/数字の種類数
    vector<size_t> bin,  // 頭文字の各アルファベットの出現回数の累積和
                   cnt,  // どのアルファベットから始まるものをいくつsaに割り当てたか
                   lms,  // LMSのインデックスを格納する配列
                   isL,  // s[i]がL型なら1 S型なら0
                   sa;   // sのsuffix arrayをインデックスで格納する配列

public:
    vector<size_t> rank; // s[i:]が辞書順で何番目のsuffixか(saの逆写像)、番兵も

    // Tが整数の時よう
    SuffixArray(vector<T> s, size_t limit=LIMIT)
     : s(s),
       len(s.size()),
       limit(limit),
       bin(limit+1, 0),
       cnt(limit+1, 0),
       isL(len+1),
       sa(len+1),
       rank(len+1) {
           (this->s).push_back(0); // 末尾に番兵の追加
           lms.reserve(len/2);     // lmsの領域の確保
           sa_is();                // SAの構築
            for (size_t i=0; i<=len; i++)
                rank[sa[i]] = i; // rankの計算
    } 

    // Tがcharの時用
    SuffixArray(string s, size_t limit=256) : SuffixArray(vector<char>(s.begin(), s.end()), limit) {}

    // LCP(高さ配列、蟻本p339)を計算する
    // lcp[i] = sa[i]とsa[i+1]の先頭何文字が一致しているか
    // このlcpをRange Minimum Queryに載せれば任意のi jに対してlcpが計算可能
    vector<int> lcp;

    void construct_lcp() {
        lcp.resize(len);
        size_t h = 0;
        for (size_t i=0; i<len; i++) {
            size_t j = sa[rank[i] - 1];
            if (h > 0) h--;
            for ( ; i+h<len && j+h<len && s[i+h] == s[j+h]; h++);

            lcp[rank[i] - 1] = (int)h;
        }
    }

    auto begin() { return sa.begin(); }
    auto end()   { return sa.end(); }

    template <typename ID>
    int operator[](ID i) { return (int)sa[(size_t)i]; }

private:

    //SA-IS法によりSuffixArrayを構築する
    void sa_is() {
        isL[len] = false;
        bin[1] = 1;
        for (size_t i=len; i>0; i--) {
            isL[i-1] = (s[i-1] == s[i]) ? isL[i] : (s[i-1] > s[i]);
            bin[(size_t)s[i-1]+1]++;
            if (isLMS(i))
                lms.push_back(i);
        }

        vector<size_t> aligned(lms); // あとでlmsは色々並べ替えるが、ここに今の整列した状態を保存しておく
        reverse(aligned.begin(), aligned.end()); // 降順になっているのをひっくり返して昇順にする

        for (size_t i=0; i<limit; i++) bin[i+1] += bin[i]; // 累積和

        induced_sort(); // 1回目のinduced sort

        fill(sa.begin(), sa.end(), 0); // saにLMS部分文字列の順位を格納する
        size_t n = 0, lmslen = lms.size();

        // 辞書順で隣り合うLMSについて一致しているかどうか調べる(たかだかn回の比較)
        for (auto itr=lms.begin(); itr+1!=lms.end(); itr++) {
            size_t i = *itr, j = *(itr+1);
            for (size_t d=0; i+d <= len && j+d <= len; d++) {
                if (s[i+d] != s[j+d] || isLMS(i+d) != isLMS(j+d)) {
                    n++;
                    break;
                } else if (d > 0 && (isLMS(i+d) || isLMS(j+d)))
                    break;
            }
            sa[j] = n;
        }

        if (n < lmslen-1) {
            vector<size_t> next_s(lmslen-1);
            for (size_t i=0; i<lmslen-1; i++) { // alignedはここで使うために用意した
                next_s[i] = sa[aligned[i]];
                sa[aligned[i]] = 0; // saはまた0リセット
            }

            // sa-isを再帰的に用いる
            SuffixArray<size_t> next(next_s, n+1);

            for (size_t i=0; i<lmslen-1; i++)
                lms[i] = aligned[(size_t)next[lmslen-1-i]];
            lms[lmslen-1] = len;
        } else {
            for (auto i:aligned) 
                sa[i] = 0; // saを0リセット
        }

        fill(cnt.begin(), cnt.end(), 0);

        induced_sort();
    }

    // induced sortの3ステップを行う
    void induced_sort() {

        // step1:LMSをひとまず書き込んでいく
        for (auto i:lms) {
            size_t c = (size_t)s[i];
            cnt[c+1]++;
            sa[bin[c+1] - cnt[c+1]] = i;
        }

        fill(cnt.begin(), cnt.end(), 0);

        //step2:L型のsuffixを埋めていく
        for (auto i:sa) {
            if (i == 0 || !isL[i-1]) continue;
            size_t c = (size_t)s[i-1];
            sa[bin[c] + cnt[c]] = i-1;
            cnt[c]++;
        } 

        fill(cnt.begin(), cnt.end(), 0);
        auto lmsitr = lms.rbegin();

        //step3:S型のsuffixを埋めていく
        for (auto itr=sa.rbegin(); itr!=sa.rend(); itr++) {
            size_t i = *itr;
            if (i == 0) continue;
            if (isLMS(i)) { // ここでlmsをsaに出てくる順に並べ替えておく
                *lmsitr = i;
                lmsitr++;
            }
            if (isL[i-1]) continue;
            size_t c = (size_t)s[i-1];
            cnt[c]++;
            sa[bin[c+1] - cnt[c]] = i-1;
        }
    }
};

// 番兵を0としているので、sの要素は全部正にする(or番兵を変える)

/* snippet ends */