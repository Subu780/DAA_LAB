# Question 1

## Description

Given a set of coin values (infinite supply of each) and a target amount V, find the smallest number of coins that add up to V. If V cannot be formed, print -1.

## File structure

```
question_1/
├── question_1.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_1.c
./a.out
```

## Explanation

Greedy does not always work here (for coins 1, 3, 4 and V = 6, greedy picks 4+1+1 = 3 coins but 3+3 = 2 coins is better), so I used dynamic programming.

- `dp[v]` stores the fewest coins needed to make amount `v`.
- Base case: `dp[0] = 0`.
- For every amount `v` from 1 to V, I try each coin `c` that is not bigger than `v`. If `v - c` is reachable, then `dp[v] = min(dp[v], dp[v - c] + 1)`.
- Unreachable amounts hold a large number (`INF`), so they never get picked as the minimum.
- `lastCoin[v]` remembers which coin gave the best answer for `v`, so I can walk back from V and print the coins that were used.
- If `dp[V]` is still `INF` at the end, the answer is -1.

**Input representation:** coins are kept in a plain int array, the target is an int, and the dp table is a 1D array of size V+1 created with `malloc`.

## Complexity analysis

There are V subproblems (amounts 1 to V). Each one loops over all n coins and does O(1) work (one comparison and one addition).

T(n, V) = sum over v = 1..V of (n * O(1)) = O(n * V)

Space: two arrays of size V+1, so O(V) (the coin array is O(n)).

Printing the coins takes at most V steps (every coin is at least 1), so it does not change the bound.

## Sample input and output

**Option 1 (manual input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: Number of coin denominations (1 to 100): 3
Enter the 3 coin values: 1 2 5
Target amount V: 11
Minimum number of coins = 3
Coins used: 1 5 5
```

**Option 2 (random input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated coins: 6 15 11 1 16
Generated target V = 44
Minimum number of coins = 4
Coins used: 6 6 16 16
```

(The random sample changes on every run.)

Another manual run where the amount cannot be made:

```
Number of coin denominations (1 to 100): 2
Enter the 2 coin values: 2 4
Target amount V: 7
Result: -1 (amount 7 cannot be made)
```
