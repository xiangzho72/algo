#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

// This will use backtrack to solve the problem
// Firstly, For each num a in the list,  set up a complementary list [b...]where a + b == k
// Then iterate through the list to buid up the nonDivisibleSubset by only add the number when 
// it's not in the complementary list, 


template<typename T>
void printV(T& s) {
   for ( auto num : s) {
       cout << " "<< num;
   }
   cout << endl;
}

//  input : vector<int> s ,  int k
//  out : map<int, set<int>>& 
//       For each item a in s, build an set where b is from the rest of vector and also 
//       : a+b%k == 0 
void buildExclusiveMap(vector<int>& s,int k, map<int, set<int>>& a_map  ) {
    for ( auto it = s.begin(); it < s.end(); it++) {
        set<int> l_set;
        for (auto jt = it+1; jt < s.end(); jt++) {
            if ((*it + *jt) % k == 0) {
                l_set.insert(*jt);
            }
        }

        if ( a_map.count(*it) == 0) {
           a_map[*it] =  l_set;
           cout << "num: " << *it << ":" ;
           printV(l_set);
        }
    }
}

//  it points to the current item which is intended to be pushed into output
//  if it meets the precondition, then it's pushed into a vector
//  then dive into the next level
int findDivisibleSubset(vector<int>& input, vector<int>::iterator it, 
                        vector<int>& output,
                        map<int, set<int>> excluded){

    for (auto num: output) {
        set<int> l_excludedSet  = excluded[num];
        if ( l_excludedSet.end() != l_excludedSet.find(*it) ) {
            return output.size();
        }
    }


    output.push_back(*it);
    int max = output.size();
    for ( auto jt = it+1; jt < input.end(); jt++) {
        int num = findDivisibleSubset(input, jt, output, excluded);
        if (num > max ) {
            max = num;
        }
    }
    output.pop_back();
    return max;
}

int nonDivisibleSubset(int k, vector<int> s) {
    map<int, set<int>> excluded;
    buildExclusiveMap(s, k , excluded);
    vector<int> output;
    int max = 0;
    for ( auto jt = s.begin(); jt < s.end(); jt++) {
        int num = findDivisibleSubset(s, jt, output, excluded);
        if (num > max ) {
            max = num;
        }
    }
    return max;
}

int main(){
    vector<int> input{19,10,12,10,24,25,22};
    int k = 4;
    cout << nonDivisibleSubset(k, input) << endl;
    return 0;

}
