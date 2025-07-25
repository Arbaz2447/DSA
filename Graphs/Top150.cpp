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





