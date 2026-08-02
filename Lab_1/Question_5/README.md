# Finding the Partition Point in a Binary Array

This repository contains a C program that efficiently finds the exact transition point (the index of the first `1`) in a sorted binary array containing a sequence of `0`s followed by a sequence of `1`s.

##  Folder Structure
* `q5.c`: The main C source code containing the logic for finding the partition point.
* `a.exe`: The compiled Windows executable file generated after compiling the code.
* `README.md`: This documentation file detailing the algorithm and implementation.

---

## The Algorithm: Binary Search (Upper Bound)

While a simple linear scan could find the transition point in $O(n)$ time, this program utilizes a highly optimized **Binary Search** approach. Because the array is strictly segregated (all `0`s come before all `1`s), the array is inherently sorted, making it a perfect candidate for binary search.

**How it works:**
1.  Initialize two pointers, `low` at the start of the array and `high` at the end.
2.  Calculate the `mid` index.
3.  **If `arr[mid] == 0`**: The transition point must be to the right. We update `low = mid + 1`.
4.  **If `arr[mid] == 1`**: We have found a `1`, meaning this *could* be the transition point. We record `ans = mid`. However, there might be an earlier `1` to the left, so we aggressively narrow our search space by setting `high = mid - 1`.
5.  Repeat until `low > high`. The variable `ans` will hold the exact index of the very first `1`.

### Complexity
*   **Time Complexity:** $O(\log n)$ — The search space is halved in every iteration.

---
##  Compilation & Execution

**1. Compile the code:**
```bash
gcc -o transition_find q5.c