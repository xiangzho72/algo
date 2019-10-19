#include <bits/stdc++.h>
#include <vector>
#include <stack>

using namespace std;

/* 1 -1  : node 0 */
/* 2 3   : node 1 ==> children of node 1 */ 
/* 4 -1  : node 2 ==> children of node 2 */
/* -1 5 */
/* -1 -1 */
/* -1 -1 */

void inOrderPrint(const vector<vector<int>>& indexes, int index, vector<int>& res){

    auto left = indexes[index][0];
    auto right = indexes[index][1];

    if (left != -1 ) inOrderPrint(indexes, left, res);
    if ( index != 0 ) res.push_back(index);
    if ( right != -1) inOrderPrint(indexes, right, res);

}


 /* levels save the nodes on each level, so in above it will be : */ 
 /* levels[0] : 0 */
 /* levels[1] : 1 */
 /* levels[2] : 2 3 */ 
 /* levels[3] : 4 5 */  
void preCompute(const vector<vector<int>>& indexes, vector<vector<int>>& levels) {
    //set up the base
    levels.push_back({0});    
    levels.push_back({1});

    stack<int> level;
    level.push(1);

    while(true) {
        vector<int> tmp;
        while(!level.empty()) {
            auto node = level.top();
            for ( auto c : indexes[node] ) {
                if (c != -1 ) tmp.push_back(c);
            }    
            level.pop();
        }
        if ( !tmp.empty() ) {
            levels.push_back(tmp);
            for_each(tmp.begin(), tmp.end(), [&level](int x){level.push(x);});
        } else {
            break;
        }
    }
}
/*
 * Complete the swapNodes function below.
 */
vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    /*
     * Write your code here.
     */


    indexes.insert(indexes.begin(),{1,-1});   // So each node of indexes means all its children node of that index :  index[1] is a vector has all the children node of node 1
    

    vector<vector<int>> levels;
    preCompute(indexes, levels);
    auto totalLevel = levels.size()-1;
    vector<vector<int>> results;

    for ( auto k : queries) {
        for ( int level = k, mul = 1; level < totalLevel; level = k*(++mul)) {
            for (auto node : levels[level]) {                
                std::swap(indexes[node][0], indexes[node][1]);
            }
        }
        
        vector<int> res;
        inOrderPrint(indexes, 0, res);
        results.push_back(res);
    }
    return results;
}

int main()
{
    ofstream fout("output.txt");

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> indexes(n);
    for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++) {
        indexes[indexes_row_itr].resize(2);

        for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++) {
            cin >> indexes[indexes_row_itr][indexes_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int queries_itr = 0; queries_itr < queries_count; queries_itr++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[queries_itr] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++) {
        for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++) {
            fout << result[result_row_itr][result_column_itr];

            if (result_column_itr != result[result_row_itr].size() - 1) {
                fout << " ";
            }
        }

        if (result_row_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

