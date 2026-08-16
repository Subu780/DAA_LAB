## Overview
This project implements a Divide and Conquer algorithm in C (q3.c) to find the maximum and minimum elements in an array of size n. The primary objective of this approach is to optimize the number of comparisons, ensuring they are strictly bounded by 3n/2, which is significantly more efficient than the standard linear scanning approach that requires 2n comparisons.

# Max and Min Finder (Divide & Conquer)

## File Directory
The directory is organized as follows:

```text
Question_3/
├── a.exe
├── q3.c
└── README.md
```

## How the Program Works
The program operates by recursively breaking down the array into smaller sub-arrays until it reaches easily solvable base cases. It utilizes pointers to track the minimum and maximum values without needing complex data structures or returning multiple variables.

### Program Flow
* **Initialization:** The user is prompted to either manually enter array elements or allow the program to generate a random array of size n. Memory is allocated on the heap (using malloc) to prevent stack overflow for large inputs.
* **Divide:** If the current array chunk has more than two elements, the algorithm calculates the midpoint and recursively splits the array into a left half and a right half.
* **Base Case (One Element):** The single element is immediately assigned as both the minimum and the maximum (0 comparisons).
* **Base Case (Two Elements):** The two elements are compared directly. The larger becomes the maximum, and the smaller becomes the minimum (1 comparison).
* **Conquer (Combine):** Once the recursive calls return, the algorithm compares the local minimums of the left and right halves to find the absolute minimum. It then compares the local maximums of the halves to find the absolute maximum (2 comparisons per merge step).

## Mathematical Derivation of the 3n/2 Bound
Let $T(n)$ represent the total number of comparisons required to find the maximum and minimum in an array of size $n$.

### The Recurrence Relation
When the array is split into two halves of size $n/2$, finding the min and max of each half takes $T(n/2)$ comparisons. Merging the results requires exactly 2 comparisons (one to compare the two minimums, and one to compare the two maximums). This gives the recurrence relation:

$$T(n) = 2T\left(\frac{n}{2}\right) + 2$$

The base condition for an array of 2 elements is:

$$T(2) = 1$$

### Solving via Substitution Method
Assuming $n$ is a power of 2 (i.e., $n = 2^k$), we can expand the recurrence relation to find the exact number of comparisons:

$$T(n) = 2T\left(\frac{n}{2}\right) + 2$$
$$T(n) = 2\left[2T\left(\frac{n}{4}\right) + 2\right] + 2 = 4T\left(\frac{n}{4}\right) + 4 + 2$$
$$T(n) = 4\left[2T\left(\frac{n}{8}\right) + 2\right] + 4 + 2 = 8T\left(\frac{n}{8}\right) + 8 + 4 + 2$$

Generalizing this pattern to $k-1$ steps, we get:

$$T(n) = 2^{k-1}T\left(\frac{n}{2^{k-1}}\right) + \sum_{i=1}^{k-1} 2^i$$

Since $\frac{n}{2^{k-1}} = \frac{2^k}{2^{k-1}} = 2$, we can substitute the base case $T(2) = 1$:

$$T(n) = 2^{k-1}(1) + (2^k - 2)$$

We know that $2^k = n$, which means $2^{k-1} = \frac{n}{2}$. Substituting $n$ back into the equation yields the final formula:

$$T(n) = \frac{n}{2} + n - 2$$
$$T(n) = \frac{3n}{2} - 2$$

Because $\frac{3n}{2} - 2$ is strictly less than $\frac{3n}{2}$, the maximum number of comparisons is mathematically proven to be bounded by 3n/2.

## Time Complexity Evaluation
While the algorithm heavily optimizes the raw comparison count, the overall Big-O time complexity remains O(n), not O(log n).

By applying the Master Theorem to the recurrence $T(n) = 2T(n/2) + 2$, we evaluate the variables $a=2, b=2,$ and $f(n)=2$. Calculating $n^{\log_b a}$ gives $n^{\log_2 2} = n^1$. Since $f(n)$ is a constant, $n^1$ is polynomially larger, meaning this falls into Case 1 of the Master Theorem.

The resulting time complexity is determined by the leaves of the recursion tree, equating to $O(n)$. This aligns with the logical constraint that finding the minimum and maximum requires evaluating every unsorted element at least once.