// 200. Number of Islands
class Solution {
private:
    void  dfs(vector<vector<char>>& grid,vector<bool>& visited,int i,int j,int& rows,int& cols, int nodeNum){
        visited[nodeNum] = true;
        int dir[4][2] = { {0,-1},{-1,0},{0,1},{1,0}}; 
        for(auto& row : dir){
            int newI = i + row[0] , newJ = j + row[1];
            if(newI < rows && newJ < cols && newJ >= 0 && newI >= 0 && grid[newI][newJ] == '1' ){
                int newId = newI * cols + newJ;
                if(!visited[newId]) dfs(grid, visited, newI, newJ
                                        , rows, cols,newId);
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        // if(rows == 1 && cols == 1) return (grid[0][0] == '1')? 1 : 0;
        vector<bool> visited(rows * cols, false);
        int cnt = 0;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                int node_num = (i * cols)+ j;
                if(!visited[node_num] && grid[i][j] == '1'){
                    cnt++;
                    dfs(grid, visited, i, j,rows,cols, node_num);
                }
            }
        }
        return cnt;
    }
};


// 133. Clone Graph
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
// Why Not This Approach 


// The problem is not about "getting everyone's parent." The problem is that
// your algorithm has short-term memory (the parent variable) when it needs
// long-term memory. It needs to remember every single node it has ever cloned,
// regardless of the path taken.

// This is precisely what the map or the array (vector<Node*> clonedNodes(101,
// NULL)) provides. It's a global memory that answers one question:

// "Have I already created a clone for this original node?"

// If yes, you retrieve the existing clone from memory.
// If no, you create a new one and put it into memory for the future.

// Your logic is very close, but you must add this "memory" component to handle
// graphs correctly. The parent check alone is not powerful enough. so if i give
// one reason why my code fails is when node is say having multiple incoming
// then whats parent ? Code Fails on parent of 3

// Parent of 3 BOOM fails !

//     (Node 2)
//       /       \
// (Node 1)       (Node 3)
//       \       /
//       (Node 4)
// class Solution {
// public:
//     Node* cloneGraph(Node* node) {
//         if(node -> neighbors.size() == 0) NULL;
//         Node* clonedNode = new Node(node -> val);
//         queue< tuple<Node*,Node*,int> > q;
//         q.push({node,clonedNode,-1});
//         while(!q.empty()){
//             auto temp = q.front();
//             q.pop();

//             Node* oldNode = get<0>(temp);
//             Node* newNode = get<1>(temp);
//             int parent = get<2>(temp);

