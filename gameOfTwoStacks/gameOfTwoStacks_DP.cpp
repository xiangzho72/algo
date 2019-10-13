#include <iostream>
#include <vector>
#include <bits/stdc++.h>


// Things to be remembered for DP : 
// 1. Set up size as 1+size in DP :  
//       mostly the current pointer is to be decided one
//       so when iterating all elements,  the pointer will be 1+size
//
// 2. Use assert as much as possible to identify any out of boundaries
//
// 3. Normally, the high level structure : 
//       out of boundries or trigger backtrack :  return  
//       if already set:    return 
//       if base case:      return  
//       else :            recursive to get the value
//  
//  4. when return:  set the value in the map, and return  the value;
//     
//  5.  auto& cur  = step[aIndex][bIndex];  remember this is a reference
//
//  6.  when moving the index,  do :  index + 1, rather than:  index ++
//      so it's better to use const int in the arguments.:

using namespace std;

vector<string> split_string(string);

//  aIndex, bIndex points to the one to be checked
int maxSteps(const int x, const vector<int>& a , const vector<int>& b,
             const int aIndex, const int bIndex,
             vector<vector<int>>& steps
        ) {

    assert( x >=0 );
    assert(aIndex < a.size() || bIndex < b.size());

    auto& cur = steps[aIndex][bIndex];

    if ( cur != -1) {
        return cur;
    }
    // If bIndex can be moved further, then move it
    // As the last element is the INT_MAX, we can ensure here that index will not be out of boundary
    auto moveB = [&]() {
        assert(bIndex < b.size());
        return b[bIndex] > x
               ? 0
               : maxSteps(x-b[bIndex] ,a,b,aIndex,bIndex+1,steps) + 1;
    };

    auto moveA = [&]() {
        assert(aIndex < a.size());
        return a[aIndex] > x
               ? 0
               : maxSteps(x-a[aIndex],a,b,aIndex+1,bIndex,steps) + 1;
    };

    if ( (aIndex == a.size()-1 && bIndex == b.size()-1 )||
         (a[aIndex] > x && b[bIndex] > x) ) {
        cur = 0;
    } else if ( aIndex == a.size()-1 || a[aIndex] > x) {
        cur = moveB(); 
    } else if ( bIndex == b.size()-1 || b[bIndex] > x) {
        cur = moveA();
    } else {
        cur = max( moveA(), moveB());
    }
    return cur;
        
}



/*
 * Complete the twoStacks function below.
 */
int twoStacks(int x, vector<int> a, vector<int> b) {
    /*
     * Write your code here.
     */
    vector<vector<int>> steps(a.size()+1, vector<int>(b.size()+1, -1));
    a.push_back(INT_MAX);
    b.push_back(INT_MAX);
    return maxSteps(x,a,b,0,0,steps);
}

int main()
{
    ofstream fout;
    fout.open("out.txt");

    int g;
    cin >> g;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int g_itr = 0; g_itr < g; g_itr++) {
        string nmx_temp;
        getline(cin, nmx_temp);

        vector<string> nmx = split_string(nmx_temp);

        int n = stoi(nmx[0]);

        int m = stoi(nmx[1]);

        int x = stoi(nmx[2]);

        string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split_string(a_temp_temp);

        vector<int> a(n);

        for (int a_itr = 0; a_itr < n; a_itr++) {
            int a_item = stoi(a_temp[a_itr]);

            a[a_itr] = a_item;
        }

        string b_temp_temp;
        getline(cin, b_temp_temp);

        vector<string> b_temp = split_string(b_temp_temp);

        vector<int> b(m);

        for (int b_itr = 0; b_itr < m; b_itr++) {
            int b_item = stoi(b_temp[b_itr]);

            b[b_itr] = b_item;
        }

        int result = twoStacks(x, a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}



