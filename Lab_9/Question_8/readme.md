# Question 8

## Minimum Number of Meeting Rooms

Given meeting intervals $[s_i,e_i)$, find the minimum number of rooms needed so that no two overlapping meetings share a room. A meeting that ends at time $t$ frees its room for one that starts at $t$.

## Files folder structure

```
Question_8/
├── q8.c
├── a.out
└── readme.md
```

Compile and run:

```bash
gcc -O2 -o a.out q8.c -lm
./a.out
```

On start the program asks whether you want to **enter the input manually** (`1`) or have the program **generate the input automatically** (`2`).

## Detailed explanation

### Algorithm
1. Sort meetings by start time.
2. Keep a min-heap of $(\text{end time},\text{room})$ for rooms currently in use.
3. For each meeting $[s,e)$: if the earliest-ending room has $\text{end}\le s$, reuse it (pop it). Otherwise open a new room. Push $(e,\text{room})$.

The number of rooms ever opened is the answer, and the program also prints the room assigned to each meeting.

**Why it is optimal.** A new room is opened only when **all** rooms in use are busy at time $s$, so at least (rooms opened) meetings overlap at time $s$. Hence the answer is at least the maximum overlap, and the greedy never uses more than that.

$$\text{rooms}=\max_t\;\bigl|\{i:\ s_i\le t<e_i\}\bigr|$$

### Validation
An $O(n^2)$ check counts, for each meeting start, how many meetings cover that moment and takes the maximum. It must equal the greedy result.

### Complexity
* Sorting: $O(n\log n)$. Heap operations: $O(n\log n)$.
* Total $O(n\log n)$ time, $O(n)$ space.

## Sample output

Mode 2 (auto-generate), `n = 8` meetings, `seed = 2`.

Typed input:

```
2
8 2
```

Output:

```
Meetings (half-open [start,end)) and assigned rooms:
  M1  [18,22) -> Room 2
  M2  [20,24) -> Room 1
  M3  [21,24) -> Room 3
  M4  [ 0, 2) -> Room 1
  M5  [ 1, 5) -> Room 2
  M6  [22,26) -> Room 2
  M7  [21,23) -> Room 4
  M8  [ 5, 7) -> Room 1
Minimum rooms required = 4
Validation (max overlap at any start) = 4 -> PASS
```
