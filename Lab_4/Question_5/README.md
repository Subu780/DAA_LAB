# Question 5

This project solves the problem of taking a list $I$ of $n$ intervals, specified as $(x_i, y_i)$ pairs, and returning a new list where all overlapping intervals have been merged. The algorithm achieves this in worst-case **$O(n \log n)$** time complexity.

---

## File Directory

```text
.
├── q2.c      # The main C source code file
├── a.out     # The compiled executable (generated after compiling)
└── README.md # The documentation file (this file)
```

---

## How the Program Works in Detail

The brute-force way to merge intervals would be to check every single interval against every other interval to see if they overlap, which would take $O(n^2)$ time. To meet the $O(n \log n)$ requirement, the algorithm relies on sorting the data first so that any overlapping intervals end up right next to each other.

### 1. The Setup (Input Representation)
The program defines a C `struct` called `Interval` to keep the start time ($x_i$) and end time ($y_i$) glued together as a single unit. It reads $n$ of these intervals into an array. For example:
> Initial array: $(1, 3), (2, 6), (8, 10), (7, 18)$

### 2. Sorting ($O(n \log n)$ time)
To make merging efficient, we first sort the entire array of intervals based strictly on their **start times** from smallest to largest. The program uses a custom implementation of **Merge Sort** to guarantee the $O(n \log n)$ worst-case time complexity. 

After sorting by start time, the example array becomes:
> Sorted array: $(1, 3), (2, 6), (7, 18), (8, 10)$

### 3. Merging Overlaps ($O(n)$ time)
Because the intervals are now sorted by when they start, we know that if an interval is going to overlap with the current one, it *must* be the very next one in the list. The program sweeps through the sorted array exactly once:

* It takes the first interval and places it into a `merged` array.
* For each subsequent interval, it checks for an overlap by comparing its start time to the **end time** of the last interval placed in the `merged` array.
* **If they overlap** (i.e., `arr[i].start <= merged[last].end`), the intervals touch or cross. The program then updates the end time of the merged interval to be the maximum of the two end times.
* **If they do not overlap**, the continuous block is broken. The program simply adds the current interval as a brand-new, separate entry in the `merged` array.

Because the program only walks through the array one time to perform these checks, this merging step takes linear $O(n)$ time.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time** | **$O(n \log n)$** | Sorting the array of structures takes $O(n \log n)$ time. The linear sweep to merge the intervals processes each item exactly once, taking $O(n)$ time. The overall worst-case time complexity is dominated by the sorting step, resulting in $O(n \log n)$. |