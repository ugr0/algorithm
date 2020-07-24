//
// 素因数分解
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// 配列の場合
/*
    入力: n は 2 以上の整数
    出力: 540 = 2^2 × 3^3 × 5 の場合、({2, 2}, {3, 3}, {5, 1})
*/
// vector<pair<long long, long long> > prime_factorize(long long n) {
//     vector<pair<long long, long long> > res;
//     for (long long p = 2; p * p <= n; ++p) {
//         if (n % p != 0) continue;
//         int num = 0;
//         while (n % p == 0) { ++num; n /= p; }
//         res.push_back(make_pair(p, num));
//     }
//     if (n != 1) res.push_back(make_pair(n, 1));
//     return res;
// }


/*
 
 map 形式の出力:
 540 = 2^2 × 3^3 × 5 の場合、{2: 2, 3: 3, 5: 1}
 
 */

map<long long, long long> prime_factorize(long long n) {
    map<long long, long long> res;
    for (long long p = 2; p * p <= n; ++p) {
        while (n % p == 0) { ++res[p]; n /= p; }
    }
    if (n != 1) res[n] = 1;
    return res;
}


int main() {
    int n; cin >> n;
    map<long long, long long> res = prime_factorize(n);
    cout << "{ " ;
    for (auto x : res) {
        cout << x.first << ": " << x.second << " ";
    }
    cout << "}" << endl;
}
