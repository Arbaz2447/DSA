// 785. Is Graph Bipartite?
// Github - 
// >**https://g.co/gemini/share/656b54684846**
class DSU{
    public:
    vector<int> parent;
    DSU(int n){
        parent.resize(n);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int findParent(int u){ // to which set they belong
        if(u == parent[u]) return u;

        return parent[u] = findParent(parent[u]);
    }
    void setUnion(int u1, int v1){ // merge parents
         int u = findParent(u1);
         int v = findParent(v1);
         if(u != v){
             parent[u] = v; 
        }
    }
};

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size(); 
        DSU dsu(2*n); 
        // 0 - n main nodes n - 2*n virtual nodes helps to build structure ! 
        // Main Doubt : even after having a cycle how can 0 - 1 - 2 - 3 - 0 is biparte ?
        // {0,2} , {1,3} i.e set a , b after partitioning they have connections from a to b but no edge in b/w
        // say 0 - 1 and 1 - 2
        // they form like 0 - 1~ - 2 (set a)   1 - 0~ - 2~ (set b)
        // if egde comes bw actual nodes like 0,2 we can detect !

        
        // and we can check weather 2 nodes are connected ! basically these virtual nodes act like cement
        // we take help of these to divide 
        // fills the holes in dsu structure which makes it stand ! in good condition!

        for(int i = 0; i < n; i++){
            for(auto& entry : graph[i]){
                int u = i;
                int v = entry;
                // lie in same set but edge lies between them
                if(dsu.findParent(u) ==  dsu.findParent(v)) return false;
                
                // thus they lie in different groups 
                dsu.setUnion(u, v + n);
                dsu.setUnion(v, u + n);
            }
        }
        return true;
    }
};
