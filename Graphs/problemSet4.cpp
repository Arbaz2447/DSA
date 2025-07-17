// 210. Course Schedule II
// same Question But With some Changes 

// Topological stack verification and cycle detection technique using Ts
// So Cycle in Directed Graph Via T.S Via BFS and DFS can be verified by checking 
// DFS -> stack size and Number of nodes
// BFS -> resultant answer and number of nodes 

// yes i know in topological sort finding using bfs  if my topological sort in resulting array is equal to number of
// nodes then its valid but can i say that throuh dfs and stack if my stack length  != number of nodes then its
// invalid ?
// yes if cycle detected you just return and dont push into stack!

// SO, basically by just T.S , You can get order , You can verify it , detect Cycle in DG , Via DFS and BFS

class Solution {
private:
    void dfs(vector<vector<int>>& adj,vector<bool>& visited,vector<bool>& dfsVisited,stack<int>& s,int i){
        visited[i] = true;
        dfsVisited[i] = true;

        // visit all children
        for(auto j : adj[i]){
            if(!visited[j]){
                dfs(adj,visited,dfsVisited,s,j);
                // pass upwards from recursion! 
            }else if(dfsVisited[j]){
                return;
            }
            // else {} ignore just visited case and go to another call! 
        }

        s.push(i);
        dfsVisited[i] = false;
    }
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        int edges = prerequisites.size();
        for(int i = 0; i < edges;i++){
            int u = prerequisites[i][0];
            int v = prerequisites[i][1];

            adj[v].push_back(u); // edge based on Question.
        }

        vector<bool> visited(numCourses,false);
        vector<bool> dfsVisited(numCourses,false);
        stack<int> s;

       for(int i = 0; i < numCourses;i++){
            if(!visited[i]){
                dfs(adj,visited,dfsVisited,s,i);
            }
       }

       // No cycle the Topological sort is valid
       vector<int> arr;
       if(s.size() == numCourses){
            while(!s.empty()){
                arr.push_back(s.top());
                s.pop();
            }
       }
       return arr;
    }
};


// 802. Find Eventual Safe States
// There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] 
// is aninteger array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i]. A node is a terminal node if there are no 
// outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).

// Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.


// To Know the Beauty of BFS , In detecting Cycle , Topological Sort etc
// so we are travelling in reverse order and decreasing 
// out degree very good my point is abt self loops .. its considered as in degree 
// and out degree in this case what i think it will always remain the count 1
// (the self looped out going edge) 
// and never be pushed into stack and never be in ans 

// Process  : use push outgoing degree nodes == 0 into queue, go backward and decrease the outgoing edge count
// if its 0 push into ans , if its not its eaither -> its having another outgoing node and can be ignored cuz 
// it will be handeled later when we come from that path
// else ->  its having self loop and we never push it in queue i.e we never come from that path so absolutely ignored


class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> revGraph(n);
        vector<int> outDegree(n, 0);

        // Reversing the adj List 
        // Reverse Traversal possible and decreasing out degree
        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                revGraph[v].push_back(u); 
                outDegree[u]++;            
            }
        }

        queue<int> q;
        vector<int> safe;
        for (int i = 0; i < n; ++i) {
            if (outDegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int node = q.front(); q.pop();
            safe.push_back(node);
            for (int parent : revGraph[node]) {
                outDegree[parent]--;
                if (outDegree[parent] == 0) {
                    q.push(parent);
                }
            }
        }
        sort(safe.begin(), safe.end());
        return safe;
    }
};
