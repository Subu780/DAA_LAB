# Question 3

## Problem
Implement the Longest Common Subsequence (LCS) algorithm using Dynamic Programming. Given two strings, find the length of their longest common subsequence and display the subsequence.

## Folder Structure
```
Question_3/
├── q3.c
├── a.out
└── README.md
```

## Mathematical Explanation

### Problem Definition
Given two strings $s1$ and $s2$, find the longest subsequence common to both. A subsequence is a sequence that appears in the same relative order but not necessarily contiguous.

Example: 
- $s1$ = "ABCDGH", $s2$ = "AEDFHR"
- LCS = "ADH" (length = 3)

### Dynamic Programming Approach

We create a 2D table $dp[i][j]$ where:
- $i$ represents length of first string considered (0 to m)
- $j$ represents length of second string considered (0 to n)
- $dp[i][j]$ = length of LCS of $s1[0..i-1]$ and $s2[0..j-1]$

**Recurrence Relation:**

$$
dp[i][j] = \begin{cases}
0 & \text{if } i=0 \text{ or } j=0 \\
dp[i-1][j-1] + 1 & \text{if } s1[i-1] == s2[j-1] \\
\max(dp[i-1][j], dp[i][j-1]) & \text{otherwise}
\end{cases}
$$

**Algorithm:**
1. Create a 2D array $dp[m+1][n+1]$
2. Initialize first row and column to 0
3. For each position $(i,j)$:
   - If characters match: add 1 to diagonal value
   - Else: take maximum from top or left
4. $dp[m][n]$ gives LCS length

**Backtracking to find LCS:**
Start from $dp[m][n]$ and move backwards:
- If characters match: include in LCS, move diagonally
- Else: move towards the larger value (up or left)

**Time Complexity:** $O(m \times n)$ - Fill $m \times n$ table entries  
**Space Complexity:** $O(m \times n)$ - 2D array of size $(m+1) \times (n+1)$
