# Question 1

The objective is to find the median of a list of $N$ numbers without sorting the entire list, and to allow the user to either input the elements manually or generate them randomly.

## Folder Structure

*   **q1.c:** The C source code file containing the algorithm
*   **a.out:** The compiled executable output file
*   **README.md:** Detailed explanation and complexity analysis

## Explanation

To find the median without sorting the entire array, this program uses a **divide and conquer algorithm**. This approach shares its core logic with Quicksort but is highly optimized for finding the $K$-th smallest element (which is exactly what a median is).

Here is a step-by-step breakdown of what the code does:

1.  **Menu & Input Handling:** The program starts by asking the user to choose between entering an array manually or generating one using `rand()`. Memory for the array is allocated dynamically based on the size $N$ provided by the user.
2.  **Partitioning:** The core of the algorithm is the `partition` function. It selects the last element of the current array segment as a "pivot". It then rearranges the array so that all elements smaller than the pivot are placed to its left, and all larger elements to its right. 
3.  **Recursive Selection (`find`):** Once the array is partitioned, the pivot is placed in its final, sorted position. The algorithm checks this position:
    *   If the pivot's position matches the target index we are looking for, we have found our answer.
    *   If the target index is smaller, the algorithm recursively partitions only the left sub-array.
    *   If the target index is larger, it recursively partitions only the right sub-array.
4.  **Calculating the Median:** The `findMedian` function acts as a wrapper. 
    *   If $N$ is odd, the median is simply the element at position $N/2 + 1$.
    *   If $N$ is even, there are two middle elements. The algorithm finds both (at positions $N/2$ and $N/2 + 1$) and calculates their average.

By discarding the irrelevant half of the array at each step, this divide and conquer approach avoids the heavy lifting of a complete sort.

## Complexity Analysis and Derivation

### 1. Time Complexity

#### Average Case: $\mathcal{O}(N)$
In the average scenario, we assume the partition step divides the array into two roughly equal halves. Let $T(N)$ be the time taken to find the element in an array of size $N$. The partitioning step takes linear time, $cN$, where $c$ is a constant. Because we only make a recursive call on *one* half of the array, the recurrence relation is:

$$T(N) = T\left(\frac{N}{2}\right) + cN$$

By repeatedly expanding this relation (substitution method):

$$T(N) = cN + c\left(\frac{N}{2}\right) + c\left(\frac{N}{4}\right) + \dots + c\left(1\right)$$

$$T(N) = cN \left(1 + \frac{1}{2} + \frac{1}{4} + \dots \right)$$

The series inside the parentheses is an infinite geometric progression with a sum of 2. Therefore:

$$T(N) = cN(2) = 2cN$$

Since constants are dropped in Big-O notation, the average time complexity is bounded by **$\mathcal{O}(N)$**.

#### Worst Case: $\mathcal{O}(N^2)$
The worst-case scenario occurs if the chosen pivot is always the maximum or minimum element in the current segment (e.g., if the array is already sorted). In this case, the partition only reduces the problem size by 1 element per recursive call. The recurrence relation becomes:

$$T(N) = T(N-1) + cN$$

Expanding this:

$$T(N) = cN + c(N-1) + c(N-2) + \dots + c(1)$$

$$T(N) = c \sum_{i=1}^{N} i = c \left( \frac{N(N+1)}{2} \right)$$

This yields a polynomial where the highest degree term is $N^2$, meaning the worst-case time complexity is **$\mathcal{O}(N^2)$**.

### 2. Space Complexity

*   **Auxiliary Space:** $\mathcal{O}(1)$
    The algorithm performs all partitioning in-place by swapping elements within the original array. No additional data structures or arrays are created during the selection process.
*   **Recursive Call Stack:** $\mathcal{O}(\log N)$ on average, and up to $\mathcal{O}(N)$ in the worst case, due to the space required by the recursive call stack of the `find` function.