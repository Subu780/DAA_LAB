# Question 8

## Description

Given n sorted keys k1..kn with search probabilities p1..pn and n+1 dummy keys d0..dn (unsuccessful searches) with probabilities q0..qn, build the binary search tree with the minimum expected search cost. The program prints the cost, the root and the shape of the tree.

## File structure

```
question_8/
├── question_8.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_8.c -lm
./a.out
```

## Explanation

For a subtree built from keys `ki..kj`:

- `w[i][j] = p_i + ... + p_j + q_{i-1} + ... + q_j` is the total probability of that range. Whenever a subtree becomes a child, every node in it goes one level deeper, so its cost increases by exactly `w[i][j]`.
- `e[i][j]` is the expected cost of the optimal tree on `ki..kj`.
- Empty subtrees (`j = i-1`) have only the dummy key: `e[i][i-1] = w[i][i-1] = q_{i-1}`.
- Try every key `r` in `i..j` as the root. Its left subtree is `ki..k(r-1)` and right subtree is `k(r+1)..kj`:

  `e[i][j] = min over r of ( e[i][r-1] + e[r+1][j] + w[i][j] )`

- `root[i][j]` stores the best `r`. The tree is rebuilt recursively using this table (`L` and `R` in the output mean left and right child; `d` entries are the dummy leaves).
- The table is filled by increasing range length (1 to n), so the smaller ranges are always ready when needed.
- The program checks that all probabilities add up to 1 before running.

**Input representation:** `p` and `q` as double arrays (p indexed 1..n, q indexed 0..n), and 2D tables `e`, `w` (doubles) and `root` (int) allocated with `malloc`.

## Complexity analysis

There are O(n^2) subproblems (pairs i <= j). For each one, we try up to j-i+1 roots, each in O(1) (w[i][j] is computed incrementally from w[i][j-1] in O(1)).

T(n) = sum over l = 1..n of (n - l + 1) * l = n(n+1)(n+2)/6 = O(n^3)

Space: three tables of size about n x n, so O(n^2).

Printing the tree is O(n).

## Sample input and output

**Option 1 (manual input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: Number of keys n (1 to 200): 5
Enter p1..p5 (search probabilities of keys): 0.15 0.10 0.05 0.10 0.20
Enter q0..q5 (probabilities of dummy keys): 0.05 0.10 0.05 0.05 0.05 0.10
Minimum expected search cost = 2.7500
Root of the optimal tree = k2
Tree structure:
*k2
    Lk1
        Ld0
        Rd1
    Rk5
        Lk4
            Lk3
                Ld2
                Rd3
            Rd4
        Rd5
```

**Option 2 (random input)**

```
Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated n = 6
p: 0.046 0.115 0.084 0.008 0.122 0.115
q: 0.069 0.115 0.084 0.107 0.061 0.061 0.015
Minimum expected search cost = 3.0229
Root of the optimal tree = k3
Tree structure:
*k3
    Lk2
        Lk1
            Ld0
            Rd1
        Rd2
    Rk5
        Lk4
            Ld3
            Rd4
        Rk6
            Ld5
            Rd6
```

(The random sample changes on every run.)
