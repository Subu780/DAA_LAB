# Coin Triangle Inversion Problem

## Problem Statement

Consider an equilateral triangle formed by closely packed pennies or other identical coins. The centers of the coins are assumed to be at the points of the equilateral triangular lattice. Design an algorithm to flip the triangle upside down in the minimum number of moves if on each move you can slide one coin at a time to its new position. Give a compact formula for the number of minimum moves.

In other words, we have an equilateral triangle built from identical coins where every coin sits exactly at a lattice point of the triangular lattice and touches its neighbours. We may pick up exactly one coin per move and slide it to some empty lattice point that keeps the coins "closely packed". The goal is to reach the upside-down (inverted) configuration of the same triangle in the fewest possible moves.

## File Structure

```
Question_1/
    ├── q1.c
    ├── a.out
    └── README.md
```

- `q1.c`: The C program implementing the formula-based and dynamic-programming approaches.
- `a.out`: The compiled executable of the C program.
- `README.md`: This documentation file.

## Detailed Explanation

### Understanding the Problem

Before writing any algorithm we must be absolutely clear about what the problem is asking.

- An equilateral triangle of side length $n$ has $n$ rows.
- By convention, the triangle of size $n$ has rows $1, 2, \dots, n$ and row $i$ contains $i$ coins.
- "The centres of the coins are at the points of the equilateral triangular lattice" simply means the coins form a perfectly packed regular arrangement. When we slide a coin we may only place it at a valid lattice position so that the final arrangement is again a perfectly packed triangle, pointing in the opposite direction.
- "Flip the triangle upside down" means the final configuration is the mirror image of the original one. The size $n$ never changes, so the **total number of coins never changes**.
- On each move we slide exactly one coin. Sliding far or short makes no difference; each relocation costs exactly one move.

### The Number of Coins in a Triangle

Let $T(n)$ be the total number of coins needed to build a triangle of size $n$. Since row $i$ has $i$ coins:

$$
T(n) = 1 + 2 + \cdots + n = \sum_{i=1}^{n} i
$$

This is the famous sum of the first $n$ natural numbers, with the closed form

$$
T(n) = \frac{n(n+1)}{2}
$$

These numbers are called **triangular numbers**. A small table makes this concrete:

| $n$ | Rows of coins | $T(n)$ |
|-----|---------------|--------|
| 1 | $1$ | $1$ |
| 2 | $1 + 2$ | $3$ |
| 3 | $1 + 2 + 3$ | $6$ |
| 4 | $1 + 2 + 3 + 4$ | $10$ |
| 5 | $1 + 2 + 3 + 4 + 5$ | $15$ |
| 6 | $\sum_{i=1}^{6} i$ | $21$ |

The formula $T(n) = \dfrac{n(n+1)}{2}$ is the "compact formula" the problem asks for.

### Why the Number of Moves Equals the Number of Coins

Superimpose the original triangle and the final inverted triangle. A coin that already occupies a lattice position present in *both* configurations need not move. A coin on a position present only in the original configuration **must** move, because the final configuration requires that position to be empty and the coin must re-appear elsewhere.

Every coin that must move is moved exactly once, and one move relocates exactly one coin. Hence:

$$
\text{minimum number of moves} = \text{number of coins that must be relocated}
$$

Since the inverted triangle is congruent to the original one, it contains exactly $T(n)$ positions. Taking the mirrored relocation view, every coin slides to its mirrored lattice location, so the number of coins that must move is exactly the total number of coins. Therefore the minimum number of moves is

$$
M(n) = T(n) = \frac{n(n+1)}{2}
$$

### Formula-Based Approach

The formula-based method is the direct application of the closed form:

$$
M(n) = \frac{n(n+1)}{2}
$$

Why is this the answer in our model?

1. The triangle needs $T(n) = \sum_{i=1}^{n} i = \dfrac{n(n+1)}{2}$ coins.
2. Every coin is relocated exactly once during the inversion.
3. Therefore $M(n) = T(n)$.

No loop over rows is required; the answer is a constant number of arithmetic operations for any $n$.

### Dynamic Programming Approach

Dynamic programming exploits **optimal substructure**: the optimal solution of a larger problem is built from the optimal solutions of smaller problems.

- A triangle of size $0$ contains no coins and needs $0$ moves.
- A triangle of size $i$ is a triangle of size $i-1$ with one extra row of exactly $i$ coins glued to its base.

If inverting a triangle of size $i-1$ costs $M(i-1)$, the bigger triangle adds $i$ coins and hence $i$ moves:

$$
M(i) = M(i-1) + i, \qquad M(0) = 0
$$

Let $dp[i]$ be the minimum number of moves to invert a triangle of side $i$.

$$
dp[i] = \begin{cases} 0 & i = 0 \\[2mm] dp[i-1] + i & i \geq 1 \end{cases}
$$

The recurrence is valid because the $i$-th row adds exactly $i$ new coins and each coin accounts for exactly one slide. Expanding the recurrence:

$$
dp[0] = 0,\;\; dp[1] = 1,\;\; dp[2] = 3,\;\; dp[3] = 6,\;\; dp[4] = 10,\;\; dp[5] = 15
$$

| $i$ | $dp[i]$ |
|-----|---------|
| 0 | $0$ |
| 1 | $1$ |
| 2 | $3$ |
| 3 | $6$ |
| 4 | $10$ |
| 5 | $15$ |

The final answer is $dp[n]$.

### Complexity Analysis

**Formula approach:** $O(1)$ time and $O(1)$ space — a constant number of integer operations, no loop, no array.

**Dynamic programming approach:** $O(n)$ time (a table of $n+1$ entries, one addition each) and $O(n)$ space. It transparently exposes the recurrence and can be extended to harder variants.

Because $T(n) = \frac{n(n+1)}{2}$ is itself the closed form of the recurrence, both approaches always agree, which is exactly what the program validates.

## Approaches

### Formula-Based Approach

```c
int calculateMinimumMovesFormula(int size) {
    return (size * (size + 1)) / 2;
}
```

This evaluates $M(n) = \dfrac{n(n+1)}{2}$ directly in constant time.

### Dynamic Programming Approach

```c
int calculateMinimumMovesDP(int size) {
    int dp[size + 1];
    dp[0] = 0;
    for (int i = 1; i <= size; i++) {
        dp[i] = dp[i - 1] + i;
    }
    return dp[size];
}
```

This fills $dp$ using the recurrence $dp[i] = dp[i-1] + i$ and returns $dp[size]$.

## Example Output

```
Choose an option:
1. Random size
2. Input size
Enter your choice (1 or 2): 1
Generated random size: 5
Minimum number of moves to invert the coin triangle (using formula): 15
Minimum number of moves to invert the coin triangle (using dynamic programming): 15
```

Both approaches agree, validating the recurrence against the closed form.
