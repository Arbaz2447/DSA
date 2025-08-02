// Painting fence algo dp ! coding ninjas ! 
// explination in book !
#include <bits/stdc++.h> 
#define mod 1000000007
// Eather overflow occurs from mod range from add or mult

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


343. Integer Break (pending ... !).
