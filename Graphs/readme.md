# 📈 My Graph Algorithms Cheatsheet

A quick reference guide to the core concepts of graph algorithms. This repository contains notes and implementations for fundamental graph theory topics.

---

## 🧭 Graph Traversals (The Foundation)

> **DFS (Depth-First Search):** Explores as far as possible down one path before backtracking, like solving a maze.

> **BFS (Breadth-First Search):** Explores layer by layer, like the ripple effect in water; it's also used to find the shortest path in an unweighted graph.

---

## 👨‍👩‍👧‍👦 Disjoint Set Union (The Group Manager)

> **DSU (Disjoint Set Union):** A data structure to efficiently track which group an element belongs to which component and to merge groups, detect cycles
> 

---

## ⛓️ Topological Sort (The Order Maker for DAGs)

> **Topological Sort (using DFS):** A DFS-based approach that creates a linear ordering of nodes based on their finish times.
> to reach node x all ndoes before x should be visited first , Detect cycle , shortest path bw a and b etc.

> **Kahn's Algorithm (using BFS):** A BFS-based approach that creates a topological sort by repeatedly finding nodes with no incoming edges.
> get incoming node data , do a bfs and reduce incoming edges , if zero store them (basically no one before me )

---

## 🌳 Minimum Spanning Tree (The Cheapest Network)

> **Prim's Algorithm:** Grows a single tree by always adding the cheapest edge that connects a new vertex to the existing tree.

> **Kruskal's Algorithm:** Builds a "forest" by adding the cheapest edges from a sorted list, as long as they don't form a cycle (uses DSU).
> we sort the edges based on weights and use dsu to connect components and it automatically prevents cycle stops when all nodes are added!
> Hint : when using kruskal algo you are bulding like shortest edge -> next shortes edge -> next shortest edge so till k whats max weight
> occured till now ? obviously the last !⭐ AND this automatically becomes the path with least difference bw adj edges cuz both the edges are least !

---

## 🗺️ Shortest Path (The Fastest Route)

> **Dijkstra's Algorithm:** Finds the path with the minimum **total sum of weights** from a single source to all other nodes.
> Neg weights wont work cuz it can be trapped in -ve cycle , optimal than bellman ford

> **Bellman Ford:** this algo finds the shortest path till i-th edge in i-th iteration
> say i need all pair shortest in data [1,2,3,4,5...] here start is say 3 and all are [inf,inf,0, inf,inf...]
>  so you start only when its 3 and updates only its edges only ! so thats shortest path till now for those edges so in 1st iteration
> edges at distance 1 has their lowest distance ! 

---

## 🔄 Cycle Detection (The Loop Finder)

> **Undirected Cycle Detection:** Uses DSU DSU helps detect a cycle by efficiently checking if the two nodes an edge connects are already in the same set. If they are, adding the new edge between them would form a cycle. or DFS to check if an edge connects two nodes already in the same component.

> **Directed Cycle Detection:** Uses DFS to check if you encounter a node that is currently in the active recursion path.

## 🔄 kosaraju Algo (SCC) strongly Connected components
> **Art of trapping dfs:** using toposort to get src and sink and cycles inside in stack and then just flip the edges in graph
> in stack -> src are on top , cycles and sink are bottom to it
> src on top becomes sink and get trapped , sink nodes becomes src and are not reachable via start of stack
> start of stack if we remove disconnected src nodes we first get root of graph which has paths and cycles and they get visited
> the nodes which were sink later became src are here trapped cuz everything else are visited !
> root node always comes on top becz its like post order traversal and non reachable nodes src nodes other than root are on top of root !
> after we process src nodes later became sink we have roots so that all cycles and paths accessable gets visited , sink nodes in prev context
> now became src so inaccessable in path and in next steps they are visited this trapped !
https://g.co/gemini/share/ba8e6cf1f3bd

## 🔄 Tarjan Algo Biconnected components (bridges , articulation points ) 

## Mislenious -> cycle detection in directed , undirected Graphs using BFS/DFS -> in problemset 1-4.
## Cycle detection DG via BFS , Fill the topological sort via kahns algo and check 
## shortest path in undirected graph (Unweighted) BFS is inbuilt to find shortest path inbuilt !

 
