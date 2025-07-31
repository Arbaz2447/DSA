// 198. House Robber
// Space Optimization !
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        int n = nums.size();


        int var1 = 0;
        int var2 = nums[0];
        int var3 = nums[1];
        for(int i = 2; i < n; i++){
            int ans = max(var1, var2) + nums[i];
            var1 = var2;
            var2 = var3;
            var3 = ans;
        }
        return max(var2,var3);
    }
};


// Tabulation 
// class Solution {
// public:
//     int rob(vector<int>& nums) {
//         if(nums.size() == 1) return nums[0];
//         int n = nums.size();

//         vector<int> dp(n + 1, -1);
//         dp[0] = 0;
//         dp[1] = nums[0];
//         dp[2] = nums[1];

//         for(int i = 2; i < n; i++){
//             dp[i + 1] = max(dp[i - 1], dp[i - 2]) + nums[i];
//         }
//         return max(dp[n-1],dp[n]);
//     }
// };

// Memoization
// class Solution {
// private:
//     int getMoney(vector<int>& nums,int index,vector<int>& dp){
//         if(index < 0) return 0;
//         if(dp[index] != -1) return dp[index];
        
//         int ans = max(getMoney(nums,index - 3,dp) ,getMoney(nums, index - 2,dp));
//         return dp[index] = ans + nums[index];
//     }
// public:
//     int rob(vector<int>& nums) {
//         if(nums.size() == 1) return nums[0];
//         int n = nums.size();
//         vector<int> dp(n,-1);
//        return max(getMoney(nums,n - 1,dp) , getMoney(nums, n - 2,dp));
//     }
// };

// Cut Into Segments
// #include<bits/stdc++.h>
// int solve(int n, vector<int>& arr,vector<int>& dp){
// 	if(n < 0) return INT_MIN;
// 	if(n == 0) return 0;

// 	if(dp[n] != -1) return dp[n];

// 	int maxi = INT_MIN;
// 	for(int i = 0; i < arr.size();i++){
// 		int ans = solve(n - arr[i],arr,dp);
// 		if(ans != INT_MIN){
// 			maxi = max(maxi,1 + ans);
// 		}
// 	}
// 	return dp[n] = maxi;
// }

// int cutSegments(int n, int x, int y, int z) {

// 	vector<int> arr;
// 	arr.push_back(x);
// 	arr.push_back(y);
// 	arr.push_back(z);

// 	vector<int> dp(n+1, -1);
// 	int ans = solve(n,arr,dp);
// 	return (ans == INT_MIN)? 0 : ans;
// }

cut into segments Tabulation and Space Optimiztaion ! pending !
343. Integer Break (pending ... !).
