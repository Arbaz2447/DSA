//1039. Minimum Score Triangulation of Polygon
// Pattern : Matrix Chain Multiplication !
class Solution {
private:
    int minTotal(vector<int>& v,int i, int j, vector<vector<int>>& dp){
        if(i + 1 == j) return 0; // basically you solved smallest problem and no problem remains so return 0;   
        if(dp[i][j] != -1) return dp[i][j];

        int mini = INT_MAX;
        for(int k = i + 1; k < j; k++){
            int val =  v[i]*v[j]*v[k] + minTotal(v,i,k,dp) + minTotal(v,k,j,dp);
            mini = min(mini, val);
        }

        return dp[i][j] = mini;
    }
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        // if dp[i][j] is assumed as base then which partition gaved min ans is stored ! 
        vector< vector<int> > dp(n, vector<int>(n,-1));
        return minTotal(values,0,n-1,dp);
    }
};

// 63. Unique Paths II
class Solution {
    private:
    const int inv = 1e9;
     int totalPaths(vector<vector<int>>& maze, int i, int j,int n, int m, vector<vector<int>>& dp){
        if(i >= n || j >= m || maze[i][j] == 1) return 0;
        if(i == n-1 && j == m-1) return 1;
        if(dp[i][j] != -1) return dp[i][j];

        int right = totalPaths(maze, i, j+1, n,m,dp);
        int down = totalPaths(maze, i + 1, j, n,m,dp);

        return dp[i][j] = right + down;
     }
    public:
    int uniquePathsWithObstacles(vector<vector<int>>& maze) {
        int rows = maze.size();
        int cols = maze[0].size();
        // early exit
        if (maze[0][0] == 1 || maze[rows - 1][cols - 1] == 1)
            return 0;
            
        vector<vector<int>> dp(rows, vector<int>(cols,-1));
        return totalPaths(maze, 0, 0, rows, cols, dp);
    }
};

// 1824. Minimum Sideway Jumps
class Solution {
private:
    const int inv = INT_MAX;
    int getMinSideJumps(vector<int>& obstacles,int pos,int lane,vector<vector<int>>& dp,vector< pair<int,int> >& nextLanes){
        if(pos == obstacles.size() - 1) return 0;
        if(obstacles[pos] == lane) return inv;
        
        if(dp[lane-1][pos] != -1) return dp[lane-1][pos]; 
            
        int sideJumps = 0;
        if(obstacles[pos + 1] != lane){ // If Next pos is Safe
            sideJumps = getMinSideJumps(obstacles, pos + 1, lane, dp,nextLanes);
        }else {
            int p1 = getMinSideJumps(obstacles, pos  , nextLanes[lane].first, dp,nextLanes);
            int p2 = getMinSideJumps(obstacles, pos, nextLanes[lane].second, dp,nextLanes);

            sideJumps = 1 + min(p1,p2);
        }

        return dp[lane-1][pos] = sideJumps;
    }
public:
    int minSideJumps(vector<int>& obstacles) {
        vector< pair<int,int> > nextLanes(4);
        nextLanes = {{0,0},{2,3},{1,3},{1,2}};
        vector<vector<int>> dp(3, vector<int>(obstacles.size(), -1));
        return getMinSideJumps(obstacles, 0, 2, dp,nextLanes);
    }
};
