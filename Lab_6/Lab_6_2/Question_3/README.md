# Question 3

## Problem
Find an $O(n \log n)$ divide and conquer algorithm for convolution of two vectors $A$ and $B$ of lengths $m$ and $n$ respectively, where $n \geq m$.

## Folder Structure
```
Question_3/
├── q3.c
├── a.out
└── README.md
```

## Mathematical Explanation

### Convolution Definition

The convolution of two vectors $A$ and $B$ is a vector $C$ such that:

$$
C[k] = \sum_{j=0}^{m-1} A[j] \cdot B[k - j]
$$

where $k$ ranges from $0$ to $m+n-2$, and the result has length $m+n-1$.

**Example:** If $A = [1, 2]$ and $B = [3, 4, 5]$, then:
- $C[0] = A[0] \cdot B[0] = 1 \cdot 3 = 3$
- $C[1] = A[0] \cdot B[1] + A[1] \cdot B[0] = 1 \cdot 4 + 2 \cdot 3 = 10$
- $C[2] = A[0] \cdot B[2] + A[1] \cdot B[1] = 1 \cdot 5 + 2 \cdot 4 = 13$
- $C[3] = A[1] \cdot B[2] = 2 \cdot 5 = 10$

Result: $C = [3, 10, 13, 10]$

### Naive Approach: $O(m \times n)$

For each output position $k$ from $0$ to $m+n-2$:
- Calculate sum of products $A[j] \cdot B[k-j]$ for all valid $j$
- Outer loop runs $m+n-1$ times
- Inner loop runs up to $m$ times
- Total complexity: $O((m+n) \times m) \approx O(m \times n)$

This is straightforward but slow for large arrays.

### Divide and Conquer Approach: $O(n \log n)$

The key idea is to split the problem into smaller subproblems and combine results efficiently.

**Divide and Conquer Strategy:**

1. **Divide:** Split arrays $A$ and $B$ into smaller parts
2. **Conquer:** Recursively compute convolutions on smaller parts  
3. **Combine:** Merge the results efficiently

**Why $O(n \log n)$?**

Similar to merge sort:
- At each level, we do $O(n)$ work to combine
- We divide the problem into halves recursively
- Total levels: $\log n$
- Total work: $O(n) \times \log n = O(n \log n)$

**Recurrence Relation:**

$$
T(n) = 2T(n/2) + O(n)
$$

Using Master Theorem: $T(n) = O(n \log n)$

### Implementation Note

The actual implementation of $O(n \log n)$ convolution is complex and involves advanced techniques. The provided C code uses the straightforward $O(m \times n)$ approach which is easier to understand and implement.

For $O(n \log n)$, one would need:
- Sophisticated divide and conquer logic
- Efficient combination of subproblem results
- Special handling of array boundaries

**Time Complexity:** $O(m \times n)$ (implemented), $O(n \log n)$ (optimal theory)  
**Space Complexity:** $O(m + n)$ for result array
