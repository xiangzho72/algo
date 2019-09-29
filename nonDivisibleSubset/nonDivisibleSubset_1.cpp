#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

//For any number K, the sum of 2 values (A & B) is evenly divisible by K if the sum of the remainders of A/K + B/K is K
//(There is also a special case where both A & B are evenly divisible, giving a sum of 0.)

//For any such remainder, there is 1 and only 1 other remainder value which will make a sum divisible by K.

//Example: with K of 5, remainder pairs are 1+4 & 2+3. Given the numbers with a remainder of 1, they can't be paired 
//with ANY of the numbers with remainder 4 (and vice versa). So, for the number of values in the resultant set, choose 
//the larger of values with remainder 1 vs. values with remainder 4. Choose the larger set of remainder 2 vs remainder 3
// Then added them up 
//
//For the special case where remainder is 0, given the set of all values which are individually divisible by K, they can
//'t be paired with any others. So, at most 1 value which is evenly divisible by K can be added to the result set
//
bool isHalf(int i, int k) {
    if ( i == 1 ) {
        if ( k == 2) return true;
    } else if ( 0 == k%i && k/2 == i) {
        return true;
    }
    return false;
}


int nonDivisibleSubset(int k, vector<int> s) {
    int *count = new int[k];
    memset(count, 0, k*sizeof(int));

    for ( auto num : s) {
        auto complementary = num % k;
        count[complementary] ++;
    }
    
    int maxN =0;
    for ( int i = 0 ; i <= k/2; i++) {
        if ( i ==0 || isHalf(i,k) ) {
            if (count[i] != 0 ) maxN += 1;
            continue;
        }
        
        maxN += max(count[i], count[k-i]) ;
    }

    return maxN;

}

int main(){
    vector<int> input{1,7,2,4};
    int k = 3;
    cout << nonDivisibleSubset(k, input) << endl;
    return 0;
}
