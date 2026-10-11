# Question 3

## Minimum Refuelling Stops

A vehicle starts with fuel $F$ (so it can travel $F$ units) and must reach distance $D$. Station $i$ is at distance $d_i$ and gives $f_i$ fuel. Find the minimum number of refuelling stops, or $-1$ if the target cannot be reached.

## Files folder structure

```
Question_3/
├── q3.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q3.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Reverse (lazy) greedy
Do not decide at a station whether to refuel. Instead, **remember** every station you pass and refuel retroactively only when stuck.

1. Sort stations by distance.
2. Keep a max-heap of the fuel amounts of stations already passed. Let $cur$ be the farthest reachable point, initially $F$.
3. While $cur<D$:
   * push the fuel of every station with $d_i\le cur$;
   * if the heap is empty, the target is unreachable, so return $-1$;
   * otherwise pop the largest fuel $f$, set $cur\leftarrow cur+f$ and increase the stop count.

**Why it is optimal.** Each time the vehicle is stuck, one more stop is unavoidable. Using the passed station with the largest fuel extends the reach the most, and any other choice reaches no farther (exchange argument).

### Validation
An independent DP: let $dp[k]$ be the farthest distance reachable with exactly $k$ stops. Process stations in order and update

$$dp[k]=\max\bigl(dp[k],\,dp[k-1]+f_i\bigr)\quad\text{if } dp[k-1]\ge d_i$$

The answer is the smallest $k$ with $dp[k]\ge D$.

### Complexity
* Sorting: $O(n\log n)$. Each station is pushed and popped at most once: $O(n\log n)$.
* Total $O(n\log n)$ time, $O(n)$ space. (The validation DP is $O(n^2)$.)

## Sample output

Mode 2 (auto-generate), `n = 6` stations, `D = 40`, `seed = 1`.

Typed input:

```
2
6 40 1
```

Output:

```
Target D = 40, initial fuel F = 9
Stations (distance, fuel): (3,8) (14,11) (15,5) (25,3) (26,7) (28,2)

Minimum refuelling stops = 4
Validation (DP over stops) = 4 -> PASS
```
