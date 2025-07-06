#include<bits/stdc++.h>
using namespace std;
/*
Parent -> i / 2;
child left = i * 2;
right child = i * 2 + 1;

insertion at left then swapping till root 
o(h)  || O(n)
*/
// Implementing Heaps
#define MAX (int)1e5 + 5
// Heap Class
// maxOfChild != i  tells we have a valid index , arr[i] < arr[maxOfChild also tells we have a index to swap with l / right;
// so  use one which is enough;
class Heap{
    int arr[MAX];
    int size;
    public:
    Heap(): size(1){}
    void insert(int elem){
        int index = size;
        size++;
        arr[index] = elem;
        // Check With Parent
        int i = index;
        while(i / 2){
            int parent = i / 2;
            if(arr[parent] < arr[i]) {
                swap(arr[parent],arr[i]);
            }
            else break;
            i = parent;
        }
    }
    void deleteHeap(){
        if(size <= 1) return;

        int index = size - 1;
        size--;
        // update the Top
        int elem = arr[1];
        arr[1] = arr[index];
        int i = 1;

        while(i < size){
            int leftChild = i * 2;
            int rightChild = i * 2 + 1;
            int maxOfChild = i;

            if(leftChild < size && arr[leftChild] > arr[maxOfChild]){
                maxOfChild = leftChild;
            }
            if(rightChild < size && arr[rightChild] > arr[maxOfChild]){
                maxOfChild = rightChild;
            }
            if(arr[i] < arr[maxOfChild]){
                swap(arr[i],arr[maxOfChild]);
            }else
                break;
            i = maxOfChild;
        }
    }
    int top() {
        return arr[1];
    }
};

// say array is  9 3 2 6 7 
// ignoring Leafs By n / 2 cuz leaf starts from n / 2
void heapify(int i , vector<int>& arr,const int& n){
    // zero based indexing !
    int left = 2 * i;
    int right = left + 1;
    // smallest index is root itself (assuming)
    int smallest = i;

    if(left < n && arr[left] < arr[smallest]){
        smallest = left;
    }

    if(right < n && arr[right] < arr[smallest]){
        smallest = right;
    }

    // if changes occured in smallest then swap
    if(smallest != i){
        swap(arr[i],arr[smallest]);
        heapify(smallest,arr,n);
    }
}

void heapSort(vector<int>& arr,int i,int& n){
    // -1,23,16,22,9,15,20,21

    int index = i;
    while(index > 1){
        swap(arr[1],arr[index]);
        index--;
        heapify(1,arr,n);
    }
}



int main(){
    Heap hp;
    Heap* hp = new Hp();
    hp.insert(1);
    hp.insert(7);
    hp.insert(9);
    hp.insert(27);
    hp.insert(3);
    hp.insert(5);
    hp.insert(15);

    hp.print();
    cout << "First Delette" << endl;
    hp.deleteHeap();
    hp.print();
    cout << "Second Delette" << endl;
    hp.deleteHeap();
    hp.print();
    cout << "Third Delette" << endl;
    hp.deleteHeap();
    hp.print();
    vector<int> arr = {-1,23,16,22,9,15,20,21};
    int n = arr.size() - 1;
    heapSort(arr,n - 1,n);

    for(int i = 1; i < n ; i++){
        cout << arr[i] << " ";
    }cout << endl;

    return 0;
}


// Build Min Heap
// Question from Coding Ninjas 
// say array is  9 3 2 6 7 
// ignoring Leafs By n / 2 cuz leaf starts from n / 2
void heapify(int i , vector<int>& arr,const int& n){
    // zero based indexing !
    int left = 2 * i + 1;
    int right = left + 1;
    // smallest index is root itself (assuming)
    int smallest = i;

    if(left < n && arr[left] < arr[smallest]){
        smallest = left;
    }

    if(right < n && arr[right] < arr[smallest]){
        smallest = right;
    }

    // if changes occured in smallest then swap
    if(smallest != i){
        swap(arr[i],arr[smallest]);
        heapify(smallest,arr,n);
    }
}


vector<int> buildMinHeap(vector<int> &arr)
{
    const int n = arr.size();
    // start from n / 2 - 1(0 based) or n / 2 (i based)
    for(int i = (n / 2) - 1 ; i >= 0; i--){
        heapify(i,arr,n);
    }
    return arr;
}

//215. Kth Largest Element in an Array Given an integer array nums and an integer k, return the kth largest element in the array.
// Input: nums = [3,2,1,5,6,4], k = 2
// Output: 5
// Just Implemented Heap Class 
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        Heap hp;
        int n = nums.size();
        for(int i = 0; i < n;i++){
            hp.insert(nums[i]);
        }
        for(int i = 1; i < k; i++){
            hp.deleteHeap();
        }
        return hp.top();
    }
};
