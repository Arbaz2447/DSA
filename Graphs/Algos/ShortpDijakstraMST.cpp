// Before You Start 
1. Shortest Path -> to know shortest path you need to know all paths before node X,
2. Dijakstra -> make start as 0 cuz to reach src to src is 0 , take a dist array to track min among all nodes.
  pq.push({0,src}); that is distance covered at {start , node number}
  "lazy deletion" -> when you found a better entry but some prev entry remains in pq but deleting is not possible
  as it remains inside somewhere , so lyDel says that when it comes ignore !
3. Prims MST -> 
  extra ds req : 
  vector< int > key or replaced by pq. to track minimum weighted edge to include all nodes 
  vector < bool > nodesIncluded(nodes,false);
  vector< int > parent(nodes , -1);
  why set to 0 ? 
      //   Setting key[0] = 0 is how you give Prim's algorithm its starting point. It's the instruction that says, 
      //   "Begin building the Minimum Spanning Tree starting from node 0."
      // The Intuition
      // Think of building a network of roads to connect several towns. You have to start construction somewhere.
      // Before key[0] = 0: Initially, your key array is filled with INT_MAX. This represents that the "cost to connect" any town is currently
      // infinite because you haven't started building yet. If you were to ask your getMin function, "Which town is the cheapest to connect right now?",
      // it wouldn't have a valid answer because all costs are infinite.
    nodes included ds so that no nodes are missed !
    why parent ds to know when we ignore a costly edge to cheaper edge the parent changes thus we can find out what to include in Final Answer !
  


    

// 2050. Parallel Courses III
// You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given a 2D integer array relations where
// relations[j] = [prevCoursej, nextCoursej] denotes that course prevCoursej has to be completed before course nextCoursej (prerequisite relationship).
// Furthermore, you are given a 0-indexed integer array time where time[i] denotes how many months it takes to complete the (i+1)th course.


// ## 1. Shortest Path in a DAG (using Topological Sort)
// (Video 94: Parallel Courses III)

// The Core Idea: You can't know the true start time for a task until all its prerequisite tasks are finished. This algorithm processes nodes in a prerequisite-first 
// order (a topological sort).

// Analogy: Making Tea ☕
// You have to boil the water before you can pour it over the tea bag. A topological sort gives you the correct sequence. To find the total time, you
// calculate the finish time for each step in that order, ensuring all previous steps are accounted for. You trust the past because the sorted order 
// guarantees you've already found the best path to every node you've already processed.

class Solution {
private:
    void dfs(vector<vector<int>>& adj,vector<bool>& visited,stack<int>& topoSort,int i){
        // go till the deepest point say a -> b -> .... -> end
        visited[i] = true;
        
        for(int neighbours : adj[i]){
            if(!visited[neighbours]){
                visited[neighbours] = true;
                dfs(adj,visited, topoSort, neighbours);
            }
        }
        // you get nodes in reverse ordering last node first then stack again reverses it !
        // cout << i << " ";
        topoSort.push(i);
    }
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        // create adjacency list;
        vector< vector<int> > adj(n);
        int edges = relations.size();
        for(int i = 0; i < edges ; i++){
            int u = relations[i][0] - 1;
            int v = relations[i][1] - 1;

            adj[u].push_back(v);
        }

        stack< int > topoSort;
        vector<bool> visited(n,false);
        // find out topological sort, to get all the nodes that have an edge to node X
        for(int i = 0; i < n; i++){
            if(!visited[i]){
                dfs(adj,visited,topoSort,i);
            }
        }

        vector<int> distance(n,0);

        // get the init distances
        for(int i = 0; i < n;i++){
            distance[i] = time[i];
        }
        
        // final simulation
        while(!topoSort.empty()){
            int start = topoSort.top(); topoSort.pop();
            int nodeDist = distance[start];
            // traverse all the neighbours
            for( auto& n : adj[start]){
                if(nodeDist + time[n] >  distance[n]){
                    distance[n] = nodeDist + time[n];
                }
            }
        }

        int m = *max_element(distance.begin(),distance.end());
        return m;
    }
};


// 743. Network Delay Time
// You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi),
// where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
// We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes 
// to receive the signal, return -1.

