# Question 6

This question solves the problem of finding a point $p$ on a line that is covered by the maximum number of intervals from a given set $S$ of $n$ intervals. The algorithm achieves this in **$O(n \log n)$** time complexity.

---

## File Directory

```text
.
├── q5.c      # The main C source code file
├── a.out     # The compiled executable (generated after compiling)
└── README.md # The documentation file (this file)
```

---

## How the Program Works in Detail

This problem is mathematically identical to finding the peak attendance at a party. An interval starting at $l_i$ is equivalent to a person arriving, and an interval ending at $r_i$ is equivalent to a person leaving. To achieve $O(n \log n)$ time, we use the **Sweep-Line (Two-Pointer)** algorithm.

### 1. Breaking the Connection (Input Representation)
Instead of processing the intervals as rigid $(l_i, r_i)$ pairs, the program splits them into two independent lists:
* All the left endpoints ($l_i$) are stored in a `starts` array.
* All the right endpoints ($r_i$) are stored in an `ends` array.

### 2. Sorting the Timelines ($O(n \log n)$ time)
The program sorts the `starts` array and the `ends` array independently in ascending order using a custom **Merge Sort**. 
* The `starts` array becomes a chronological list of every point where an interval opens.
* The `ends` array becomes a chronological list of every point where an interval closes.

### 3. The Timeline Sweep ($O(n)$ time)
With both lists sorted, the program uses two pointers (`i` for `starts`, `j` for `ends`) to sweep across the number line from left to right:
* It compares the next available start point `starts[i]` with the next available end point `ends[j]`.
* **If a start point comes first (or at the exact same time):** The program increments the `current_coverage` count by $1$. If this count exceeds the `max_coverage`, it updates the maximum and records the current start point as the `best_point`. The `starts` pointer `i` moves forward.
* **If an end point comes first:** The program decrements the `current_coverage` count by $1$, as an interval has fully closed. The `ends` pointer `j` moves forward.

### 4. Handling Inclusive Endpoints
The problem explicitly states: *"assume an endpoint counts as being in its interval."* 
This means if Interval A ends at $50$, and Interval B starts at $50$, they overlap exactly at $p = 50$. 

The algorithm perfectly handles this via the condition `if (starts[i] <= ends[j])`. The `<=` ensures that if a start and an end happen at the exact same coordinate, the algorithm processes the **start** first, temporarily increasing the overlap count before it processes the end. 

---

## Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time** | **$O(n \log n)$** | Separating the endpoints takes $O(n)$ time. Sorting both the `starts` and `ends` arrays independently takes $O(n \log n)$ time. The two-pointer sweep processes each endpoint at most once, taking linear $O(n)$ time. The overall worst-case time complexity is determined by the sorting step, resulting in $O(n \log n)$. |