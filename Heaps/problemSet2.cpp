// 1705. Maximum Number of Eaten Apples
// Same pattern of previous question
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        // apples -> 2 4 5 1 0 5
        // expiry -> 4 2 1 3 2 0 
        
        // find out max day to simulate the loop 
        int n =  days.size(), LastDay = 0;
        for(int i = 0; i < n;i++){
            LastDay = max(LastDay, days[i] + i);
        }
        // we need to eat apples with lower expiry date first 
        priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int, int> > > pq;
        int eatenApples = 0;
        int day = 0;
        while(day < n || !pq.empty()){// eaither array ends or queue is empty
            if(day < n){
               // on a particular day Number of apples are there.
                int count = apples[day];
                int expiry = days[day] + day;
    
                // Add Number of apples and their priority !
                if(count != 0)
                pq.push({expiry,count});  
            }
            // Remove if Expired Apples || if day is greater then you are expired 
            while(!pq.empty() && (pq.top().first <= day)) pq.pop();
            // only valid apples are left to this point !
            if(!pq.empty()){
                auto data = pq.top();
                pq.pop();
                if(data.second > 0){
                    data.second--;
                    eatenApples++;
                    if(data.second > 0)
                    pq.push(data);
                }
            }
            day++;
        }
        return eatenApples;
    }
    
};
// same heap pattern as above
// 1094. Car Pooling
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // 3 data members  start -> end , Number Of passengers
        // arrivals to be sorted so that i will not miss any cuz the vechicle dosent turn 
        sort(trips.begin(),trips.end(), [](const vector<int>& a,const vector<int>& b){
            // if a < b based on second element then leave else swap , the true condition states they are 
            // alined correctly
            return a[1] < b[1];
        });
        
        priority_queue< pair<int,int> , vector< pair<int, int> > , greater< pair<int,int > > >  pq;

        // get max distance to be travelled !
        int n = trips.size(),maxLoc = 0;
        for(int i = 0; i < n;i++){
            maxLoc = max(maxLoc,trips[i][2]);
        }
        int currCapacity = 0;
        int i = 0;
        // valid loop and you must go to destination
        for(int loc = 0; loc <= maxLoc; loc++){
            //add passengers
            // multiple passengers can get into vech same day!
            while(i < n && trips[i][1] == loc){
                // if some one is dropped then remove him first 
                    while(!pq.empty() && pq.top().first == loc){
                        auto data = pq.top();
                        pq.pop();
                        currCapacity -= data.second;
                    }
                currCapacity += trips[i][0];
                if(currCapacity > capacity) return false;
                pq.push({trips[i][2],trips[i][0]});
                i++;
            }
            // neither the passenger drops before the desired loc nor after the location
            while(!pq.empty() && pq.top().first == loc){
                auto data = pq.top();
                pq.pop();
                currCapacity -= data.second;
            }
            
        }
        return pq.empty();
    }
};
// Rod Question 
// Hardest part Generating Kth Smallest Subsequence with heaps so that the smallest subsequence is taken
// 2386. Find the K-Sum of an Array
// total - 2000th smallest
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
            auto [toBeSubtracted , idx] = pq.top(); pq.pop();

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
/* Include and Exclude -> the above Q */

