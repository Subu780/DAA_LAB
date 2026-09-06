# Question 1

## Problem
Write a program to find the nth Fibonacci number using Dynamic Programming.

## Folder Structure
```
Question_1/
├── q1.c
├── a.out
└── README.md
```

## Mathematical Explanation

The Fibonacci sequence is defined as:
- $F(0) = 0$
- $F(1) = 1$
- $F(n) = F(n-1) + F(n-2)$ for $n \geq 2$

### Dynamic Programming Approach (Tabulation)

Instead of using recursion which recalculates the same values multiple times, we use dynamic programming to store previously calculated values in an array.

**Algorithm:**
1. Create an array $dp[]$ of size $n+1$
2. Initialize base cases: $dp[0] = 0$, $dp[1] = 1$
3. Fill the array iteratively: $dp[i] = dp[i-1] + dp[i-2]$ for $i$ from $2$ to $n$
4. Return $dp[n]$

**Time Complexity:** $O(n)$ - Single loop from 2 to n  
**Space Complexity:** $O(n)$ - Array of size n+1
