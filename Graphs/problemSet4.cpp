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

// Code Written By me , BFS Logic Thats it
// 1091. Shortest Path in Binary Matrix
// Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
// A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1))
class Solution {
public: 
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if(grid[0][0] == 1 || grid[n-1][n-1] == 1)return -1;
        int res = grid[n-1][n-1];
        vector< unordered_map < int , bool > > visited(n);
        queue< tuple < int , int, int > > q;
        vector< pair<int,int> > arr(8);
        arr = { {-1,-1},{-1,0},{-1,1}, {0,-1},{0,1},{1,-1},{1,0},{1,1} };
        q.push({0,0,1});
        visited[0][0] = true;
        while(!q.empty()){
            auto top = q.front(); q.pop();

            int i = get<0>(top);
            int j = get<1>(top);
            int c = get<2>(top);

            if(i == n-1 && j == n-1) return c;
            // for all directions
            for(int d = 0 ; d < 8 ; d++){
                int t1 = i + arr[d].first;
                int t2 = j + arr[d].second;
                if(t1 < n && t2 < n && t1 >= 0 && t2 >= 0 && !visited[t1][t2]){
                    visited[t1][t2] = true;
                    if(grid[t1][t2] == 0){
                        q.push({t1,t2,c+1});
                    }
                }
            }
        }
        return -1;
    }
    
};

// CodeStudio 
// // Shortest path in an unweighted graph
// Problem statement
// The city of Ninjaland is analogous to the unweighted graph. The city has ‘N’ houses numbered from 1 to ‘N’ respectively and are connected by M bidirectional
// roads. If a road is connecting two houses ‘X’
// and ‘Y’ which means you can go from ‘X’ to ‘Y’ or ‘Y’ to ‘X’. It is guaranteed that you can reach any house from any other house via some combination of roads. 
// Two houses are directly connected by at max one road.
// A path between house ‘S’ to house ‘T’ is defined as a sequence of vertices from ‘S’ to ‘T’. Where starting house is ‘S’ and the ending house is ‘T’ and there is 
// a road connecting two consecutive houses. Basically, the path looks like this: (S , h1 , h2 , h3 , ... T). you have to find the shortest path from ‘S’ to ‘T’.
// For example
// In the below map of Ninjaland let say you want to go from S=1 to T=8, the shortest path is (1, 3, 8). You can also go from S=1 to T=8  via (1, 2, 5, 8)  
//     or (1, 4, 6, 7, 8) but these paths are not shortest.

vector<int> shortestPath( vector<pair<int,int>> edges , int n , int m, int s , int t){
	// create adjcency list;
	vector<vector<int> > adj(n);
	for(int i = 0; i < m;i++){
		int u = edges[i].first - 1;
		int v = edges[i].second - 1;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// perform bfs
	queue<int> q;
	vector<bool> visited(n);
	vector<int> parent(n);
	s--; t--;


	q.push(s);
	parent[s] = -1;
	visited[s] = true;

	while(!q.empty()){
		int top = q.front();
		q.pop();

		for(int j : adj[top]){
			// ans is locked here
			if(!visited[j]){
				visited[j] = true;
				parent[j] = top;
				q.push(j);
			}
		}
	}


	// parent array;
	vector<int> res;
	res.push_back(t + 1);
	int p = parent[t];
	while(p != -1){
		res.push_back(p + 1);
		p = parent[p];
	}
	reverse(res.begin(),res.end());
	return res;
}


