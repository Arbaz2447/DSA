# 📈 My Graph Algorithms Cheatsheet

A quick reference guide to the core concepts of graph algorithms. This repository contains notes and implementations for fundamental graph theory topics.

---

## 🧭 Graph Traversals (The Foundation)

> **DFS (Depth-First Search):** Explores as far as possible down one path before backtracking, like solving a maze.

> **BFS (Breadth-First Search):** Explores layer by layer, like the ripple effect in water; it's also used to find the shortest path in an unweighted graph.

---

## 👨‍👩‍👧‍👦 Disjoint Set Union (The Group Manager)

> **DSU (Disjoint Set Union):** A data structure to efficiently track which group an element belongs to and to merge groups.

---

## ⛓️ Topological Sort (The Order Maker for DAGs)

> **Topological Sort (using DFS):** A DFS-based approach that creates a linear ordering of nodes based on their finish times.

> **Kahn's Algorithm (using BFS):** A BFS-based approach that creates a topological sort by repeatedly finding nodes with no incoming edges.

---

## 🌳 Minimum Spanning Tree (The Cheapest Network)

> **Prim's Algorithm:** Grows a single tree by always adding the cheapest edge that connects a new vertex to the existing tree.

> **Kruskal's Algorithm:** Builds a "forest" by adding the cheapest edges from a sorted list, as long as they don't form a cycle (uses DSU).

---

## 🗺️ Shortest Path (The Fastest Route)

> **Dijkstra's Algorithm:** Finds the path with the minimum **total sum of weights** from a single source to all other nodes.

---

## 🔄 Cycle Detection (The Loop Finder)

> **Undirected Cycle Detection:** Uses DSU or DFS to check if an edge connects two nodes already in the same component.

> **Directed Cycle Detection:** Uses DFS to check if you encounter a node that is currently in the active recursion path.
