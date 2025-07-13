//Creating and Printing

//You are given an undirected graph of 'N' nodes and 'M' edges. Your task is to create the graph and print the adjacency list of the graph. I
//t is guaranteed that all the edges are unique, i.e., if there is an edge from 'X' to 'Y', then there is no edge present from 'Y' to 'X' and
//vice versa. Also, there are no self-loops present in the graph.
vector < vector < int >> printAdjacency(int n, int m, vector < vector <int >> & graph) {
    
    //get all Neighbours for every node.
    vector<int> arr[n];
    // basically size of graph
    for(int i = 0 ; i < m;i++){
        int u = graph[i][0];
        int v = graph[i][1];

        // push for undirected graph /
        arr[v].push_back(u);
        arr[u].push_back(v);
    }

    // make common neighbours in adjacency list
    vector<vector<int>> res(n);
    for(int i = 0; i < n; i++){

        res[i].push_back(i);

        for(int j = 0; j < arr[i].size();j++){
            res[i].push_back(arr[i][j]);
        }
    }

    return res;

}


// Graphs + backtracking 
// 797. All Paths From Source to Target
class Solution {
private:
    void solve(vector<vector<int>>& graph, vector< vector<int> >& ans,vector<int>& arr, int& target,int i){
        arr.push_back(i);
        // base case
        if(i == target){
            // the last path it should end here so push
            ans.push_back(arr);
        } else{
           for(int j = 0; j < graph[i].size(); j++){
                int next = graph[i][j];
                solve(graph,ans,arr,target,next);
           }
        }
        arr.pop_back();
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size() - 1;
        vector< vector<int> > ans;
        vector<int> arr;
        solve(graph,ans,arr,n,0);
        return ans;
    }
};
