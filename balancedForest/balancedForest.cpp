#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

struct Node {
    int index{};
    int value{};
    long sum{};

    vector<Node*> children;
    Node* parent{nullptr};

    Node() {}
    Node(int index, int value) : index(index), value(value) {}

    long sumOfAll(){
        if (sum != 0) return sum;

        sum = value;
        for ( auto p : children ) {
                sum += p->sumOfAll();
        }
        return sum;
    }

    // Return p current parent, which could be null;
    Node* addChild(Node* p) {
        children.push_back(p);
        Node* ret = p->parent;
        p->parent = this;
        return ret;
    }

    void removeChild(Node* p) {
        children.erase(remove(children.begin(),children.end(), p), children.end());
    }

    
    void setAsRoot(){
        
        Node* previous = nullptr;
        Node* p = this;
        Node* pNext = p->parent;
        Node* pNextNext = nullptr;
        while(pNext) {
            //cout << "cur: " << p->index << ", next: " << pNext->index << endl;

            pNext->removeChild(p);            
            pNextNext = p->addChild(pNext);
            p->sum = 0;
            p->parent = previous;

            previous = p;
            p = pNext;
            pNext = pNextNext;
        }        
        p->sum =0;
        parent =nullptr;
        //p->parent = nullptr;
        sum = sumOfAll();
    }

};


bool isChildrenOfRoot(Node* root, Node* t) {
        if ( root == t) { 
            return true;
        }

        for( auto p : root->children) {
            if ( isChildrenOfRoot (p, t)) {
                return true;
            }
        }
        return false; 
} 

bool isSameTree(Node* l, Node* r) {
    assert( l != nullptr && r != nullptr);
    return isChildrenOfRoot(l,r) || isChildrenOfRoot(r,l);
}


// input i and return vector<int> are the indexes in the sum : vector<node>
void findEqualNode(Node* t, const vector<Node*>& sum, vector<Node*>& equalNodes){
    assert( t!= nullptr);

    auto comp = [](Node* l, Node*r){ return l->sum < r->sum;};

    auto itU = std::upper_bound(sum.begin(), sum.end(), t, comp);
    auto itL = std::lower_bound(sum.begin(), sum.end(), t, comp);

    if ( itU - itL > 1) {
        for ( auto p = itL ; p < itU ; p++) {
            if ( (*p) != t ) {
                equalNodes.push_back(*p);
            }
        }
    }

    Node tmp(0, 0);
    tmp.sum = sum[sum.size()-1]->sum - 2*t->sum;
    itU = std::upper_bound(sum.begin(), sum.end(), &tmp, comp);
    itL = std::lower_bound(sum.begin(), sum.end(), &tmp, comp);
        for ( auto p = itL ; p < itU ; p++) {
                equalNodes.push_back(*p);
        }

    sort(equalNodes.begin(),equalNodes.end(), comp);    

}

void printT(Node* root) {
     cout << root->index << ":" << root->value << ":" << root->sum << endl;
     for(auto p: root->children) {
         printT(p);
     }
}


int lowestValue(const vector<Node* >& sum) {
    // pick up the possible candidates: 
    long T= sum[sum.size()-1]->sum; 
    float low = ((float)T)/3;
    float high = ((float)T)/2;
    int previous =0;
    for (auto p: sum) 
    {
        if ( p->sum != previous ) {
            previous = p->sum ;
        }
        else {
            continue;
        }
        
        if ( p->sum == high ) {
            return high;
        }
        if ( p->sum >= low && p->sum < high ) {
            //cout << "potential i:" << p->index << " with sum:" << p->sum << endl;

            vector<Node*> equalNodes;
            findEqualNode(p, sum, equalNodes);
            for( auto e: equalNodes) {
                //cout << p->index << " has equal node : " << e->index << " ";
                if ( !isSameTree(e,p)) {
                    //cout << " not on a same tree " << endl;
                    return 3*p->sum - T;
                }    
            }
        }
    }
    return -1;
}


// This build up a tree, and also a set with all unique node index;
// so later we can loop through all possible indexes
Node* buildTree(const vector<int>& c, vector<vector<int>> edges, map<int, Node*>& nodes){

    Node* root = new Node(1, c[1]); 
    nodes.insert(pair<int, Node*>(1, root));

    sort(edges.begin(), edges.end(), 
         [](vector<int>& l, vector<int>& r){return l[0] < r[0];}
        );

    queue<int> children;
    children.push(1);

    while( !children.empty())    
    {
        int current = children.front();
        children.pop();

        vector<vector<int>>:: iterator it; 
        while ( (it = find_if(edges.begin(), edges.end(),
                          [current](vector<int>& x){return x[0] == current;}
                         )) != edges.end() ){
            int index = (*it)[1];
            int value = c[index];  
            Node* child = new Node(index, value);
            nodes[current]->addChild(child);
            //cout << " cur: " << nodes[current]->index << " now has child: " << index << endl;
            children.push(index);
            auto ret =nodes.insert(pair<int, Node*>(index,child));
            assert( ret.second == true);
            edges.erase(it);
        } 
    }

    while( edges.size() ){ 
        for( auto it=edges.begin(); it<edges.end();) {
            if ( nodes.count((*it)[1]) == 0 &&
                 nodes.count((*it)[0]) == 0) {
                it++;
                continue;                
            }
            
            int parentI{}, childI{};
            if ( nodes.count((*it)[1]) > 0) {
                parentI = (*it)[1];
                childI =  (*it)[0];
            } else if ( nodes.count((*it)[0]) > 0){
                parentI = (*it)[0];
                childI =  (*it)[1];
            }

            Node* child = new Node(childI, c[childI]);
            nodes[parentI]->addChild(child);
            auto ret = nodes.insert(pair<int,Node*>(childI,child));
            assert( ret.second == true);
            //cout << " cur: " << parentI << " now has child: " << childI << endl;

            it = edges.erase(it);
        }
    }    

    return root;
}


// Complete the balancedForest function below.
int balancedForest(vector<int> c, vector<vector<int>> edges) {
    //Add one more node
    c.insert(c.begin(),0);
    // Build up tree
    map<int, Node*> nodes;
    Node* root = buildTree(c, edges, nodes);

    vector<Node*> sum;
    for(auto n : nodes) {
        sum.push_back(n.second);
    }

    int ret = INT32_MAX;
    for ( auto n : nodes) {
        auto node = n.second;
        node->setAsRoot();
        //printT(node);
        sort(sum.begin(), sum.end(), [](Node* l, Node* r){ return l->sum < r->sum;});
        //for_each(sum.begin(), sum.end(), [](Node* n){cout<< n->index << " ";});

        int tmp = lowestValue(sum);
        //cout << "current node index: " << node->index << ", found : " << tmp << endl;
        ret = min ( ret, tmp==-1?INT32_MAX: tmp);

    }
    return ret == INT32_MAX ? -1: ret;    
}

int main()
{
    ofstream fout("output.txt");

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string c_temp_temp;
        getline(cin, c_temp_temp);

        vector<string> c_temp = split_string(c_temp_temp);

        vector<int> c(n);

        for (int i = 0; i < n; i++) {
            int c_item = stoi(c_temp[i]);

            c[i] = c_item;
        }

        vector<vector<int>> edges(n - 1);
        for (int i = 0; i < n - 1; i++) {
            edges[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> edges[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int result = balancedForest(c, edges);

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
