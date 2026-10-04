# Question 2

## Description

Given distinct positive coin values (infinite supply) and a target V, count the number of different combinations of coins that sum to V. Order does not matter, so 1+2 and 2+1 count as one.

## File structure

```
question_2/
├── question_2.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_2.c
./a.out
```

## Explanation

- `ways[v]` is the number of combinations that make amount `v`.
- `ways[0] = 1` because there is exactly one way to make 0 (take nothing).
- The important part is the loop order. The **coin loop is outside** and the amount loop is inside. For each coin `c`, I go through `v = c .. V` and do `ways[v] += ways[v - c]`.
- Because a coin is fully processed before moving to the next coin, a combination is always built in the order of the coin list, so 1+2 and 2+1 are never counted twice. (If the loops were swapped, we would count permutations instead.)
- The answer can grow fast, so I used `long long`.

**Input representation:** int array for coins, int target, and a 1D `long long` array of size V+1.

## Complexity analysis

The outer loop runs n times and the inner loop runs at most V times, each iteration doing one addition.

T(n, V) = sum over i = 1..n of (V - c_i + 1) = O(n * V)

Space: O(V) for the `ways` array.

## Sample input and output

**Option 1 (manual input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: Number of coin denominations (1 to 100): 3
Enter the 3 distinct coin values: 1 2 3
Target amount V: 4
Number of distinct combinations = 4
```

**Option 2 (random input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated coins: 6 5 1 9 4
Generated target V = 12
Number of distinct combinations = 12
```

(The random sample changes on every run.)

For coins {1, 2, 3} and V = 4 the four combinations are 1+1+1+1, 1+1+2, 2+2 and 1+3.
