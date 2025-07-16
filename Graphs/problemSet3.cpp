// 207. Course Schedule

// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
//You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
// Return true if you can finish all courses. Otherwise, return false.


class Solution {
private:
vector<vector<int> > adjList(vector< vector<int> >& edges,int& n){
  vector<vector<int> > adj(n);
  // traverse all pairs
  int m = edges.size();
  for(int i = 0; i < m; i++){
    int u = edges[i][0];
    int v = edges[i][1];

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
public:
    bool canFinish(int n, vector<vector<int>>& prerequisites) {
        if(prerequisites.size() == 0) return true;
        vector< vector<int> > adj;
        adj = adjList(prerequisites,n);

        vector<bool> visited(n,false); // Not to repeat Nodes
        vector<bool> dfsVisited(n, false);

        for(int i = 0; i < n; i++){
                if(!visited[i]){
                    if(dfs(i, visited,dfsVisited,adj)){
                    return false;
                }
            }
        }

        return true;
    }
};

// 210. Course Schedule II
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where
// prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
// Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them.
// If it is impossible to finish all courses, return an empty array.

class Solution {
private:
vector<vector<int>> adjList(vector<vector<int>>& edges, int& n) {
    vector<vector<int>> adj(n);
    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        adj[b].push_back(a); // b → a
    }
    return adj;
}

bool dfs(int node, vector<bool>& visited, vector<bool>& dfsVisited, vector<vector<int>>& adj, stack<int>& s) {
    visited[node] = true;
    dfsVisited[node] = true;

    for (int neighbour : adj[node]) {
        if (!visited[neighbour]) {
            if (dfs(neighbour, visited, dfsVisited, adj, s)) return true;
        } else if (dfsVisited[neighbour]) {
            return true; // cycle found
        }
    }

    dfsVisited[node] = false;
    s.push(node);
    return false;
}

public:
vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj = adjList(prerequisites, n);

    vector<bool> visited(n, false);
    vector<bool> dfsVisited(n, false);
    stack<int> s;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, visited, dfsVisited, adj, s)) return {};
        }
    }

    vector<int> ans;
    while (!s.empty()) {
        ans.push_back(s.top());
        s.pop();
    }

    return ans;
}
};

// If any case you wanted to validate the Topological sort then do like this aldough after dfs not required 
class Solution {
private:
    vector<vector<int>> adjList(vector<vector<int>>& edges, int& n) {
        vector<vector<int>> adj(n);
        for (int i = 0; i < edges.size(); i++) {
            int v = edges[i][0];
            int u = edges[i][1];
            adj[u].push_back(v);  // u → v (u is prerequisite for v)
        }
        return adj;
    }

    bool dfs(int node, vector<bool>& visited, vector<bool>& dfsVisited,
             vector<vector<int>>& adj, stack<int>& s) {
        visited[node] = true;
        dfsVisited[node] = true;

        for (int neighbour : adj[node]) {
            if (!visited[neighbour]) {
                if (dfs(neighbour, visited, dfsVisited, adj, s)) return true;
            } else if (dfsVisited[neighbour]) {
                return true; // cycle found
            }
        }

        dfsVisited[node] = false;
        s.push(node); // add to topo sort after all children visited
        return false;
    }

    bool isValidTopoOrder(vector<int>& topoOrder, vector<vector<int>>& prerequisites, int n) {
        vector<int> pos(n);
        for (int i = 0; i < topoOrder.size(); ++i) {
            pos[topoOrder[i]] = i;
        }
        for (auto& pre : prerequisites) {
            int a = pre[0], b = pre[1];
            if (pos[b] > pos[a]) {
                return false;  // prerequisite comes after dependent → invalid
            }
        }
        return true;
    }

public:
    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj = adjList(prerequisites, n);

        vector<bool> visited(n, false);
        vector<bool> dfsVisited(n, false);
        stack<int> s;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(i, visited, dfsVisited, adj, s)) {
                    return {}; // cycle found → impossible
                }
            }
        }

        vector<int> ans;
        while (!s.empty()) {
            ans.push_back(s.top());
            s.pop();
        }

        // Optional validation (can be skipped in contests)
        if (!isValidTopoOrder(ans, prerequisites, n)) {
            return {};
        }

        return ans;
    }
};



