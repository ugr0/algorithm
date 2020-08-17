/*
二分探索めぐる式

入力: a(n), key
出力: keyがどこに入るか
*/

#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, key; cin >> n >> key;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];

    int ng = -1;
    int ok = (int)a.size();

    while(abs(ok - ng) > 1){
        int mid = (ng + ok) / 2;
        auto f = [&](int idx){
            //条件判定が>=であればlower_bound、>であればupper_bound
            if(a[idx]>= key) return true;
            else return false;
        };

        if(f(mid)) ok = mid;
        else ng = mid;
    }

    cout << ok << endl;
}