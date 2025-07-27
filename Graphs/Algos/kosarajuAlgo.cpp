// Count Strongly Connected Components (Kosaraju’s Algorithm) code studio

// Initution -> you basically use topological sort why to get order of nodes
// like - sink nodes at bottom(incoming edges) and src nodes on top of stack 
// why - similar to post order and unreachable will be on their top 
// so you basically reverse the graph so that reachable is unreachable and vice versa
// the top of stack were src becomes sink i.e if we do dfs they are trapped !
// then the topological sort gives cycles nodes becz now the stack contains src at bottom end
// these cycles cant reach sink nodes cuz theve becomed src
// so when we go till bottom the all the nodes which were pure sink becms src nodes
// even the last nodes which were src due to all nodes visited with help of order in stack
// despite of having way its trapepd ! 

// frequently asked Queries verified from gemini 
// has source ssc on top for sure the cycleed nodes however you change 
// they form a cycle and they are combined a component but the trapped ones
//  are source ssc which become sink ssc (no path to go ) by stack we get order thats it nah

// so basically when you reverse the src becomes sink and due to no path outwards
//  they get trapped and coming to sink nodes becomes src they can go out but here 
//  topological sort ensures that the src nodes comes first (after change they become sink )
//   so the actual sink nodes taking incoming edges will have out going edges but they come
//    after the src node (which is now sink) and cycles are next in order despite the sink 
//    nodes after reversal becomes src becz due to topological sort every thing gets visited
//     so basically even after having the way you become trapped ! didnt i understood this 
//     algo 100% it feels so gud Alhamdulillah !

// ive got another Q how does this topological sort gives src on top ?
//  my reply : if we assume this graph just for sec assume as a tree basically
//   your like inorder traversal abstractly not exactly so root comes at last
//    even dough if we some how missed here ! then whatever the nodes comes into
//     stack in the end the unreachable nodes comes at top i.e the src nodes , 
//     if no src nodes then the root which is sc comes on top !

// so basically what i said is correct nah that post order kinda thing say in addtion
//  we have any unreachabel nodes even they appended to top nah in y/n!

#include<bits/stdc++.h>
void getTopoSort(stack<int>& s, vector<vector<int>>& adj, int i,vector<bool>& visited){
    visited[i] = true;

    for(auto& child : adj[i]){
        if(!visited[child]){
            getTopoSort(s, adj, child,visited);
        }
    }

    s.push(i);
}

void dfsMarkAll(vector<vector<int>>& rev, vector<bool>& visited, int n){
    visited[n] = true;
    for(auto& child : rev[n]){
        if(!visited[child]){
            dfsMarkAll(rev, visited, child);
        }
    }
}

int stronglyConnectedComponents(int v, vector<vector<int>> &edges){
	vector<vector<int> >adj(v);
    int edge = edges.size();
    for(int i = 0; i < edge; i++){
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
    }
    stack<int> s;
    vector<bool> visited(v,false);
    // get topological sort 
    for(int i = 0; i < v; i++){
        if(!visited[i]){
            getTopoSort(s, adj, i,visited);
        }
    }
    fill(visited.begin(),visited.end(), false);
    // reverse adj list v -> u 
    vector<vector<int>> rev(v);
    for(int i = 0; i < edge; i++){
        rev[edges[i][1]].push_back(edges[i][0]);
    }

    int cnt = 0;
    while(!s.empty()){
        int top = s.top();
        s.pop();

        if(!visited[top]){
            cnt++;
            dfsMarkAll(rev, visited, top);
        }
    }
    return cnt;
}

// 2360. Longest Cycle in a Graph
class Solution {
private:
void getTopoSort(stack<int>& s, vector<vector<int>>& adj, int i,vector<bool>& visited){
    visited[i] = true;

    for(auto& child : adj[i]){
        if(!visited[child]){
            getTopoSort(s, adj, child,visited);
        }
    }

    s.push(i);
}
// task is not to find cycle becz the structure is changed 

// int dfsMarkAll(vector<vector<int>>& rev, vector<bool>& visited, int n){
//     visited[n] = true;
//     int cnt = 0;
//     for(auto& child : rev[n]){
//         if(!visited[child]){
//             cnt = dfsMarkAll(rev, visited, child);
//             if(cnt > 0) return cnt + 1;
//         }else return 1;
//     }
//     return 0;
// }

// accha got it the cycles get saturated rightt ? after changing edges reverse the graph the cycles gets blocked
// so you just need to count nodes! because the structure is changed 

// take eg to better understand , 1 -> 2 , 2 -> 4, 4 -> 7 , 7 -> 5 , 5 -> 2 ! after reversing it changes ! 

int dfsMarkAll(vector<vector<int>>& rev, vector<bool>& visited, int n){
    visited[n] = true;
    int count = 1; // Count the current node
    for(auto& child : rev[n]){
        if(!visited[child]){
            count += dfsMarkAll(rev, visited, child);
        }
    }
    return count;
}
public:
    int longestCycle(vector<int>& edges) {
        int v = edges.size();
        vector<vector<int> >adj(v);

        int edge = edges.size();
        for(int i = 0; i < edge; i++){
            if(edges[i] != -1)
            adj[i].push_back(edges[i]);
        }

        stack<int> s;
        vector<bool> visited(v,false);
        // get topological sort 
        for(int i = 0; i < v; i++){
            if(!visited[i]){
                getTopoSort(s, adj, i,visited);
            }
        }
        fill(visited.begin(),visited.end(), false);
        // reverse adj list v -> u 
        vector<vector<int>> rev(v);
        for(int i = 0; i < edge; i++){
            if(edges[i] != -1)
            rev[edges[i]].push_back(i);
        }

        int maxi = 0;

        while(!s.empty()){
            int top = s.top();
            s.pop();

            if(!visited[top]){
                int cnt = dfsMarkAll(rev, visited, top);
                maxi = max(maxi, cnt);
            }
        }
        
        return (maxi < 2)? -1 : maxi;
    }
};
