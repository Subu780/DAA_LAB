# Question 1

This question solves the problem of sorting a given set of `n` pairs `(number, color)` by their color, while ensuring that the numbers within each color group remain strictly sorted. 

The colors are ordered as follows: **Red (R) -> Blue (B) -> Yellow (Y)**. The algorithm achieves this in **O(n)** time complexity.

---

## File Directory

```text
.
├── q1.c      # The main C source code file
├── a.out     # The compiled executable (generated after compiling)
└── README.md # The documentation file (this file)
```

---

## How the Program Works in Detail

The core challenge of this problem is to group the items by color in exactly **O(n) time** (which means we can only loop through the list a constant number of times) without ruining the fact that the numbers are already sorted. 

To do this, the algorithm uses a technique similar to **Bucket Sort**.

### 1. The Setup (Input)
The program takes an array of pairs. We assume the input is already sorted numerically, for example:
> `2(R) 5(B) 7(R) 8(Y) 12(B)`

### 2. Distributing into Buckets (O(n) time)
Instead of comparing elements against each other (which would take O(n log n) time), the program creates three temporary arrays (buckets): one for Red, one for Blue, and one for Yellow.

It loops through the original array exactly once from left to right. 
* If it sees a **Red** item, it goes into the Red bucket.
* If it sees a **Blue** item, it goes into the Blue bucket.
* If it sees a **Yellow** item, it goes into the Yellow bucket.

**Why does this keep the numbers sorted?** 
Because we process the original array strictly from left to right, smaller numbers are always put into the buckets *before* larger numbers. This natural preservation of order is called a **stable sort**.

### 3. Reassembly (O(n) time)
Once the items are distributed, the program simply copies the contents of the buckets back into the original array in the required order:
1. First, dump the **Red** bucket.
2. Second, dump the **Blue** bucket.
3. Third, dump the **Yellow** bucket.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time** | **O(n)** | We loop through the array once to distribute the items, and once to copy them back. |