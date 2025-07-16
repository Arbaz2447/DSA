//733. Flood Fill
//  BFS Logic
class Solution {
public:
private:
    void bfs(vector<vector<int>>& image, int a, int b, int x,
             unordered_map<int, unordered_set<int>>& visited, int n, int m) {
        using T = tuple<int, int, int>;
        queue<T> q;
        q.push({image[a][b], a, b});
        int target = image[a][b];

        while (!q.empty()) {
            auto getT = q.front();
            q.pop();

            int c = get<0>(getT);
            int i = get<1>(getT);
            int j = get<2>(getT);

            
            
            visited[i].insert(j);
            if (c == target) {
                image[i][j] = x;
                // 4 Possible directiions
                if (i + 1 < n &&
                    visited[i + 1].find(j) == visited[i + 1].end()) {
                    q.push({image[i+1][j], i + 1, j});
                }
                if (j + 1 < m && visited[i].find(j + 1) == visited[i].end()) {
                    q.push({image[i][j+1], i, j + 1});
                }
                if (i - 1 >= 0 &&
                    visited[i - 1].find(j) == visited[i - 1].end()) {
                    q.push({image[i-1][j], i - 1, j});
                }
                if (j - 1 >= 0 && visited[i].find(j - 1) == visited[i].end()) {
                    q.push({image[i][j - 1], i, j - 1});
                }
            }
        }
    }

public:
    // eaither you stop at the end of matrix or
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,int color) {
        unordered_map<int, unordered_set<int>> visited;
        int i = sr, j = sc;
        int n = image.size(), m = image[0].size();
        if (image[sr][sc] == color)
            return image;

        bfs(image, i, j, color, visited, n, m);
        return image;
    }
};

// Coding Ninjas
// Cycle Detection In Undirected Graph
// Using DFS
#include<bits/stdc++.h>
vector<vector<int>> makeList(vector<vector<int>>& edges, int n, int m) {
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0] - 1;
        int v = edges[i][1] - 1;

        adj[u].push_back(v);
        adj[v].push_back(u);   
    }
    return adj;
}

bool dfs(vector<vector<int>>& adj,int i, vector<bool>& visited, unordered_map<int,int>& parent){
    visited[i] = true;
    bool ans = false;
    for(int connection: adj[i]){
        if(!visited[connection]){
            parent[connection] = i;
            ans = dfs(adj,connection,visited,parent);
            if(ans == true) return true;
        }else{
            if(connection != parent[i]){
                return true;
            }
        }
    }
    return false;
}
string cycleDetection (vector<vector<int>>& edges, int n, int m){
// create Adjacency List
    vector<vector<int> > adj(n);
    adj = makeList(edges,n,m);
    bool ans = false;
    vector<bool> visited(adj.size(),false);
    unordered_map<int,int> parent;
    for(int i = 0; i < n;i++){
        if(!visited[i]){
            parent[i] = -1;
            // No need of visited and recursion can handle itself ! just by one parent is required !
            // O(n) space is saved!
            if(dfs(adj,i,visited,parent)){
                return "Yes";
            }
        }
    }
    return "No";

}



// Using BFS
#include<bits/stdc++.h>

vector<vector<int>> makeList(vector<vector<int>>& edges, int n, int m) {
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0] - 1;
        int v = edges[i][1] - 1;

        adj[u].push_back(v);
        adj[v].push_back(u);   
    }
    return adj;
}

void bfs(vector<vector<int>>& adj,int i,bool& ans,vector<bool>& visited){
    unordered_map<int,int> parent;
    
    queue<int> q;
    q.push(i);
    parent[i] = -1;
    visited[i] = true;
    while(!q.empty()){
        auto top = q.front();
        q.pop();

        for(int i = 0 ; i < adj[top].size();i++){
            int connection = adj[top][i];

            if(!visited[connection]){
                visited[connection] = true;
                parent[connection] = top;
                q.push(connection);
            }else{
                if(parent[top] != connection){
                    ans = true;
                    return;
                }
            }
        }
    }
}


string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    // create Adjacency List
    vector<vector<int> > adj(n);
    adj = makeList(edges,n,m);
    bool ans = false;
    vector<bool> visited(adj.size(),false);
   
    for(int i = 0; i < n;i++){
        if(!visited[i]){
            bfs(adj,i,ans,visited);
            if(ans == true){
                return "Yes";
            }
        }
    }
    return "No";
}


// coding ninjas
//  Detect Cycle In A Directed Graph
vector<vector<int> > adjList(vector< pair<int,int> >& edges,int& n){
  vector<vector<int> > adj(n);
  // traverse all pairs
  int m = edges.size();
  for(int i = 0; i < m; i++){
    pair<int,int> edge = edges[i];
    int u = edge.first - 1;
    int v = edge.second - 1;

    adj[u].push_back(v);
  }
  return adj;
}



bool dfs(int i,vector<bool>& visited,vector<bool>& dfsVisited,vector<vector<int>>& adj){
  
  dfsVisited[i] = true;
  visited[i] = true;

  for(int neighbour : adj[i]){
      if(!visited[neighbour]){
        bool ans = dfs(neighbour, visited,dfsVisited, adj);
        if(ans) return true;
      }
      else if(dfsVisited[neighbour]){
        return true;
      }
  }

  dfsVisited[i] = false;
  return false;

} 
  
int detectCycleInDirectedGraph(int n, vector < pair < int, int >> & edges) {
    // create Adj List
  vector<vector<int>> adj;
  adj = adjList(edges,n);

  vector<bool> visited(n,false); // Not to repeat Nodes
  vector<bool> dfsVisited(n, false);

  for(int i = 0; i < n; i++){
      if(!visited[i]){
        if(dfs(i, visited,dfsVisited,adj)){
        return 1;
      }
    }
  }

  return 0;
}

