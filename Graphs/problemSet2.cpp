//733. Flood Fill
//  BFS Logic
class Solution {
public:
private:
    void bfs(vector<vector<int>>& image, int a, int b, int x,
             unordered_map<int, unordered_set<int>>& visited, int n, int m) {
        using T = tuple<int, int, int>;
        queue<T> q;
        q.push({image[a][b], a, b});
        int target = image[a][b];

        while (!q.empty()) {
            auto getT = q.front();
            q.pop();

            int c = get<0>(getT);
            int i = get<1>(getT);
            int j = get<2>(getT);

            
            
            visited[i].insert(j);
            if (c == target) {
                image[i][j] = x;
                // 4 Possible directiions
                if (i + 1 < n &&
                    visited[i + 1].find(j) == visited[i + 1].end()) {
                    q.push({image[i+1][j], i + 1, j});
                }
                if (j + 1 < m && visited[i].find(j + 1) == visited[i].end()) {
                    q.push({image[i][j+1], i, j + 1});
                }
                if (i - 1 >= 0 &&
                    visited[i - 1].find(j) == visited[i - 1].end()) {
                    q.push({image[i-1][j], i - 1, j});
                }
                if (j - 1 >= 0 && visited[i].find(j - 1) == visited[i].end()) {
                    q.push({image[i][j - 1], i, j - 1});
                }
            }
        }
    }

public:
    // eaither you stop at the end of matrix or
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,int color) {
        unordered_map<int, unordered_set<int>> visited;
        int i = sr, j = sc;
        int n = image.size(), m = image[0].size();
        if (image[sr][sc] == color)
            return image;

        bfs(image, i, j, color, visited, n, m);
        return image;
    }
};
