# Selection Sort Algorithm Analysis

## Directory Structure
The project files are organized within the directory as follows:

* **Question_6**
  * `a.exe`
  * `q6.c`
  * `README.md`

---

## Theoretical Analysis

### 1. Algorithm Pseudocode
The algorithm described is Selection Sort. Assuming an array `A` indexed from 1 to $n$:

```text
SELECTION-SORT(A)
1. n = length[A]
2. for i = 1 to n - 1
3.     min_index = i
4.     for j = i + 1 to n
5.         if A[j] < A[min_index]
6.             min_index = j
7.     swap A[i] with A[min_index]
```

### 2. Loop Invariant
To prove the algorithm's correctness, it maintains the following loop invariant:

> At the beginning of each loop $i$, it is guaranteed that $A[1 \dots i-1]$ is perfectly sorted, and every remaining element from $A[i]$ to $A[n]$ is greater than or equal to $A[i-1]$.

### 3. Why Run for Only $(n - 1)$ Elements?
The algorithm only needs to execute for the first $n - 1$ elements because once you have correctly identified and placed the $n - 1$ smallest elements into their final sorted positions, the only remaining element in the array must logically be the absolute maximum element. Since there is only one empty slot remaining at the very end of the array, this maximum element is naturally forced into its correct, final position. An array of size 1 is inherently sorted, making an $n$-th iteration entirely redundant.

### 4. Running Time Complexity
* **Worst-case running time:** $\Theta(n^2)$
  The outer loop runs $n - 1$ times, and the inner loop makes $n - i$ comparisons per iteration. Summing this arithmetic series results in a quadratic polynomial.
* **Is the best-case running time any better?** 
  No. Even if the array is already perfectly sorted, the algorithm has no mechanism to detect this. It must still blindly scan the entire unsorted right-side partition during every single iteration to confirm it has found the minimum element. Therefore, it makes the exact same number of comparisons, resulting in a best-case time complexity of $\Theta(n^2)$.

---

## Sample Program Output

```text
Enter 1 to input the array manually, or 2 to generate a random array: 2
Enter the number of elements: 100
Generating 100 random numbers...

Original Array:
428 820 803 78 961 96 989 859 984 621 629 851 503 347 555 808 823 478 670 330 754 765 67 840 369 283 819 14 577 707 304 968 519 536 256 118 306 59 30 272 224 433 85 332 419 827 38 925 557 903 76 430 386 767 974 704 182 505 53 297 447 407 190 830 611 272 970 881 733 167 460 278 404 498 419 651 548 110 865 278 545 456 899 580 913 343 698 742 370 537 584 254 572 107 471 260 208 781 879 218 

Sorted Array:
14 30 38 53 59 67 76 78 85 96 107 110 118 167 182 190 208 218 224 254 256 260 272 272 278 278 283 297 304 306 330 332 343 347 369 370 386 404 407 419 419 428 430 433 447 456 460 471 478 498 503 505 519 536 537 545 548 555 557 572 577 580 584 611 621 629 651 670 698 704 707 733 742 754 765 767 781 803 808 819 820 823 827 830 840 851 859 865 879 881 899 903 913 925 961 968 970 974 984 989 
```