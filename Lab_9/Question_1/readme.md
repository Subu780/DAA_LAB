# Question 1

## Fractional Knapsack with Deterioration Rate

There are $n$ items with value $v_i$, weight $w_i$ and decay rate $\lambda_i>0$. An item consumed at time $t$ has effective density $\frac{v_i}{w_i}-\lambda_i t$. With capacity $W$, decide the consumption order and how much of each item to take so that the total value is maximised.

## Files folder structure

```
Question_1/
├── q1.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q1.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Model (stated assumptions)
The statement does not fix how time advances, so the program uses this model:

* Items are consumed one after another at a rate of **1 unit of weight per unit of time**, so time $t$ equals the weight consumed so far.
* A unit taken from item $i$ at time $t$ yields $d_i-\lambda_i t$, where $d_i=v_i/w_i$.
* Weights are integers (unit slots). Finer "fractions" are obtained by scaling the units.

### Step 1: greedy order (exchange argument)
Take two adjacent blocks, $a$ units of item $i$ and $b$ units of item $j$, starting at time $T$.

$$V_{i\to j}=a(d_i-\lambda_iT)+b\bigl(d_j-\lambda_j(T+a)\bigr)$$

$$V_{j\to i}=b(d_j-\lambda_jT)+a\bigl(d_i-\lambda_i(T+b)\bigr)$$

$$V_{i\to j}-V_{j\to i}=ab(\lambda_i-\lambda_j)$$

So item $i$ should come first exactly when $\lambda_i>\lambda_j$. **Every optimal schedule consumes the chosen items in decreasing order of $\lambda$**, independently of $v_i$ and $w_i$. Sorting by $\lambda$ is the greedy step.

### Step 2: how much of each item
Plain "pick the highest current density" is **not** optimal. Take item A with $d=10,\lambda=0,w=5$ and item B with $d=9,\lambda=5,w=5$, and $W=10$. Greedy-by-density takes A first (value $50$). Taking B first and then A gives more, because B decays quickly.

With the order fixed, let $T_i$ be the start time of item $i$ and $k_i\in[0,w_i]$ the amount taken. The value of item $i$ is

$$k_i d_i-\lambda_i\left(k_iT_i+\frac{k_i(k_i-1)}{2}\right)$$

Define $dp[i][T]$ as the best value using the first $i$ items (in $\lambda$-order) with exactly $T$ units consumed:

$$dp[i][T]=\max_{0\le k\le \min(w_i,T)}\Bigl(dp[i-1][T-k]+k d_i-\lambda_i\bigl(k(T-k)+\tfrac{k(k-1)}{2}\bigr)\Bigr)$$

The answer is $\max_{T\le W}dp[n][T]$. Back-pointers give the amounts and the schedule.

### Validation
For $n\le5$, $W\le8$ the program enumerates **every** assignment of the $W$ time slots (each slot gets an item or stays idle) and compares the best value with the DP result.

### Complexity
* Sorting by $\lambda$: $O(n\log n)$.
* DP: $O(nW)$ states with up to $w_i+1$ transitions each, so $O(nW\,w_{\max})$ time and $O(nW)$ space.

## Sample output

Mode 2 (auto-generate), `n = 5`, `W = 8`, `seed = 15`.

Typed input:

```
2
5 8 15
```

Output:

```
Items:
 id  value  weight  lambda  density
  1   48.0       3    1.00    16.00
  2   15.0       3    0.00     5.00
  3   34.0       2    1.00    17.00
  4   32.0       2    2.00    16.00
  5   39.0       3    2.50    13.00

Optimal schedule (decreasing lambda), time starts at 0:
  t= 0.. 2 : item 4, 2 unit(s)
  t= 2.. 5 : item 1, 3 unit(s)
  t= 5.. 7 : item 3, 2 unit(s)
  t= 7.. 8 : item 2, 1 unit(s)
Total weight consumed = 8 / 8
Maximum total value   = 97.000
Brute force optimum    = 97.000  -> PASS
```
