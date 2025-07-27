//684. Redundant Connection
// WHat it tells is -> process edges as its given and return the node which causes the cycle ! 
// Essense of DSU pure application of dsu !
class DSU{
    public:
        vector<int> parent;
        vector<int> rank;
        DSU(int n){
            parent.resize(n + 1);
            rank.resize(n + 1,0);
            for(int i = 1; i <= n; i++){
                parent[i] = i;
            }
        }

        int findParent(int u){
            if(parent[u] == u) return u;
            // do path compression
            return parent[u] = findParent(parent[u]);
        }
        bool unionSet(int u, int v){
            u = findParent(u);
            v = findParent(v);
            // do they belong to same set ?
            if(u != v){
                // merge them by changing their parent !
                if(rank[u] < rank[v]){
                    // u is smaller tree and v is larger tree
                    parent[u] = v;
                }else if(rank[v] < rank[u]){
                    parent[v] = u;
                }else{
                    parent[v] = u;
                    rank[u]++;
                }
                return false;
            }else return true;
        }
};


class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // process the nodes do they belong to same parent ? 
        // -> if yes by connecting them they form a cycle 
        // if no connect them 
        int maxNode = -1;
        for(auto& edge : edges){
            maxNode = max(maxNode, edge[0]);
            maxNode = max(maxNode, edge[1]);
        }
        DSU dsu(maxNode);
        for(auto& edge : edges){
            int elem1 = edge[0];
            int elem2 = edge[1];
            
            bool isCycle = dsu.unionSet(elem1,elem2);

            if(isCycle) return edge;
        }
        return {};
    }
};



class DSU{
    public:
        vector<int> parent;
        vector<int> rank;
        DSU(int n){
            parent.resize(n);
            rank.resize(n,0);
            for(int i = 0; i < n; i++){
                parent[i] = i;
            }
        }

        int findParent(int u){
            if(parent[u] == u) return u;
            // do path compression
            return parent[u] = findParent(parent[u]);
        }
        void unionSet(int u, int v){
                // merge them by changing their parent !
                if(rank[u] < rank[v]){
                    // u is smaller tree and v is larger tree
                    parent[u] = v;
                }else if(rank[v] < rank[u]){
                    parent[v] = u;
                }else{
                    parent[v] = u;
                    rank[u]++;
                }
        }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {

        int n = points.size();
        // take all edges
        vector< tuple < int , int , int > > edges;
        for(int i = 0; i < n; i++){
            auto point1 = points[i];
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                auto point2 = points[j];
                int edgeWeight = abs(point1[0] - point2[0]) + abs(point1[1] - point2[1]);
                edges.push_back({edgeWeight, i, j});
            }
        }
        sort(edges.begin(), edges.end());

        // use DSU to build the components
        DSU dsu(n);
        int totalWeight = 0;
        for(const auto& edge : edges){
            int u = get<1>(edge);
            int v = get<2>(edge);
            int w = get<0>(edge);

            int parent1 = dsu.findParent(u);
            int parent2 = dsu.findParent(v);

            if(parent1 != parent2){
                totalWeight += w;
                dsu.unionSet(parent1, parent2);
            }
        }
        
        return totalWeight;
    }
};

// just optimizations
/*
1. Reduce Duplicate Edges
Currently, your edge-creation loop creates an edge from point i to j, and also another identical edge from j to i. You can cut the number of edges you create and sort in half by only looking forward.
Your current code:
for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){ // Checks every other point
        if(i == j) continue;
        // ...
    }
}
A more efficient way
for(int i = 0; i < n; i++){
    for(int j = i + 1; j < n; j++){ // Only checks points after i
        // ...
    }
}
This change will significantly speed up the edge creation and sorting steps.

2. Early Exit
A Minimum Spanning Tree connecting n points will always have exactly n - 1 edges. Once you've added n - 1 edges to your tree, you know you're done and can stop processing the rest of the (more expensive) edges.
You can add a counter to track this:
int totalWeight = 0;
int edgesUsed = 0; // New counter
for(const auto& edge : edges){
    // ...
    if(parent1 != parent2){
        totalWeight += w;
        dsu.unionSet(parent1, parent2);
        edgesUsed++;
        if (edgesUsed == n - 1) { // Early exit condition
            break;
        }
    }
}
return totalWeight;
You've perfectly understood the reasoning for the second optimization, but let's clarify the first one.
## Optimization 1 (Creating Edges)
Your thinking, "connect with all upcoming edges," sounds more like the logic inside the Kruskal's loop where you're building the tree. This optimization is actually about the step before that, when we first create our big list of all possible connections.
The idea is simpler: the distance from Point A to Point B is the exact same as the distance from Point B to Point A.
Because the connection is mutual, we don't need to create two edges in our list representing the same connection. By using a loop like for j = i + 1, we ensure that for every pair of points, we only calculate the distance and add the edge to our list once. This makes our initial list half the size, which is much faster to create and sort.
*/