//             for(int i = 0; i < oldNode -> neighbors.size(); i++){
//                 if(oldNode -> neighbors[i] -> val != parent){
//                     newNode -> neighbors.push_back(new Node(oldNode ->
//                     neighbors[i] -> val));
//                      q.push({oldNode -> neighbors[i],newNode -> neighbors[i],
//                      oldNode -> val});
//                 }
//             }
//         }
//         return clonedNode;
//     }
// }; 
// Working Code !
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node == NULL) return NULL;
        // do BFS
        queue< Node* > q;
        Node* clone = new Node(node -> val);
        unordered_map < Node* , Node* > m;
        m[node] = clone;
        q.push(node);

        while(!q.empty()){
            Node* temp = q.front(); q.pop();

            for(int i = 0; i < temp -> neighbors.size(); i++){
                // Avoiding Duplicate memory creation
                // push Node Only once Despite of having many incoming edges 
                if(m.find(temp -> neighbors[i]) == m.end()){
                    m[temp -> neighbors[i]] = new Node(temp -> neighbors[i] -> val);
                    q.push(temp -> neighbors[i]);
                }
                m[temp] -> neighbors.push_back(m[temp -> neighbors[i]]);
                
            }
        }
        return clone;
    }
};
// 130. Surrounded Regions
class Solution {
private:
    void dfs(vector<vector<char>>& board, int i, int j,const int& rows,const int& cols){
        if(i >= 0 && i < rows && j >= 0 && j < cols && board[i][j] == 'O'){
            board[i][j] = '#';
        
            dfs(board, i - 1 , j, rows , cols);
            dfs(board, i , j - 1, rows , cols);
            dfs(board, i , j + 1, rows , cols);
            dfs(board, i + 1, j, rows , cols);
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        const int rows = board.size(), cols = board[0].size();
        // border traversal 
        for(int i = 0; i < rows ; i++){
            if(board[i][0] ==  'O') dfs(board, i, 0,rows,cols);
            if(board[i][cols - 1] == 'O') dfs(board, i, cols - 1,rows,cols);
        }
        for(int i = 0; i < cols ; i++){
            if(board[0][i] == 'O') dfs(board, 0, i,rows,cols);
            if(board[rows - 1][i] == 'O') dfs(board, rows - 1, i,rows,cols);
        }

        // make changes 
        for(int i = 0; i < rows ; i++){
            for(int j = 0; j < cols; j++){
                if(board[i][j] == '#') board[i][j] = 'O';
                else if(board[i][j] == 'O') board[i][j] = 'X';
            }
        }
    }
};

// 399. Evaluate Division
// You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the 
// equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.
// You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.
// Return the answers to all queries. If a single answer cannot be determined, return -1.0.
// Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.
// Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.

// Example 1:
// Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
// Explanation: 
// Given: a / b = 2.0, b / c = 3.0
// queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
// return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
// note: x is undefined => -1.0

class Solution {
private:
    bool dfs(unordered_map < string ,vector < pair < string , double > > >& edges,string node, string& dst ,
             double val, double& res,unordered_set<string>& visited){
            visited.insert(node);
            if(node == dst){
                res = val;
                return true;
            }

            for(auto& [nextNode, nextVal] : edges[node]){
                if(visited.find(nextNode) != visited.end()) continue;
                bool ans = dfs(edges, nextNode, dst, val * nextVal, res,visited);
                if(ans == true) return true;
            }
        return false;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                                vector<vector<string>>& queries) {
        // adj
        unordered_map < string ,vector < pair < string , double > > > edges;
        for(int i = 0; i < values.size(); i++){
            string u = equations[i][0];
            string v = equations[i][1];
            double w = values[i];
            edges[u].push_back({v,w});
            edges[v].push_back({u, (1.0/w)});
            
        }
        // dfs
        vector<double> res;
        for(auto& q : queries){
            string u = q[0];
            string v = q[1];
            if((edges.find(u) != edges.end()) && (edges.find(v) != edges.end())){
                //nodes can be present what if there is no relation among them ?
                // so still chance of -1
                double val = 0.0;
                unordered_set<string> visited;
                
                if(dfs(edges, u, v, 1,val,visited))
                    res.push_back(val); 
                else res.push_back(-1.0);
 
            }
            else res.push_back(-1.0);
        }
        return res;
    }
};


// 909. Snakes and Ladders

// if visited ignore why ? it mean i already have it , it means i have the 
//same square in less total already !
class Solution {
private:
    // My code ! 
    pair<int,int> getI(int num, const int& rows, const int& cols){
        // in which row it might lie ?
        // use zero based indexing ! 
        int r =  rows - 1 - (num - 1)/ cols;
        int c = -1;
        // check from reverse 
        if((rows - 1 - r) & 1 ) c = cols - 1 - ((num - 1) % cols);
        else c = (num - 1) % cols;

        return {r,c};
    }
    // Gemini
    // pair<int,int> getI(int num, const int& rows, const int& cols){
    //     int r = rows - 1 - (num - 1) / cols;
    //     int c;
    //     if ((rows - 1 - r) % 2 == 0) { // check direction from the bottom
    //         c = (num - 1) % cols;
    //     } else {
    //         c = cols - 1 - ((num - 1) % cols);
    //     }
    //     return {r,c};
    // }
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        const int r = board.size();
        const int c = board[0].size();
        int goal = r * c;
        // { box Number,Number of steps }
        queue < pair < int, int > > q;
        q.push({1,0});
        vector<bool> visited(goal + 1,false);
        visited[1] = true;
        
        while(!q.empty()){
            auto top = q.front();
            q.pop();
            int sqNo = top.first;
            int steps = top.second;
            if(sqNo == goal) return steps;

            for(int i = 1; i <= 6 ; i++){
                int nextStep = sqNo + i;
                // if > goal next also becomes grater no point of continue !
                if(nextStep > goal) break; 
                
                pair<int,int> index = getI(nextStep,r,c);
                int destination = board[index.first][index.second];
                
                if(destination == -1) destination = nextStep;

                if(destination == goal) return steps + 1;
                 
                if(!visited[destination]){
                    visited[destination] = true;
                    q.push({destination,steps + 1});
                }
            }
        }
        return -1;
    }
};

// 994. Rotting Oranges
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        // Init 
        int rows = grid.size(), cols = grid[0].size();
        vector<bool> visited(rows * cols, false);
        using P = pair < int , int >;
        queue< P > q;
        int dir[4][2] = {{-1,0}, {0,-1}, {0,1}, {1,0}};
        int time = 0;

        // Init Queue
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(grid[i][j] == 2) q.push({i,j});
            }
        }

        // empty the Queue
        while(!q.empty()){
            int size = q.size();
             bool timeTaken = false;
            for(int z = 0; z < size; z++){
                auto top = q.front(); q.pop();  
                int i = top.first, j = top.second;
               
                // traverse all directions for next sec 
                for(auto& d : dir){
                    int ni = i + d[0], nj = j + d[1];
                    if(ni >= 0 && nj >= 0 && nj < cols && ni < rows && grid[ni][nj] == 1 && 
                       !visited[ni * cols + nj]){
                        timeTaken = true;
                        visited[ni * cols + nj] = true;
                        q.push({ni,nj});
                    }
                }
            }
            if(timeTaken) time++;
        }
        // check if there remain any 1 cell with unvisited 
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(grid[i][j] ==  1 && !visited[i * cols + j]) return -1;
            }
        }
        return time;
    }
};


