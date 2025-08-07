Ultimate Marathon on DP Matrix Pattern ! 
  -62. Unique Paths
  -64. Minimum Path Sum
  -931. Minimum Falling Path Sum
  -1463. Cherry Pickup II
  -3363. Find the Maximum Number of Fruits Collected


// 62. Unique Paths
class Solution {
private:
    int traverse(int i, int j ,  vector< vector<int> >& grid,int n, int m,vector< vector<int> >& dp){
        if(i == m - 1 && j == n - 1){
            return 1;
        }
        if(dp[i][j] != -1) return dp[i][j];
        // go right
        int right = 0, down = 0;
        if(j + 1 < n)
            right = traverse(i, j + 1, grid,n,m,dp);
        if(i + 1 < m)
            down = traverse(i + 1, j, grid,n,m,dp);
        
        return dp[i][j] = down + right;
    }
public:
    int uniquePaths(int m, int n) {
        vector< vector<int> > grid(m, vector<int>(n,0));
        vector< vector<int> > dp(m,vector<int>(n,-1));
        grid[m-1][n-1] = 1;
        int ans = traverse(0,0, grid,n,m,dp);
        return ans;
    }
};


//64 Minimum Path Sum 
class Solution {
private:
    int getSum(int i, int j, vector<vector<int>>& grid,vector<vector<int>>& dp){
        
        if(i == 0 && j == 0) return grid[i][j];
        if(dp[i][j] != -1) return dp[i][j];
        
         int top = INT_MAX, left = INT_MAX;
         if(i-1 >= 0)
         top = getSum(i-1, j, grid, dp) + grid[i][j];
         if(j-1 >= 0)
         left = getSum(i, j - 1,grid, dp) + grid[i][j];
        
        return dp[i][j] = min(top,left);
    }
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m,-1));
        return getSum(n-1, m-1, grid,dp);
    }
};


// 931. Minimum Falling Path Sum
class Solution {
private:
    int getSum(int i, int j, vector<vector<int>>& grid,vector<vector<int>>& dp,int n){
        
        if(i == n - 1) return grid[i][j];
        if(dp[i][j] != -100000) return dp[i][j];
        int leftMin = INT_MAX, rightMin = INT_MAX, currMin = INT_MAX;
        if(j - 1 >= 0)
            leftMin = getSum(i + 1, j - 1, grid, dp, n);
        if(j + 1 < n)
            rightMin = getSum(i + 1, j + 1, grid, dp, n);
        currMin = getSum(i + 1, j, grid, dp, n);

        return dp[i][j] = min(leftMin, min(rightMin, currMin)) + grid[i][j];
    }
public:

    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n,-100000));
        int minPath = INT_MAX;
        for(int i = 0; i < n; i++){
             minPath = min(minPath,getSum(0,i,grid,dp,n));
        }
        return minPath;
    }
};

// 1463. Cherry Pickup II
class Solution {
private:
    int getMax(int i, int j1, int j2, vector<vector<int>>& grid,vector< vector < vector<int> > >& dp,int rows, int cols){
        if(j1 < 0 || j1 >= cols || j2 < 0 || j2 >= cols) return -1e8; // max() avoids !
        if(i == rows - 1){
            if(j1 == j2) return grid[i][j1];
            return grid[i][j1] + grid[i][j2];
        }

        if(dp[i][j1][j2] != -1) return dp[i][j1][j2];
        // Robot1Pos N Robot2Pos
        
        int LeftNLeft = getMax(i + 1, j1 - 1, j2 - 1, grid, dp, rows, cols);
        int LeftNMid = getMax(i + 1, j1 - 1, j2, grid, dp, rows, cols);
        int LeftNRight = getMax(i + 1, j1 - 1, j2 + 1, grid, dp, rows, cols);
        
        int MidNLeft = getMax(i + 1, j1, j2 - 1, grid, dp, rows, cols);
        int MidNMid = getMax(i + 1, j1, j2, grid, dp, rows, cols);
        int MidNRight = getMax(i + 1, j1, j2 + 1, grid, dp, rows, cols);

        int RightNLeft = getMax(i + 1, j1 + 1, j2 - 1, grid, dp, rows, cols);
        int RightNMid = getMax(i + 1, j1 + 1, j2, grid, dp, rows, cols);
        int RightNRight = getMax(i + 1, j1 + 1, j2 + 1, grid, dp, rows, cols);

        int max_value = -1;
        if(j1 == j2) max_value = grid[i][j1];
        else max_value = grid[i][j1] + grid[i][j2];

        // store combined maximum store !
        return dp[i][j1][j2] = max_value + max({LeftNLeft,LeftNMid,LeftNRight,MidNRight,MidNLeft,MidNMid
                                   ,RightNLeft,RightNMid,RightNRight});
    }
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        vector< vector < vector<int> > > dp(rows, vector<vector<int>>(cols , vector<int>(cols, -1)) );
        return getMax(0, 0, cols - 1, grid, dp,rows,cols);
    }
};



// 3363. Find the Maximum Number of Fruits Collected



// 3363. Find the Maximum Number of Fruits Collected

