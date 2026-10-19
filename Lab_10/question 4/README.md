# Question 4: Reverse Time-Step DSU Application

A vertex-weighted undirected graph loses its vertices one at a time in the order $P=[p_1,\dots,p_V]$ (deleting a vertex removes its incident edges). After every deletion print the maximum vertex-value sum over the remaining connected components.

## File Structure

```
question 4/
├── question 4.c
├── a.out
└── readme.md
```

## Explanation

### Input representation
$V$, the vertex values $a[1..V]$ (non-negative), $E$, the edge list and the deletion order $P$ (a permutation of $1..V$). Here the whole graph is known in advance, so it is stored as an **adjacency list in compressed (CSR) form**: `start[]` and `adj[]` of total size $2E$. Option 2 generates 6-9 vertices, $V$ to $V+3$ edges and a random deletion order.

### Idea: process time backwards
DSU supports *merging* but not *splitting*. Deletions split components, so reverse time and treat them as **insertions**.

Let $res[i]$ be the answer after the first $i$ deletions. After all $V$ deletions nothing remains, so $res[V]=0$. Going from $i$ deletions to $i-1$ deletions means *adding back* vertex $p_i$. Therefore:

$$\text{for } i=V,V-1,\dots,2:\quad \text{activate } p_i,\ \text{union it with every active neighbour},\quad res[i-1]=\max_{\text{components}}\text{sum}$$

The set of active vertices after adding back $p_i,\dots,p_V$ is exactly the set of vertices remaining after $i-1$ deletions, and the DSU components on it are exactly the connected components of the remaining graph.

Since values are non-negative, adding a vertex and merging components can never reduce a component's sum, so a running maximum `cur` is correct: `cur = max(cur, sum[find(p_i)])`. (This is why the program rejects negative values.)

### Complexity
- Building the adjacency list: $\Theta(V+E)$.
- Each vertex is activated once and each edge is examined at most twice (once from each endpoint), with $O(\alpha(V))$ per union.
- Total time $O\bigl((V+E)\,\alpha(V)\bigr)$; space $\Theta(V+E)$.
- Recomputing components after every deletion would cost $\Theta(V(V+E))$.

## Compile and Run

```bash
gcc "question 4.c" -o a.out
./a.out
```

Every program shows a menu: **1** enter input manually, **2** generate random input, **0** exit.

## Sample Output

A manual run (option 1) followed by one random run (option 2), then exit. The random run is different every time the program is executed.

```
===== Reverse Time-Step DSU (Vertex Deletions) =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 1
Enter number of vertices V (1-1000000): 5
Enter the 5 vertex values (non-negative): 4 1 7 3 5
Enter number of edges E (0-1000000): 4
Enter 4 edges as 'u v' (vertices 1..5):
1 2
2 3
3 4
4 5
Enter the deletion order (a permutation of 1..5): 3 1 5 2 4

V = 5, E = 4
Vertex values: 4 1 7 3 5
Deletion order P: 3 1 5 2 4

After deleting p1 = 3: max component sum = 8
After deleting p2 = 1: max component sum = 8
After deleting p3 = 5: max component sum = 3
After deleting p4 = 2: max component sum = 3
After deleting p5 = 4: max component sum = 0

===== Reverse Time-Step DSU (Vertex Deletions) =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 2
Generated random input: V = 9, E = 9
Edges: (8,2) (3,6) (7,4) (1,3) (5,6) (2,1) (5,2) (9,2) (7,8)

V = 9, E = 9
Vertex values: 8 8 16 5 15 8 17 3 14
Deletion order P: 2 4 8 6 1 7 3 5 9

After deleting p1 = 2: max component sum = 47
After deleting p2 = 4: max component sum = 47
After deleting p3 = 8: max component sum = 47
After deleting p4 = 6: max component sum = 24
After deleting p5 = 1: max component sum = 17
After deleting p6 = 7: max component sum = 16
After deleting p7 = 3: max component sum = 15
After deleting p8 = 5: max component sum = 14
After deleting p9 = 9: max component sum = 0

===== Reverse Time-Step DSU (Vertex Deletions) =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 0
```
