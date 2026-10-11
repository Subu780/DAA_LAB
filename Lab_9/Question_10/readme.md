# Question 10

## Greedy Superstring Conjecture (open problem)

Given strings $s_1,\dots,s_n$, find the shortest string containing every $s_i$ as a substring. The greedy algorithm repeatedly merges the pair with the largest overlap. The question is how far greedy can be from the optimum.

## Files folder structure

```
Question_10/
├── q10.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q10.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### What the program does
1. **Preprocess:** remove duplicates and strings that are substrings of another string. They never change the answer.
2. **Greedy:** repeatedly pick the ordered pair $(a,b)$ with the largest overlap $\text{ov}(a,b)$ (longest suffix of $a$ equal to a prefix of $b$) and replace them by the merged string $a\cdot b[\text{ov}(a,b)\dots]$, until one string is left.
3. **Exact optimum (for comparison):** after preprocessing, an optimal superstring is a permutation of the strings with maximal consecutive overlaps. A bitmask DP finds it:

$$dp[S][\ell]=\max_{p\in S\setminus\{\ell\}}\Bigl(dp[S\setminus\{\ell\}][p]+\text{ov}(p,\ell)\Bigr)$$

   and $\text{OPT}=\sum_i|s_i|-\max_\ell dp[\text{all}][\ell]$.
4. Print $\text{greedy}/\text{OPT}$ and verify the greedy result contains every input string.

### Status of the conjecture
The classical conjecture says greedy returns a string of length at most $2\cdot\text{OPT}$. The lab handout states that a September 2026 arXiv paper, *Disproving the Greedy Superstring Conjecture*, gives instances with ratio at least $\frac{9k+2}{4k+4}$ for even $k\ge10$, approaching $9/4$. The handout also says this claim is **not officially validated yet**, and this readme has not independently checked it. The program above only measures the ratio on small random instances, where greedy is often optimal but sometimes slightly worse (as in the sample).

### Validation
* The greedy output must contain every input string (`PASS`/`FAIL`).
* The DP optimum is an independent exact answer, so the printed ratio is always $\ge1$.

### Complexity
Let $m\le n$ be the strings left after preprocessing and $L$ the maximum total length.
* Greedy: $m-1$ rounds, each scanning $O(m^2)$ pairs with $O(L)$-ish overlap tests (naive), so $O(m^3L^2)$ in the worst case with this simple implementation. With suffix-tree / Aho-Corasick techniques it can be done in $O(N\log N)$ for total input length $N$.
* Exact DP: $O(2^m m^2)$ time, $O(2^m m)$ space, so only for small $n$ (the program caps $n\le12$).

## Sample output

Mode 2 (auto-generate), `n = 6` strings of length `5` over an alphabet of size `2`, `seed = 15`. In this run greedy is **not** optimal.

Typed input:

```
2
6 5 2 15
```

Output:

```
Input strings: babba baaba baaaa bbbab babba babaa
After removing duplicates/substrings: 5 string(s)
Greedy merges:
  merge "bbbab" + "babba" (overlap 3) -> "bbbabba"
  merge "babaa" + "baaba" (overlap 3) -> "babaaba"
  merge "bbbabba" + "baaaa" (overlap 2) -> "bbbabbaaaa"
  merge "bbbabbaaaa" + "babaaba" (overlap 0) -> "bbbabbaaaababaaba"
Greedy superstring  : bbbabbaaaababaaba (length 17)
Contains every input string: PASS
Optimal length (DP)  : 15
Greedy / Optimal     : 1.1333
Greedy is optimal here: no
```
