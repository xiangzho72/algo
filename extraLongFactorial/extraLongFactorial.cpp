#include <vector>
#include <iostream>
using namespace std;
void extraLongFactorial(int n)
{
    vector<int> res;
    
    res.push_back(1);

    for ( int i=2; i<=n; i++) {
        for ( auto it = res.begin(); it != res.end(); it++) {
            *it *= i;
        }

        for (int j=0; j< res.size(); j++) {
            if ( res[j] < 10 ) continue;

            if ( j == res.size() - 1 ) res.push_back(0);
            res[j+1] += res[j]/10;
            res[j] = res[j] % 10;
        }
    }

    for (auto it = res.rbegin(); it < res.rend(); it++) {
        cout << *it;
    }

}


int main()
{
    int n = 25;
    extraLongFactorial(n);
    return 0;
}

