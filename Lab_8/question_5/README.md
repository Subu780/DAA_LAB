# Question 5

## Description

Given an array of n positive integers, find the maximum possible sum of a strictly increasing subsequence.

## File structure

```
question_5/
├── question_5.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_5.c
./a.out
```

## Explanation

This is the LIS idea, except we add up the values instead of counting the length.

- `sum[i]` is the maximum sum of an increasing subsequence that **ends at a[i]**.
- It starts as `a[i]` (the element alone).
- For every `j < i` with `a[j] < a[i]`, we can append `a[i]` after the best sequence ending at `j`, so `sum[i] = max(sum[i], sum[j] + a[i])`.
- The answer is the largest `sum[i]` over all i.
- `prev[i]` records the previous index so the actual subsequence can be printed by walking back from the best end.

Note that the longest increasing subsequence is not always the one with the biggest sum. In the sample, 1 2 3 4 5 is the longest, but 1 2 3 100 has a larger sum.

**Input representation:** an int array for the elements and a `long long` array for the sums (to avoid overflow).

## Complexity analysis

For each i the inner loop runs i times, doing O(1) work:

T(n) = sum from i = 0 to n-1 of i = n(n-1)/2 = O(n^2)

Space: `sum`, `prev` and `chain` arrays, O(n).

## Sample input and output

**Option 1 (manual input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: Number of elements (1 to 100000): 7
Enter the 7 positive elements: 1 101 2 3 100 4 5
Maximum sum of an increasing subsequence = 106
Subsequence: 1 2 3 100
```

**Option 2 (random input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated array: 46 95 11 1 76 75 89 35 51
Maximum sum of an increasing subsequence = 211
Subsequence: 46 76 89
```

(The random sample changes on every run.)
