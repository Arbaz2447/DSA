// 721. Accounts Merge

// Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
// Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
//  Approach 1 DFS 
class Solution {
private:
    // like preorder traversal 
    void dfs(unordered_map < string , vector < string > >& adj,unordered_set < string >& visited
            ,string email,vector<string>& container){
        visited.insert(email);
        container.push_back(email);

        for(auto& n : adj[email]){
            if(visited.find(n) == visited.end()){
                dfs(adj,visited,n,container);
            }
        }
    }
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map < string , string > emailToName;
        unordered_map < string , vector < string > > adj;
        // create adj list and emailtoName
        for(auto& ac : accounts){
            string name = ac[0];
            string uEmail = ac[1];
            emailToName[uEmail] = name;
            for(int i = 2; i < ac.size(); i++){
                string vEmail = ac[i];
                adj[uEmail].push_back(vEmail);
                adj[vEmail].push_back(uEmail);
                emailToName[vEmail] = name;
            }
            if(ac.size() == 2) adj[uEmail];
        }


        
        // traverse adj list and perform traversal
        vector<vector<string>> res;
        unordered_set < string > visited;

        for(auto& [email , neighbors] : adj){
            
            if(visited.find(email) == visited.end()){
                
                vector<string> container;
                dfs(adj,visited, email,container);
                
                sort(container.begin(),container.end());
                container.insert(container.begin(), emailToName[container[0]]);
                res.push_back(container);
            }
        }
        return res;
    }
};

// Approach 2
class DSU{
    public:
    // why dsu here -> managing connected components of a graph 
    vector<int> parent;
    vector<int> rank;
    DSU(int n){
        parent.resize(n);
        rank.resize(n,0);
        for(int i = 0; i < n ; i++) parent[i] = i; // everyone is their parent at start
    }
    int findParent(int n){
        if(parent[n] == n) return n;
        // path compression so that the next time it uses its rapidly fast !
        return parent[n] = findParent(parent[n]);
    }
    void setUnion(int u, int v){
        u = findParent(u);
        v = findParent(v);
        if(u != v){ // belongs to diff parents combine them to 1 & compare by ranks to maintain height
            if(rank[u] < rank[v]){
                parent[u] = v;
            }else if(rank[u] > rank[v]){
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
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int uniqueId = 0;
        unordered_map < string , int > emailToId;
        unordered_map < string , string > emailToUser;
        // Step 1:
        // assume emails as nodes and assign them an id
        // also handle which email belongs to which userName
        for(const auto& arr : accounts){
            string userName = arr[0];

            for(int i = 1 ; i < arr.size();i++){
                // Part 1 : if unique number not assingd assign them
                string email = arr[i];
                if(emailToId.find(email) == emailToId.end()){
                    emailToId[email] = uniqueId++;
                }
                // Part 2 : We need to track what all emails belong to which user !
                emailToUser[email] = userName;
            }
        }

        // Step 2 :
        // Make Connections between all nodes 
        DSU dsu(uniqueId);
       
        for(const auto& rec : accounts){
            string email = rec[1]; 
            // All of them should have a Link
            for(int i = 2; i < rec.size(); i++){
                string email2 = rec[i];
                dsu.setUnion(emailToId[email], emailToId[email2]);
            }
        }
        //Step 3:
        // Group them based on the parent and we need to deal with the groups later 
        // traversing accounts is not gud because it has duplicate emails
        // and if we traverse all entries in emailToId we can classify all of them with ease!
        unordered_map < int , vector < string > > components;
        for(const auto& [email, id] : emailToId){
            int parent = dsu.findParent(id);
            components[parent].push_back(email);
            
        }
        // step 4 
        // classify the output
        vector<vector<string>> res;
        for(auto& [num , arr] : components){
            sort(arr.begin(), arr.end());
            arr.insert(arr.begin(), emailToUser[arr[0]]);
            res.push_back(arr);
        }
        return res;
    }
};

// 433. Minimum Genetic Mutation
// Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
// Output: 1
// Example 2:

// Input: startGene = "AACCGGTT", endGene = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
// Output: 2
// whole startstr is one node and its neighbours are the nodes diff in 1 letter 
class Solution {
private:
    int getDiff(string s1, string s2){
        int i = 0, j = 0 , diff = 0;
        while(i < s1.size() && j < s2.size()){
            if(s1[i++] != s2[j++]) diff++;
        }
        return diff;
    }
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        queue < tuple<int, string >  > q;
        unordered_set < string > visited;
        // cnt and start string 
        q.push({0,startGene});
        visited.insert(startGene);
        while(!q.empty()){
            auto top = q.front(); q.pop();
            int cnt = get<0>(top);
            string str = get<1>(top);

            if(str == endGene) return cnt;

            for(auto& neigh : bank){
                if(visited.find(neigh) == visited.end() && getDiff(neigh, str) == 1){
                    visited.insert(neigh);
                    q.push({cnt + 1,neigh});
                }
            }
            
        }
        return -1;
    }
};

