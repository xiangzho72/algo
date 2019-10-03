#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;
template <typename T>
void printT(T& t) {
    for ( auto item : t) {
        cout << item.start << "->"<< item.end<< " ";
    }
    cout << endl;

}


struct Workshop { 
    int start;
    int dur;
    int end;

    bool operator < ( const Workshop& other) const {
        return (start < other.start);
    }

    bool operator == ( const Workshop& other) const {
        return ( start == other.start);
    }
};

typedef vector<Workshop>::iterator  It; 

struct AvailableWorkshops {
    int n;
    vector<Workshop> workshops;

    AvailableWorkshops(int size){
        n = size;
        workshops.reserve(n);
    }
};

AvailableWorkshops* initialize(int start[], int dur[], int n) {
    AvailableWorkshops* avail = new AvailableWorkshops(n);

    for(int i=0; i<n; i++) {
        Workshop aWork;
        aWork.start = start[i];
        aWork.dur = dur[i];
        aWork.end = start[i] + dur[i];
        avail->workshops.push_back(aWork);
    }
    sort ( avail->workshops.begin(), avail->workshops.end());
    printT(avail->workshops);
    return avail;
}

int buildMax(vector<Workshop>&, It, map<int,int>&);

int findNumOfWorkshops(vector<Workshop>& workshops, It it, map<int,int>&maxs) {
    auto end = (*it).end;

    Workshop a{end,0,0};
    auto nextIt = std::lower_bound(workshops.begin(),workshops.end(),a);
    if ( nextIt == workshops.end()){
        return 1;
    }else {

        return 1 + buildMax(workshops, nextIt, maxs);
    }
}

int buildMax(vector<Workshop>& workshops, It it, map<int, int>& maxs){
    int start = (*it).start;
    if ( it == workshops.end()) {
        return 0;
    }
    if (maxs.count(start) >0 ) {
        return maxs[start];
    }
    
    if ((it+1) == workshops.end()) {
       maxs[start] = 1; 
    } else {
        auto cur = findNumOfWorkshops(workshops, it, maxs); 
        while ( (it+1) != workshops.end() && (*it).start == (*(it+1)).start ) {
           auto nxt = findNumOfWorkshops(workshops,it+1, maxs);
           cur = max(nxt, cur);
           it++;
        }
        maxs[start] = cur;
    }
    return maxs[start];
}

int CalculateMaxWorkshops(AvailableWorkshops* avail) {
    map<int,int> maxs;
    auto workshops = avail->workshops;
    auto it = workshops.begin();
    auto cur = buildMax(workshops, it, maxs);

    while ( ++it != workshops.end()) {
        auto nxt = buildMax(workshops, it, maxs);
        cout << (*it).start << ":" << maxs[(*it).start] << endl;
        cur = max(nxt, cur);
    }
    return cur;
}


int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    AvailableWorkshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
