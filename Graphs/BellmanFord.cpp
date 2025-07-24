//  Bellman-Ford is a single-source algorithm, just like Dijkstra's.
// which updates some of nodes making other nodes reachable and The Guarantee: After the k-th pass,
// the algorithm is guaranteed to have found the shortest path from the source to any other node that
// uses at most k edges. to be shortest why ? youve visited all possible 
// edges from any src so next nodes connected to src so you have shortest till k edges
// now use this to calc next nodes
// so v nodes has v - 1 times calculation (0-based)!

//here all the nodes are updated but we can gurentee that we have shortest dist till N1
// why ? how ? weve seeen every node that leads to 1 (0 - based) as of now we have 
// shortest till 1 (ist iteration ) n - 1th iteration we have shortest at n - 1th node

// dijakstra : picks a node updates dist to all its neighbours
// and ballmanford : takes a src node updates all reachable nodes
// and gurenntes that the nodes at kth iteration gureentes that nodes
// with k most edges has shortest path

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        int edges = flights.size();

        // not n - 1 cuz its not shortest edge its at most k stops 
        for(int j = 0; j <= k; j++){
            // start from where you left 
            vector<int> updationsAtKth = dist;


            for(int i = 0; i < edges; i++){
                int u = flights[i][0];
                int v = flights[i][1];
                int w = flights[i][2];
                // default value in map is 0 and here is int max !
                // you must compare with temp becz as long as you are limiting the stops its necessary 
                // for finding the shortest path till k stops !
                if((dist[u] != INT_MAX) && dist[u] + w < updationsAtKth[v]){
                    updationsAtKth[v] = dist[u] + w;
                }
            }
            // transfer the data back
            dist = updationsAtKth;
        }
        return (dist[dst] != INT_MAX)? dist[dst] : -1;
        
    }
};




// wrong but why its wrong !
// class Solution {
// public:
//     int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
//         vector<int> dist(n, INT_MAX);
//         dist[src] = 0;
//         int edges = flights.size();
//         // not n - 1 cuz its not shortest edge its at most k stops 
//         for(int i = 0; i <= k; i++){
//             unordered_map<int,int> updationsAtKth;
//             for(int i = 0; i < edges; i++){
//                 int u = flights[i][0];
//                 int v = flights[i][1];
//                 int w = flights[i][2];
//                     // so i think what i made wrong was  i should use updationsAtKth values till i exit the inner loop !
//                     //  and the map gives 0 by default , and it just gives yes or no to compare .find == .end so here
//                     //   vector should be used !
//                     // data updated in prev iteration should only be used !
//                 if((dist[u] != INT_MAX)){
//                     updationsAtKth[v] = min(dist[u] + w,updationsAtKth[v]);
//                 }
//             }
//             // transfer the data back
//             for(auto& [key, value] : updationsAtKth){
//                 dist[key] = min(dist[key], value); 
//             }
//         }
//         return (dist[dst] != INT_MAX)? dist[dst] : -1;
//     }
// };









