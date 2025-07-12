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

// 52.  N Queens - ii
class Solution {
private:
    bool isSafe(vector<vector<int>>& maze,int i , int j , int &n,unordered_map< int , bool >& pos){
        // check row
        if(j >= n || pos[i] == true) return false;
        // diagonal
        int s = i;
        int e = j;

        // 2 diagonal optimization could also be done
        while(s >= 0 && e >= 0){
            if(maze[s--][e--] == 1) return false;
        }
         s = i;
         e = j;
        while(s < n && e >= 0){
            if(maze[s++][e--] == 1) return false;
        }
        return true;
    }
    void solve(vector<vector<int>>& maze,int& n, int col, int& w,int& queens,unordered_map< int , bool >& pos){
        if(queens == n){
            w++;
            return;
        }
        // Why Not tracking row Becz -> when you place a queen you move on 
        // eaither you get ans in depth or not i have to find all possibilities so

        for(int i = 0; i < n; i++){
            if(isSafe(maze,i,col,n,pos)){
                queens++;
                maze[i][col] = 1;
                pos[i] = true;
                solve(maze,n,col + 1,w,queens,pos);
                pos[i] = false;
                maze[i][col] = 0;
                queens--;
            }   
        }
    }
public:
    int totalNQueens(int n) {
        unordered_map< int , bool > QueensPos;
        vector< vector<int> > maze(n, vector<int>(n,0));
        int size = n;
        int numberOfways = 0;
        int Q = 0;
        solve(maze,size,0,numberOfways,Q,QueensPos);
        return numberOfways;
    }
};

// 37.Soduku solver 
// Excellent Explination of formula 
/*1. Get top-left corner of the 3×3 box:

int startRow = (row / 3) * 3;
int startCol = (col / 3) * 3;

2. Use this loop:
for(int k = 0; k < 9; k++) {
    int r = startRow + k / 3;  // Row offset (0, 1, 2)
    int c = startCol + k % 3;  // Col offset (0, 1, 2)
    // Access cell (r, c)
}*/

class Solution {
public:
    bool isSafe(char& val,vector<vector<char>>& board,int& n,int& i, int& j){
        for(int it = 0; it < 9 ; it++){
            // you have 9 chances check rows cols and 3x3
            if(board[i][it] == val) return false;
            if(board[it][j] == val) return false;
            
            // get the top left i mean get initial positions
            int startRow = (i / 3) * 3;
            int startCol = (j / 3) * 3;

            // traverse that initial position 3*3 times
            
            int rowIndex = startRow + (it / 3);// only move once after 3 steps
            int colIndex = startCol + (it % 3); // this should move every time
            if(board[rowIndex][colIndex] == val) return false;
        }
        return true;
    }
    
    bool solve(vector<vector<char>>& board,int& n){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                // if its empty cell
                if(board[i][j] == '.'){
                    // you can place Numbers 1 - 9
                    for(int k = 1; k <= 9; k++){
                        char val = '0' + k;
                        if(isSafe(val,board,n,i,j)){
                            board[i][j] = val;
                            bool solved = solve(board,n);
                            if(solved){ // if board gets solved then the value putted is gud
                                return true;
                            }else{ // nah then backtrack and use another value.
                                board[i][j] = '.';
                            }
                        }
                    }
                    return false;
                }
            }
        }
        // dont care 
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {

        // do backtracking if wrong ans else make the changes permanent
        int n = board.size();
        bool ans = solve(board,n);
    }
};
