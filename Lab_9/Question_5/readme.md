# Question 5

## Candy Distribution (bi-directional slope greedy)

$n$ children stand in a line, each with a rating. Every child gets at least one candy, and a child with a higher rating than an immediate neighbour must get more candies than that neighbour. Find the minimum total number of candies.

## Files folder structure

```
Question_5/
├── q5.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q5.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Algorithm (two passes)
Start with $c_i=1$ for all $i$.

* **Left to right:** if $r_i>r_{i-1}$ then $c_i=c_{i-1}+1$. This satisfies every left-neighbour constraint.
* **Right to left:** if $r_i>r_{i+1}$ then $c_i=\max(c_i,\,c_{i+1}+1)$. This satisfies every right-neighbour constraint without breaking the first pass, because values are only increased.

The answer is $\sum_i c_i$.

**Why it is optimal.** Each pass sets the smallest value forced by one direction. The final $c_i$ is the maximum of the two lower bounds, and every constraint is satisfied, so no smaller assignment exists. In terms of slopes, $c_i=\max(\text{length of rising run ending at }i,\ \text{length of falling run starting at }i)$ with $1$ added.

### Validation
* A **one-pass slope** method (counting rising and falling runs and correcting the peak) must give the same total.
* For $n\le7$ a brute force tries every candy vector with values in $1..n$ and keeps the cheapest valid one.

### Complexity
* Two linear scans: $O(n)$ time, $O(n)$ space for the candy array.
* The one-pass cross-check uses $O(1)$ extra space.

## Sample output

Mode 2 (auto-generate), `n = 8` children, `seed = 5`.

Typed input:

```
2
8 5
```

Output:

```
Ratings: 8 6 4 1 6 2 9 7
Candies: 4 3 2 1 2 1 2 1
Minimum total candies = 16
One-pass slope method = 16 -> PASS
(Brute-force check runs only when n<=7)
```
