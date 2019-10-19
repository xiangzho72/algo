#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
template<typename T>
void printV(const T& v) {
    for ( int i = 0 ; i < v.size(); i++)  {
        cout << i << ":" << v[i] << endl;
    }
    cout << endl;
}

struct Node{
    int v{};
    int i{};

    Node(int v, int i) : v(v), i(i) {}
    
    bool operator >= (const Node& o) const{
        return v >= o.v;
    }

    bool operator <= (const Node& o) const{
        return v <= o.v;
    }
};


void preCompute(const vector<int>& arr, vector<int>& higher,  vector<int>& lower)
{
    stack<Node> high;
    stack<Node> low;

    auto computeLarger = [&high, &higher](const Node& node) {
        while( !high.empty() && node >= high.top() ) {
             high.pop();
        }

        if (high.empty()) {
            higher.push_back(0);  // no previous one is bigger than current            
        } else {
            higher.push_back(high.top().i);
        }
        high.push(node);
    };


    auto computeLess = [&low, &lower](const Node& node) {
        while( !low.empty() && node >= low.top() ) {
             low.pop();
        }

        if (low.empty()) {
            lower.push_back(0);  // no previous one is bigger than current            
        } else {
            lower.push_back(low.top().i);
        }
        low.push(node);
    };


    for ( int i=0; i<arr.size(); i++ ) {
        auto x = arr[i];
        auto node = Node(x,i+1);
        computeLarger(node);
    }

    for ( int i=arr.size()-1; i>=0; i-- ){
        auto x = arr[i];
        auto node = Node(x,i+1);
        computeLess(node);
    }


}


// Complete the solve function below.
uint32_t solve(vector<int> arr) {
    vector<int> higher;
    vector<int> lower;
    preCompute(arr, higher, lower);
    //printV(higher);
    //printV(lower);

    uint32_t maxN =0;
    for ( int i=1; i< arr.size()-1; i++)
    {
        maxN = std::max(maxN, (uint32_t)(higher[i])*lower[arr.size()-i-1]);
    }
    return maxN;
}

int main()
{
    ofstream fout("output.txt");

    int arr_count;
    cin >> arr_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(arr_count);

    for (int arr_itr = 0; arr_itr < arr_count; arr_itr++) {
        int arr_item = stoi(arr_temp[arr_itr]);

        arr[arr_itr] = arr_item;
    }

    uint32_t result = solve(arr);

    fout << result << "\n";

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
