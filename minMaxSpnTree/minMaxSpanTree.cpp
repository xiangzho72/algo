#include <vector>
#include <tuple>   // for std::tie
#include <utility>  // for std::make_pair
#include <iostream> 
using namespace std;
struct Children {
    int numChildren{1};   // Direction children including itself
    vector<int> others;   // Indirection children
    int sz{};
};


int sizeOfChildren(vector<Children>& children, int index) {
    auto& s = children[index];

    auto sz = s.numChildren;
    for ( auto other: s.others) {
        sz += sizeOfChildren(children, other);
    }
    s.sz = sz;
    return sz;

}

int findParent(const vector<int>& parent, const int index) {
    if ( parent[index] == -1) {
        return index;
    }

    return findParent(parent, parent[index]);
}

void childrenBuild(vector<int>& parent, vector<Children>& children, int x, int y) {
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    int n = parent.size()/2;

    if ( xset != yset) {
        parent[xset] = yset;   // xset parent is yset

        // yset children is xset
        if ( xset <= n ) {
            children[yset].numChildren ++;
        } else {
            children[yset].others.push_back(xset);
        }
    }

}


pair<int,int> computeGraph(vector<vector<int>> gh) {
    int n = gh.size();
    vector<int> parent(2*n + 1, -1);  // initalize to -1
    vector<Children> children(2*n + 1);

    for( auto& edge : gh) {
        int x = edge[0];
        int y = edge[1];

        childrenBuild(parent, children, x, y);
    }
    
    int lMax = 0;
    int lMin = 2*n;
    for ( int i=n+1; i<2*n+1; i++ ) {
        if ( parent[i] == -1) {
            auto sz = sizeOfChildren(children, i);

            lMax = max(sz, lMax);
            if ( sz != 1 ) lMin = min(sz, lMin);
        }

    }

    return make_pair(lMin, lMax);

}


int main() 
{
    vector<vector<int>> gb{
       {        1,6}, 
       {        2,7},
       {        3,8},
       {        4,9},
       {        2,6}};

    int lMin(0), lMax(0);
    tie(lMin, lMax) = computeGraph(gb);
    cout << lMin << " " << lMax << endl;

}

