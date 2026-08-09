# DAA Lab 2

This repository contains the complete implementation for **Lab 2**. All algorithms and benchmarking routines are implemented in **C** using `<time.h>` for precise CPU timing. The resulting performance metrics are exported to CSV files and visualized as order-of-growth curves using **Python** (`matplotlib`, `pandas`, `numpy`).

---

## Folder Structure

The repository is organized into dedicated subdirectories for each problem:

```text
Lab_2/
├── README.md
├── Question_1/
│   ├── a.out
│   ├── q1.c
│   ├── q1_plot.py
│   ├── q1_plot_results.png
│   ├── README.md
│   └── results.csv
├── Question_2/
│   ├── a.out
│   ├── q2.c
│   ├── q2_plot.py
│   ├── merge_sort_plot.png
│   ├── README.md
│   └── results.csv
└── Question_3/
    ├── a.out
    ├── q3.c
    ├── q3_plt.py
    ├── q3_merge_plot.png
    ├── README.md
    └── results.csv
```

---

## Prerequisites & Environment Setup

To run the benchmarking suites and generate visualization plots, ensure you have a standard **C compiler (`gcc`)** and **Python 3** with the required data science packages (`pandas`, `matplotlib`, `numpy`).

### Package Installation by Platform

#### 1. Linux (Ubuntu / Debian)
Install the build essentials and Python package manager:
```bash
sudo apt update
sudo apt install build-essential python3 python3-pip python3-venv -y
pip3 install pandas matplotlib numpy
```

#### 2. macOS
Using [Homebrew](https://brew.sh/):
```bash
brew install gcc python3
pip3 install pandas matplotlib numpy
```

#### 3. Windows
* Ensure **MinGW-w64** / **GCC** is installed and added to your system `PATH`.
* Install the Python packages via PowerShell or Command Prompt:
```bash
python -m pip install --upgrade pip
pip install pandas matplotlib numpy
```

---

## Lab Questions

### Question 1: Dictionary Operations Benchmark
**Problem Statement:**
Consider a dictionary ($D$) abstract data type that permits access to data items by content (key). The following are the primary operations that the dictionary supports:
* $\text{Search}(D, k)$: Given a search key $k$, return a pointer to the element in the dictionary $D$ whose key value is $k$, if one exists.
* $\text{Insert}(D, x)$: Given a data item $x$, add it to the dictionary $D$.
* $\text{Delete}(D, x)$: Given a pointer $x$ to a data item in the dictionary $D$, remove it from $D$.
* $\text{Max}(D)$ or $\text{Min}(D)$: Retrieve the item with the largest (or smallest) key from $D$.
* $\text{Predecessor}(D, x)$ or $\text{Successor}(D, x)$: Retrieve the item from $D$ whose key is immediately before (or after) the item $x$ in sorted order.

Evaluate and benchmark the asymptotic worst-case running times for all seven primary operations implemented across six data structures:
1. Unsorted Array
2. Sorted Array
3. Singly Linked Unsorted List
4. Singly Linked Sorted List
5. Doubly Linked Unsorted List
6. Doubly Linked Sorted List

---

### Question 2: Merge Sort vs. Modified (3-Way) Merge Sort
**Problem Statement:**
Consider the following modification to merge sort: divide the input array into thirds (rather than halves), recursively sort each third, and finally combine the results using a three-way merge subroutine.
* What is the worst-case running time of this modified merge sort?
* Validate your claim by benchmarking and plotting the order of growth for both the standard 2-way merge sort and the modified 3-way merge sort.

---

### Question 3: Merging $k$ Sorted Arrays
**Problem Statement:**
Suppose you are given $k$ sorted arrays, each with $n$ elements, and you want to combine them into a single sorted array of $kn$ elements.
* **Method 1 (Sequential Merge):** Use the merge subroutine repeatedly—merging the first two arrays, then merging the result with the third array, then with the fourth, and so on until the $k^{\text{th}}$ array. 
  * *Worst-Case Time Complexity:* $O(k^2 n)$
* **Method 2 (Divide & Conquer Merge):** Divide the $k$ arrays into $\frac{k}{2}$ pairs of arrays and use the merge subroutine to combine each pair, resulting in $\frac{k}{2}$ sorted arrays of length $2n$. Repeat this step until only one length-$kn$ sorted array remains.
  * *Worst-Case Time Complexity:* $O(kn \log k)$
* Validate and compare the performance of both methods empirically across various scaling parameters of $k$ and $n$.

---

## How to Run the Code

Navigate into any question directory and run the chained compile-execute-plot command:

```bash
# For Question 1
cd Question_1
gcc q1.c && ./a.out && python3 q1_plot.py

# For Question 2
cd ../Question_2
gcc q2.c && ./a.out && python3 q2_plot.py

# For Question 3
cd ../Question_3
gcc q3.c && ./a.out && python3 q3_plt.py
```