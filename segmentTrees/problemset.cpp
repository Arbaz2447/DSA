3479. Fruits Into Baskets III
// You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.
// From left to right, place the fruits according to these rules:
// Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
// Each basket can hold only one type of fruit.
// If a fruit type cannot be placed in any basket, it remains unplaced.
// Return the number of fruit types that remain unplaced after all possible allocations are made.
// Github - https://g.co/gemini/share/08d93fbf1938
class Solution {
public:
    class segmentTree{
        public:
        vector<int> tree;
        const vector<int>* arr;
        int size;
        segmentTree(int n){
            size = n;
            tree.resize(4 * n);
        }
        // 1 based for tree and 0 based for array(i/p) !
        void buildTree(int node, int start, int end){
            // Which data to place in leaf Nodes !
            if(start == end){
                tree[node] = (*arr)[start];
            }
            else{
                // place data in leaf and recursively update max via postorder
                int mid = start + (end - start) / 2;
                buildTree(2 * node,start, mid);
                buildTree(2 * node + 1,mid + 1, end);
                // place max among chlid nodes and fill bottom up !
                tree[node] = max(tree[2*node], tree[2*node + 1]);
            }
        }
        int findWeight(int weight, int start , int end, int node){


            if(tree[node] < weight) return -1;

            if(start == end){
                return start; // i already have weight right ? in basket ! so return index
            }
            
            int mid = start + (end - start) / 2;
            if(tree[node * 2] >= weight){
               return findWeight(weight, start , mid, node * 2);
            }else{
                return findWeight(weight, mid + 1 , end, node * 2 + 1);
            }
        }

        void update(int index, int val , int start , int end, int node){
            if(start == end){
                tree[node] = val;
                return;
            }

            int mid = start + (end - start) / 2;
            if(start <= index && index <= mid){
                update(index, val, start, mid, node * 2);
            }else{
                update(index, val, mid+1,end, node * 2 + 1);
            }

            // after overriding change max;
            tree[node] = max(tree[node * 2], tree[(node * 2) + 1]);
        }
    };
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = baskets.size();
        segmentTree tree(n);
        tree.arr = &baskets;
        tree.buildTree(1,0,n-1);
        int remaining = 0;
        for(int i = 0; i < n; i++){
            int get = tree.findWeight(fruits[i], 0, n - 1, 1);

            if(get == -1){
                remaining++;
            }else{
                tree.update(get, -1, 0, n - 1, 1);
            }
        }
        return remaining;
    }
};



