# Question 6

## Description

Given two strings A (length m) and B (length n), find the minimum number of insertions, deletions and substitutions needed to turn A into B, and print the sequence of operations (traceback).

## File structure

```
question_6/
├── question_6.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_6.c
./a.out
```

## Explanation

- `dp[i][j]` is the edit distance between the first `i` characters of A and the first `j` characters of B.
- Base cases: `dp[i][0] = i` (delete all i characters) and `dp[0][j] = j` (insert all j characters).
- If `A[i-1] == B[j-1]`, no operation is needed: `dp[i][j] = dp[i-1][j-1]`.
- Otherwise `dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1])`, which are replace, delete and insert respectively.
- The answer is `dp[m][n]`.

**Traceback:** start at `(m, n)` and go back to `(0, 0)`, checking how the current cell was reached:

1. characters equal and `dp[i][j] == dp[i-1][j-1]`: **keep**, move diagonally
2. `dp[i][j] == dp[i-1][j-1] + 1`: **replace**, move diagonally
3. `dp[i][j] == dp[i-1][j] + 1`: **delete** `A[i-1]`, move up
4. otherwise: **insert** `B[j-1]`, move left

The steps are collected from the end, so they are printed in reverse to show the operations from left to right.

**Input representation:** two character strings (no spaces) and a 2D int table of size (m+1) x (n+1).

## Complexity analysis

The table has (m+1)(n+1) cells and each one takes O(1) (three lookups and a min).

Filling the table: O(m * n). Traceback: every step reduces i or j (or both), so at most m + n steps, O(m + n).

Total time = O(m * n). Space = O(m * n).

## Sample input and output

**Option 1 (manual input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: Enter string A (no spaces): kitten
Enter string B (no spaces): sitting
Minimum edit distance = 3
Traceback (A -> B):
  Replace 'k' with 's'
  Keep    'i'
  Keep    't'
  Keep    't'
  Replace 'e' with 'i'
  Keep    'n'
  Insert  'g'
```

**Option 2 (random input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated A = bccadca
Generated B = cbddbdab
Minimum edit distance = 6
Traceback (A -> B):
  Insert  'c'
  Keep    'b'
  Replace 'c' with 'd'
  Replace 'c' with 'd'
  Replace 'a' with 'b'
  Keep    'd'
  Replace 'c' with 'a'
  Replace 'a' with 'b'
```

(The random sample changes on every run.)
