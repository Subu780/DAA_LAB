# Question 1: Online Graph Bipartiteness Testing

Edges of an undirected graph on $V$ vertices arrive one by one. Add an edge if the graph stays bipartite; otherwise report that it violates bipartiteness and skip it.

## File Structure

```
question 1/
├── question 1.c
├── a.out
└── readme.md
```

## Explanation

### Input representation
Because edges arrive online, the graph is **never stored as an adjacency list or matrix**. The only state kept is a Disjoint Set Union (DSU) forest over the vertices $1..V$ with three arrays: `parent[]`, `size[]` and `par[]`. The input is read as $V$, the number of edges $m$ and then the stream of pairs $(u,v)$ (vertices numbered $1..V$). Option 2 of the menu generates a random graph with 5-10 vertices and 8-15 edges.

### Idea: DSU with parity
A graph is bipartite $\iff$ it is 2-colourable $\iff$ it has no odd cycle. For every vertex $x$ define $\pi(x)=\text{colour}(x)\oplus\text{colour}(\text{root}(x))$, the parity of the tree path from $x$ to its root. `par[x]` stores the parity from $x$ to `parent[x]`, and `find` returns the root together with $\pi(x)$ (XOR of `par` along the path, which path compression keeps correct).

For a new edge $(u,v)$, let $r_u,\pi_u$ and $r_v,\pi_v$ be the results of `find`:

| Case | Meaning | Action |
|---|---|---|
| $u=v$ | self-loop, an odd cycle of length 1 | reject |
| $r_u=r_v$ and $\pi_u=\pi_v$ | $u,v$ have the same colour, so the existing path between them has even length and the new edge closes an **odd cycle** | reject |
| $r_u=r_v$ and $\pi_u\ne\pi_v$ | the new edge closes an even cycle (or is a parallel edge) | accept, nothing changes |
| $r_u\ne r_v$ | two different components, no cycle is formed | accept, merge by size and set $par[r_{\text{small}}]=\pi_u\oplus\pi_v\oplus 1$ so that $u$ and $v$ get different colours |

**Why the cycle test is correct.** Within a component the accepted edges form a bipartite graph, so every $u$-$v$ path has the same parity, namely $\pi_u\oplus\pi_v$. Adding $(u,v)$ makes a cycle of length (path length) $+1$, which is odd exactly when the path length is even, i.e. when $\pi_u=\pi_v$. Rejected edges are skipped, so the accepted graph is bipartite at all times. For $V\le 30$ the program prints the final 2-colouring (side 0 and side 1).

### Complexity
With union by size and path compression each `find`/`union` costs amortised $O(\alpha(V))$, where $\alpha$ is the inverse Ackermann function ($\alpha(V)\le 4$ for any practical $V$).
- Time: $\Theta(V)$ for initialisation $+\ O(m\,\alpha(V))$ for the $m$ edges, i.e. $O(V+m\,\alpha(V))$.
- Space: $\Theta(V)$ for the DSU (the edge list is only held to replay the input; truly online use needs no edge storage).
- Without compression the union-by-size tree height is $O(\log V)$, giving a worst case of $O(m\log V)$ anyway.

## Compile and Run

```bash
gcc "question 1.c" -o a.out
./a.out
```

Every program shows a menu: **1** enter input manually, **2** generate random input, **0** exit.

## Sample Output

A manual run (option 1) followed by one random run (option 2), then exit. The random run is different every time the program is executed.

```
===== Online Bipartiteness Testing =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 1
Enter number of vertices V (1-1000000): 6
Enter number of edges m (0-1000000): 8
Enter 8 edges as 'u v' (vertices are 1..6):
1 2
2 3
3 1
3 4
4 5
5 6
6 1
2 5

V = 6, edges arriving online: 8

Edge   1: (1, 2) -> ACCEPTED (merged two components)
Edge   2: (2, 3) -> ACCEPTED (merged two components)
Edge   3: (3, 1) -> REJECTED (same colour: would close an odd cycle)
Edge   4: (3, 4) -> ACCEPTED (merged two components)
Edge   5: (4, 5) -> ACCEPTED (merged two components)
Edge   6: (5, 6) -> ACCEPTED (merged two components)
Edge   7: (6, 1) -> ACCEPTED (same component, colours differ: even cycle or parallel edge)
Edge   8: (2, 5) -> ACCEPTED (same component, colours differ: even cycle or parallel edge)

Accepted: 7   Rejected: 1   (graph stayed bipartite throughout)
A valid 2-colouring of the final graph:
  Side 0: 1 3 5
  Side 1: 2 4 6

===== Online Bipartiteness Testing =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 2
Generated random graph: V = 8, m = 11

V = 8, edges arriving online: 11

Edge   1: (2, 4) -> ACCEPTED (merged two components)
Edge   2: (7, 1) -> ACCEPTED (merged two components)
Edge   3: (7, 6) -> ACCEPTED (merged two components)
Edge   4: (4, 2) -> ACCEPTED (same component, colours differ: even cycle or parallel edge)
Edge   5: (6, 2) -> ACCEPTED (merged two components)
Edge   6: (4, 5) -> ACCEPTED (merged two components)
Edge   7: (3, 1) -> ACCEPTED (merged two components)
Edge   8: (1, 3) -> ACCEPTED (same component, colours differ: even cycle or parallel edge)
Edge   9: (8, 3) -> ACCEPTED (merged two components)
Edge  10: (4, 2) -> ACCEPTED (same component, colours differ: even cycle or parallel edge)
Edge  11: (6, 5) -> ACCEPTED (same component, colours differ: even cycle or parallel edge)

Accepted: 11   Rejected: 0   (graph stayed bipartite throughout)
A valid 2-colouring of the final graph:
  Side 0: 2 3 5 7
  Side 1: 1 4 6 8

===== Online Bipartiteness Testing =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 0
```
