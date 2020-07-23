//
// 正の整数 n の約数を列挙する, O(√n)
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


vector<long long> calc_divisor(long long n) {
    vector<long long> res;
    for (long long i = 1LL; i*i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            long long j = n / i;
            if (j != i) res.push_back(j);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

int main() {
    long long N;
    cin >> N;
    vector<long long> div = calc_divisor(N);
    
    for (auto x: div){
        cout << x << endl;
    }
    
}