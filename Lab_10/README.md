# Lab 10

Design and Analysis of Algorithms: graphs, Disjoint Set Union (Union-Find) and connected components.

Every program is written in C and has the same menu: **1** enter input manually, **2** generate random input, **0** exit. Compile with `gcc "question N.c" -o a.out` (quote the name, it contains a space).

Notation: $\alpha$ is the inverse Ackermann function (at most 4 for any practical input size).

---

## Question 1: Online Graph Bipartiteness Testing

Edges arrive one at a time. An edge is added only if the graph stays bipartite; otherwise it is reported and skipped.

- **Approach:** DSU that also stores the colour parity of each vertex relative to its root. An edge whose two ends are in the same component with the same colour closes an odd cycle and is rejected. Edges between different components are merged with the parity adjusted.
- **Input:** $V$, the number of edges $m$, then the edge stream (vertices 1 to $V$). No adjacency list is stored.
- **Complexity:** $O(V + m\,\alpha(V))$ time, $\Theta(V)$ space.

## Question 2: Dynamic Connected Components in a Grid

An $R \times C$ grid starts as water. Land cells are added one by one and the number of 4-connected islands is printed after each addition.

- **Approach:** each cell is flattened to the index $r \cdot C + c$. A new land cell adds 1 island, and each union with a land neighbour that really merges two islands subtracts 1.
- **Input:** $R$, $C$, the number of additions $k$, then the positions (rows and columns from 0). Duplicates and out-of-grid positions are ignored.
- **Complexity:** $O(RC + k\,\alpha(RC))$ time, $\Theta(RC)$ space.

## Question 3: Maximum Weight Component with Size Constraints

Vertices have weights and edges are added in sequence. After each edge, report the largest total vertex weight among components of size at most $K$.

- **Approach:** DSU storing each component's size and total weight, plus a max-heap with lazy deletion. Components larger than $K$ stay ineligible forever, and outdated heap entries are discarded when they reach the top. A running maximum would not work because the answer can decrease.
- **Input:** $V$, the vertex weights, $E$, the edges as `u v weight`, then $K$. Edge weights are echoed but do not affect the answer, since only vertex weights are summed.
- **Complexity:** $O((V+E)\log V)$ time, $\Theta(V+E)$ space.

## Question 4: Reverse Time-Step DSU Application

Vertices are deleted in a given order. After each deletion, report the maximum vertex-value sum over the remaining connected components.

- **Approach:** DSU cannot split components, so time is reversed and the deletions become insertions. Vertices are added back from last to first, each is united with its active neighbours, and a running maximum of component sums gives the answers.
- **Input:** $V$, the non-negative vertex values, $E$, the edges, then the deletion order (a permutation of 1 to $V$). The graph is stored as a compact adjacency list.
- **Complexity:** $O((V+E)\,\alpha(V))$ time, $\Theta(V+E)$ space.

## Question 5: Lexicographically Smallest Connected Component Permutation

Given a permutation of $1..n$ and a list of allowed swaps, find the lexicographically smallest permutation reachable.

- **Approach:** positions joined by swaps form components, and any arrangement inside a component is reachable. So each component gets its own values in increasing order at its own positions in increasing order. Because the input is a permutation, scanning the values $1..n$ in order produces the sorted assignment without any sorting.
- **Input:** $n$, the permutation, the number of swaps $m$, then the swap pairs (positions 1 to $n$).
- **Complexity:** $O((n+m)\,\alpha(n))$ time, $\Theta(n+m)$ space.

---

## Summary

| Q | Technique | Time |
|---|---|---|
| 1 | DSU with parity | $O(V + m\,\alpha)$ |
| 2 | DSU with coordinate flattening | $O(RC + k\,\alpha)$ |
| 3 | DSU with size and weight, plus lazy max-heap | $O((V+E)\log V)$ |
| 4 | Reverse-time DSU | $O((V+E)\,\alpha)$ |
| 5 | DSU, then per-component sorted assignment | $O((n+m)\,\alpha)$ |
