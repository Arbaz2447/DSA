2787. Ways to Express an Integer as Sum of Powers
279. Perfect Squares
983. Minimum Cost For Tickets


// 2787. Ways to Express an Integer as Sum of Powers
// Given two positive integers n and x.
// Return the number of ways n can be expressed as the sum of the xth power 
// of unique positive integers, in other words, the number of sets of unique integers [n1, n2, ..., nk] where n = n1x + n2x + ... + nkx.
// Since the result can be very large, return it modulo 109 + 7.
// For example, if n = 160 and x = 3, one way to express n is n = 23 + 33 + 53.
class Solution {
private:
    const int mod = 1e9 + 7;
    long long power(int base, int exp) {
        long long res = 1;
        for (int i = 0; i < exp; ++i) {
            res *= base;
        }
        return res;
    }
    
    int getNoOfWays(int num, int n ,const int& x,vector<vector<int>>& dp){
        // Base Cases 
        if(n == 0) return 1;
        int value = power(num,x);
        if(value > n || n < 0) return 0;
        if(dp[num][n] != -1) return dp[num][n];

        long long include = getNoOfWays(num + 1, n - value, x , dp);
        long long exclude = getNoOfWays(num + 1, n, x , dp);

        
        return dp[num][n] = (include + exclude) % mod;
    }
public:
    int numberOfWays(int n, int x) {
        const int power = x;
        // As we Need Unique powers then comes take it or leave it Knapsack 0/1
        vector<vector<int>> dp(n + 1, vector<int>(n+1, -1));
        return getNoOfWays(1,n, power, dp);
    }
};



// 279. Perfect Squares
// Given an integer n, return the least number of perfect square numbers that sum to n.
// A perfect square is an integer that is the square of an integer; in other words, it is the product of some 
// integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.
class Solution {
private:
    int getMin(int n,vector<int>& dp){
        if(n == 0) return 0;
        if(dp[n] != INT_MAX) return dp[n];
        int mini = INT_MAX;
        for(int i = 1; i*i <= n; i++){
            mini = min(mini , 1 + getMin(n - (i * i), dp));
        }
        return dp[n] = mini;
    }
public:
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        return getMin(n,dp);
    }
};


// 983. Minimum Cost For Tickets
// You have planned some train traveling one year in advance. The days of the year in which you will travel 
// are given as an integer array days. Each day is an integer from 1 to 365.

// Train tickets are sold in three different ways:

// a 1-day pass is sold for costs[0] dollars,
// a 7-day pass is sold for costs[1] dollars, and
// a 30-day pass is sold for costs[2] dollars.
// The passes allow that many days of consecutive travel.

// For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.
// Return the minimum number of dollars you need to travel every day in the given list of days.
class Solution {
private:
    int minimumCost(vector<int>& days, vector<int>& cost, int index,int n,vector<int>& dp){
        if(index >= n) return 0;
        if(dp[index] != -1) return dp[index];
        int dailyPass = cost[0] + minimumCost(days, cost, index + 1,n,dp);

        int validDays = days[index] + 6;
        int i;
        for(i = index ; i < n && days[i] <= validDays; i++){}
        int weeklyPass = cost[1] + minimumCost(days,cost,i,n,dp);

        validDays = days[index] + 29;
        int j;
        for(j = index ; j < n && days[j] <= validDays; j++){}
        int monthlyPass = cost[2] + minimumCost(days,cost, j,n,dp);
        return dp[index] = min({dailyPass,weeklyPass,monthlyPass});
    }
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        sort(days.begin(), days.end());// Don't apply directly in production ! 
        vector<int> dp(days.size() + 1, -1);
        return minimumCost(days,costs,0,days.size(),dp);
    }
};