// ## 2. Dijkstra's Algorithm (Shortest Path in a General Graph)
// (Video 95: Network Delay Time)
// The Core Idea: Find the shortest path from a starting point by always exploring the closest, unvisited node next. It's like a ripple expanding, 
//   always moving from the nearest point outward.
// Analogy: Spreading Wildfire 🔥
// Imagine a fire starts at one tree (the source). It will always spread to the closest, unburnt tree first. The algorithm works just like this: from
// all the nodes you can reach, you always greedily jump to the one that is closest to your starting point. You keep track of the "time to burn" for 
//   each tree and always prioritize the one with the lowest time.

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // create adjacency list
        int src = k - 1;
        int edges = times.size();
        vector < vector < pair< int , int > > > adj(n);
        for(int i = 0; i < edges ; i++){
            int u = times[i][0] - 1;
            int v = times[i][1] - 1;
            int w = times[i][2];

            adj[u].push_back({v,w});
        }

        vector<int> dist(n,INT_MAX);

        // distance of source is 0
        dist[src] = 0;
        using p = pair < int , int >;
        priority_queue < p , vector < p > , greater < p > > pq;
        pq.push({0,src});

        while(!pq.empty()){
            auto node = pq.top(); pq.pop();
            int nodeNumber = node.second;
            int nodeDist = node.first;
            // "lazy deletion"
            if(nodeDist <= dist[nodeNumber]) {
                // traverse adj list of that node ?
                for(const auto &n : adj[nodeNumber]){
                    int neighNumber = n.first;
                    int neighDist = n.second;
                    // n is vector of pairs 
                    if(dist[nodeNumber] + neighDist < dist[neighNumber]){
                        dist[neighNumber] = dist[nodeNumber] + neighDist;
                        pq.push({dist[neighNumber],neighNumber});
                    }
                }
            }
        }
        
        int ans = *max_element(dist.begin(),dist.end());
        return (ans == INT_MAX)? -1 : ans; 
    }
};
// 1584. Min Cost to Connect All Points
// You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
// The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, 
//   where |val| denotes the absolute value of val.

// # 3. Prim's Algorithm (Minimum Spanning Tree)
// (Video 96: Min Cost to Connect All Points)
// The Core Idea: Build a network by always adding the cheapest possible edge that connects a new node to your existing, growing network.
//   The goal is not the shortest path from a source, but the cheapest total cost to connect everyone.
// Analogy: Connecting Islands 🏝️
// You want to build bridges to connect all islands with the minimum amount of material. You start with one island. 
//   Then you look at all possible bridges to new islands and build the absolute cheapest one. Now you have a network of two islands. 
//   From your entire two-island network, you again find the absolute cheapest bridge to a new, unconnected island and build it. 
//   You repeat this until all islands are connected. You're always greedily expanding your network with the cheapest possible link.

class Solution {
private:
    int getMin(vector< int >& key,vector < bool >& nodesIncluded,int& n){
        int mini = INT_MAX;
        int minIndex = -1;
        for(int i = 0; i < n ; i++){
            if(!nodesIncluded[i] && key[i] < mini){
                mini = key[i];
                minIndex = i;
            }
        }
        return (minIndex == -1)? -1 : minIndex;
    }
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        // create adjacency list 
        int nodes = points.size();
        vector< vector < pair<int , int> > > adj(nodes);
        for(int i = 0 ; i < nodes - 1; i++){
                auto node1 = points[i];
            for(int j = i + 1 ; j < nodes ; j++){
                auto node2 = points[j];
                int dist = abs(node1[0] - node2[0]) + abs(node1[1] - node2[1]);
                adj[i].push_back({j,dist});
                adj[j].push_back({i,dist});
            }
        }

        // key array of number of nodes 
        vector< int > key(nodes, INT_MAX);
        vector < bool > nodesIncluded(nodes,false);
        vector< int > parent(nodes , -1);
        
        // Core Prims ALGO (Greedy Way)
        
        key[0] = 0;
        for(int c = 0; c < nodes ; c++){
            int u = getMin(key, nodesIncluded,nodes);
            if(u == -1) break;
            nodesIncluded[u] = true;
            // Traverse Adjacency List 
            int size = adj[u].size();
            for(int i = 0 ; i < size; i++){
                int v = adj[u][i].first;
                int w =  adj[u][i].second;

                if(!nodesIncluded[v] && w < key[v]){
                    key[v] = w;
                    parent[v] = u;
                }
            }
        }
        // total sum of key array!
         long long ans = 0;
        for (int i = 0; i < nodes; i++) {
            if (key[i] != INT_MAX) {
                ans += key[i];
            }
        }
        return ans; 

    }
};

// Optimization of using pq to get min elements
// just as prev Q use pq
