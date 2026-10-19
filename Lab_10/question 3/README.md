# Question 3: Maximum Weight Component with Size Constraints

Vertex $v$ has weight $w_v$ and edges are added one at a time. After every addition report the maximum total vertex weight over all connected components whose size is at most $K$.

## File Structure

```
question 3/
├── question 3.c
├── a.out
└── readme.md
```

## Explanation

### Input representation
The graph is given as the vertex-weight array $w[1..V]$, then the edge **stream** $(u,v,\text{edgeweight})$ and the threshold $K$. No adjacency structure is needed: the connectivity is kept in a DSU where each root stores `size[root]` and `W[root]` (the total vertex weight of its component). **Edge weights do not change the *vertex* weight total, so they are only echoed in the output.** Option 2 generates 6-9 vertices, 6-10 edges and $K\in[3,5]$.

### Idea
- Merging two components adds their sizes and weights: $\text{size}=s_1+s_2$ and $W=W_1+W_2$. An edge inside one component changes nothing.
- A component is **eligible** only while $\text{size}\le K$. Sizes never decrease, so once a component exceeds $K$ it stays ineligible forever (it still exists and can keep merging, it just never counts).
- The answer can *decrease* (an eligible component can merge into an ineligible one), so a running maximum is not enough. A **max-heap with lazy deletion** is used: whenever a component of size $\le K$ is created, push `(W, root)`. Before answering, pop the top while it is *stale*, that is while
$$\neg\Bigl(\text{parent}[r]=r\ \wedge\ W[r]=w_{\text{entry}}\ \wedge\ \text{size}[r]\le K\Bigr)$$
The first non-stale top is the answer (its weight and component size are printed). If the heap becomes empty, no component has size $\le K$ and the program prints `none`. Vertex weights may even be negative.

### Complexity
- Heap entries: $V$ initial singletons $+$ at most one per successful merge, so $\le V+E$ entries.
- Each entry is pushed once and popped at most once: $O(\log(V+E))$ each.
- DSU work: $O((V+E)\,\alpha(V))$.
- Total time $O\bigl((V+E)\log V\bigr)$ (the heap dominates); space $\Theta(V+E)$.

## Compile and Run

```bash
gcc "question 3.c" -o a.out
./a.out
```

Every program shows a menu: **1** enter input manually, **2** generate random input, **0** exit.

## Sample Output

A manual run (option 1) followed by one random run (option 2), then exit. The random run is different every time the program is executed.

```
===== Maximum Weight Component with Size Constraint =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 1
Enter number of vertices V (1-1000000): 6
Enter the 6 vertex weights: 5 3 8 2 7 4
Enter number of edges E (0-1000000): 5
Enter 5 edges as 'u v weight' (vertices 1..6):
1 2 1
3 4 2
2 3 3
5 6 1
4 5 4
Enter size threshold K (>= 1): 3

V = 6, E = 5, size limit K = 3
Vertex weights: 5 3 8 2 7 4

Initially:            max eligible weight = 8 (component size 1)
After edge   1 (1,2,w=1): max eligible weight = 8 (component size 1)
After edge   2 (3,4,w=2): max eligible weight = 10 (component size 2)
After edge   3 (2,3,w=3): max eligible weight = 7 (component size 1)
After edge   4 (5,6,w=1): max eligible weight = 11 (component size 2)
After edge   5 (4,5,w=4): max eligible weight = none (no component has size <= 3)

===== Maximum Weight Component with Size Constraint =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 2
Generated random input: V = 8, E = 9, K = 4

V = 8, E = 9, size limit K = 4
Vertex weights: 11 3 4 11 7 18 13 13

Initially:            max eligible weight = 18 (component size 1)
After edge   1 (4,6,w=6): max eligible weight = 29 (component size 2)
After edge   2 (4,3,w=2): max eligible weight = 33 (component size 3)
After edge   3 (3,8,w=2): max eligible weight = 46 (component size 4)
After edge   4 (6,3,w=7): max eligible weight = 46 (component size 4)
After edge   5 (5,1,w=8): max eligible weight = 46 (component size 4)
After edge   6 (7,8,w=8): max eligible weight = 18 (component size 2)
After edge   7 (3,1,w=1): max eligible weight = 3 (component size 1)
After edge   8 (7,4,w=2): max eligible weight = 3 (component size 1)
After edge   9 (1,7,w=6): max eligible weight = 3 (component size 1)

===== Maximum Weight Component with Size Constraint =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 0
```
