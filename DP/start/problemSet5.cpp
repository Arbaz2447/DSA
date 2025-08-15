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
