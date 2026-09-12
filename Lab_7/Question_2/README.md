# Egg Dropping Problem

## Problem Statement

"Super egg testing experiment. A firm has invented a super-strong egg. For publicity purposes, it wants to determine the highest floor in a 100-storey building from which such an egg can fall without breaking. The firm has given a tester two identical eggs to experiment with. The same egg can be dropped multiple times unless it breaks. What is the minimum number of droppings that is guaranteed to determine the highest safe floor in all cases? Design a dynamic programming generalized solution for $E$ eggs and $F$ floors. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm."

## File Structure

```
Question_2/
    ├── q2.c
    ├── a.out
    └── README.md
```

- `q2.c`: the C program implementing top-down memoized and bottom-up tabular DP solvers.
- `a.out`: the compiled binary of the program.
- `README.md`: this documentation file.

## Detailed Explanation

Imagine a building with $F$ floors and $E$ identical eggs. There is an unknown critical floor $f$ such that an egg survives any drop from floors $1..f$ and breaks for every floor above $f$. If an egg survives it is undamaged and reusable; if it breaks it is lost forever. We want an adaptive strategy whose **worst-case number of drops** is as small as possible, guaranteed for every possible $f$.

With one egg the answer is forced: we must drop from floor $1$, then $2$, then $3$, and so on, because a single break destroys all information. Hence

$$
\text{eggDrop}(1, f) = f
$$

The key observation is **optimal substructure**. Suppose we have $e$ eggs, $f$ floors, and our first drop is from floor $x$. Two things can happen:

- If the egg **breaks**, the answer is below $x$; we still have $e-1$ eggs and $x-1$ floors, costing $\text{eggDrop}(e-1, x-1)$ further drops.
- If the egg **survives**, the answer is at $x$ or above; the egg is reusable, and $f-x$ floors remain above, costing $\text{eggDrop}(e, f-x)$ further drops.

Because nature is adversarial, we must prepare for the worse of the two outcomes, and we are free to choose the best first floor $x$. This yields the DP recurrence:

$$
\boxed{\;\text{eggDrop}(e, f) = 1 + \min_{1 \leq x \leq f}\; \max\bigl(\text{eggDrop}(e-1, x-1),\; \text{eggDrop}(e, f-x)\bigr)\;}
$$

with base cases

$$
\text{eggDrop}(e, 0) = 0, \qquad \text{eggDrop}(1, f) = f
$$

The $1$ counts the current drop, the $\max$ models the worst case chosen by the adversary, and the $\min$ selects the first floor that makes that worst case as small as possible.

The same pairs $(e, f)$ recur in many branches, so the subproblems **overlap**. This makes DP the perfect tool: the top-down version memoizes results in a table initialized to $-1$, while the bottom-up version fills a table $\text{drops}[e][f]$ in increasing order of $e$ and $f$.

### The Classic 2-Egg 100-Floor Argument

Drop the first egg from floor $x$. If it breaks, check floors $1..x-1$ with the second egg one by one, costing at most $x-1$ more drops, so this branch costs at most $1 + (x-1) = x$. If it survives, jump up by $x-1$ floors and repeat, shrinking the "gap" by one each time. With $2$ eggs and $t$ trials available, the number of floors coverable is the triangular number

$$
1 + 2 + \cdots + t = \frac{t(t+1)}{2}
$$

For $100$ floors we need the smallest $t$ with $\frac{t(t+1)}{2} \geq 100$. Since $\frac{13 \cdot 14}{2} = 91 < 100$ and $\frac{14 \cdot 15}{2} = 105 \geq 100$, the answer is

$$
\boxed{t = 14}
$$

### Floors Coverable with $t$ Trials

With $e$ eggs and $t$ trials, the number of floors coverable is the binomial sum

$$
\sum_{i=1}^{e} \binom{t}{i}
$$

| trials $t$ | floors, 1 egg | floors, 2 eggs $\left(\frac{t(t+1)}{2}\right)$ | floors, 3 eggs |
|-------------|---------------|------------------------------------------------|-----------------|
| 1 | $1$ | $1$ | $1$ |
| 2 | $2$ | $3$ | $3$ |
| 3 | $3$ | $6$ | $7$ |
| 4 | $4$ | $10$ | $14$ |
| 13 | $13$ | $91$ | $377$ |
| 14 | $14$ | $105$ | $560$ |

### Complexity Analysis

For a pair $(e, f)$ the recurrence scans all $x \in [1, f]$, so each table entry costs $O(f)$ work. There are $O(EF)$ entries, giving

$$
O(E \cdot F \cdot F) = O(EF^2)
$$

time for both the memoized top-down version and the bottom-up version. Both tables hold $(E+1)(F+1)$ entries, so space is $O(EF)$.

## Approaches

### Top-Down (Memoized) DP

`eggDropTopDown(e, f)` mirrors the recurrence directly: returns $f$ when $e = 1$, $0$ when $f = 0$, and otherwise consults the memo table first. If the entry equals $-1$, it loops $x$ over $1..f$, computes the two recursive values, takes their max, keeps the minimum, stores $\text{best} + 1$, and returns it.

#### Implementation

A table of size $(E+1) \times (F+1)$ is allocated with `malloc`, initialized to $-1$ and freed after the call.

### Bottom-Up (Tabular) DP

`eggDropBottomUp` fills `drops[e][f]` in increasing order of $e$ and $f$ so every dependency is already known. Row $e = 1$ is filled with `drops[1][f] = f`, and `drops[e][0] = 0` for every $e$.

#### Implementation

For each cell, the code scans $x$ from $1$ to $f$, computes the max of the two already-known table values, keeps the minimum, and stores $\text{best} + 1$. The answer is `drops[E][F]`.

## Example Output

```
Menu:
1. Random eggs and floors
2. Manual input of eggs and floors
3. Classic problem: 2 eggs, 100 floors
0. Exit
Enter your choice: 2
Enter eggs (1..10): 2
Enter floors (1..200): 100
User input Eggs: 2 Floors: 100
Minimum droppings (top-down memoized DP): 14
Minimum droppings (bottom-up DP): 14
Both approaches agree.
```
