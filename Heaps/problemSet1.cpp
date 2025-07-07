// 215. Kth Largest Element in an Array
// use min heap for kth Smallest -> o(n) space of heap
// use max heap for kth Largest -> o(n) space of heap

// use max heap for kth Smallest -> O(h) space maintaining heap;
// use min heap for kth Largest -> O(h) space maintaining heap of k size ;

int kthSmallest(vector<int>& nums, int k) {
    priority_queue<int> maxHeap;

    for (int num : nums) {
        maxHeap.push(num);
        if (maxHeap.size() > k)
            maxHeap.pop(); // remove largest to keep k smallest
    }

    return maxHeap.top(); // kth smallest
}



// Merge two binary Max heaps
// Difficulty: EasyAccuracy: 58.65%Submissions: 54K+Points: 2
// Given two binary max heaps as arrays, merge the given heaps to form a new max heap.
class Solution {
  public:
    void heapify(int i,vector<int>& res,int& n){
        // say if given data was not max heaps 
        // check with left child
        int left = 2 * i + 1;
        int right = left + 1;
        int greater = i;
        // if(left exist)
        // using greater insted of i so that next if can take advantage
        if(left < n && res[left] > res[greater]){
            greater = left;
        }
        if(right < n && res[right] > res[greater]){
            greater = right;
        }
        
        if(greater != i){
            // we found a value so swap
            swap(res[greater],res[i]);
            heapify(greater,res,n);
        }
    }
    vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {
        // 2 max heaps in 2 vectors
        // whats the advantge im taking of 2 max heaps.
        // assume the 2 are not heaps just BT now convert them into heaps 
        int s = m + n;
        vector<int> res(s);
        // merge them
        for(int i = 0; i < n;i++){
            res[i] = a[i];
        }
        for(int i = n; i < n + m; i++){
            res[i] = b[i - n];
        }
        // remaining
        for(int i = s/2 - 1; i >= 0; i--){
            heapify(i,res,s);   
        }
        return res;
    }
};

// Leetocde 958. Check Completeness of a Binary Tree and Check Heap =>> this GFG 
class Solution {
private:
int countNodes(TreeNode* root){
    if(root == NULL) return 0;

    int left = countNodes(root -> left);
    int right = countNodes(root -> right);

    return 1 + left + right;
}


bool isCBT(TreeNode* root,int currIndex,int& totalNodes){
    if(root == NULL) return true;
    else if(currIndex >= totalNodes){
        return false;
    }
    else{
        bool left = isCBT(root -> left,2*currIndex + 1,totalNodes);
        bool right = isCBT(root -> right,2*currIndex + 2,totalNodes);

        // if left and right are safe that is CBT 
        return left && right;
        // check if any node exceeds the total count 0- based indexing so >= 
        // if any null comes in before its like it assumes there is node thus count becomes greater !
    }
        
}
public:
    bool isCompleteTree(TreeNode* root) {
        int n = countNodes(root);
        return isCBT(root,0,n);
    }
};
// Is Binary Tree Heap
// Difficulty: MediumAccuracy: 34.41%Submissions: 133K+Points: 4
// You are given a binary tree, and the task is to determine whether it satisfies the properties of a max-heap.

// A binary tree is considered a max-heap if it satisfies the following conditions:

// Completeness: Every level of the tree, except possibly the last, is completely filled, and all nodes are as far left as possible.
// Max-Heap Property: The value of each node is greater than or equal to the values of its children.

