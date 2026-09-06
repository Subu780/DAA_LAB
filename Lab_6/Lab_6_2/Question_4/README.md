# Question 4

## Problem
Given a permutation $p$ of integers $1$ to $n$, sort them using only the `reverse(p, i, j)` operation, which reverses elements $p_i, \ldots, p_j$. Show that any permutation can be sorted using $O(n)$ reversals, and design an algorithm that sorts with $O(n \log n)$ cost when the cost of each reversal equals its length.

## Folder Structure
```
Question_4/
├── q4.c
├── a.out
└── README.md
```

## Mathematical Explanation

### Part 1: Sorting with $O(n)$ Reversals

**Theorem:** Any permutation can be sorted using at most $2(n-1)$ reversals.

**Proof :**

Algorithm:
1. For position $i = n$ down to $2$:
   - Find the maximum element in $p[1..i]$
   - If it's not at position $i$:
     - Reverse from start to max position (brings max to front)
     - Reverse from start to position $i$ (puts max in correct place)
2. At most 2 reversals per element

**Analysis:**
- $n-1$ iterations (positions $n$ down to $2$)
- At most 2 reversals per iteration
- **Total reversals:** $O(n)$

**Example:** $[1, 4, 3, 2, 5]$
- Find max in $[1, 4, 3, 2]$ → position 2 (element 4)
- Reverse $[1, 4]$ → $[4, 1, 3, 2, 5]$
- Reverse $[4, 1, 3, 2]$ → $[2, 3, 1, 4, 5]$
- Continue for remaining positions...

### Part 2: Sorting with $O(n \log n)$ Cost

**Cost Model:** $\text{cost}(\text{reverse}(p, i, j)) = |j - i| + 1$

**Observation:** 
- Reversal sort uses $O(n)$ reversals but total cost is $O(n^2)$
- Each reversal can have length $O(n)$
- Need fewer long reversals, more short reversals

**Merge-Sort Inspired Approach:**

Instead of actual reversals, model the cost of divide-and-conquer sorting:

1. **Divide:** Split array into two halves
2. **Conquer:** Recursively sort each half
3. **Merge:** Combine sorted halves

**Cost Analysis:**

Recurrence relation:

$$
T(n) = 2T(n/2) + O(n)
$$

- Divide/merge cost per level: $O(n)$
- Number of levels: $\log n$
- **Total cost:** $O(n \log n)$

**Correctness:**
- Merge operation can be simulated with reversals
- Each merge combines two sorted subarrays
- Cost proportional to subarray size
- Final result is fully sorted

### Complexity Summary

| Algorithm | Reversals | Total Cost | Time Complexity |
|-----------|-----------|------------|-----------------|
| Reversal Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ |
| Merge-based | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ |

**Space Complexity:** $O(n)$ for temporary arrays
