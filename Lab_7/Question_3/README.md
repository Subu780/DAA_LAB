# Reve's Puzzle (Tower of Hanoi with Four Pegs)

## Problem Statement

There are eight disks of different sizes and four pegs. Initially, all the disks are on the first peg in order of size, the largest on the bottom and the smallest on the top. The objective is to transfer all the disks to another peg by a sequence of moves. Only one disk can be moved at a time, and it is forbidden to place a larger disk on top of a smaller one. Devise an algorithm that solves the puzzle in 33 moves. Generalize your algorithm for an $n$-disk problem. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## File Structure

```
Question_3/
    ├── q3.c
    ├── a.out
    └── README.md
```

- `q3.c`: C source implementing the Frame-Stewart DP and recursive move generator.
- `a.out`: the compiled binary of the program..
- `README.md`: this documentation file.

## Detailed Explanation

### The Classic Three-Peg Tower of Hanoi

The original Tower of Hanoi uses three pegs and $n$ disks. To move $n$ disks from a source peg to a destination peg using a helper peg:

1. move the top $n-1$ disks from source to helper (using destination as spare),
2. move the largest disk from source to destination,
3. move the $n-1$ disks from helper onto destination (using source as spare).

This gives the recurrence

$$
T(n) = 2\,T(n-1) + 1, \qquad T(1) = 1
$$

whose closed form is

$$
T(n) = 2^{n} - 1
$$

For 8 disks the three-peg solution requires $2^8 - 1 = 255$ moves.

### How the Fourth Peg Helps

Adding a fourth peg provides extra "parking" space for intermediate stacks. Instead of one helper peg we may temporarily distribute disks across two auxiliary pegs, which lets the largest disks move fewer times. The rules are unchanged; only the available peg space grows.

### The Frame-Stewart Algorithm

The Frame-Stewart algorithm for four pegs (conjectured optimal, not proven in general) works as follows. To move $n$ disks from source to destination using all four pegs:

1. Choose an integer $k$ with $0 \le k < n$. Move the $k$ **smallest** disks from source to a spare peg, using all four pegs recursively.
2. Move the remaining $n-k$ **largest** disks from source to destination using classic three-peg Hanoi (these disks are never placed on smaller ones, since the $k$ small disks are safely out of the way).
3. Move the $k$ small disks from the spare peg onto the destination, using all four pegs recursively.

### The Recurrence

Let $T(n)$ be the minimum number of moves for $n$ disks on four pegs. The Frame-Stewart strategy costs:

$$
T(n) = \min_{0 \le k < n} \Bigl[\, 2\,T(k) + \bigl(2^{\,n-k} - 1\bigr) \Bigr], \qquad T(0) = 0
$$

The term $2\,T(k)$ is the two recursive four-peg calls (moving $k$ disks out and back), and $2^{\,n-k} - 1$ is the three-peg Hanoi cost for the $n-k$ largest disks.

### Choosing $k$: The Argmin

For each $n$, the optimal $k$ is the value minimizing the expression above:

$$
k^{*}(n) = \arg\min_{0 \le k < n} \Bigl[\, 2\,T(k) + 2^{\,n-k} - 1 \Bigr]
$$

There is no known closed form for $k^{*}(n)$ in the four-peg case, and the general Frame-Stewart conjecture (that this strategy is optimal for any number of pegs) remains an open problem. For any fixed number of pegs, however, the optimal $k$ can be computed efficiently by dynamic programming.

### Optimal Move Counts for Four Pegs ($n = 1..8$)

| $n$ | $T(n)$ |
|-----|--------|
| 1 | $1$ |
| 2 | $3$ |
| 3 | $5$ |
| 4 | $9$ |
| 5 | $13$ |
| 6 | $17$ |
| 7 | $25$ |
| 8 | $\mathbf{33}$ |

The highlight: $T(8) = 33$ — exactly 33 moves for 8 disks on four pegs, versus 255 on three pegs.

### Complexity Analysis

- **DP computation:** evaluating $T(i) = \min_k \left[2\,T(k) + 2^{\,i-k} - 1\right]$ for every $i$ with an inner loop over $k$ gives $O(n^2)$ time and $O(n)$ space.
- **Move generation:** the recursive generator produces exactly $T(n)$ moves; four-peg $T(n)$ grows polynomially (substantially better than the exponential $2^n - 1$ of three-peg Hanoi).
- **Recursion depth:** the Frame-Stewart recursion has depth $O(n)$.

## Approaches

### Frame-Stewart Dynamic Programming

Precompute $T[i]$ and the argmin `bestK[i]` for all disk counts up to $n$ bottom-up. Base case $T(0) = 0$; for each $i$, try every split $k$ and store the minimum cost and its argmin.

#### Implementation

`computeDP(n)` fills `T[]` and `bestK[]` with an outer loop over $i$ and an inner loop over $k$, evaluating the cost as `2 * T[k] + (1 << (i - k)) - 1` (where `1 << m` computes $2^m$) and recording the minimum.

### Recursive Move Generation (validation)

Given `bestK[]`, `frameStewart4` produces the actual move sequence, delegating the middle phase to the classic three-peg `hanoi3`. A global counter tracks the produced moves and compares them against the DP value.

#### Implementation

- `hanoi3(m, bottom, from, to, helper)`: classic recursive three-peg moves.
- `frameStewart4(n, first, src, aux1, aux2, dst)`: splits using `bestK[n]`, recursing twice on $k$ disks (all four pegs) and once on $n-k$ disks (three pegs).
- `solveReve(n)`: orchestrates the DP and generation; prints the full move list for $n \le 10$, otherwise only the counts.

## Example Output

Manual run with 8 disks (option 2, input 8):

```
Reve's Puzzle (Tower of Hanoi with Four Pegs)
1. Random number of disks (1-10)
2. Enter number of disks (1-15)
3. Classic Reve case: 8 disks
Choose an option: Enter number of disks (1-15): Disks: 8
Minimum moves computed by Frame-Stewart DP: 33
Move sequence by Frame-Stewart recursion:
Move disk 1 from peg 1 to peg 4
Move disk 2 from peg 1 to peg 2
   ...
Move disk 1 from peg 1 to peg 4
Moves counted from printed sequence: 33
DP value and counted moves agree.
```

The DP recurrence guarantees $T(8) = 33$, and the printed move sequence of exactly 33 moves validates both the algorithm and its implementation.
