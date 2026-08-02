# Element Uniqueness Check

This repository contains a C program designed to determine if an array of random numbers contains any duplicate values, utilizing a frequency/hash array technique.

## Folder Structure
* `q6.c`: The main C source code containing the logic for the uniqueness check.
* `a.exe`: The compiled Windows executable file generated after compiling the code.
* `README.md`: This documentation file detailing the algorithm, complexity, and analysis.


## The Algorithm: Direct Access Hash Array

To find duplicates, this program uses a **Direct Access Hash Array** (often called a Frequency Array). 

**How it works:**
1.  We define a `MAX_VAL` constant (50000 in this code) which represents the maximum possible number in the array.
2.  We initialize an array named `hash` of size `MAX_VAL`, with all elements set to 0. 
3.  We iterate through our target array of random numbers. For each number (`key`), we use it directly as an index in our `hash` array and increment the value at that index (`hash[key]++`).
4.  If at any point `hash[key]` becomes strictly greater than 1, it means we have encountered that specific number before. We can immediately return `true` (duplicates found).
5.  If the loop finishes without triggering this condition, all numbers are unique.

### Complexity
*   **Time Complexity:** $O(n)$ — The algorithm passes through the array exactly once. The look-up time in the hash array is $O(1)$.
*   **Space Complexity:** $O(M)$ — Where $M$ is `MAX_VAL`. We require an auxiliary array of size equivalent to the maximum possible value generated.

## Conclusion: What happens for a "sufficiently large" $n$?

Based on the problem statement's query about large values of $n$, we can conclude two major limitations regarding this specific algorithm:

### 1. The Stack Overflow Problem (Memory Limitation)
In this C implementation, `int hash[MAX_VAL] = {0};` is allocated directly on the **Stack**. The stack usually has a strict size limit provided by the operating system (typically around 1 MB to 8 MB). 
If the range of random numbers becomes "sufficiently large" (for example, if `MAX_VAL` is increased to $10,000,000$ to accommodate a huge range of random numbers), this array would require roughly 40 MB of memory. Allocating this on the stack will instantly cause a **Stack Overflow (Segmentation Fault)**, crashing the program. 
*Conclusion:* While fast, this method scales terribly with memory. For massive ranges, one must either use dynamic heap allocation (`malloc`), switch to an $O(n \log n)$ sorting approach which requires $O(1)$ space, or use a dynamically resizing Hash Set.

### 2. The Pigeonhole Principle
If $n$ (the number of random elements generated) becomes larger than `MAX_VAL` (the maximum possible unique integer), we don't even need an algorithm to check for duplicates. By the mathematical **Pigeonhole Principle**, if you place $n$ items into $m$ containers where $n > m$, at least one container must contain more than one item. Therefore, for $n > 50000$, duplicates are logically guaranteed 100% of the time.

##  Compilation & Execution

**1. Compile the code:**
```bash
gcc -o duplicate_find q6.c