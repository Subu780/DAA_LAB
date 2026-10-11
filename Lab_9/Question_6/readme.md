# Question 6

## Reorganise String with K-Distance Apart

Given a string $S$ and an integer $K$, rearrange $S$ so that equal characters are at least $K$ positions apart. If this is impossible, return an empty string.

## Files folder structure

```
Question_6/
├── q6.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q6.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Algorithm (max-heap with cooldown)
1. Count the frequency of each character and put the characters in a max-heap by remaining count (ties by character).
2. For position $i=0,1,\dots,n-1$:
   * if the heap is empty, the arrangement is **impossible**, so return an empty string;
   * pop the character $c$ with the largest remaining count, place it at position $i$ and decrement its count;
   * the character placed at position $i-K+1$ has now waited $K-1$ positions, so push it back into the heap if its count is still positive.

A character placed at position $p$ can reappear first at $p+K$, which gives the distance requirement. For $K\le1$ no restriction applies.

**Why greedy works.** Always using the most frequent available character keeps the large counts from being stranded at the end, where they would be forced into a conflict. If the heap runs empty, then every remaining character is in cooldown, which means a valid arrangement does not exist.

### Validation
* The output is checked to be a permutation of $S$ with every equal pair at least $K$ apart.
* For $|S|\le10$ a backtracking search decides feasibility independently and the answers must agree.

### Complexity
Let $\sigma$ be the alphabet size.
* Each of the $n$ steps does $O(1)$ heap operations on at most $\sigma$ elements: $O(n\log\sigma)$ time.
* Space: $O(n+\sigma)$.

## Sample output

Mode 2 (auto-generate), length `9`, alphabet size `3`, `K = 3`, `seed = 40`.

Typed input:

```
2
9 3 3 40
```

Output:

```
S = "cbcaabcba", K = 3
Rearranged: "abcabcabc"
Output check (same letters, spacing >= K): PASS
Brute-force feasibility = possible -> PASS
```
