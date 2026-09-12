# Matrix Chain Multiplication (MCM)

## Problem Statement

Consider the matrix chain multiplication problem. Write a program in C to implement the dynamic programming solution of the MCM problem to find the minimum number of scalar multiplications involved and the corresponding ordering to obtain the final result.

## File Structure

```
Question_7/
    ├── q7.c
    ├── a.out
    └── README.md
```

- `q7.c`: the C implementation of MCM with menu-driven input, DP computation, and recursive parenthesization printing.
- `a.out`: the compiled binary of the program..
- `README.md`: this documentation file.

## Detailed Explanation

### Input Representation

The input is an array $p[0..n]$ of $n+1$ integers representing the dimensions of $n$ matrices. Matrix $A_i$ (for $i = 1..n$) has dimensions $p[i-1] \times p[i]$. For example, if $p = \{10, 30, 5, 60\}$, then $A_1$ is $10 \times 30$, $A_2$ is $30 \times 5$, $A_3$ is $5 \times 60$.

### Why Order Matters

Multiplying an $(m \times n)$ matrix by an $(n \times p)$ matrix costs $m \cdot n \cdot p$ scalar multiplications. For the chain $A_1 A_2 A_3$ with $A_1: 10\times30$, $A_2: 30\times5$, $A_3: 5\times60$:

$$
((A_1 A_2) A_3): \quad 10\cdot30\cdot5 + 10\cdot5\cdot60 = 1500 + 3000 = 4500
$$

$$
(A_1 (A_2 A_3)): \quad 30\cdot5\cdot60 + 10\cdot30\cdot60 = 9000 + 18000 = 27000
$$

The first ordering is six times cheaper than the second.

### Dynamic Programming Optimal Substructure

The key insight is **optimal substructure**: in an optimal parenthesization of $A_i A_{i+1} \dots A_j$, the final split occurs at some $k$ with $i \le k < j$, and both sub-chains $A_i \dots A_k$ and $A_{k+1} \dots A_j$ must themselves be optimally parenthesized. Letting $m[i][j]$ be the minimum cost for $A_i \dots A_j$:

$$
m[i][j] = \begin{cases} 0 & i = j \\[2mm] \displaystyle \min_{i \le k < j} \Bigl[\, m[i][k] + m[k+1][j] + p[i-1]\, p[k]\, p[j] \,\Bigr] & i < j \end{cases}
$$

We also store the argmin split

$$
s[i][j] = \arg\min_{i \le k < j} \Bigl[\, m[i][k] + m[k+1][j] + p[i-1]\, p[k]\, p[j] \,\Bigr]
$$

so the parenthesization can be reconstructed.

### Two-Table Scheme

Two 2D arrays are maintained:

1. the **cost table** $m[i][j]$ — minimum scalar multiplications for the sub-chain $A_i..A_j$;
2. the **split table** $s[i][j]$ — the optimal split index $k$.

Diagonal entries $m[i][i] = 0$ (a single matrix costs nothing).

### Reconstruction of Optimal Order

Using $s$, the optimal parenthesization is printed recursively: if $i = j$ output $A_i$; otherwise output `(`, recurse on $(i, s[i][j])$ and $(s[i][j]+1, j)$, then `)`.

### Example Walkthrough: $p = \{40, 20, 30, 10, 30\}$

Four matrices: $A_1: 40\times20$, $A_2: 20\times30$, $A_3: 30\times10$, $A_4: 10\times30$.

Base costs:

$$
m[1][2] = 40\cdot20\cdot30 = 24000, \quad
m[2][3] = 20\cdot30\cdot10 = 6000, \quad
m[3][4] = 30\cdot10\cdot30 = 9000
$$

Length-3 chains:

$$
m[1][3] = \min\bigl( 0 + 6000 + 40\cdot20\cdot10,\; 24000 + 0 + 40\cdot30\cdot10 \bigr) = \min(14000, 36000) = 14000
$$

$$
m[2][4] = \min\bigl( 0 + 9000 + 20\cdot30\cdot30,\; 6000 + 0 + 20\cdot10\cdot30 \bigr) = \min(27000, 12000) = 12000
$$

Full chain:

$$
m[1][4] = \min_{\,k=1,2,3}\bigl( m[1][k] + m[k+1][4] + p[0]\,p[k]\,p[4] \bigr) = \min(36000,\, 69000,\, 50000) = 26000
$$

**Cost table $m$:**

| $i \backslash j$ | 1 | 2 | 3 | 4 |
|------------------|-----|------|------|------|
| 1 | 0 | 24000 | 14000 | **26000** |
| 2 | — | 0 | 6000 | 12000 |
| 3 | — | — | 0 | 9000 |
| 4 | — | — | — | 0 |

**Split table $s$:** $s[1][3] = 1$, $s[2][4] = 3$, $s[1][4] = 1$, so the optimal parenthesization is

$$
(A_1\,(A_2\,A_3))\,A_4 \quad \text{cost } 26000
$$

### Complexity

- **Time:** $O(n^3)$ — three nested loops over chain length, start index, and split point.
- **Space:** $O(n^2)$ — the $m$ and $s$ tables.

## Approaches

### Dynamic Programming (bottom-up)

Fill the cost table by increasing chain length $l = 2..n$. For each length, every start index $i$ gives $j = i + l - 1$, and every split $k \in [i, j-1]$ is tried, taking the minimum per the recurrence.

#### Implementation

```c
for (len = 2; len <= n; len++) {
    for (i = 1; i <= n - len + 1; i++) {
        j = i + len - 1;
        m[i][j] = LLONG_MAX;
        for (k = i; k < j; k++) {
            long long cost = m[i][k] + m[k+1][j] + (long long)p[i-1]*p[k]*p[j];
            if (cost < m[i][j]) {
                m[i][j] = cost;
                s[i][j] = k;
            }
        }
    }
}
```

### Reconstruction of Optimal Order

Using the split table, `printOrder(s, i, j)` prints the parenthesization: the base case $i = j$ prints $A_i$; otherwise it prints `(`, recurses on the left and right sub-chains, then `)`.

#### Implementation

```c
void printOrder(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOrder(s, i, s[i][j]);
        printf(" ");
        printOrder(s, s[i][j] + 1, j);
        printf(")");
    }
}
```

## Example Output

Manual run with $p = \{10, 30, 5, 60\}$:

```
Matrix Chain Multiplication
1. Random dimensions
2. Enter dimensions
Enter choice: Enter number of matrices (1-20): Enter 4 dimensions (p[0] p[1] ... p[3]): Number of matrices: 3
Dimensions: A1:10x30 A2:30x5 A3:5x60
Minimum scalar multiplications: 4500
Optimal parenthesization: ((A1 A2) A3)
```

The output matches the recurrence: $m[1][3] = \min_k \{ m[1][k] + m[k+1][3] + p[0]p[k]p[3] \} = 4500$ via the split $k = 1$, i.e. $((A_1 A_2) A_3)$.
