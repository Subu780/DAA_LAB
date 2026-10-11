# Question 4

## Minimum Cost to Connect Sticks

Sticks have lengths $L_1,\dots,L_n$. Joining sticks of lengths $x$ and $y$ costs $x+y$ and produces one stick of length $x+y$. Find the minimum total cost to join all sticks into one.

## Files folder structure

```
Question_4/
├── q4.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q4.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Algorithm
Always join the **two shortest** sticks.

1. Insert all lengths into a min-heap.
2. While more than one stick remains: pop $x\le y$, add $x+y$ to the cost and push $x+y$.

**Why it is optimal.** The process builds a binary tree whose leaves are the sticks. A stick at depth $\ell_i$ is counted $\ell_i$ times, so

$$\text{cost}=\sum_{i=1}^{n}L_i\,\ell_i$$

This is exactly the Huffman problem with $L_i$ as frequencies, so the greedy merge of the two smallest is optimal (the two smallest can be assumed to be deepest siblings).

### Validation
For $n\le8$ the program tries **every** pair at every step recursively and takes the cheapest total.

### Complexity
* Building the heap: $O(n)$. $n-1$ iterations with 2 pops and 1 push: $O(n\log n)$.
* Total $O(n\log n)$ time, $O(n)$ space. Costs use `long long`.

## Sample output

Mode 2 (auto-generate), `n = 6` sticks, `seed = 3`.

Typed input:

```
2
6 3
```

Output:

```
Sticks: 7 6 9 1 6 1
  step 1: join 1 + 1 -> 2 (cost so far 2)
  step 2: join 2 + 6 -> 8 (cost so far 10)
  step 3: join 6 + 7 -> 13 (cost so far 23)
  step 4: join 8 + 9 -> 17 (cost so far 40)
  step 5: join 13 + 17 -> 30 (cost so far 70)
Minimum total cost = 70
Brute force        = 70 -> PASS
```
