# Question 3

This question solves the generalized $k$-SUM problem. Given a set $S$ of $n$ integers and a target integer $T$, the algorithm tests whether exactly $k$ integers in the set add up to $T$. It achieves this in **$O(n^{k-1} \log n)$** time complexity.

---

## File Directory

```text
.
├── q3.c      # The main C source code file
├── a.out     # The compiled executable (generated after compiling)
└── README.md # The documentation file (this file)
```

---

## How the Program Works in Detail

To understand how this algorithm achieves the specific **$O(n^{k-1} \log n)$** time complexity, we have to look at how a standard brute-force approach works and how we can optimize its very last step.

If you were to write a brute-force solution, you would use $k$ nested loops to pick every possible combination of $k$ numbers. For example, if $k = 4$, you would have 4 loops inside each other. Checking every combination takes $O(n^k)$ time. Our goal is to eliminate that final, deepest loop and replace it with something much faster.

### 1. The Preparation: Sorting
Before doing any searching, the program sorts the entire array of integers in ascending order using a custom **Merge Sort** algorithm. 
* Sorting takes $O(n \log n)$ time.
* This is a mandatory setup step because the fast search technique we want to use at the very end (Binary Search) only works on strictly sorted data.

### 2. The Recursion: Picking $(k-1)$ Elements
Because $k$ is a variable provided by the user, we cannot hardcode a specific number of `for` loops. Instead, the program uses a recursive function called `kSumRecursive` to simulate nested loops dynamically. 

However, it does not pick all $k$ elements. It is strictly programmed to stop after picking **$k-1$** elements. Here is how the recursion manages this:
* **`depth` tracking:** The function keeps track of how many numbers it has picked. It starts at depth $0$ and stops when depth reaches $k-1$.
* **`start` index:** To ensure we don't use the same element twice, and to prevent checking the same combination backwards, every recursive call only looks at elements *after* the currently picked element.
* **`current_sum`:** As it picks numbers, it adds them up to maintain a running total of the chosen $k-1$ elements. Let's call this running total $S_{k-1}$.

Because we are picking $k-1$ items from an array of size $n$, this recursive picking process takes **$O(n^{k-1})$** time.

### 3. The Math and The Binary Search: Finding the $k$-th Element
When the recursion reaches depth $k-1$, we have picked a combination of numbers which gives us our sum $S_{k-1}$.

Mathematically, we know that for the full combination to succeed, the final $k$-th element (let's call it $x_k$) must satisfy:

$$ S_{k-1} + x_k = T $$

This means the exact number we are looking for in the remainder of the array is:

$$ x_k = T - S_{k-1} $$

Instead of looping through the rest of the array one-by-one to find $x_k$ (which would cost $O(n)$ time and bring our total time back up to $O(n^k)$), we use **Binary Search**.
* Binary Search looks for $x_k$ in the remaining portion of the sorted array.
* By repeatedly cutting the search area in half, Binary Search finds the number (or proves it does not exist) in just **$O(\log n)$** time.

If Binary Search finds the exact remainder, the program successfully returns the full $k$ elements. If it fails, the recursion backtracks, picks a different $k-1$ combination, and tries the Binary Search again.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time** | **$O(n^{k-1} \log n)$** | Generating all combinations of $k-1$ elements requires $O(n^{k-1})$ operations. For every single one of those combinations, we perform a Binary Search which takes $O(\log n)$ time. Multiplying these together gives the final worst-case time complexity of $O(n^{k-1} \log n)$. *(Note: The initial $O(n \log n)$ sorting step is absorbed by Big-O notation because it is strictly smaller than the final complexity).* |