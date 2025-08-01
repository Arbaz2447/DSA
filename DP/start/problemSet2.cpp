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

// cut into segments Tabulation and Space Optimiztaion ! pending ! code studio
int solve(int n, vector<int>& arr){
    vector<int> dp(n+1, INT_MIN);
    dp[0] = 0;
    for(int i = 1; i <= n; i++){

        // traverse whole array for smallest subproblem !
        for(int j = 0 ; j < arr.size(); j++){
            if(i - arr[j] >= 0 && dp[i - arr[j]] != INT_MIN){
                dp[i] = max(dp[i],1 + dp[i - arr[j]]);
            }
        }
    }
    return dp[n];
}

int cutSegments(int n, int x, int y, int z) {

    vector<int> arr;
    arr.push_back(x);
    arr.push_back(y);
    arr.push_back(z);

    int ans = solve(n,arr);
    return (ans == INT_MIN)? 0 : ans;
}

// 213. House Robber II
class Solution {
private:
    int solve(vector<int>& nums){
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
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        
        vector<int> first(nums.begin() + 1, nums.end());
        vector<int> second(nums.begin() , nums.end() - 1);

        int val2 = solve(second);
        int val1 = solve(first);
        int res = max(val2,val1);
        return (res != INT_MIN)? res : 0; 
    }
};

 // same code optimized by gpt 
/*
🔁 Optimized Version (No extra vector creation):
cpp
Copy
Edit
class Solution {
private:
    int solve(vector<int>& nums, int start, int end){
        int len = end - start + 1;
        if(len == 1) return nums[start];

        int var1 = 0;
        int var2 = nums[start];
        int var3 = nums[start + 1];

        for(int i = start + 2; i <= end; i++){
            int ans = max(var1, var2) + nums[i];
            var1 = var2;
            var2 = var3;
            var3 = ans;
        }
        return max(var2, var3);
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];

        int val1 = solve(nums, 1, n - 1);      // exclude first house
        int val2 = solve(nums, 0, n - 2);      // exclude last house
        return max(val1, val2);
    }
};
*/

// Count derangements
// A Derangement is a permutation of ‘N’ elements, such that no element appears in its original position. For example, 
// an instance of derangement of {0, 1, 2, 3} is {2, 3, 1, 0}, because 2 present at index 0 is not at its initial 
// position which is 2 and similarly for other elements of the sequence.
// Given a number ‘N’, find the total number of derangements possible of a set of 'N’ elements.

//My Understanding 
// so basically what i got is you have for n size array you can place in n - 1 positions so you multiply 
// n - 1 * (...) then basically you will land on pos k , that elem k has 2 choices eaither it can also land on 
// place of n so what remains n - 2 elem basically this is a sub problem and n - 2 empty places what if it dosent 
// land ? n - 1 places and n - 1 elem also a sub problem , so n - 1 * ( F(n - 1) + F(n - 2) ) im basically right ?

// https://gemini.google.com/share/1ba78ca5ac6f

#include<vector>
#define m 1000000007
long long int getAns(int n , vector<long long int>& dp){
     if(n == 1) return 0;
     if(n == 2) return 1;

    if(dp[n] != -1)return dp[n];

    long long int t1 = getAns(n - 1, dp);
    long long int t2 = getAns(n - 2, dp);
    long long int sum = (t1 + t2) % m;
    long long int ans =  ((n - 1LL) * sum) % m;
    return dp[n] = ans;
}


long long int countDerangements(int n) {

    vector<long long > dp(n + 1, -1);
    return getAns(n,dp);
}




343. Integer Break (pending ... !).
