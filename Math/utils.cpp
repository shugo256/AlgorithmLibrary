#include <cstdio>
#include <numeric>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

#define mod (long)(1e9 + 7)
#define INF (long)1e15
#define MAX_N 100001

using namespace std;

// 最大公約数
template <typename T>
T gcd(T a, T b) {
    if (a > b) {
        T buf = a;
        a = b;
        b = buf;
    }
    return a == 0 ? b : gcd(a, b%a);
}

// 最小公倍数
template <typename T>
T lcm(T a, T b) {
    return a / gcd(a, b) * b;
}


// 分割数 sum個のものをn個以下のグループに分ける方法
// ex) sum=4,n=3なら 4=1+1+2=1+3=2+2=4で4通り
int partition(int n, int sum) {
    int dp[n + 1][sum + 1];
    fill(dp[0], dp[n+1], 0);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            dp[i][j] = (dp[i - 1][j] + (j - i >= 0 ? dp[i][j - i] : 0)) % mod;
        }
    }
    return dp[n][sum];
}

// べき乗 powのint高速化ver
long powi(int x, int n) {
    if (n <= 0) return 1;
    else {
        long xn = powi(x, n/2);
        if (n%2 == 0) return xn*xn;
        else return xn*xn*x;
    }
}

// 素数判定 2からfor分で回して行く limitはどこまでやるか エラトステネスの篩
bool isPrime[100011];
void computePrimes(int limit = 100010) {
    assert(limit < 100011);                    // #include <cassert>
    fill(isPrime, isPrime + limit + 1, true);  //最初全部trueにしておく
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= limit; i++)
        if (isPrime[i])
            for (int j = 2 * i; j <= limit; j += i) isPrime[j] = false;
}
