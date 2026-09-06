# Question 1

## Problem
Given an array with $n$ unsorted integer elements, find the worst-case complexity of various 1D array operations and validate them through implementation.

## Folder Structure
```
Question_1/
├── q1.c
├── a.out
└── README.md
```

## Mathematical Explanation

### Operations and Their Complexities

**(i) Finding the maximum element**
- **Complexity:** $O(n)$
- Must scan all elements once to find maximum
- Cannot do better without additional structure

**(ii) Finding the first and second largest elements**
- **Complexity:** $O(n)$
- Single pass through array maintaining two variables
- Compare each element with current first and second

**(iii) Finding the mean**
- **Complexity:** $O(n)$
- Sum all elements: $\text{mean} = \frac{1}{n}\sum_{i=1}^{n} a_i$
- Single pass to compute sum

**(iv) Finding the median**
- **Complexity:** $O(n \log n)$
- Requires sorting the array first
- Median is middle element (or average of two middle elements)

**(v) Finding the standard deviation**
- **Complexity:** $O(n)$
- Standard deviation: $\sigma = \sqrt{\frac{1}{n}\sum_{i=1}^{n}(a_i - \mu)^2}$
- Two passes: one for mean, one for variance

**(vi) Finding the mode**
- **Complexity:** $O(n \log n)$
- Sort array, then count consecutive equal elements
- Can also use hash map for $O(n)$ average case

**(vii) Removing all duplicates**
- **Complexity:** $O(n \log n)$
- Sort first, then remove consecutive duplicates in $O(n)$
- Alternative: hash set for $O(n)$ average case

**(viii) Reversing the elements**
- **Complexity:** $O(n)$
- Swap elements from both ends moving towards center
- Requires $n/2$ swaps

**(ix) Partitioning with respect to pivot**
- **Complexity:** $O(n)$
- Single pass similar to quicksort partition
- Move elements less than pivot to left side
