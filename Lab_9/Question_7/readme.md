# Question 7

## Minimise Deviation in Array

Given an array of positive integers, you may multiply any odd element by $2$ or divide any even element by $2$, any number of times. The deviation is $\max(A)-\min(A)$. Minimise it.

## Files folder structure

```
Question_7/
├── q7.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q7.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Key observation
* An odd number can be doubled once, and then it behaves as an even number.
* An even number can only be halved until it becomes odd, so its largest reachable value is itself.

So after doubling every odd element once, **every element can only decrease**, and each element $x$ can take values $x,x/2,x/4,\dots$ down to its odd part.

### Algorithm
1. Double every odd element, so every element is at its largest possible value. Put all in a max-heap and keep $mn=\min$.
2. Record $best=\max-mn$.
3. Repeat: pop the maximum $t$. Update $best=\min(best,\,t-mn)$. If $t$ is odd, stop, because the maximum can no longer be reduced. Otherwise push $t/2$ and update $mn=\min(mn,t/2)$.

**Why it is optimal.** The only way to reduce the deviation is to lower the current maximum. Once the maximum is odd it cannot decrease, and any later state has deviation at least $\max-mn$ that we already recorded. Each state visited is the best one for its current minimum, so $best$ is optimal.

### Validation
For $n\le8$ the program enumerates every combination of reachable values for each element (odd: $\{x,2x\}$; even: the halving chain) and takes the smallest deviation.

### Complexity
Each element is halved at most $O(\log M)$ times, where $M$ is the largest value.
* Heap operations: $O(n\log M)$ pushes and pops, each $O(\log n)$.
* Total $O(n\log n\log M)$ time, $O(n)$ space.

## Sample output

Mode 2 (auto-generate), `n = 6`, `seed = 4`.

Typed input:

```
2
6 4
```

Output:

```
Array: 2 24 35 27 44 38
Initial deviation = 42
Minimum deviation = 33
Brute force       = 33 -> PASS
```
