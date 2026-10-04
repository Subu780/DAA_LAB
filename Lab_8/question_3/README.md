# Question 3

## Description

Given two sequences X and Y, find the length of their longest common subsequence (LCS) and also print the actual subsequence.

## File structure

```
question_3/
├── question_3.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_3.c
./a.out
```

## Explanation

- `L[i][j]` is the LCS length of the first `i` characters of X and the first `j` characters of Y. Row 0 and column 0 are all 0.
- If `X[i-1] == Y[j-1]`, the characters match, so `L[i][j] = L[i-1][j-1] + 1`.
- Otherwise `L[i][j] = max(L[i-1][j], L[i][j-1])`.
- `L[m][n]` is the length of the LCS.

**Reconstruction:** start at `(m, n)`. If the characters match, that character belongs to the LCS, so I put it in the answer (from the back) and move diagonally. If not, I move to the neighbour (up or left) that has the bigger value. This continues until `i` or `j` becomes 0.

**Input representation:** sequences are read as character strings (no spaces) and the table is a 2D int array of size (m+1) x (n+1) made with `malloc`/`calloc`.

## Complexity analysis

The table has (m+1)(n+1) cells and each cell is filled in O(1).

T(m, n) = O(m * n) for filling the table, plus O(m + n) for the traceback (each step reduces i or j by at least 1).

Total time = O(m * n). Space = O(m * n) for the table.

## Sample input and output

**Option 1 (manual input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: Enter sequence X (no spaces): ABCBDAB
Enter sequence Y (no spaces): BDCABA
Length of LCS = 4
LCS = BCBA
```

**Option 2 (random input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated X = BCCADCACCBDD
Generated Y = DABCCACDCA
Length of LCS = 7
LCS = BCCADCA
```

(The random sample changes on every run.)

Note: an LCS may not be unique (for ABCBDAB and BDCABA, BCBA, BDAB and BCAB are all valid). The program prints one of them.
