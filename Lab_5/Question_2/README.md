# Question 2

The objective is to find the $K$-th smallest element in a list of $N$ numbers without fully sorting the list, with options for manual input or random array generation.

## Folder Structure

*   **q2.c:** The C source code file containing the algorithm
*   **a.out:** The compiled executable output file
*   **README.md:** Detailed explanation and complexity analysis

## Explanation 

To find the $K$-th smallest element without sorting the entire array, this program uses a **divide and conquer algorithm**. 

Here is a step-by-step breakdown of what the code does:

1.  **Menu & Input Handling:** The program allows the user to choose between entering an array manually or generating one randomly. It asks for the size of the array ($N$) and the desired position ($K$).
2.  **Partitioning:** The core of the algorithm is the `partition` function. It selects the last element of the current array segment as a "pivot". It rearranges the array so that all elements smaller than or equal to the pivot are placed to its left, and all larger elements to its right. 
3.  **Recursive Selection (`findKthSmallest`):** Once partitioned, the pivot is in its final, sorted position. We check if this index matches $K-1$ (since arrays are 0-indexed):
    *   If it matches, we have found the $K$-th smallest element.
    *   If the target index is smaller, the element must be in the left sub-array. The algorithm recursively partitions only the left side.
    *   If the target index is larger, it recursively partitions only the right side.

By consistently discarding the irrelevant half of the array at each step, we avoid the $\mathcal{O}(N \log N)$ cost of a full sort.

## Complexity Analysis and Derivation

### 1. Time Complexity

#### Average Case: $\mathcal{O}(N)$
In the average scenario, the partition step divides the array into two roughly equal halves. Let $T(N)$ be the time taken to find the element in an array of size $N$. The partitioning step takes linear time, $cN$, where $c$ is a constant. Because we only make a recursive call on *one* half of the array, the recurrence relation is:

$$T(N) = T\left(\frac{N}{2}\right) + cN$$

By repeatedly expanding this relation (substitution method):

$$T(N) = cN + c\left(\frac{N}{2}\right) + c\left(\frac{N}{4}\right) + \dots + c\left(1\right)$$

$$T(N) = cN \left(1 + \frac{1}{2} + \frac{1}{4} + \dots \right)$$

The series inside the parentheses is an infinite geometric progression with a sum of 2. Therefore:

$$T(N) = cN(2) = 2cN$$

Since constants are dropped in Big-O notation, the average time complexity is tightly bounded by **$\mathcal{O}(N)$**.

#### Worst Case: $\mathcal{O}(N^2)$
The worst-case scenario occurs if the chosen pivot is consistently the maximum or minimum element in the current segment (e.g., if the array is already sorted in ascending or descending order). In this case, the partition only reduces the problem size by 1 element per recursive call. The recurrence relation becomes:

$$T(N) = T(N-1) + cN$$

Expanding this:

$$T(N) = cN + c(N-1) + c(N-2) + \dots + c(1)$$

$$T(N) = c \sum_{i=1}^{N} i = c \left( \frac{N(N+1)}{2} \right)$$

This yields a polynomial where the highest degree term is $N^2$, making the worst-case time complexity **$\mathcal{O}(N^2)$**.

### 2. Space Complexity

*   **Auxiliary Space:** $\mathcal{O}(1)$
    The algorithm performs all partitioning in-place by swapping elements within the original array. No additional arrays are created.
*   **Recursive Call Stack:** $\mathcal{O}(\log N)$ on average, and up to $\mathcal{O}(N)$ in the worst case, due to the space required by the recursive call stack.