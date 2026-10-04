# Question 4

## Description

Given an integer array, find the length of the longest strictly increasing subsequence (LIS). The program solves it with two approaches, O(n^2) and O(n log n), and prints both so they can be compared.

## File structure

```
question_4/
├── question_4.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_4.c
./a.out
```

## Explanation

### Approach 1: O(n^2) dynamic programming

- `len[i]` is the length of the longest increasing subsequence that **ends at index i**.
- Every element alone is a subsequence of length 1, so `len[i]` starts at 1.
- For every `j < i` with `a[j] < a[i]`, we can extend the sequence ending at `j`, so `len[i] = max(len[i], len[j] + 1)`.
- The answer is the maximum value in `len[]`.
- `prev[i]` stores the `j` that gave the best value, so the subsequence itself can be printed by following `prev` backwards from the best end.

### Approach 2: O(n log n) with binary search

- Keep an array `tails`, where `tails[k]` is the **smallest possible last element** of an increasing subsequence of length `k+1`. This array is always sorted.
- For each element `x`, binary search for the first position in `tails` whose value is `>= x` (strict increase, so equal values replace instead of extending).
  - If `x` is bigger than everything, it goes at the end and the LIS grows by 1.
  - Otherwise it replaces that position, which keeps the tail as small as possible for future extension.
- The final size of `tails` is the LIS length. (The array itself is not necessarily a real LIS, only its length is correct, which is why the printed subsequence comes from Approach 1.)

**Input representation:** an int array of size n allocated with `malloc`.

## Complexity analysis

### Approach 1

For each i (0 to n-1) the inner loop runs i times:

T(n) = sum from i = 0 to n-1 of i = n(n-1)/2 = O(n^2)

Space: `len` and `prev` arrays, O(n).

### Approach 2

For each of the n elements, one binary search over an array of size at most n costs O(log n) and the update is O(1):

T(n) = n * O(log n) = O(n log n)

Space: the `tails` array, O(n).

## Sample input and output

**Option 1 (manual input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: Number of elements (1 to 100000): 8
Enter the 8 elements: 10 9 2 5 3 7 101 18
O(n^2) method     : LIS length = 4
O(n log n) method : LIS length = 4
One such subsequence: 2 5 7 101
```

**Option 2 (random input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated array: 46 45 11 1 26 25 39 35 1 44 38
O(n^2) method     : LIS length = 4
O(n log n) method : LIS length = 4
One such subsequence: 11 26 39 44
```

(The random sample changes on every run.)