class Solution {
private:
    int totalNodes(Node* tree){
        // total left nodes + total right Nodes + 1
        if(tree == NULL) return 0;
        else return (totalNodes(tree -> left) + totalNodes(tree -> right) + 1);
    }
    // Why pass Assumed place of node ? we will assume the tree is full !
    // other hand i have actual count of nodes 
    // when ever my assumption is > actual nodes -> wrong ans!
    bool checkCBT(Node* tree,int currIndex,int& total){
        if(tree == NULL) return true; // becz a single node is CBT so 
        else if(currIndex/* starts from 0*/ >= total/*One based indexong so >=*/){
            return false;
        }
        // is left a Complete tree
        bool left = checkCBT(tree -> left,2* currIndex + 1,total);
        bool right = checkCBT(tree -> right,2* currIndex + 2,total);
        return left && right;
    }
    pair<int,bool> checkHeap(Node* root,int data){
        if(root == NULL) return {0,true};
        if(root -> left == NULL && root -> right == NULL) return {root -> data,true};
        
        
        pair<int,bool> left = checkHeap(root -> left,data);
        pair<int,bool> right = checkHeap(root -> right,data);
        
        
        
        pair<int,bool> res;
        res.first = root -> data;
        res.second = left.second && right.second && root -> data > max(left.first,right.first);
    
        return res;
    }
  public:
    bool isHeap(Node* tree) {
        // code here
        int n = totalNodes(tree);
        if(checkCBT(tree,0,n) && checkHeap(tree,tree -> data).second) return true;
        else return false;
    }
};
// Minimum Cost of ropes
// iven an array, arr[] of rope lengths, connect all ropes into a single rope with the minimum total cost. The cost to connect two ropes is the sum of their lengths. 
// Examples
// Input: arr[] = [4, 3, 2, 6]
// Output: 29
class Solution {
  public:
    int minCost(vector<int>& arr) {
        // code here
        priority_queue< int , vector<int> , greater<int> > pq;
        for(int i = 0; i < arr.size();i++){
            pq.push(arr[i]);
        }
        int c = 0;
        while(pq.size() > 1){
            int elem1 = pq.top();pq.pop();
            int elem2 = pq.top();pq.pop();
            c += elem1 + elem2;
            pq.push(elem1 + elem2);
        }
        return c;
    }
};

// Complete BST to Min Heap
// GFG Given a binary search tree which is also a complete binary tree. The problem is to convert the given BST into a Min Heap with the 
//condition that all the values in the left subtree of a node should be less than all the values in the right subtree of the node. This 
//condition is applied to all the nodes, in the resultant converted Min Heap. 
// C++ implementation to convert the given
// BST to Min Heap
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

// and copy the values from the inorder array to nodes
void preorderFill(Node* root, vector<int>& inorderArr,int& index) {
    if(root == NULL) return;

    root -> data = inorderArr[index++];
    preorderFill(root -> left,inorderArr,index);
    preorderFill(root -> right,inorderArr,index);
}

void inorder(Node* root,vector<int>& arr){
    if(root == NULL) return;
    inorder(root -> left,arr);
    arr.push_back(root -> data);
    inorder(root -> right,arr);
}

// Function to convert BST to Min Heap
void convertBSTtoMinHeap(Node* root) {
    vector<int> elem;
    inorder(root,elem);
    // It should be a min heap that is left > root && right > root 
    // we need a tree such that all the nodes of left < nodes of right    left < root if 1st condition is added then root < left < right
    // filling the array sorted such that we get smallest thenmed then greatest elem 
    //     node == smallest 
    /*/    / \
    /*/// L   R

    // here the first you start with root then fill the entire left part then the entire right part so pre order 
    int i = 0;
    preorderFill(root,elem,i);

}

void preorder(Node* root){
    if(root == NULL) return ;
    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root -> right);
}

int main() {

    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(6);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->right->left = new Node(5);
    root->right->right = new Node(7);

    preorder(root);
    convertBSTtoMinHeap(root);
    cout << " " << endl;
    preorder(root);
    return 0;
}

// Todays daily Question Heaps
// Leetcode 1353. Maximum Number of Events That Can Be Attended
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        // Min Heap
        priority_queue< int, vector<int> , greater<int> > pq;
        //Order of start dates is important to reduce unwanted wait time
        sort(events.begin(),events.end());
        // Now the data will be Based on index 0 -> 
        // [1,2][1,2][2,3][3,4]
        

        // start day to end day for every day track number of events attended
        int rows = events.size(),maxi = 0;
        for(int i = 0; i < rows; i++){
            maxi = max(maxi, events[i][1]);
        }
        int index = 0,count = 0;
            for(int day = 1; day <= maxi; day++){
                // for every day add all events deadlines into min heap
                // so that ending event occurs first !

                // events of this day and push end dates of every event
                while(index < rows && events[index][0] == day){
                    pq.push(events[index][1]);
                    index++;
                }
                // While Completing Some Events Some Might Expire 
                // When Can a event be expired when Current date is > event end date
                while(!pq.empty() && pq.top() < day) pq.pop();
                // You have Events already sorted to start date + end dates sorted In non decreasing in heap
                // expired events are removed and only valid form this day and sorted by priority are in heap 
                if(!pq.empty()){
                    pq.pop(); // attend a event
                    count++;
                }
            }
        return count;
    }
};
