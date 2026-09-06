# Question 2

## Problem
Implement the 0/1 Knapsack problem using Dynamic Programming. Given n items with their weights and profits and a knapsack of capacity W, determine the maximum profit that can be obtained.

## Folder Structure
```
Question_2/
├── q2.c
├── a.out
└── README.md
```

## Mathematical Explanation

### Problem Definition
Given:
- $n$ items, each with weight $wt[i]$ and value $val[i]$
- Knapsack capacity $W$
- Each item can be taken (1) or not taken (0)

Find: Maximum value that can be obtained without exceeding capacity $W$

### Dynamic Programming Approach

We create a 2D table $dp[i][w]$ where:
- $i$ represents items considered (0 to n)
- $w$ represents capacity (0 to W)
- $dp[i][w]$ = maximum value achievable with first i items and capacity w

**Recurrence Relation:**

$$
dp[i][w] = \begin{cases}
0 & \text{if } i=0 \text{ or } w=0 \\
dp[i-1][w] & \text{if } wt[i-1] > w \\
\max(val[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]) & \text{otherwise}
\end{cases}
$$

**Algorithm:**
1. Create a 2D array $dp[n+1][W+1]$
2. Initialize first row and column to 0
3. For each item $i$ and capacity $w$:
   - If item weight > capacity: don't include item
   - Else: take maximum of (including item, excluding item)
4. Return $dp[n][W]$

**Time Complexity:** $O(n \times W)$ - Fill $n \times W$ table entries  
**Space Complexity:** $O(n \times W)$ - 2D array of size $(n+1) \times (W+1)$
