# PCB Network Optimization

This project models PCB components as a weighted graph and finds the Minimum Spanning Tree (MST) with the minimum total connection cost.

The project is implemented in C and uses graph algorithms such as BFS, DFS, Kruskal's algorithm, and Union-Find.

## Project Scope

- Graph representation
- Adjacency list
- Adjacency matrix
- BFS traversal
- DFS traversal
- Connected graph check
- Kruskal MST algorithm
- Union-Find data structure
- Cycle prevention
- Total MST cost calculation
- Basic graph visualization/output
- Dynamic node and edge updates

## Team Responsibilities

### feature/graph-core

This branch is responsible for the core graph structure.

Tasks:

- Define Graph, Node, and Edge structs
- Implement adjacency list
- Implement adjacency matrix
- Add node function
- Add edge function
- Store edge weights

### feature/bfs-dfs

This branch is responsible for graph traversal algorithms.

Tasks:

- Implement Queue structure for BFS
- Implement Stack structure or recursive logic for DFS
- Implement BFS algorithm
- Implement DFS algorithm
- Check whether the graph is connected

### feature/kruskal-unionfind

This branch is responsible for finding the Minimum Spanning Tree.

Tasks:

- Implement Union-Find data structure
- Implement Kruskal's algorithm
- Sort edges by weight
- Prevent cycles
- Calculate total MST cost

### feature/ui-visualization

This branch is responsible for displaying the graph and results.

Tasks:

- Print adjacency list
- Print adjacency matrix
- Display BFS and DFS results
- Display MST edges
- Display total MST cost
- Highlight MST result in output if possible

### feature/docs-integration

This branch is responsible for documentation and project integration.

Tasks:

- Update README.md
- Prepare sample test data
- Write integration notes
- Prepare report skeleton
- Check that all modules work together

## How to Compile

```bash
gcc main.c graph.c bfs_dfs.c kruskal.c -o pcb_network
