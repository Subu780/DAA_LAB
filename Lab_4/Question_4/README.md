# Question 4

This question solves the problem of finding the peak attendance time at a party, given the entry times ($a_i$) and exit times ($b_i$) of $n$ distinct persons. The algorithm analyzes this data to determine the time when the maximum number of people were simultaneously present, achieving an **$O(n \log n)$** time complexity.

---

## File Directory

```text
.
├── q4.c      # The main C source code file
├── a.out     # The compiled executable (generated after compiling)
└── README.md # The documentation file (this file)
```

---

## How the Program Works in Detail

To solve this in $O(n \log n)$ time, the algorithm uses a classic **Sweep-Line** (or Two-Pointer) technique. The key insight is that to find the maximum number of people in the room, we do not need to know *who* is arriving or leaving; we only need to know *when* a door opens and whether it let someone in or out.

### 1. Breaking the Connection (Input Representation)
Instead of keeping a person's arrival and departure times paired together in a structure, the program completely separates them:
* All arrival times ($a_i$) are put into one array: `arr_in`.
* All departure times ($b_i$) are put into a completely different array: `arr_out`.

### 2. Sorting the Timelines ($O(n \log n)$ time)
The program sorts `arr_in` and `arr_out` independently in ascending order using a custom **Merge Sort**. 
* `arr_in` becomes a chronological list of every time the door opened to let someone in.
* `arr_out` becomes a chronological list of every time the door opened to let someone out.

### 3. The Timeline Sweep ($O(n)$ time)
With both lists sorted chronologically, the program uses two pointers (`i` for arrivals, `j` for departures) to sweep through the events in the exact order they occurred in real time:
* It compares the next arrival time `arr_in[i]` with the next departure time `arr_out[j]`.
* **If the arrival time is smaller:** The next event in reality is someone walking in. The program increases the `current_guests` count by $1$. If this count is higher than our recorded `max_guests`, it saves the new max and records this arrival time as the `peak_hour`. The arrival pointer `i` moves forward.
* **If the departure time is smaller:** The next event is someone walking out. The program decreases the `current_guests` count by $1$. The departure pointer `j` moves forward.
*(Note: The problem guarantees all times are distinct, so we do not have to handle the scenario where arrival and departure times are exactly equal).*

The algorithm naturally terminates when all arrivals have been processed, as the peak attendance cannot increase once no more guests are entering.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time** | **$O(n \log n)$** | Separating the arrays takes $O(n)$. Sorting both arrays independently takes $O(n \log n)$ time. The two-pointer sweep processes each event at most once, taking linear $O(n)$ time. The overall worst-case time complexity is dominated by the sorting step, resulting in $O(n \log n)$. |