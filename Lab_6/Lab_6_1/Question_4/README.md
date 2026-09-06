# Question 4

## Problem
Write a program to implement Matrix Chain Multiplication using Dynamic Programming. Given the dimensions of N-1 matrices in an array arr[], determine the minimum number of scalar multiplications required to multiply the complete matrix chain.

## Folder Structure
```
Question_4/
├── q4.c
├── a.out
└── README.md
```

## Mathematical Explanation

### Problem Definition
Given $n$ matrices with dimensions stored in array $arr[]$ where:
- Matrix $i$ has dimensions $arr[i-1] \times arr[i]$
- We need to find the optimal order to multiply these matrices

Example:
- $arr[] = \{10, 30, 5, 60\}$
- 3 matrices: $M_1(10 \times 30)$, $M_2(30 \times 5)$, $M_3(5 \times 60)$
- Different orders give different costs

### Dynamic Programming Approach

We create a 2D table $dp[i][j]$ where:
- $dp[i][j]$ = minimum multiplications needed to compute $M[i]$ to $M[j]$

**Recurrence Relation:**

$$
dp[i][j] = \begin{cases}
0 & \text{if } i = j \text{ (single matrix)} \\
\min_{i \leq k < j} (dp[i][k] + dp[k+1][j] + arr[i-1] \times arr[k] \times arr[j]) & \text{otherwise}
\end{cases}
$$

**Algorithm:**
1. Create 2D array $dp[n][n]$
2. Initialize diagonal to 0 (single matrices)
3. For chain length $L$ from 2 to $n$:
   - For each starting position $i$:
     - Calculate ending position $j = i + L - 1$
     - Try all split points $k$ between $i$ and $j$
     - Choose $k$ that gives minimum cost
4. Return $dp[1][n-1]$

**Example:** $arr[] = \{10, 30, 5, 60\}$
- Option 1: $(M_1 \times M_2) \times M_3 = 10 \times 30 \times 5 + 10 \times 5 \times 60 = 1500 + 3000 = 4500$
- Option 2: $M_1 \times (M_2 \times M_3) = 30 \times 5 \times 60 + 10 \times 30 \times 60 = 9000 + 18000 = 27000$
- Minimum = 4500

**Time Complexity:** $O(n^3)$ - Three nested loops  
**Space Complexity:** $O(n^2)$ - 2D array of size $n \times n$
