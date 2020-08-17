//
// エラトステネスの篩
//


/*

    n 以下の素数をすべて列挙する

*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// isprime[i] iが素数なら1,素数でないなら0
vector<int> isprime;

vector<int> Era(int n) {
    isprime.resize(n, 1);
    vector<int> res;
    isprime[0] = 0; isprime[1] = 0;
    for (int i = 2; i < n; ++i) isprime[i] = 1;
    for (int i = 2; i < n; ++i) {
        if (isprime[i]) {
            res.push_back(i);
            for (int j = i*2; j < n; j += i) isprime[j] = 0;
        }
    }
    return res;
}

//primes...100000未満の素数の配列
vector<int> primes = Era(100000);

int main() {
    int n;
    while (cin >> n) {
        int num = upper_bound(primes.begin(), primes.end(), n) - primes.begin(); // n 以下が何個か
        cout << num << endl;
    }
}