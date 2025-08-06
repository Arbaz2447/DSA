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
343. Integer Break (pending ... !).
