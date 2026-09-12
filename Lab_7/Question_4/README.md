# Security Switches Problem

## Problem Statement

There is a row of $n$ security switches protecting a military installation entrance. The switches can be manipulated as follows:

(i) The rightmost switch may be turned on or off at will.

(ii) Any other switch may be turned on or off only if the switch to its immediate right is on and all the other switches to its right, if any, are off.

(iii) Only one switch may be toggled at a time.

Devise an algorithm to turn off all the switches, which are initially all on, in the minimum number of moves. (Toggling one switch is considered one move.) By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## File Structure

```
Question_4/
    ├── q4.c
    ├── a.out
    └── README.md
```

- `q4.c`: the C program implementing BFS shortest-path solver with sequence reconstruction, and closed-form formula check.
- `a.out`: the compiled binary of the program..
- `README.md`: this documentation file.

## Detailed Explanation

### Modelling Switches as Binary Digits

Label switches $1..n$ left to right, so switch $n$ is the rightmost. Let bit $(i-1)$ of a mask be $1$ when switch $i$ is on:

$$
\text{mask} = \sum_{i=1}^{n} \text{bit}(\text{switch}\;i) \cdot 2^{\,i-1}
$$

- all switches on $\Rightarrow$ every bit is $1$: $\text{mask} = (1 \ll n) - 1 = 2^{n} - 1$;
- all switches off $\Rightarrow$ the goal mask is $0$;
- toggling switch $i$ flips bit $(i-1)$.

A state is uniquely identified by its $n$-bit mask, which encodes which of the $2^n$ configurations the row is in.

### State Graph and Shortest-Path View

The toggle rules define a graph on the $2^n$ masks: an edge goes from mask $m$ to mask $m'$ when a single legal toggle turns $m$ into $m'$. Toggling is its own inverse, so the graph behaves like an undirected graph. The problem is: find the **shortest path** from the all-on node to the all-off node, where every edge costs one move.

### Approach A: Breadth-First Search

BFS explores the graph level by level. The first time BFS reaches a node, it has arrived by the shortest possible path, so the level at which $0$ is discovered is exactly the minimum number of moves:

$$
M(n) = \operatorname{dist}(\,2^{n} - 1,\; 0\,)
$$

A predecessor map stores, for every state, the mask we came from and the switch flipped, so the optimal toggle sequence can be reconstructed by walking backwards from $0$. The sequence is printed only for $n \le 10$; the count stays exact regardless.

**Complexity:** there are $2^n$ states, each enqueued at most once, and each state tests at most $n$ candidate toggles with $O(n)$ bit checks each, giving $O(2^n)$ time and $O(2^n)$ memory.

### Approach B: The Closed-Form Formula

The BFS results for small $n$ follow a clean pattern:

| $n$ | 1 | 2 | 3 | 4 | 5 |
|-----|---|---|---|---|---|
| $M(n)$ | 1 | 2 | 5 | 10 | 21 |

These satisfy the linear recurrence

$$
M(n) = M(n-1) + 2\,M(n-2) + 1, \qquad M(1) = 1,\; M(2) = 2
$$

which is verified by the table: $5 = 2 + 2\cdot 1 + 1$, $10 = 5 + 2\cdot 2 + 1$, $21 = 10 + 2\cdot 5 + 1$. Solving the recurrence gives the closed form

$$
\boxed{\;M(n) = \left\lfloor \frac{2^{\,n+1} - 1}{3} \right\rfloor\;}
$$

Check the small cases: $n=1 \Rightarrow \left\lfloor\frac{4-1}{3}\right\rfloor = 1$, $n=2 \Rightarrow \left\lfloor\frac{7}{3}\right\rfloor = 2$, $n=3 \Rightarrow \frac{15}{3} = 5$, $n=4 \Rightarrow \left\lfloor\frac{31}{3}\right\rfloor = 10$, $n=5 \Rightarrow \frac{63}{3} = 21$. Evaluated in 64-bit integer arithmetic, this costs $O(1)$ time and $O(1)$ memory. Comparing it with the BFS count validates the BFS implementation.

## Approaches

### Breadth-First Search (shortest path)

Represent each configuration as an $n$-bit mask and run BFS over the $2^n$ nodes with edges = legal single toggles. The first discovery of node $0$ gives the minimum moves; a predecessor map reconstructs the optimal sequence.

#### Implementation

In `q4.c` the predicate `canToggle` checks the rules (rightmost switch always allowed; otherwise the neighbour to the right must be on and all further-right bits off). BFS uses a queue plus `prev` and `move` arrays. After the search the sequence is rebuilt backwards and printed when $n \le 10$.

### Closed-Form Formula

The minimum is $M(n) = \left\lfloor \frac{2^{\,n+1} - 1}{3} \right\rfloor$, derived from the recurrence $M(n) = M(n-1) + 2\,M(n-2) + 1$.

#### Implementation

`formula` computes `((1ULL << (n + 1)) - 1) / 3` with `unsigned long long` arithmetic (safe for all $n \le 20$) and `main` prints it directly below the BFS count for comparison.

## Example Output

A manual run with $n = 3$, whose minimum is $5$ moves:

```
Security Switches Problem
1. Random number of switches (1-10)
2. Enter number of switches (1-20)
Choose an option: Enter number of switches (1-20): Switches: 3
Initial state: all ON
Minimum moves (BFS shortest path): 5
Minimum moves (closed-form formula): 5
Both approaches agree.
Optimal toggle sequence (5 moves):
Toggle switch 3
Toggle switch 1
Toggle switch 3
Toggle switch 2
Toggle switch 3
```

The printed sequence runs through $111 \to 011 \to 010 \to 110 \to 100 \to 000$, matching $M(3) = \left\lfloor \frac{2^4 - 1}{3} \right\rfloor = 5$.
