# Question 7

## Description

Given a rod of length n and a price list where `p[i]` is the price of a piece of length i, find the maximum revenue from cutting the rod (cuts are integers, and not cutting at all is allowed) and print the lengths of the pieces in the optimal cut.

## File structure

```
question_7/
├── question_7.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_7.c
./a.out
```

## Explanation

- `best[j]` is the maximum revenue for a rod of length `j`, with `best[0] = 0`.
- For a rod of length `j`, we choose the length `i` (1 to j) of the first piece. We get `price[i]` for it and then the best we can do with the remaining `j - i`, so `best[j] = max over i of (price[i] + best[j - i])`.
- `firstCut[j]` stores the `i` that gave the maximum.
- **Reconstruction:** start with `left = n`, print `firstCut[left]`, subtract it from `left`, and repeat until `left` is 0.

**Input representation:** prices are stored in an int array indexed from 1 to n (index 0 unused, so `price[i]` really is the price of length i). Revenue is `long long`.

## Complexity analysis

For each j from 1 to n the inner loop runs j times:

T(n) = sum from j = 1 to n of j = n(n+1)/2 = O(n^2)

Reconstruction takes at most n steps. Space: O(n) for `best`, `firstCut` and `price`.

## Sample input and output

**Option 1 (manual input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: Rod length n (1 to 10000): 8
Enter prices for lengths 1 to 8: 1 5 8 9 10 17 17 20
Maximum revenue = 22
Pieces: 2 6
```

**Option 2 (random input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated rod length n = 7
Generated prices: 1 6 4 7 15 18 15
Maximum revenue = 21
Pieces: 2 5
```

(The random sample changes on every run.)
