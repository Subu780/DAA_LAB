# Question 9

## Hu-Tucker Greedy Simulation (optimal alphabetic tree)

Given weights $w_1,\dots,w_n$ in a fixed order, build a binary tree whose leaves appear **in that order** from left to right and which minimises $\sum_i w_i\cdot\text{depth}(i)$.

## Files folder structure

```
Question_9/
├── q9.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q9.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Algorithm (Hu-Tucker)
**Phase 1: combination.** Keep a sequence of nodes. Original leaves are *terminal*, merged nodes are not. Two nodes are **compatible** if there is no terminal node strictly between them.

Repeat $n-1$ times:
1. Among all compatible pairs $(i<j)$ choose the one with the smallest weight sum (ties: leftmost $i$, then leftmost $j$).
2. Replace the pair by one non-terminal node of that weight, placed at the position of the left node.

Unlike Huffman, the two smallest nodes may **not** be merged if a terminal node lies between them, because that would break the left-to-right order.

**Phase 2: reconstruction.** Phase 1 gives the correct leaf depths (levels) $\ell_1,\dots,\ell_n$, but the tree it built need not keep the order. Rebuild the ordered tree with a stack: push leaf $i$ with level $\ell_i$, and while the top two entries have equal level $L$, merge them into one entry of level $L-1$.

The optimal cost is

$$\sum_{i=1}^{n} w_i\,\ell_i \;=\; \text{sum of all merged weights in Phase 1}$$

### Validation
The classic interval DP gives the optimal alphabetic tree cost:

$$C[i][j]=\min_{i\le k<j}\bigl(C[i][k]+C[k+1][j]\bigr)+\sum_{t=i}^{j}w_t,\qquad C[i][i]=0$$

The program checks that this equals the Hu-Tucker cost, and also that the Phase 2 stack construction produced a valid tree. The program was additionally tested on thousands of random inputs, including heavy ties.

### Complexity
* This implementation scans all compatible pairs at each of the $n-1$ steps: $O(n^2)$ per step in the worst case and $O(n^3)$ overall for the naive scan. In practice the inner loop stops at the first terminal, so it is much faster. With a priority-queue implementation (Hu-Tucker / Knuth, Hu-Tucker's original bound) the problem is solved in $O(n\log n)$.
* Phase 2: $O(n)$ stack operations.
* The validation DP is $O(n^3)$ time, $O(n^2)$ space.

## Sample output

Mode 2 (auto-generate), `n = 8`, `seed = 3`.

Typed input:

```
2
8 3
```

Output:

```
Weights: 7 26 19 1 16 11 13 17
Leaf levels (phase 1): 3 3 2 4 4 3 3 3
Phase 2 tree (in-order 1..n): (((1 2) 3) (((4 5) 6) (7 8)))
Optimal cost sum(w_i*depth_i) = 328 (merge-sum = 328)
Interval-DP optimum           = 328 -> PASS
```
