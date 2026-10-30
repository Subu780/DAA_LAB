# Lab 11

Three programs in C, each with a menu: **1** enter the input manually, **2** generate a random input, **0** exit. Every question folder contains the source file, the compiled `a.out`, and a long `readme.md` with the problem analysis, proofs, complexity derivation, a worked example and real sample output.

## Questions at a glance

| # | Problem | Technique | Time | Details |
|---|---|---|---|---|
| 1 | Shortest paths when the cost depends on the parity of the weight-1 edges used | 0-1 BFS on a parity-doubled graph (deque) | $\Theta(V+E)$ | [question 1](question%201/readme.md) |
| 2 | Radius-constrained Voronoi partition of a graph around $K$ hubs | one multi-source BFS with owner labels and an index tie-break | $\Theta(V+E)$ | [question 2](question%202/readme.md) |
| 3 | Shortest word-ladder transformation, $N\le 10^5$, $L\le 10$ | bidirectional BFS over wildcard-pattern buckets | $O(NL\log(NL))$ | [question 3](question%203/readme.md) |

---

## Question 1: Parity-constrained shortest paths (0-1 BFS)

A directed graph has edge weights in $\lbrace 0,1\rbrace$. A path costs its weight $W(P)$ plus a penalty $C$ if it uses an **odd** number of weight-1 edges. The task is to find the minimum cost to every vertex.

- **Key observation.** Since weights are 0 or 1, the weight equals the number $k_1$ of weight-1 edges, so $\mathrm{Cost}=k_1+C\cdot[k_1\text{ odd}]$. This function is *not* monotone in $k_1$ (for example $f(1)=1+C$ can exceed $f(2)=2$), so one distance per vertex is not enough.
- **Approach.** Keep one distance **per parity**: run 0-1 BFS on the implicit doubled graph with states $(v,p)$. A weight-0 edge keeps the parity bit and goes to the **front** of the deque, a weight-1 edge flips it and goes to the **back**. Then $\mathrm{Cost}^{\ast}(v)=\min(a_v,\ b_v+C)$, where $a_v$ and $b_v$ are the best even and odd distances.
- **Input.** `V E S C` followed by `E` lines `u v w`; the graph is stored in CSR arrays and the doubled graph is never built.
- **Complexity.** $2V$ states and $2E$ transitions, each handled once: $\Theta(V+E)$ time and space, with no heap.

## Question 2: Voronoi cell partitioning (multi-source BFS)

Given $K$ hubs and a radius $R$, every vertex is assigned to its nearest hub (smallest hub **index** on ties), or to $-1$ when no hub is within distance $R$.

- **Approach.** Put all hubs in the queue at distance 0 and run a single BFS. The owner label travels with the wavefront; a vertex takes the smallest owner among its neighbours one level closer. Vertices at distance $R$ are not expanded, so the search stops early.
- **Proofs in the readme.** The BFS level equals $\min_i\operatorname{dist}(v,h_i)$; the owner satisfies a clean recursion over levels; and every cell is connected.
- **Input.** `V E`, the edges, `K`, the hub vertices, `R`.
- **Complexity.** $\Theta(V+E)$ instead of $\Theta(K(V+E))$ for $K$ separate searches. For $R$ small, only the neighbourhood of the hubs is touched.

## Question 3: Shortest word transformation (bidirectional BFS)

Find the minimum number of one-letter mutations turning $A$ into $B$, where every intermediate word must be in the dictionary $D$ (or $-1$).

- **Neighbour finding.** Two words are at Hamming distance 1 if and only if they share a **wildcard pattern** (`hot` has `*ot`, `h*t`, `ho*`). Words are filed into $L$ buckets each, using exact base-27 64-bit keys (no hash collisions), so the explicit graph is never built.
- **Search.** Bidirectional BFS expanding the smaller frontier, scanning every bucket at most once per direction. The first time the two searches touch the same word the path is provably shortest. A shortest sequence is printed as well.
- **Input.** `N`, the `N` words, `A`, `B`. $A$ need not be in $D$; $B$ must be.
- **Complexity.** $O(NL\log(NL))$, dominated by sorting the pattern index; the search itself is $O(NL)$. On a test dictionary of $10^5$ words, $L=10$, the two searches together labelled about $3\,300$ of $93\,483$ reachable words (distance 22), in $0.18$ s.

---

## Repository layout

```
Lab 11/
├── README.md              this file
├── question 1/
│   ├── question 1.c
│   ├── a.out
│   └── readme.md
├── question 2/
│   ├── question 2.c
│   ├── a.out
│   └── readme.md
└── question 3/
    ├── question 3.c
    ├── a.out
    └── readme.md
```

## Build and run

The folder names contain a space, so quote the paths:

```bash
cd "question 1"
gcc -O2 -Wall -Wextra "question 1.c" -o a.out
./a.out
```

The same works for `question 2` and `question 3`. The shipped `a.out` files are Linux x86-64 binaries; recompile on your own machine if one does not run.

## How the programs were verified

- Each program was compared with an independent brute-force implementation on hundreds of random inputs (500, 500 and 600 cases for questions 1, 2 and 3) with no mismatches.
- All programs were run under AddressSanitizer and UndefinedBehaviorSanitizer without any report.
- Large inputs were timed: $V=10^6$, $E=2\cdot 10^6$ (questions 1 and 2) and $N=10^5$, $L=10$ (question 3) each complete in about a second or less.

## Conventions used in all programs

- Vertices are numbered from 1.
- Invalid input is rejected with a message; the menu then continues.
- "Generate input" prints the random instance it produced, so the run can be reproduced by typing it into option 1.
