// Painting fence algo dp ! coding ninjas ! 
// explination in book !
// Eather overflow occurs from mod range from add or mult
#define mod 1000000007
int add(int a , int b){
    return (a + b) % mod; // modulo arithmatic appled !
}
int mul(int a , int b){
    return (1LL * a * b) % mod; // modulo arithmatic appled !
}
int solve(int n, int k,vector<int>& dp){
    if(n == 1) return k;
    if(n == 2) return add(k , mul( k , k - 1 ) );

    if(dp[n] != -1) return dp[n];

    return dp[n] = add( mul(solve(n-1,k,dp),k - 1) , mul(solve(n-2,k,dp),k-1) );
}
int numberOfWays(int n, int k) {
    vector<int> dp(n + 1, -1);
    return solve(n,k,dp);
}



// 377. Combination Sum IV
// Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.
//Memoization !
class Solution {
private:
    int findWays(vector<int>& nums, int k,vector<int>& dp){
        if(k == 0) return 1;
        if(k < 0) return 0;
        if(dp[k] != -1) return dp[k];
        int cnt = 0;
        for(int i = 0; i < nums.size(); i++){
            cnt += findWays(nums, k - nums[i],dp);
        }
        return dp[k] = cnt;
    }
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, -1);
        return findWays(nums,target,dp);
    }
};

// 0 - 1 Knapsack Problem , CodeStudio !

class Solution {
  public:
  
    int getMax(int w, int item, vector<int> &val, vector<int> &wt,vector<vector<int>> &dp){
        if(item == 0){
            if(wt[item] <= w){
                return val[item];
            }
            return 0;
        }
        if(dp[item][w] != -1) return dp[item][w];
       
        int maxOnEx = getMax(w, item - 1,val, wt,dp);
        int maxOnIn = 0;
        if(wt[item] <= w){
             maxOnIn = val[item] + getMax(w - wt[item], item - 1,val , wt,dp);
        }
        
        return dp[item][w] = max(maxOnEx,maxOnIn);
    }
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        vector< vector<int> > dp(val.size(), vector<int>(W + 1,-1));
        return getMax(W,val.size() - 1, val, wt,dp);
    }
};

// Decode Ways 91 Leetcode !
class Solution {
private:
    int totalWays(string& s,int startI, int& n,vector<int>& dp){
        if(startI >= n) return 1;
        if(s[startI] == '0') return 0;
        // Memoize !
        if(dp[startI] != -1) return dp[startI];

        int parititon1 = totalWays(s,startI + 1, n, dp);

        int parititon2 = 0;
        // Check if its <= 26 and check will i get valid next call !
        if(startI + 1 < n){
            int num = (s[startI] - '0') * 10 + (s[startI + 1] - '0');  
            if(num <= 26) parititon2 = totalWays(s,startI + 2, n, dp);
        }

        return dp[startI] = parititon1 + parititon2;
    }
public:
    int numDecodings(string s) {
        int n = s.length();
        vector<int> dp(n, -1);
        return totalWays(s,0,n,dp);
    }
};

343. Integer Break (pending ... !).
