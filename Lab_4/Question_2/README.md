# Question 2

This question solves the problem of finding whether there exists a pair of elements, one from set S1 and one from set S2, that add up to a target number `x`. The algorithm achieves this in **O(n log n)** time complexity.

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

The brute-force way to solve this would be to check every element in S1 against every element in S2, but that would take O(n^2) time. To meet the O(n log n) requirement, the algorithm relies on sorting and a two-pointer approach.

### 1. Sorting (O(n log n) time)
First, the program sorts both arrays (S1 and S2) in ascending order. It uses a custom implementation of **Merge Sort** to guarantee the O(n log n) worst-case time complexity.

### 2. Two-Pointer Search (O(n) time)
Once the arrays are sorted, the program uses two pointers to efficiently sweep through them and find the target sum:
* Pointer `i` starts at the **beginning** of S1 (the smallest element).
* Pointer `j` starts at the **end** of S2 (the largest element).

The program then enters a loop where it calculates the sum of the two elements `S1[i] + S2[j]`:
* **If the sum equals x:** A matching pair is found, and the program returns true.
* **If the sum is strictly less than x:** The current sum is too small. Because S1 is sorted, we can increase our sum by moving pointer `i` forward to the next larger element in S1.
* **If the sum is strictly greater than x:** The current sum is too large. Because S2 is sorted, we can decrease our sum by moving pointer `j` backward to the next smaller element in S2.

The search stops either when the pair is found, or when the pointers cross the boundaries of the arrays, meaning no such pair exists. Because the pointers only move in one direction, this search step takes linear time.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time** | **O(n log n)** | Sorting both arrays takes O(n log n) time. The two-pointer sweep processes the arrays at most once, taking O(n) time. The overall worst-case time complexity is dominated by the sorting step, resulting in O(n log n). |