// 3x Hard !
// One Of Hardest Till Now 
// 2386. Find the K-Sum of an Array
// LeetCode Explination https://leetcode.com/problems/find-the-k-sum-of-an-array/solutions/6939622/most-begginer-friendly-heap-solution-c
class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        // step 1 : find the kth largest sub array by just taking positives and make every one pos
        // cuz we will be removing them one by one.
        int n = nums.size();
        long long sum = 0;
        for(int i = 0; i< n;i++){
            if(nums[i] > 0) sum += nums[i]; // 1st largest sum is obviously the sum(positives);
            nums[i] = abs(nums[i]);  // pos and neg dont matter here because you are just removing
        }
        sort(nums.begin(),nums.end());
        // sorted array so that kth smallest sub array could be taken out 

        using p = pair<long long,long long>;
        priority_queue< p , vector< p > , greater< p > > pq;
        pq.push({0,0}); // why ? toBeSubtracted 0 for first time && start making subsequences from 0th i
        // generating subsequences with heap 
        // gives smallest element in O(log n) 
        
        k--; // becz we already found 1st largest
        while(k--){ // remaining times we have to perform
            auto [
                 , idx] = pq.top(); pq.pop();

            // just include at index i with prev values => say for [1,2,3] its generating 
            // 0 + 1 then 1 + 2 then 3 + 3
            if(idx < n){
            pq.push({toBeSubtracted + nums[idx] , idx + 1});
                // remove prev index so that it genertes only single element previous one
                // execpt for first case every node generates 2 subseq including curr index && removing prev
                if(idx > 0){
                    pq.push({toBeSubtracted + nums[idx] - nums[idx - 1], idx + 1});
                } 
            }
        }
        return sum - pq.top().first;
    }
};


// 23. Merge k Sorted Lists
class Compare{
    public:
    bool operator()(ListNode* a, ListNode* b){
        // false condition for min heap cuz its always max
        return a -> val > b -> val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
    
        priority_queue < ListNode* , vector < ListNode* > , Compare > pq;
        int n = lists.size();
        for(int i = 0; i < n; i++){
            if(lists[i] != NULL)
            pq.push(lists[i]);
        }
        ListNode* head = NULL ,*tail = NULL;
        while(!pq.empty()){
            ListNode* t = pq.top(); pq.pop();

            if(head == NULL) {
                head = t;
                tail = t;
            }else{
                tail -> next = t;
                tail = t;
            }

            if(t -> next){
                pq.push(t -> next);
            }
        } 
        return head;
    }
};

// 632. Smallest Range Covering Elements from K Lists
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {

        //Main goal to increase minimum distance so that we could get min distance
        // if we increase max the distance  increases insted of decreasing

        // I need data + its Location i , j
        using T = tuple< int , int , int >;

        // min to track Minimum.
        priority_queue< T , vector < T > , greater < T > > pq;
        // get min and max 
        int mn = INT_MAX , mx = INT_MIN;
        int rows = nums.size();
        for(int i = 0; i < rows ; i++){
            int element = nums[i][0];
            mx = max(mx , element);
            mn = min(mn , element);
            pq.push({element,i,0});
        }
        // You have Prevous Distance and you get new Distace , You have to compare Both of them
        int maxi = mx, mini = mn;

        while(!pq.empty()){
            // you are popping from min heap so that you get bigger and bigger elements and 
            // on other side the max distance is fixed so you will reach minimum with min heap
            auto [data, i, j] = pq.top(); pq.pop();

            // the data is slightly larger and max remains same
            mini = data;
            // check and update if lower
            if(mx - mn >  maxi - mini){
                mx = maxi;
                mn = mini;
            }

            // You popped element
            // so that means one rows element is not included and next occuring element is greater than
            // prev so its obvz that its distance reduces 

            // You have To maintain Elements in all rows one got popped so add next elem form that same row
            // So the distance reduces !

            if(j + 1 < nums[i].size()){
                maxi = max(maxi,nums[i][j + 1]);
                pq.push({nums[i][j + 1],i, j + 1});
            }else break;
        }
        return {mn,mx};
    }
};