// 1192. Critical Connections in a Network Finding Bridge ! 

// How DFS is used to find bridges ! or biconnected components
// in simple terms they are independent && low value fk it we have to pass low to top ! any how not imp
//  but the main condition is this "discovered[node] < lowest[neig]"! and imp
class Solution {
public:
    void dfs(vector<vector<int>>& adj,vector<bool>& visited,vector<int>& discovered,vector<int>& lowest,int parent,int node , int timer , vector<vector<int>>& res){
        // ive visited 
        visited[node] =  true;
        discovered[node] = lowest[node] = timer++;
        for( auto& neig : adj[node]){
            // parent case
            if( neig == parent) continue;      
            if(!visited[neig]){
                dfs(adj,visited,discovered,lowest,node,neig,timer, res);
                /*
                    this is wrong blind else case !
                     if(lowest[node] > lowest[neig]){
                    // backedge is present
                    lowest[node] = min(lowest[neig], lowest[node]);
                    // backedge is present but bw child and next but its not gureented that 
                    // node <-> neig  is not gureented ! 
                    }else {
                        res.push_back({node, neig});
                    }
                */
                /*
                    why wrong :-
                    so what i said is correct nah ? in yes or no tell me """ 
                    the backedge gureentees a reverse cycle say x- y then y to x
                    is gureented to be cycle but not x <-> y this edge is gureented 
                    this will not effect in this context   but the next
                    nodes (prev contexts in rec calls )when we go back falsely assume there is a cycle but this edge
                    x <-> y can be skipped but its assumed to be safe " right ?
                    yes !
                */
                // also works
                if(lowest[node] > lowest[neig]){
                    lowest[node] = lowest[neig];
                }
                else if(discovered[node] < lowest[neig]){
                    res.push_back({node, neig});
                }

                //also works
                /*if(lowest[node] > lowest[neig]){
                    lowest[node] = min(lowest[neig], lowest[node]);
                    if(discovered[node] < lowest[neig]) {
                        res.push_back({node, neig});
                }*/

                
            }else{
                // back edge -> which simply says youre connected all around
                lowest[node] = min(lowest[neig], lowest[node]);
            }
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        if(n == 2) return connections;
        // to perform dfs so prepare adj list
        vector < vector < int > > adj(n);
        int edges = connections.size();
        for(int i = 0 ; i < edges; i++){
            int u = connections[i][0];
            int v = connections[i][1];
            
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector < bool > visited(n,false);
        // extra ds required to find backedge and the required Bridge
        vector < int > discovered(n);
        vector < int > lowestTime(n);
        vector < vector < int > > res;
        // perform dfs
        for(int i = 0; i < n; i++){
            if(!visited[i]){
                // should  track parent so that i can ignore the parent case !
                dfs(adj,visited, discovered,lowestTime,-1,i, 0, res);
            }
        }
        return res;
    }
};

// Articulation Point - I GFG 
class Solution {
  public:
    void dfs(vector<int> adj[], vector<bool>& visited, vector<int>& disc, vector<int>& low,int node,int parent, int& timer,vector<int>& res){
        visited[node] = true;
        low[node] = disc[node] = timer;
        timer++;
        
        for(auto& neigh : adj[node]){
            if(neigh == parent) continue;
            
            if(!visited[neigh]){
                dfs(adj,visited,disc, low, neigh, node, timer, res);
                // back track and mark all in cycle
                low[node] = min(low[node], disc[neigh]);
                
                // check for articulation point if say my child has > lower time than my disc then 
                // there is no other way for my child other than me
                // if its equal to that means they are in a cycle saturated without any other connection
                // except this 
                
                // could be simplified but more sound !
                if(disc[node] < low[neigh] && parent != -1) res.push_back(node);
                else if(disc[node] == low[neigh] && parent != -1)  res.push_back(node);
                
                
                
            }else{
                // backedge found
                low[node] = min(low[node], disc[neigh]);
            }
            
        }
    }
    vector<int> articulationPoints(int V, vector<int> adj[]) {
       vector<int> disc(V);
       vector<int> low(V);
       vector<int> res;
       vector<bool> visited(V,false);
       int timer = 0;
       
       // dfs for all nodes components have -1 as parent
       for(int i = 0; i < V; i++){
           if(!visited[i]){
               dfs(adj,visited,disc,low,i, -1,timer,res);
           }
       }
       if(res.size() == 0) return {-1};
       sort(res.begin() , res.end());
       return res;
    }
};
