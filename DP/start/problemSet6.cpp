300. Longest Increasing Subsequence
354. Russian Doll Envelopes


// 300. Longest Increasing Subsequence
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> arr;
        arr.push_back(nums[0]);

        for(int i = 1; i < nums.size(); i++){
            if(nums[i] > arr.back()) arr.push_back(nums[i]);
            else{
                int idx = lower_bound(arr.begin(), arr.end(), nums[i]) - arr.begin();
                arr[idx] = nums[i];
            }
        }
        return arr.size();
    }
};

// Longest Increasing Subsequence memo , Tab

/*
class Solution {
private:
    // int maximimLength(vector<int>& nums, int index, int prevIndex,vector<vector<int>>& dp){
    //     if(index == nums.size()){
    //         return 0;
    //     }
    //     if(dp[index][1 + prevIndex] != -1) return dp[index][1+prevIndex];
    //     // Include
    //     int ans1 = 0;
    //     if(prevIndex == -1 ||  nums[index] > nums[prevIndex]){
    //          ans1 = 1 + maximimLength(nums, index + 1, index,dp);
    //     }

    //     int ans2 = maximimLength(nums, index + 1, prevIndex,dp);
    //     return dp[index][1+prevIndex] = max(ans1,ans2);
    // }
    int tabulation(vector<int>& nums){
        // if(index == nums.size()){ we need extra row for this 
        //     return 0;
        // }
        int n = nums.size();
        vector< vector<int>> dp(n+1,vector<int>(n+1, 0));

        for(int i = n - 1; i >= 0; i--){
            for(int c = i - 1; c >= -1; c--){
                int ans1 = 0;
                if(c == -1 ||  nums[i] > nums[c]){
                     ans1 = 1 + dp[i + 1][i+1]; // [check next index of i + 1][prev value is i + 1]
                }
        
                int ans2 =dp[i + 1][c+1];// prev can be -1

                dp[i][c+1] = max(ans1,ans2);
            }
        }
        return dp[0][0];
    }
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // dp[currIndex][prevIndex]
        return tabulation(nums);
    }
};
*/

// 354. Russian Doll Envelopes
class Solution {
private:
    int lengthOfLIS(vector<vector<int>>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> arr;
        arr.push_back(nums[0][1]);

        for(int i = 1; i < nums.size(); i++){
            if(nums[i][1] > arr.back()) arr.push_back(nums[i][1]);
            else{
                int idx = lower_bound(arr.begin(), arr.end(), nums[i][1]) - arr.begin();
                arr[idx] = nums[i][1];
            }
        }
        return arr.size();
    }
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // avoiding the same lhs adding by decending the rhs !
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a,const vector<int>& b){
           if(a[0] == b[0]) return a[1] > b[1];
           return a[0] < b[0];
        });

        return lengthOfLIS(envelopes);

    }
};
