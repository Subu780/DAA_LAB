# Question 2

## Huffman Coding (canonical codebook)

Given symbol frequencies, build a prefix-free binary code with minimum expected length and print the **canonical** Huffman codebook, in which codes are ordered by (length, symbol).

## Files folder structure

```
Question_2/
├── q2.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q2.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Algorithm
1. Put all symbols in a min-heap keyed by frequency. Ties are broken by creation order so the run is deterministic.
2. Repeat $n-1$ times: pop the two smallest nodes $x,y$ and push a new node of weight $f_x+f_y$.
3. Depth of each leaf in the final tree is its code length $\ell_i$. For $n=1$ the single symbol gets length $1$.

**Why greedy works.** Some optimal tree has the two least frequent symbols as sibling leaves at the deepest level. Merging them gives a subproblem on $n-1$ symbols with the same optimal structure, so the greedy choice is safe.

### Canonical codes
Sort symbols by $(\ell_i,\text{symbol})$. Then

$$c_1=0,\qquad c_{k}=(c_{k-1}+1)\ll(\ell_k-\ell_{k-1})$$

and the code of symbol $k$ is $c_k$ written with $\ell_k$ bits. This only needs the lengths, which is why canonical codes are cheap to transmit.

### Validation
* Cost $\sum f_i\ell_i$ is compared with an independent **two-queue** Huffman computation.
* Kraft equality $\sum_i 2^{-\ell_i}=1$ is checked, which holds for a full binary tree.
* All code pairs are checked to be prefix-free.

### Complexity
* Heap construction and $n-1$ merges: $O(n\log n)$.
* Depth computation: $O(n)$. Canonical sort: $O(n^2)$ insertion sort in the code, or $O(n\log n)$ with a better sort.
* Space: $O(n)$.

## Sample output

Mode 2 (auto-generate), `n = 6` symbols, `seed = 5`.

Typed input:

```
2
6 5
```

Output:

```
Canonical Huffman codebook:
 sym  freq  len  code
  e     27    2  00
  f     33    2  01
  a     26    3  100
  b     16    3  101
  c     11    3  110
  d     23    3  111
Total encoded length = 348 bits, average = 2.5588 bits/symbol
Validation: two-queue cost = 348, Kraft sum = 1: yes, prefix-free: yes -> PASS
```
