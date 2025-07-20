// code studio
// Minimum Spanning Tree

#include<algorithm>
bool cmp(vector<int>& a, vector<int>&b){
  return a[2] < b[2];
}

void makeSet(vector<int>& parent,vector<int>& rank,int& n){
    for(int i = 0; i < n; i++){
      // they themselves are the parents
      parent[i] = i;
    }
}

int findParent(vector<int>& parent, int node){
  if(parent[node] == node) return node;

  parent[node] = findParent(parent,parent[node]);
  return parent[node];
}

void unionSet(int u , int v ,vector<int>& parent,vector<int>& rank,int n){
  int pOu = findParent(parent,u);
  int pOv = findParent(parent,v);

    if(pOu != pOv){
        if(rank[pOv] > rank[pOu]){
          parent[pOu] = pOv;
        }else if(rank[pOv] < rank[pOu]){
          parent[pOv] = pOu;
        }else{
          parent[pOv] = pOu;
          rank[pOu]++;
        }
    }
}

int minimumSpanningTree(vector<vector<int>>& edges, int n){
  vector<int> parent(n,-1);
  vector<int> rank(n,0);
  // assuming n nodes and they themselves are parent.
  makeSet(parent,rank,n);
  int t = 0;
  sort(edges.begin(),edges.end(),cmp);

  for(int i = 0; i < edges.size() ; i++){
    int u = findParent(parent,edges[i][0]);
    int v = findParent(parent,edges[i][1]);
    int w = edges[i][2];

    if(u != v){
      // if not included then include.(weight)
      t += w;
      unionSet(u,v,parent,rank,n);
    }
    // as soon as all the components are included with the minimum edges then exit !
  }
  return t;
}
// 547. Number of Provinces
// pure DSU ds application 
// step 1 : you assume every node as sepreate component and parent node is node itself
// step 2 : you take weights , the edges in small to inc order until every node is connected
// rank is used to maintain the height like smaller tree is merged with larger not vice versa so 
// path compression in find parent is very optimal cuz we need the root to compare so !


class Solution {
private:
    void init(vector<int> &parent, vector<int>& rank, int&n){
        for(int i = 0; i < n; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }
    int findParent(int u,vector<int>& parent){
        // the root node
        if(u == parent[u]) return u;
        // compression or flatten all the intermediate nodes to root
        parent[u] = findParent(parent[u],parent);
        return parent[u];
    }

    void unionSet(int u, int v ,vector<int>& rank,vector<int>& parent,int& n){
        if(rank[u] > rank[v]){
            parent[v] = u;
        }else if(rank[u] < rank[v]){
            parent[u] = v;
        }else{
            parent[u] = v;
            rank[v]++;
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int> parent(n);
        vector<int> rank(n);
        init(parent,rank,n);

        for(int i = 0; i < n;i++){
            for(int j = 0; j < n;j++){
                if(i != j && isConnected[i][j] == 1){
                    int parentOfu = findParent(i,parent);
                    int parentOfv = findParent(j,parent);

                    // Ignore if same compontent
                    if(parentOfu != parentOfv){
                        unionSet(parentOfu, parentOfv , rank,parent, n);
                    }
                }
            }
        }
        // traverse the parent array and find no of roots
        int t = 0;
        for(int i = 0; i < n;i++){
            if(parent[i] == i){
                t++;
            }
        }
        return t;
    }
};

// 1631. Path With Minimum Effort
// you compute all edges and store in vector
// sort them apply kruskal algo so that 
// you start making route from start to end while the cost is increasing from this path to next path
// so the maximum effort cost is the -> recent cost which occured when
//  start and end are included in one component

class DSU{
    public:
    vector<int> parent;
    vector<int> rank;
    DSU(int n){
        parent.resize(n);
        rank.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }
    int findParent(int n){
        if(n == parent[n]) return n;

        return parent[n] = findParent(parent[n]);
    }
    void unionSet(int u , int v){
        u = findParent(u);
        v = findParent(v);
        if(u != v){
            if(rank[u] < rank[v]){
            parent[u] = v;
            }else if(rank[v] < rank[u]){
                parent[v] = u;
            }else{
                parent[v] = u;
                rank[u]++;
            }
        }
    }
};

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();

        if(rows == 1 && cols == 1) return 0;

        using T = tuple < int , int , int >;
        vector< T > edges;

        for(int i = 0; i < rows ; i++){
            for(int j = 0; j < cols ; j++){
                // for each node assign a unique value;
                int currNode = (i * cols) + j;

                // go next right
                if(i + 1 < rows){
                    int nextNode = (i + 1) * cols + j;  
                    int weight = abs(heights[i][j] - heights[i+1][j]);
                    edges.push_back({weight, currNode,nextNode});
                }
                if(j + 1 < cols){
                    int nextNode = i * cols + (j + 1);  
                    int weight = abs(heights[i][j] - heights[i][j+1]);
                    edges.push_back({weight, currNode,nextNode});
                }
            }
        }
        // to select minimum edges first.
        sort(edges.begin(),edges.end());
        int size = edges.size();
        
        int startNode = 0;
        int endNode = rows * cols - 1;
        // DSU LOGIC Till both start and end are connected into ans.
        DSU dsu(rows * cols);
        for(auto& edge : edges){
            // edge is tuple
            int u = get<1>(edge);
            int v = get<2>(edge);
            int w = get<0>(edge);
            
            dsu.unionSet(u,v);
            

            // start node and end node has same parent ?
            if(dsu.findParent(startNode) == dsu.findParent(endNode)){
                return w;
            }
        }
        return 0;
    }
};

