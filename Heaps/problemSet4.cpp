// 373. Find K Pairs with Smallest Sums
// First Step See The Pattern of finding the Smallest pairs
// 0,0 -> 0,1 or 1,0 then once increment left with right const and right with left const i.e i,j
// do this k times that is you are maintaing heap states instead of storing everything

// This Approach you will vistit to same i , j again, maintaining to avoid duplicates is crutial !
// to avoid to push duplicate in heap why ? the final ans will contain duplicate so maintain unordered map <> as shown



class Node{
    public:
    int i,j,sum;
    Node(int a, int b, int c): i(a),j(b),sum(c){}
};
class Compare{
  public:
    bool operator()(Node* a, Node* b){
        // if this returns true swap happens {Heapify}
        return a -> sum > b -> sum;
    }
};
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {

        priority_queue < Node* , vector < Node* > ,Compare > pq;
        vector<vector<int>> res;
        Node* node = new Node(0,0,nums1[0] + nums2[0]);
        pq.push(node);
        int n = k;
        int lenOf1 = nums1.size();
        int lenOf2 = nums2.size();

        // to avoid duplicates to be added in pq
        unordered_map < int , unordered_set< int > > visited;
        
        while(n-- && (!pq.empty())){
            // smallest sum will be popped
            Node* temp = pq.top(); pq.pop();
            int i = temp -> i;
            int j = temp -> j;

            res.push_back({nums1[i],nums2[j]});

            // next elements
            if(j + 1 < lenOf2 && visited[i].find(j + 1) == visited[i].end() ){
                Node* temp1 = new Node(i,j+1,nums1[i] + nums2[j+1]);
                pq.push(temp1);
                visited[i].insert(j+1);
            }
            if(i + 1 < lenOf1 && visited[i + 1].find(j) == visited[i].end()){
                Node* temp2 = new Node(i+1,j,nums1[i+1] + nums2[j]);
                pq.push(temp2);
                visited[i+1].insert(j);
            }
        }
        return res;
    }
};

// 295. Find Median from Data Stream
// Sorting and finding is expensive

// Maintain 2 heaps Like First Half as max heap 
// Maintain  second Half as min heap Increasing

// max heap  .... X .... min heap
// You can access the middle by max.top and min.top

// but the part is maintaing the 2 their difference should not be more than 1 so that we will access exactly at middle
// when ever new element comes select which heap to store
// if it makes diff > 1 then shift 1 data to other heap and then insert thus maintaining the diff

// Code Makes Sense Now

class MedianFinder {
public:
    priority_queue < int,vector< int >,greater< int > > min;
    priority_queue < int,vector< int >,less< int > > max;
    MedianFinder() {}
    
    void addNum(int num) {

        if(min.size() == max.size()){
            
           if(min.empty() && max.empty()){
               max.push(num);
               return;
           }
            if(num > max.top()) min.push(num);
            else max.push(num);
        
        }else if(min.size() > max.size()){
            if(num > min.top()){
                // push in min but maintain difference 1 
                max.push(min.top()); min.pop();
                min.push(num);
            }else{
                max.push(num);
            }
        }else{
            if(num > max.top()){
                min.push(num);
            }else{
                min.push(max.top()); max.pop();
                max.push(num);
            }
        }
    }
    
    double findMedian() {
        if(min.size() == max.size()){
            if(min.empty() && max.empty()) return -1;
            double ans = ((double)max.top() + min.top())/ 2.0;
            return ans;
        }else if(min.size() > max.size()){
            return min.top();
        }else{
            return max.top();
        }
    }
};

// 502. IPO
// Doubt 1 : maintain min heap and max variable
// problem : if you take max and discard smaller values of current capital..those discarded values might have more
// profit than the higher captial ones so i should keep track of them;

// Obviously i need a min heap
// Why MAX heap To not to discard any value got so far so that not to miss any profit

// Min will be empty first 
// there remains some data in max so run until both becomes empty

// Algo
// Push every thing into min heap Capital bases
// pop and put in max heap until curr cap can handle
// else pop max profit from all you have and += to cap

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        using P = pair< int , int >;
        priority_queue < P , vector < P > , greater < P > > min;
        priority_queue < int , vector < int > , less < int > > max;

        int K = k;
        int size = profits.size();
        for(int i = 0; i < size; i++){
            min.push({capital[i],profits[i]});
        }
      
        while(K--){
            // smallest Node
            if(!min.empty()){
                auto p = min.top();
            
                while(w >= p.first && !min.empty()){
                    max.push(p.second);
                    min.pop();
                    if(!min.empty()) p = min.top();
                }
            }
            
            if(max.empty()) break;
            
            w += max.top();
            max.pop();
        }
        return w;
    }
};
