// rat In a Maze problem GFG
// Find Unique Paths - ii left after DP
class Solution {
    private:
     void getValues(vector<vector<int>>& visited,vector<vector<int>>& maze,vector<string>& ans,string& res,int i,int j,int& n,int& m){
         if(i == n-1 && j == m-1){
             ans.push_back(res);
             return;
         }
          
          if(i < n && j < m && i >= 0 && j >= 0 && visited[i][j] == 0 && maze[i][j] != 0){
              visited[i][j] = 1;
                // up call
                res.push_back('U');
                getValues(visited,maze,ans,res,i-1,j,n,m);
                res.pop_back();
                
                res.push_back('D');
                getValues(visited,maze,ans,res,i+1,j,n,m);
                res.pop_back();
                
                res.push_back('L');
                getValues(visited,maze,ans,res,i,j-1,n,m);
                res.pop_back();
                
                res.push_back('R');
                getValues(visited,maze,ans,res,i,j+1,n,m);
                res.pop_back();
                

              visited[i][j] = 0;
          }
       
     }
  public:
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        // code here
        int rows = maze.size();
        int cols = maze[0].size();
        
        vector< vector<int> > visited(rows , vector<int>(cols));
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                visited[i][j] = 0;
            }
        }
        
        vector<string> ans;
        string res = "";
        getValues(visited,maze,ans,res,0,0,rows,cols);
        sort(ans.begin(),ans.end());
        return ans;
    }
};

// Leetcode 51. N-Queens
// backtracking is just Undo
//💡 Recursion + Backtraking Concept is straight Forward so think straight forward !

class Solution {
public:

     void updateRes(vector<vector<string>>& res,vector<vector<int>>& mat,int& n){
        vector<string> ans;
        for(int i = 0; i < n; i++){
            string s = "";
            for(int j = 0; j < n; j++){
                if(mat[i][j] == 1) s+="Q";
                else s+=".";
            }
            ans.push_back(s);
        }
        res.push_back(ans);
    }

    bool isValid(vector<vector<int>>& mat,int i, int j,int& n){
        // check col
        int row = i;
        int col = j;
        while(col >= 0){
            if(mat[row][col] == 1) return false;
            col--;
        }
        // No need of row check
        // check upper Left diagonal
        row = i;
        col = j;
        while(row >= 0 && col >= 0){
            if(mat[row][col] == 1) return false;
            col--;
            row--;
        }
        row = i;
        col = j;
        while(row < n && col >= 0){
            if(mat[row][col] == 1) return false;
            col--;
            row++;
        }
        return true;
    }

    void solve(vector<vector<string>>& res,vector<vector<int>>& mat,int& Q, int& n, int j){
        // Queen Count is same as N
        if(Q == n) {
            updateRes(res,mat,n);
            return;
        }
        // check row and diagonal and no need for col cuz we are just calling next
        for(int row = 0; row < n; row++){
            if(isValid(mat,row,j,n)){
                mat[row][j] = 1;
                Q++;
                solve(res,mat,Q,n,j+1);
                // say if you reached b.s then youve stored the res what if you are wrong at some point
                // then check another possibility by backtrack;
                Q--;
                mat[row][j] = 0;
            }
        }
        
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector< vector<int>> mat(n , vector<int>(n,0));
        int Q = 0;
        solve(res,mat,Q,n,0);
        return res;
    }
};
