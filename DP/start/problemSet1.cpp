// 70. Climbing Stairs
class Solution {
public:
    int climbStairs(int n) {

        int stair0 = 1 , stair1 = 1;
        for(int i = 2; i <= n; i++){
           int stairN = stair0 + stair1;
            stair0 = stair1;
            stair1 = stairN;
        }
        return stair1;
    }
};

// tabulation
// class Solution {
// public:
//     int climbStairs(int n) {
//         vector<int> dp(n + 1,-1);

//         dp[0] = dp[1] = 1; // from 0 - 1st && 0 - 2nd stair is possible
//         for(int i = 2; i <= n; i++){
//             dp[i] = dp[i - 1] + dp[i - 2];
//         }
//         return dp[n];
//     }
// };

// Memoization !
// class Solution {
// private:
//     int countWays(int n ,vector<int>& dp){

//         if(n == 0) return 1; // stating that your path is correct
//         if(n < 0) return 0; // invalid path cant be counted.

//         if(dp[n] != -1) return dp[n];

//         return dp[n] = countWays(n - 1,dp) + countWays(n - 2,dp);
//     }
// public:
//     int climbStairs(int n) {
//         vector<int> dp(n + 1,-1);
//         return countWays(n, dp);
//     }
// };


// 746. Min Cost Climbing Stairs
class Solution {
public:
    // Space Optimization ! 
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        
        int stair0 = cost[0];
        int stair1 = cost[1];
        //Here dp size n + 1 is a Must !
        for(int i = 2; i < cost.size();i++){
            int stairN = min(stair1, stair0) + cost[i];
            stair0 = stair1;
            stair1 = stairN;
        } 
        return min(stair0, stair1);
    }
};

// tabulation 
// class Solution {
// public:
//     int minCostClimbingStairs(vector<int>& cost) {
//         int n = cost.size();
//         vector<int> dp(n + 1, -1);
//         dp[0] = cost[0];
//         dp[1] = cost[1];
//         //Here dp size n + 1 is a Must !
//         for(int i = 2; i < cost.size();i++){
//             dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
//         }
//         dp[n] = min(dp[n-1], dp[n-2]); 
//         return dp[n];
//     }
// };
// Memoization !

// class Solution {
// private:
//     int costOf(int n, vector<int>& cost,vector<int>& dp){
//         if(n < 0) return 0;
//         if(n == 0) return cost[0];

//         // Memoization
//         if(dp[n] != -1) return dp[n];

//         return dp[n] = min(costOf(n - 1, cost,dp), costOf(n - 2, cost,dp)) + cost[n];
//     }
// public:
//     int minCostClimbingStairs(vector<int>& cost) {
//         int n = cost.size();
//         //if you do bottom up greedy wont work ! based on my mindset right now
//         // Top down might work 
//         vector<int> dp(n + 1, -1);
//         int minCost = min(costOf(n - 1,cost,dp), costOf(n - 2,cost,dp));
//         return minCost;
//     }
// };

322. Coin Change
// Memoization + recursion
// sort desending ! 

class Solution {
private:
    int cnt(vector<int>& coins, int amount, vector<int>& dp){
        if(amount == 0) return 0;
        // here ⭐
        if(amount < 0) return INT_MAX;
        
        if(dp[amount] != -1) return dp[amount];
        // here ⭐ in both stars if i use upwards -1 then the int max is in all recursive levels
        // so i pass int max up but i expect -1 so use one value(integrity) for unreachable val !
        int mini = INT_MAX;
        for(int i = 0; i < coins.size(); i++){
            int val =  cnt(coins,amount - coins[i],dp);
            // if we get a valid min value it should be checked 
            // basically in memoization we instantly get out so level tracking is in accurate 
            if(val != INT_MAX){
                mini = min(mini,val + 1);
            }
        }
        
        // for this current amount The minimum value among coin array is mini ! 
        // Similar sub problem ! DP....!
        // dp[amount] thus amount + 1 req.
        return dp[amount] = mini;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        
        vector<int> dp(amount + 1, -1);
        int sol = cnt(coins,amount,dp);
        return (sol == INT_MAX)? -1 : sol;
        
    }
};

// Tabulation ! 104 19:00
