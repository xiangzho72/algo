#include <iostream>
#include <deque> 
using namespace std;
// We create a Deque, Qi of capacity k, that stores only useful elements of current window of k elements. 
// An element is useful if it is in current window and is greater than all other elements on left side of it in current
// window. We process all array elements one by one and maintain Qi to contain useful elements of current window and 
// these useful elements are maintained in sorted order. The element at front of the Qi is the largest and element at 
// rear of Qi is the smallest of current window. 

//  Time complexity is O(n)
template <typename T>
void printT(T& t) {
    for (auto item : t) {
        cout << " " << item ;
    }
    cout << endl;
}
// For every element,  previous smaller one are useless so remove them
void update(int *arr, int index, deque<int>& indexes) {

    while ( !indexes.empty() && arr[indexes.back()] <= arr[index]) {
        indexes.pop_back();
    }
    indexes.push_back(index);

}

void fromArray(int* arr, int k, deque<int>& indexes) {
    if ( k == 1) {
        indexes.push_back(0);
        return;
    }

    for (int i =0 ; i<k ; i++ ) {
        update(arr,i,indexes);

    }
//    printT(indexes);
    return;
}



void printKMax(int arr[], int n, int k){
	//Write your code here.
    deque<int> indexes;
    int windowSize = k > n ? n : k;
    fromArray(arr, windowSize, indexes);
    if ( k >= n) {
        return;
    }
        
    for (int i=k; i<n; i++) {
        cout << arr[indexes.front()] << " ";
        if ( indexes.front() == i-k) {
            indexes.pop_front();
        }
        update(arr, i, indexes);
//        printT(indexes);
    }
    cout << endl;
}


int main(){
    int arr[] = {8,10,8,6,4,7,5};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    int k = 4;
    printKMax(arr,arrSize,k);

}
