//Creating and Printing Adjacency List 
//You are given an undirected graph of 'N' nodes and 'M' edges. Your task is to create the graph and print the adjacency list of the graph. I
//t is guaranteed that all the edges are unique, i.e., if there is an edge from 'X' to 'Y', then there is no edge present from 'Y' to 'X' and
//vice versa. Also, there are no self-loops present in the graph.
vector < vector < int >> printAdjacency(int n, int m, vector < vector <int >> & graph) {
    //get all Neighbours for every node.
    vector<int> arr[n];
    // basically size of graph
    for(int i = 0 ; i < m;i++){
        int u = graph[i][0];
        int v = graph[i][1];

        // push for undirected graph /
        arr[v].push_back(u);
        arr[u].push_back(v);
    }
    // make common neighbours in adjacency list
    vector<vector<int>> res(n);
    for(int i = 0; i < n; i++){

        res[i].push_back(i);

        for(int j = 0; j < arr[i].size();j++){
            res[i].push_back(arr[i][j]);
        }
    }
    return res;
}




// 841. Keys and Rooms
// Visiting all Rooms if yes True else false
// First room is unlocked 
// Input: rooms = [[1],[2],[3],[]]
// Output: true
// Explanation: 
// We visit room 0 and pick up key 1.
// We then visit room 1 and pick up key 2.
// We then visit room 2 and pick up key 3.
// We then visit room 3.
// Since we were able to visit every room, we return true.
// Simple BFS in Graphs 
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        queue<int> q;
        vector<bool> visited(n,false);
        int cnt = 0;
        q.push(0);
        visited[0] = true;
        cnt++;
        
        while(!q.empty()){
            int front = q.front(); q.pop();

            for(auto num : rooms[front]){
                if(!visited[num]){
                    //Non visited room so 
                    cnt++;
                    visited[num] = true;
                    q.push(num);
                }
            }
        }
        return cnt == n;
    }
};




// Code Studio Simple DFS 
// Create Adjacency List
vector<vector<int>> makeAdjacencyList(vector<vector<int>> &edges , int e,int v){
    vector<vector<int>> adj(v);
    for(int i = 0; i < e; i++){
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return adj;
}
// DFS Code , 
//Like go in depth until no other path to explore
// go one step back and check for other paths (Not visited paths only) 
//- if already visited path occurs stop 
void dfs(vector<vector<int>>& res,vector<vector<int>>& adj,vector<bool>& visited,int& n,int i,vector<int>& ans){
    if(!visited[i]){
        ans.push_back(i);
        visited[i] = true;
        for(int j = 0 ; j < adj[i].size() ; j++){
            dfs(res,adj,visited,n,adj[i][j],ans);
        }
    }
}
vector<vector<int>> depthFirstSearch(int V, int E, vector<vector<int>> &edges){
    // Initilizing ADJ List
    int n = V;
    vector<bool> visited(n,false);
    vector<vector<int>> adj;
    adj = makeAdjacencyList(edges,E,V);
    // For every node DFS Becz of Disconnected components , if not visited call DFS
    vector<vector<int>> res;
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            vector<int> preRes;
            dfs(res,adj,visited,n,i,preRes);
            res.push_back(preRes);
        }
    }
    return res;
}




// 1971. Find if Path Exists in Graph
// Find path exist or not DFS is Economical to find path
class Solution {
private:
vector<vector<int>> makeAdjacencyList(vector<vector<int>> &edges , int e,int v){
    vector<vector<int>> adj(v);
    for(int i = 0; i < e; i++){
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return adj;
}
void dfs(vector<vector<int>>& adj,vector<bool>& visited,int& n,int i,int& dest,bool& found){
    
    if(!visited[i]){
        visited[i] = true;
        for(int j = 0 ; j < adj[i].size() ; j++){

            if(adj[i][j] == dest){
                found = true;
                return;
            }

            dfs(adj,visited,n,adj[i][j],dest,found);
        }
    }
}
bool depthFirstSearch(int V, int E, vector<vector<int>> &edges,int src,int dest){  
    int n = V;
    vector<bool> visited(n,false);
    vector<vector<int>> adj;
    adj = makeAdjacencyList(edges,E,V);
    bool found = false;
    dfs(adj,visited,n,src,dest,found);
    return found;   
}
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if(n == 1){
            return source == destination;
        }

        return depthFirstSearch(n,edges.size(),edges,source,destination);
    }
};




// Graphs + backtracking (DFS)
// 797. All Paths From Source to Target , All Paths (DFS) from source 
class Solution {
private:
    void solve(vector<vector<int>>& graph, vector< vector<int> >& ans,vector<int>& arr, int& target,int i){
        arr.push_back(i);
        // base case
        if(i == target){
            // the last path it should end here so push
            ans.push_back(arr);
        } else{
           for(int j = 0; j < graph[i].size(); j++){
                int next = graph[i][j];
                solve(graph,ans,arr,target,next);
           }
        }
        arr.pop_back();
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size() - 1;
        vector< vector<int> > ans;
        vector<int> arr;
        solve(graph,ans,arr,n,0);
        return ans;
    }
};
